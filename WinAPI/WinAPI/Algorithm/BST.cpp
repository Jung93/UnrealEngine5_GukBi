#include "BST.h"

BinarySearchTree::BinarySearchTree()
{

}

BinarySearchTree::~BinarySearchTree()
{
	//TODO : 모든 노드 삭제

}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (root == nullptr)
	{
		root = newNode;
		return;
	}

	Node* node = root;
	Node* parent = nullptr;

	//자리 찾기
	while (true)
	{
		if (node == nullptr)
			break;

		parent = node;
		if (key < node->key)
		{
			node = node->leftChild;
		}
		else
		{
			node = node->rightChild;
		}

	}

	newNode->parent = parent;
	if (key < parent->key)
		parent->leftChild = newNode;
	else
		parent->rightChild = newNode;


}

void BinarySearchTree::PrintTree(Node* node)
{
	if (node == nullptr)
		return;

	//전위순회 : 부모 - 왼쪽자식들 - 오른쪽자식들
	//cout << node->key << endl;
	//PrintTree(node->leftChild);
	//PrintTree(node->rightChild);

	//중위순회 : 왼쪽자식들 - 부모 - 오른쪽자식들
	//PrintTree(node->leftChild);
	//cout << node->key << endl;
	//PrintTree(node->rightChild);

	//후위순회 : 왼쪽자식들 - 오른쪽자식들 - 부모
	PrintTree(node->leftChild);
	PrintTree(node->rightChild);
	cout << node->key << endl;


}

Node* BinarySearchTree::Search(Node* node, int key)
{
	Node* searchNode = node;

	while (true)
	{
		if (searchNode == nullptr)
			break;

		if (key == searchNode->key)
			break;

		if (key < searchNode->key)
			searchNode = searchNode->leftChild;
		else
			searchNode = searchNode->rightChild;
	}

	return searchNode;
}

Node* BinarySearchTree::Min(Node* node)
{
	Node* minNode = node;
	Node* parent = nullptr;
	while (true)
	{
		if (minNode == nullptr)
			break;

		parent = minNode;
		minNode = minNode->leftChild;
	}

	return parent;
}

Node* BinarySearchTree::Max(Node* node)
{
	Node* minNode = node;
	Node* parent = nullptr;
	while (true)
	{
		if (minNode == nullptr)
			break;

		parent = minNode;
		minNode = minNode->rightChild;
	}

	return parent;
}

Node* BinarySearchTree::Previous(Node* node)
{
	Node* previousNode = node->leftChild;

	if (previousNode != nullptr)
		previousNode = Max(previousNode);

	return previousNode;
}

Node* BinarySearchTree::Next(Node* node)
{
	Node* nextNode = node->rightChild;

	if (nextNode != nullptr)
		nextNode = Min(nextNode);

	return nextNode;
}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{




}

void BinarySearchTree::Remove(Node* node)
{
	Node* searchNode = node;

	while (true)
	{
		if (searchNode->rightChild == nullptr)
			break;

		cout << searchNode->key << endl;
		swap(searchNode, searchNode->rightChild);
	}


}
