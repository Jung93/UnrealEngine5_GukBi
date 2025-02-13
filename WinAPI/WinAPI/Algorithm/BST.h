#pragma once

#include <iostream>

using namespace std;

struct Node
{
	Node() {}
	Node(int key) { this->key = key; }
	~Node() {};

	int data = 0;
	int key = -1;

	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	Node* parent = nullptr;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	void Insert(int key);
	void PrintTree(Node* node);

	Node* Search(Node* node, int key);//key���� ������ ��� ��ȯ
	Node* Min(Node* node);//Ʈ������ ���� ���� ���� ������ ��� ��ȯ
	Node* Max(Node* node);//Ʈ������ ���� ū ���� ������ ��� ��ȯ

	Node* Previous(Node* node);// node���� ��ĭ ���� node
	Node* Next(Node* node);// node���� ��ĭ ū node

	void Replace(Node* node1, Node* node2);
	void Remove(Node* node);

	Node* root = nullptr;


private:
};