#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


struct Node
{
	string data;

	vector<Node*> children;


};

Node* CreateTree()
{
	Node* root = new Node();
	root->data = "°³¹ßÆÀ";

	Node* programing = new Node();
	programing->data = "ÇÁ·Î±×·¡¹ÖÆÀ";
	root->children.push_back(programing);
	{
		Node* node1 = new Node();
		node1->data = "Å¬¶óÀÌ¾ðÆ®";
		programing->children.push_back(node1);

		Node* node2 = new Node();
		node2->data = "¼­¹ö";
		programing->children.push_back(node2);

		Node* node3 = new Node();
		node3->data = "¿£Áø";
		programing->children.push_back(node3);
	}

	Node* art = new Node();
	art->data = "¾ÆÆ®ÆÀ";
	root->children.push_back(art);
	{
		Node* node1 = new Node();
		node1->data = "¸ðµ¨¸µ";
		art->children.push_back(node1);

		Node* node2 = new Node();
		node2->data = "¹è°æ";
		art->children.push_back(node2);

		Node* node3 = new Node();
		node3->data = "¿øÈ­";
		art->children.push_back(node3);
	}

	Node* planning = new Node();
	planning->data = "±âÈ¹ÆÀ";
	root->children.push_back(planning);
	{
		Node* node1 = new Node();
		node1->data = "½ºÅä¸®";
		planning->children.push_back(node1);

		Node* node2 = new Node();
		node2->data = "ÄÁÅÙÃ÷";
		planning->children.push_back(node2);

		Node* node3 = new Node();
		node3->data = "·¹º§µðÀÚÀÎ";
		planning->children.push_back(node3);
	}

	return root;
}

void PrintTree(Node* node, int depth = 0)
{

	for (int i = 0; i < depth; i++)
		cout << "-";

	cout << node->data << endl;

	for (auto child : node->children)
	{
		PrintTree(child, depth + 1);
	}
}

int main()
{
	Node* root = CreateTree();

	PrintTree(root);


	return 0;

}