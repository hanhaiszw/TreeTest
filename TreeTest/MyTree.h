#pragma once
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};
class MyTree
{
public:

public:
	MyTree();
	~MyTree();
	//通过先序遍历和中序遍历构建二叉树
	BinaryTreeNode * Construct(int* preorder, int* inorder, int lenght);

	void postOrder(BinaryTreeNode* rootTree);
	void preOrder(BinaryTreeNode* rootTree);
	void inOrder(BinaryTreeNode* rootTree);

	//非递归遍历方法
	void PreOrderTraverse(BinaryTreeNode* rootTree);
	void InOrderTraverse(BinaryTreeNode* rootTree);
	void PostOrderTraverse(BinaryTreeNode* rootTree);

	//队列实现树的层次遍历
	void LevelOrderTraverse(BinaryTreeNode* rootTree);

	void destory(BinaryTreeNode* rootTree);
	int getDepth(BinaryTreeNode* rootTree);
private:
	BinaryTreeNode * ConstructCore(
		int* startPreorder, int* endPreorder,
		int* startInorder, int* endInorder
	);
};

