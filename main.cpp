#include <iostream>

#include "Tree.h"

int main()
{
	Tree<size_t> tree;

	tree.populateByVector({0, 1, 2, 3});

	std::cout << "Tree values: " << tree.toString() << std::endl;

	std::cout << "Swapping" << std::endl;
	tree.swapRandomNode();

	std::cout << "Tree values: " << tree.toString() << std::endl;

	tree.populateByVector({0, 1, 2, 3, 4, 5, 6, 7});

	std::cout << "Tree values: " << tree.toString() << std::endl;

	std::cout << "Swapping twice" << std::endl;
	tree.swapRandomNode();
	tree.swapRandomNode();

	std::cout << "Tree values: " << tree.toString() << std::endl;

	return 0;
}
