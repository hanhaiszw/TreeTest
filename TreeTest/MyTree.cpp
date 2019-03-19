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
	//ǰ��������еĵ�һ�������Ǹ��ڵ��ֵ
	int rootValue = startPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();

	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = nullptr;

	//�ݹ������������ֻ��һ���ڵ�
	//�����������һ���ڵ�
	if (startPreorder == endPreorder) {
		//��������һ���ڵ� �� ��������Ľڵ������������Ľڵ㣬�򷵻أ��������
		if (startInorder == endInorder
			&& *startPreorder == *startInorder)
			return root;
		else
			throw std::exception("Invalid input.");
	}

	//����������������ҵ����ڵ��ֵ
	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;
	//û���ҵ�
	if (rootInorder == endInorder && *rootInorder != rootValue)
		throw std::exception("Invalid input.");

	int leftLength = rootInorder - startInorder;  //?������ַ���������
	int* leftPreorderEnd = startPreorder + leftLength;

	if (leftLength > 0) {
		//����������
		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}

	//����������
	if (leftLength < endPreorder - startPreorder) {
		//����������
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}


	return root;
}


//ǰ��
void MyTree::preOrder(BinaryTreeNode * rootTree)
{
	if (rootTree != nullptr)
	{
		std::cout << rootTree->m_nValue << "    ";
		preOrder(rootTree->m_pLeft);
		preOrder(rootTree->m_pRight);
		
	}
}
//����
void MyTree::inOrder(BinaryTreeNode * rootTree)
{	
	if (rootTree != nullptr)
	{
		inOrder(rootTree->m_pLeft);
		std::cout << rootTree->m_nValue <<"    ";
		inOrder(rootTree->m_pRight);
	}
}
//����
void MyTree::postOrder(BinaryTreeNode* rootTree)
{
	if (rootTree != nullptr)
	{
		postOrder(rootTree->m_pLeft);
		postOrder(rootTree->m_pRight);
		std::cout << rootTree->m_nValue << "    ";
	}

}




//�ǵݹ��������
void MyTree::PreOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "������" << std::endl;
		return;
	}
	BinaryTreeNode* pNode = rootTree;
	
	std::stack<BinaryTreeNode*> treeStatck;
	while (pNode||!treeStatck.empty())
	{
		while (pNode) {
			treeStatck.push(pNode);
			//����
			std::cout << pNode->m_nValue << "    ";
			pNode = pNode->m_pLeft;
		}
		//��ջ����Ҫ�ж���ջ����
		pNode = treeStatck.top();
		treeStatck.pop();
		//����������
		pNode = pNode->m_pRight;
	}
}

//�ǵݹ��������
void MyTree::InOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "������" << std::endl;
		return;
	}
	BinaryTreeNode* pNode = rootTree;
	std::stack<BinaryTreeNode*> treeStack;
	while (pNode || !treeStack.empty()) {
		//�����ߵ���ͷ
		////����ջ����TΪ��Ҳ��������ջʱ��ִ������ĳ�ջ����
		while (pNode) {
			treeStack.push(pNode);
			pNode = pNode->m_pLeft;
		}
		//��ջ�����ж���ջ����
		pNode = treeStack.top();
		treeStack.pop();
		//����
		std::cout << pNode->m_nValue << "    ";
		//����������
		pNode = pNode->m_pRight;
	}
}

//�ǵݹ�������,��һ����Ǳ���������Ƿ���ʹ� 
void MyTree::PostOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "����!" << std::endl;
		return;
	}
	std::stack<BinaryTreeNode*> treeStack;
	BinaryTreeNode* pNode = rootTree;
	BinaryTreeNode* lastVisited = nullptr;   //��¼��һ�η��ʵĽڵ�

	while (pNode || !treeStack.empty()) {
		//�ߵ�����
		while (pNode != nullptr) {
			treeStack.push(pNode);
			pNode = pNode->m_pLeft;
		}
		BinaryTreeNode* top = treeStack.top();
		if (top->m_pRight == nullptr || lastVisited == top->m_pRight) {
			treeStack.pop();
			//����
			std::cout << top->m_nValue << "    ";

			lastVisited = top;
			//���������һ��ѭ��ʱ pNode==nullptr��
		}
		else {
			pNode = top->m_pRight;
		}
	}	
}

/*
ʹ�ö�����ɲ�α���
*/
void MyTree::LevelOrderTraverse(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		std::cout << "����!" << std::endl;
		return;
	}
	std::queue<BinaryTreeNode*> treeQueue;
	BinaryTreeNode* pNode = rootTree;
	BinaryTreeNode* temp;  
	treeQueue.push(pNode);
	while (!treeQueue.empty()) {
		temp = treeQueue.front(); //ȡ���׵�Ԫ��
		treeQueue.pop();  //����
		//����
		std::cout << temp->m_nValue << "    ";
		//�������ǿ�ʱ��� 
		if (temp->m_pLeft != nullptr) {
			treeQueue.push(temp->m_pLeft);
		}
		//�������ǿ�ʱ��� 
		if (temp->m_pRight != nullptr) {
			treeQueue.push(temp->m_pRight);
		}
	}
}

//�ͷ����ڴ�ռ�
void MyTree::destory(BinaryTreeNode * rootTree)
{
	if (rootTree != nullptr) {
		destory(rootTree->m_pLeft);
		destory(rootTree->m_pRight);
		delete rootTree;
		rootTree = nullptr;
	}
}

//��ȡ���ĸ߶�
int MyTree::getDepth(BinaryTreeNode * rootTree)
{
	if (rootTree == nullptr) {
		return 0;
	}
	//�������������
	int nLeft = getDepth(rootTree->m_pLeft);
	//�������������
	int nRight = getDepth(rootTree->m_pRight);
	//�Ƚ�������������������
	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}
