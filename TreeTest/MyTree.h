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
	//ͨ����������������������������
	BinaryTreeNode * Construct(int* preorder, int* inorder, int lenght);

	void postOrder(BinaryTreeNode* rootTree);
	void preOrder(BinaryTreeNode* rootTree);
	void inOrder(BinaryTreeNode* rootTree);

	//�ǵݹ��������
	void PreOrderTraverse(BinaryTreeNode* rootTree);
	void InOrderTraverse(BinaryTreeNode* rootTree);
	void PostOrderTraverse(BinaryTreeNode* rootTree);

	//����ʵ�����Ĳ�α���
	void LevelOrderTraverse(BinaryTreeNode* rootTree);

	void destory(BinaryTreeNode* rootTree);
	int getDepth(BinaryTreeNode* rootTree);
private:
	BinaryTreeNode * ConstructCore(
		int* startPreorder, int* endPreorder,
		int* startInorder, int* endInorder
	);
};

