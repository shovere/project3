#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class AVLTree {
private:

	struct Node {
		T data;
		Node* left;
		Node* right;

		Node();
		Node(T& data);
		Node(T& data, Node* left, Node* right);
	};
	Node* root;
	bool(*comparison)(T, T);
	static bool cmp(T& first, T& second);

	Node* Search(Node* node, T& data);
	Node* RotateLeft(Node* node);
	Node* RotateRight(Node* node);
	Node* RotateLeftRight(Node* node);
	Node* RotateRightLeft(Node* node);
	int CheckBalanceFactor(Node* node);
	int CheckHeight(Node* node);
	Node* Balance(Node* node);
	Node* InsertNode(Node* node, T& data);
	void DeleteAllNodes(Node* node);
	void Traverse(Node* root); //In order traversal
	void CopyFromTree(Node* node);
	Node* FindParent(Node* node, Node* child);
	std::vector<T>& GetAscending(Node* node, std::vector<T>& vec, int num);
	std::vector<T>& GetDescending(Node* node, std::vector<T>& vec, int num);
	int size;

public:
	AVLTree();
	AVLTree(bool(*comparison)(T, T));
	AVLTree(AVLTree& other);
	AVLTree& operator=(AVLTree& other);
	~AVLTree();
	void Insert(T data);
	bool Delete(T data);
	T& Find(T& data);
	std::vector<T>& Ascend(std::vector<T>& vec, int num);
	std::vector<T>& Descend(std::vector<T>& vec, int num);
	int GetSize();
	void Clear();
	void Print();
};

//Default constructor Node
template <typename T>
AVLTree<T>::Node::Node() {
	data = nullptr;
	left = nullptr;
	right = nullptr;
}

//Modified constructor with data supplied
template <typename T>
AVLTree<T>::Node::Node(T& data) {
	this->data = data;
	left = nullptr;
	right = nullptr;
}

//Modified constructor with data and pointers defined
template <typename T>
AVLTree<T>::Node::Node(T& data, Node* left, Node* right) {
	this->data = data;
	this->left = left;
	this->right = right;
}

//Default constructor for AVLTree
template <typename T>
AVLTree<T>::AVLTree() {
	root = nullptr;
	comparison = AVLTree<T>::cmp;
	size = 0;
}

//Supply a comparator function to specify how data is sorted
template <typename T>
AVLTree<T>::AVLTree(bool(*comp)(T, T)) {
	root = nullptr;
	comparison = comp;
	size = 0;
}

//Copy constructor
template <typename T>
AVLTree<T>::AVLTree(AVLTree& other) {
	size = 0;
	comparison = other.comparison;
	CopyFromTree(other.root);
}

//Copy assignment operator
template <typename T>
typename AVLTree<T>::AVLTree& AVLTree<T>::operator=(AVLTree& other) {
	Clear();
	comparison = other.comparison;
	CopyFromTree(other.root);
	return *this;
}

//Destructor
template <typename T>
AVLTree<T>::~AVLTree() {
	Clear();
}

//Performs a left rotation at the given node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateLeft(Node* node) {
	Node* rightChild = node->right;
	node->right = rightChild->left;
	rightChild->left = node;
	return rightChild;
}

//Performs a right rotation at the given node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateRight(Node* node) {
	Node* leftChild = node->left;
	node->left = leftChild->right;
	leftChild->right = node;
	return leftChild;
}

//Performs a left-right rotation at the given node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateLeftRight(Node* node) {
	node->left = RotateLeft(node->left);
	return RotateRight(node);
}

//Performs a right-left rotation at the given node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::RotateRightLeft(Node* node) {
	node->right = RotateRight(node->right);
	return RotateLeft(node);
}

//Returns the height of the subtree at the given node
template <typename T>
int AVLTree<T>::CheckHeight(Node* node) {
	if (!node)
		return 0;
	return 1 + std::max(CheckHeight(node->left), CheckHeight(node->right));
}

//Returns the balance factor of the subtree at the given node
template <typename T>
int AVLTree<T>::CheckBalanceFactor(Node* node) {
	return CheckHeight(node->left) - CheckHeight(node->right);
}

//Checks the balance factor of the given node and performs rotations if necessary (Balance < -1 || Balance > 1)
/*
	Balance < -1 && Balance of Right Child == 1: right-left rotation
	Balance < -1 && Balance of Right Child == -1: left rotation
	Balance > 1 && Balance of Left Child == 1: right rotation
	Balance > 1 && Balance of Left Child == -1: left-right rotation
*/
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::Balance(Node* node) {
	if (!node)
		return nullptr;
	node->left = Balance(node->left);
	node->right = Balance(node->right);
	if (CheckBalanceFactor(node) < -1) {
		if (CheckBalanceFactor(node->right) == 1) {
			return RotateRightLeft(node);
		}
		else if (CheckBalanceFactor(node->right) == -1) {
			return RotateLeft(node);
		}
	}
	else if (CheckBalanceFactor(node) > 1) {
		if (CheckBalanceFactor(node->left) == 1) {
			return RotateRight(node);
		}
		else if (CheckBalanceFactor(node->left) == -1) {
			return RotateLeftRight(node);
		}
	}
	return node;
}

//Searches the tree for a node that contains the specified data based on tree comparitor function
//returns nullptr of no node is found
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::Search(Node* node, T& data) {
	if (!node)
		return node;
	if (comparison(data, node->data))
		node = Search(node->left, data);
	else if (comparison(node->data, data))
		node = Search(node->right, data);
	
	return node;
}

