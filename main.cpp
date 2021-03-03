#include <iostream>

#include "Tree.h"

void printTreeValues(Tree<size_t> tree)
{
	auto treeIt = tree.getIterator();
	std::cout << "Values: ";
	while (treeIt.hasNext())
		std::cout << treeIt.next()->getValue() << " ";
	std::cout << std::endl;
}

int main()
{
	Tree<size_t> tree;

	tree.populateByVector({0, 1, 2, 3});

	printTreeValues(tree);

	std::cout << "Swapping" << std::endl;
	tree.swapRandomNode();

	printTreeValues(tree);

	tree.populateByVector({0, 1, 2, 3, 4, 5, 6, 7});

	printTreeValues(tree);

	std::cout << "Swapping twice" << std::endl;
	tree.swapRandomNode();
	tree.swapRandomNode();

	printTreeValues(tree);

	return 0;
}
