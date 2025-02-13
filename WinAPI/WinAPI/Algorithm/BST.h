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

	Node* Search(Node* node, int key);//key값을 가지는 노드 반환
	Node* Min(Node* node);//트리에서 가장 작은 값을 가지는 노드 반환
	Node* Max(Node* node);//트리에서 가장 큰 값을 가지는 노드 반환

	Node* Previous(Node* node);// node보다 한칸 작은 node
	Node* Next(Node* node);// node보다 한칸 큰 node

	void Replace(Node* node1, Node* node2);
	void Remove(Node* node);

	Node* root = nullptr;


private:
};