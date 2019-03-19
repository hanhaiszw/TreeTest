#include "stdafx.h"
#include "MyTree.h"
#include <exception>
#include <iostream>
#include <memory>
#include <stack>
#include <queue>
MyTree::MyTree()
{
}


MyTree::~MyTree()
{
}

BinaryTreeNode * MyTree::Construct(int * preorder, int * inorder, int length)
{
	if (preorder == nullptr || inorder == nullptr || length <= 0)
		return nullptr;
	return ConstructCore(preorder, preorder + length - 1,
		inorder, inorder + length - 1);
}

BinaryTreeNode * MyTree::ConstructCore(int * startPreorder, int * endPreorder, int * startInorder, int * endInorder)
{
	//前序遍历序列的第一个数字是根节点的值
	int rootValue = startPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();

	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;

	//递归结束条件，当只有一个节点
	//先序遍历序列一个节点
	if (startPreorder == endPreorder) {
		//中序排列一个节点 且 先序遍历的节点等于中序遍历的节点，则返回；否则出错。
		if (startInorder == endInorder
			&& *startPreorder == *startInorder)
			return root;
		else
			throw std::exception("Invalid input.");
	}

	//在中序遍历序列中找到根节点的值
	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;
	//没有找到
	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw std::exception("Invalid input.");

	int leftLength = rootInorder - startInorder;  //?两个地址相减？？？
	int* leftPreorderEnd = startPreorder + leftLength;

	if (leftLength > 0) {
		//构建左子树
		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}

	//还有右子树
	if (leftLength < endPreorder - startPreorder) {
		//构建右子树
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}


	return root;
}


//前序
void MyTree::preOrder(BinaryTreeNode * rootTree)
{
	if (rootTree != nullptr)
	{
		std::cout << rootTree->m_nValue << "    ";
		preOrder(rootTree->m_pLeft);
		preOrder(rootTree->m_pRight);
		
	}
}
//中序
void MyTree::inOrder(BinaryTreeNode * rootTree)
{	
	if (rootTree != nullptr)
	{
		inOrder(rootTree->m_pLeft);
		std::cout << rootTree->m_nValue <<"    ";
		inOrder(rootTree->m_pRight);
	}
}
//后序
void MyTree::postOrder(BinaryTreeNode* rootTree)
{
	if (rootTree != nullptr)
	{
		postOrder(rootTree->m_pLeft);
		postOrder(rootTree->m_pRight);
		std::cout << rootTree->m_nValue << "    ";
	}

}




//非递归先序遍历
void MyTree::PreOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "空树！" << std::endl;
		return;
	}
	BinaryTreeNode* pNode = rootTree;
	
	std::stack<BinaryTreeNode*> treeStatck;
	while (pNode||!treeStatck.empty())
	{
		while (pNode) {
			treeStatck.push(pNode);
			//访问
			std::cout << pNode->m_nValue << "    ";
			pNode = pNode->m_pLeft;
		}
		//出栈：需要判定出栈或标记
		pNode = treeStatck.top();
		treeStatck.pop();
		//访问右子树
		pNode = pNode->m_pRight;
	}
}

//非递归中序遍历
void MyTree::InOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "空树！" << std::endl;
		return;
	}
	BinaryTreeNode* pNode = rootTree;
	std::stack<BinaryTreeNode*> treeStack;
	while (pNode || !treeStack.empty()) {
		//向左走到尽头
		////先入栈：若T为空也即不能入栈时则执行下面的出栈操作
		while (pNode) {
			treeStack.push(pNode);
			pNode = pNode->m_pLeft;
		}
		//出栈：需判定出栈或标记
		pNode = treeStack.top();
		treeStack.pop();
		//访问
		std::cout << pNode->m_nValue << "    ";
		//起到链接作用
		pNode = pNode->m_pRight;
	}
}

//非递归后序遍历,用一个标记标记右子树是否访问过 
void MyTree::PostOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "空树!" << std::endl;
		return;
	}
	std::stack<BinaryTreeNode*> treeStack;
	BinaryTreeNode* pNode = rootTree;
	BinaryTreeNode* lastVisited = nullptr;   //记录上一次访问的节点

	while (pNode || !treeStack.empty()) {
		//走到最左
		while (pNode != nullptr) {
			treeStack.push(pNode);
			pNode = pNode->m_pLeft;
		}
		BinaryTreeNode* top = treeStack.top();
		if (top->m_pRight == nullptr || lastVisited == top->m_pRight) {
			treeStack.pop();
			//访问
			std::cout << top->m_nValue << "    ";

			lastVisited = top;
			//从这里结束一次循环时 pNode==nullptr的
		}
		else {
			pNode = top->m_pRight;
		}
	}	
}

/*
使用队列完成层次遍历
*/
void MyTree::LevelOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "空树!" << std::endl;
		return;
	}
	std::queue<BinaryTreeNode*> treeQueue;
	BinaryTreeNode* pNode = rootTree;
	BinaryTreeNode* temp;  
	treeQueue.push(pNode);
	while (!treeQueue.empty()) {
		temp = treeQueue.front(); //取队首的元素
		treeQueue.pop();  //出队
		//访问
		std::cout << temp->m_nValue << "    ";
		//左子树非空时入队 
		if (temp->m_pLeft != nullptr) {
			treeQueue.push(temp->m_pLeft);
		}
		//右子树非空时入队 
		if (temp->m_pRight != nullptr) {
			treeQueue.push(temp->m_pRight);
		}
	}
}

//释放树内存空间
void MyTree::destory(BinaryTreeNode * rootTree)
{
	if (rootTree != nullptr) {
		destory(rootTree->m_pLeft);
		destory(rootTree->m_pRight);
		delete rootTree;
		rootTree = nullptr;
	}
}

//获取树的高度
int MyTree::getDepth(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		return 0;
	}
	//求左子树的深度
	int nLeft = getDepth(rootTree->m_pLeft);
	//求右子树的深度
	int nRight = getDepth(rootTree->m_pRight);
	//比较左右子树，返回最大的
	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}
