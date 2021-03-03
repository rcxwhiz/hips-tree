#ifndef NODE_H
#define NODE_H

#include <vector>

template <typename T>
class Node
{
public:
	T getValue()
	{
		return value;
	}
	void setValue(T v)
	{
		value = v;
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
	void inOrderNodes(std::vector<T>& values)
	{
		if (isLeaf())
		{
			values.push_back(value);
		}
		else
		{
			if (left != nullptr)
				left->inOrderNodes(values);
			if (right != nullptr)
				right->inOrderNodes(values);
		}
	}

private:
	Node* left = nullptr;
	Node* right = nullptr;
	T value = 0;
};

#endif //NODE_H
