#ifndef SEARCHTREE
#define SEARCHTREE



struct Node
{
	Node(int key, int ind);
	Node();

	int lowerKey = -1;
	int greaterKey = -1;

	int lowerBinIndex = -1;
	int greaterBinIndex = -1;

	Node* parent = nullptr;

	Node* leftNode = nullptr;
	Node* midNode = nullptr;
	Node* rightNode = nullptr;

	Node* addElem(int key, int ind, int* pres);
	Node* searchAddableNode(int key);
	Node* keepBalance(Node* newData, int* pres);

	Node* searchElem(int key);
	void printTree(int lvl);
	Node* removeElem(int key);
	void lvlMerge(Node* brother);

};

#endif // !SEARCHTREE
