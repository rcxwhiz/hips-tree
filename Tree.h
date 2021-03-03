#ifndef TREE_H
#define TREE_H

#include <iostream>

#include <stack>
#include <vector>

#include "Node.h"

bool isPowerOfTwo(int n)
{
	if (n == 0)
		return false;
	return (ceil(log2(n)) == floor(log2(n)));
}

template <typename T>
class Tree
{
public:
	Tree() = default;
	explicit Tree(std::vector<T> values)
	{
		populateByVector(values);
	}
	void populateByVector(std::vector<T> values)
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
	void populateToLevelValue(size_t level, T value)
	{
		resetTree();
		root = populateToLevelValueHelper(level, value);
		depth = level;
	}
	void populateToLevel(size_t level)
	{
		resetTree();
		root = populateToLevelHelper(level);
		depth = level;
	}
	void resetTree()
	{
		recursiveDelete(root);
		root = nullptr;
	}
	std::vector<T> inOrderValues()
	{
		std::vector<T> values;
		root->inOrderNodes(values);
		return values;
	}
	void swapRandomNode()
	{
		size_t level = rand() % (depth - 1);
		swapRandomNodeHelper(root, level);
	}

	~Tree()
	{
		recursiveDelete(root);
	}

	// FIXME this iterator just breaks the tree a bit
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

	TreeIterator getIterator()
	{
		return TreeIterator(root);
	}

private:
	void swapRandomNodeHelper(Node<T>* node, size_t level)
	{
		if (level == 0)
		{
			node->swapBranches();
		}
		else
		{
			if (rand() % 1)
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

	Node<T>* root = nullptr;
	size_t depth = 0;
};

#endif //TREE_H
