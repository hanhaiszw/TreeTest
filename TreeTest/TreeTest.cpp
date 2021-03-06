// TreeTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "MyTree.h"
#include <iostream>
int main()
{
	//int preorder[8] = { 1,2,4,7,3,5,6,8 };
	//int inorder[8] = { 4,7,2,1,5,3,8,6 };
	int preorder[9] = { 3,1,5,7,2,4,6,8,9 };
	int inorder[9] = { 7,2,5,1,4,3,8,6,9 };
	int nodeNum = sizeof(preorder) / sizeof(int);
	std::cout << "树的节点数" << nodeNum << std::endl;
	MyTree myTree;
	BinaryTreeNode* root = myTree.Construct(preorder, inorder, nodeNum);
	std::cout << "后序遍历" << std::endl;
	myTree.postOrder(root);
	std::cout << std::endl;
	std::cout << "先序遍历" << std::endl;
	myTree.preOrder(root);
	std::cout << std::endl;
	std::cout << "中序遍历" << std::endl;
	myTree.inOrder(root);
	std::cout << std::endl;

	std::cout << "非递归先序遍历" << std::endl;
	myTree.PreOrderTraverse(root);
	std::cout << std::endl;

	std::cout << "非递归中序遍历" << std::endl;
	myTree.InOrderTraverse(root);
	std::cout << std::endl;


	std::cout << "非递归后序遍历" << std::endl;
	myTree.PostOrderTraverse(root);
	std::cout << std::endl;

	std::cout << "层次遍历" << std::endl;
	myTree.LevelOrderTraverse(root);
	std::cout << std::endl;

	std::cout << "树的深度为" << myTree.getDepth(root) << std::endl;
	//销毁树
	myTree.destory(root);
	system("pause");
	return 0;
}