//Inserts a new node into the tree and rebalances if necessary
//If a node containing the specified data is already in the tree, nothing happens
template <typename T>
void AVLTree<T>::Insert(T data) {
	root = InsertNode(root, data);
	root = Balance(root);
}

//Helper function for Insert(T data)
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::InsertNode(Node* node, T& data) {

	if (!node) {

		node = new Node(data);
		size++;
		return node;
	}
	if (comparison(data, node->data)) {
		node->left = InsertNode(node->left, data);
	}
	else if (comparison(node->data, data)) {
		node->right = InsertNode(node->right, data);
	}
	return node;
}

//Finds the parent node of the specified node, or nullptr if its the root
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::FindParent(Node* node, Node* child) {
	Node* parent = nullptr;
	Node* nextNode = node;
	while (nextNode) {
		if (comparison(child->data, nextNode->data)) {
			parent = nextNode;
			nextNode = nextNode->left;
		}
		else if (comparison(nextNode->data, child->data)) {
			parent = nextNode;
			nextNode = nextNode->right;
		}
		else {
			return parent;
		}
	}
	return nullptr;
}

//Helper function to Clear()
//Deletes all nodes in the tree
template <typename T>
void AVLTree<T>::DeleteAllNodes(Node* node) {
	if (!node)
		return;
	DeleteAllNodes(node->left);
	DeleteAllNodes(node->right);
	delete node;
}

//Deletes a specified node from the tree, and rebalances if necessary
template <typename T>
bool AVLTree<T>::Delete(T data) {
	Node* node = Search(root, data);
	if (!node)
		return false;
	if (node->left && node->right) {
		Node* replacement = node->left;
		if (!replacement->right) {
			node->data = replacement->data;
			node->left = nullptr;
			delete replacement;
		}
		else {
			while (replacement->right) {
				if (!replacement->right->right)
					break;
				replacement = replacement->right;
			}
			node->data = replacement->right->data;
			delete replacement->right;
			replacement->right = nullptr;
		}

	}
	else if (node->left) {
		Node* parent = FindParent(root, node);
		if (!parent) {
			root = node->left;
			delete node;
		}
		else if (parent->left == node) {
			parent->left = node->left;
			delete node;
		}
		else {
			parent->right = node->left;
			delete node;
		}
	}
	else if (node->right) {
		Node* parent = FindParent(root, node);
		if (!parent) {
			root = node->right;
			delete node;
		}
		else if (parent->left == node) {
			parent->left = node->right;
			delete node;
		}
		else {
			parent->right = node->right;
			delete node;
		}
	}
	else {
		Node* parent = FindParent(root, node);
		if (!parent) {
			delete node;
			root = nullptr;
		}
		else if (parent->left == node)
			parent->left = nullptr;
		else
			parent->right = nullptr;
		delete node;
	}
	root = Balance(root);
	size--;
	return true;
}

//Searches the tree for a node that contains the specified data, and return a reference to it if found
//Returns a reference to the supplied data if not found in tree.
template <typename T>
T& AVLTree<T>::Find(T& data) {
	Node* temp = Search(root, data);
	if (temp)
		return Search(root, data)->data;
	else
		return data;
}

//Deletes all nodes from the tree and sets the root to nullptr
template <typename T>
void AVLTree<T>::Clear() {
	DeleteAllNodes(root);
	root = nullptr;
	size = 0;
}

//Performs in order traversal of the tree
//Prints out primative data types
template <typename T>
void AVLTree<T>::Print() {
	Traverse(root);
}

//In order tree traversal
template <typename T>
void AVLTree<T>::Traverse(Node* root) {
	if (!root)
		return;
	Traverse(root->left);
	std::cout << root->data << std::endl;
	Traverse(root->right);
}

//Inserts nodes from another tree into this tree
template <typename T>
void AVLTree<T>::CopyFromTree(Node* node) {
	if (!node)
		return;
	CopyFromTree(node->left);
	Insert(node->data);
	CopyFromTree(node->right);
}

//Helper function to Ascend()
//Returns a vector of T data in ascending order up to the specified number of elements
template <typename T>
std::vector<T>& AVLTree<T>::GetAscending(Node* node, std::vector<T>& vec, int num) {
	if (!node)
		return vec;
	if (vec.size() < num) {
		GetAscending(node->left, vec, num);
	}
	if (vec.size() < num) {
		vec.push_back(node->data);
	}
	if (vec.size() < num) {
		GetAscending(node->right, vec, num);
	}
	return vec;

}

//Helper function to Descend()
//Returns a vector of T data in descending order up to the specified number of elements
template <typename T>
std::vector<T>& AVLTree<T>::GetDescending(Node* node, std::vector<T>& vec, int num) {
	if (!node)
		return vec;
	if (vec.size() < num) {
		GetDescending(node->right, vec, num);
	}
	if (vec.size() < num) {
		vec.push_back(node->data);
	}
	if (vec.size() < num) {
		GetDescending(node->left, vec, num);
	}
	return vec;
}

//Returns a vector of T data in ascending order up to the specified number of elements
template <typename T>
std::vector<T>& AVLTree<T>::Ascend(std::vector<T>& vec, int num) {
	return GetAscending(root, vec, num);
}

//Returns a vector of T data in descending order up to the specified number of elements
template <typename T>
std::vector<T>& AVLTree<T>::Descend(std::vector<T>& vec, int num) {
	return GetDescending(root, vec, num);
}

//Default comparison function
template <typename T>
bool AVLTree<T>::cmp(T& first, T& second) {
	return first < second;
}

//Returns the size of the tree
template <typename T>
int AVLTree<T>::GetSize() {
	return size;
}


