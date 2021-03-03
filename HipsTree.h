#ifndef HIPSTREE_H
#define HIPSTREE_H

#include <cmath>
#include <ctime>
#include <memory>
#include <sstream>
#include <stack>
#include <vector>

/*
 * Node class
 */
template <typename T>
class Node
{
public:
	T getValue()
	{
		// TODO might want to throw an exception if the value is null
		return *value;
	}
	void setValue(T v)
	{
		delete value;
		value = new T();
		*value = v;
	}
	Node* getLeft()
	{
		return left;
	}
	Node* getRight()
	{
		return right;
	}
	void setLeft(Node* node)
	{
		left = node;
	}
	void setRight(Node* node)
	{
		right = node;
	}
	bool isLeaf()
	{
		return (left == nullptr) && (right == nullptr);
	}
	void swapBranches()
	{
		std::swap(left, right);
	}
	void inOrderValues(std::vector<T>& values)
	{
		if (isLeaf())
		{
			values.push_back(*value);
		}
		else
		{
			if (left != nullptr)
				left->inOrderValues(values);
			if (right != nullptr)
				right->inOrderValues(values);
		}
	}
	void inOrderNodes(std::vector<Node<T>*>& nodes)
	{
		if (isLeaf())
		{
			nodes.push_back(this);
		}
		else
		{
			if (left != nullptr)
				left->inOrderNodes(nodes);
			if (right != nullptr)
				right->inOrderNodes(nodes);
		}
	}

private:
	Node* left = nullptr;
	Node* right = nullptr;
	T* value = nullptr;
};

/*
 * Tree class
 */
template <typename T>
class HipsTree
{
public:
	/*
	 * Gets a shared pointer to a blank tree
	 */
	static std::shared_ptr<HipsTree<T>> getTree()
	{
		srand(time(nullptr));
		return std::make_shared<HipsTree<T>>();
	}
	/*
	 * Gets a shared pointer to a tree populated with a vector of leaves
	 */
	static std::shared_ptr<HipsTree<T>> getTree(const std::vector<T>& values)
	{
		srand(time(nullptr));
		return std::make_shared<HipsTree<T>>(values);
	}
	/*
	 * Default constructor (tricky to use without accidentally calling deconstructor)
	 */
	HipsTree() = default;
	/*
	 * Constructor with values (tricky to use without accidentally calling deconstructor)
	 */
	explicit HipsTree(const std::vector<T>& values)
	{
		populateByVector(values);
	}
	/*
	 * Populates the tree with a vector of leaves - the vector should be a power of 2
	 */
	void populateByVector(const std::vector<T>& values)
	{
		if (!isPowerOfTwo(values.size()))
			throw std::runtime_error("Vector of values is not a power of 2 in size");
		populateToLevel(log2(values.size()) + 1);
		auto treeIt = TreeIterator(root);
		for (const auto& value : values)
		{
			treeIt.next()->setValue(value);
		}
	}
	/*
	 * Populates the tree to a given number of layers filling the leaves with a given value
	 */
	void populateToLevelValue(size_t level, T value)
	{
		resetTree();
		root = populateToLevelValueHelper(level, value);
		depth = level;
	}
	/*
	 * Creates a tree with uninitialized values to a given number of layers
	 */
	void populateToLevel(size_t level)
	{
		resetTree();
		root = populateToLevelHelper(level);
		depth = level;
	}
	/*
	 * Deletes all nodes and makes tree have size 0
	 */
	void resetTree()
	{
		recursiveDelete(root);
		root = nullptr;
		depth = 0;
	}
	/*
	 * Gets a vector of copies of the values of the leaves
	 */
	std::vector<T> inOrderValues()
	{
		std::vector<T> values;
		root->inOrderValues(values);
		return values;
	}
	/*
	 * Gets a vector of pointers to the leaves
	 */
	std::vector<Node<T>*> inOrderLeaves()
	{
		std::vector<Node<T>*> nodes;
		root->inOrderNodes(nodes);
		return nodes;
	}
	/*
	 * Chooses a random level and then random branches until it reaches that level, eventually switching the left and
	 * right children of a node
	 */
	void swapRandomNode()
	{
		size_t level = rand() % (depth - 1);
		swapRandomNodeHelper(root, level);
	}
	/*
	 * Uses random branches to reach a specified level then swaps those branches
	 */
	void swapRandomNodeLevel(size_t level)
	{
		swapRandomNodeHelper(root, level);
	}
	/*
	 * Returns the current depth of the tree in layers
	 */
	size_t getDepth()
	{
		return depth;
	}
	/*
	 * Deconstructor deletes nodes
	 */
	~HipsTree()
	{
		recursiveDelete(root);
	}

	/*
	 * Tree iterator class allows traversing the leaves of the tree
	 */
	class TreeIterator
	{
	public:
		explicit TreeIterator(Node<T>* root)
		{
			Node<T>* currentNode = root;
			while (currentNode != nullptr)
				nodes.push(currentNode), currentNode = currentNode->getLeft();
		}

		Node<T>* next()
		{
			if (nodes.empty())
				return nullptr;

			Node<T>* top = nodes.top();

			Node<T>* currentNode = nodes.top()->getRight();
			nodes.pop();
			while (currentNode != nullptr)
				nodes.push(currentNode), currentNode = currentNode->getLeft();

			if (top->isLeaf())
				return top;
			else
				return next();
		}

		bool hasNext()
		{
			return !nodes.empty();
		}

	private:
		std::stack<Node<T>*> nodes;
	};

	/*
	 * Returns an iterator that will start at the first leaf
	 */
	TreeIterator getIterator()
	{
		return TreeIterator(root);
	}
	/*
	 * Returns a string of the values of the leaves in order
	 */
	std::string toString(const std::string& sep=", ")
	{
		std::stringstream ss;
		auto it = getIterator();
		std::string se;
		while (it.hasNext())
		{
			ss << se << it.next()->getValue();
			se = sep;
		}
		return ss.str();
	}

private:
	/*
	 * Various helper functions and members
	 */

	void swapRandomNodeHelper(Node<T>* node, size_t level)
	{
		if (level == 0)
		{
			node->swapBranches();
		}
		else
		{
			if (rand() % 2)
				swapRandomNodeHelper(node->getLeft(), level - 1);
			else
				swapRandomNodeHelper(node->getRight(), level - 1);
		}
	}
	void recursiveDelete(Node<T>* node)
	{
		if (node != nullptr)
		{
			recursiveDelete(node->getLeft());
			recursiveDelete(node->getRight());
			delete node;
		}
	}
	Node<T>* populateToLevelValueHelper(size_t level, T value)
	{
		if (level > 0)
		{
			auto node = new Node<T>();
			if (level == 1)
				node->setValue(value);
			node->setLeft(populateToLevelValueHelper(level - 1, value));
			node->setRight(populateToLevelValueHelper(level - 1, value));
			return node;
		}
		return nullptr;
	}
	Node<T>* populateToLevelHelper(size_t level)
	{
		if (level > 0)
		{
			auto node = new Node<T>();
			node->setLeft(populateToLevelHelper(level - 1));
			node->setRight(populateToLevelHelper(level - 1));
			return node;
		}
		return nullptr;
	}
	bool isPowerOfTwo(int n)
	{
		if (n == 0)
			return false;
		return (ceil(log2(n)) == floor(log2(n)));
	}

	Node<T>* root = nullptr;
	size_t depth = 0;
};

#endif //HIPSTREE_H
