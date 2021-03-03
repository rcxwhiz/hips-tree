#include <iostream>

#include "Tree.h"

int main()
{
	/*
	 * Get an empty tree of whatever type
	 */
	auto tree = Tree<size_t>::getTree();
	std::cout << "Empty tree: " << tree->toString() << std::endl;

	/*
	 * Populate a tree using a vector
	 */
	tree->populateByVector({0, 1, 2, 3});
	std::cout << "Tree populated: " << tree->toString() << std::endl << std::endl;

	/*
	 * Get a tree with values filled in
	 */
	tree = Tree<size_t>::getTree({5, 6, 7, 8});
	std::cout << "New tree populated: " << tree->toString() << std::endl;

	/*
	 * Swap random node
	 */
	tree->swapRandomNode();
	std::cout << "Tree with node swapped: " << tree->toString() << std::endl << std::endl;

	/*
	 * Get a vector of pointers to leaves (can use to modify the value of a leaf in tree)
	 */
	tree->populateByVector({0, 1, 2, 3, 4, 5, 6, 7});
	auto leaves = tree->inOrderLeaves();
	std::cout << "Leaves: ";
	for (const auto& leaf : leaves)
		std::cout << leaf->getValue() << " ";
	std::cout << std::endl;

	/*
	 * Get a vector of leaf values (can not be used to modify value of a leaf in tree)
	 */
	auto leafValues = tree->inOrderValues();
	std::cout << "Leaves: ";
	for (const auto& value : leafValues)
		std::cout << value << " ";
	std::cout << std::endl;

	return 0;
}
