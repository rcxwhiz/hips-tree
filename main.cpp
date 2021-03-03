#include <iostream>

#include "HipsTree.h"

void printLargeTree(const std::shared_ptr<HipsTree<size_t>>& tree, size_t numPrint)
{
	auto it = tree->getIterator();
	for (size_t i = 0; i < numPrint; i++)
		std::cout << it.next()->getValue() << " ";
	std::cout << "... ";
	for (size_t i = 0; i < ((size_t) pow(2, (double) tree->getDepth() - 1) - 2 * numPrint); i++)
		it.next();
	for (size_t i = 0; i < numPrint; i++)
		std::cout << it.next()->getValue() << " ";
	std::cout << std::endl;
}

int main()
{
	/*
	 * Get an empty tree of whatever type (this tree will automatically manage its memory)
	 */
	auto tree = HipsTree<size_t>::getTree();
	std::cout << "Empty tree: " << tree->toString() << std::endl;

	/*
	 * Populate a tree using a vector
	 */
	tree->populateByVector({0, 1, 2, 3});
	std::cout << "Tree populated: " << tree->toString() << std::endl << std::endl;

	/*
	 * Get a tree with values filled in
	 */
	tree = HipsTree<size_t>::getTree({5, 6, 7, 8});
	std::cout << "New tree populated: " << tree->toString() << std::endl;

	/*
	 * Swap random node at specific level
	 */
	tree->swapRandomNodeLevel(0);
	std::cout << "Tree with root node swapped: " << tree->toString() << std::endl;

	/*
	 * Swap random node at random level
	 */
	tree->swapRandomNode();
	std::cout << "Tree with node swapped: " << tree->toString() << std::endl << std::endl;

	/*
	 * Get a vector of pointers to leaves (can use to modify the value of a leaf in tree)
	 * If your nodes were holding an object instead of a primitive, you could call methods on that object to modify it
	 */
	tree->populateByVector({0, 1, 2, 3, 4, 5, 6, 7});

	// this is the vector
	auto leaves = tree->inOrderLeaves();
	std::cout << "Leaf node values: ";
	for (const auto& leaf : leaves)
		std::cout << leaf->getValue() << " ";
	std::cout << std::endl;

	// change a value of a node
	leaves.at(2)->setValue(400);
	// get values from tree to show a value in the tree changed
	leaves = tree->inOrderLeaves();
	std::cout << "Leaf node values after one has been changed: ";
	for (const auto& leaf : leaves)
		std::cout << leaf->getValue() << " ";
	std::cout << std::endl;

	/*
	 * Get a vector of leaf values (can not be used to modify value of a leaf in tree)
	 */
	// this is the vector
	auto leafValues = tree->inOrderValues();
	std::cout << "Leaf values: ";
	for (const auto& value : leafValues)
		std::cout << value << " ";
	std::cout << std::endl << std::endl;

	/*
	 * Demo working at large size
	 */
	std::cout << " === Large Tree Demo ===" << std::endl << std::endl;

	// size of demo tree in layers
	// on my machine things start slowing down at 23-25 layers
	// 27 took ~9.6GB or RAM which was the most I could do before having issues running out
	// swaps are very fast no matter the size
	// getting the values of the leaves in order starts to slow down at large sizes
	const size_t demoTreeSize = 10;
	const size_t demoTreeSwaps = 10;
	const size_t numberOfSpacesToPrint = 20;
	const bool printTree = true;

	std::vector<size_t> values;
	for (size_t i = 0; i < (size_t) pow(2, demoTreeSize); i++)
		values.push_back(i);
	tree->populateByVector(values);

	std::cout << "Initial tree with " << demoTreeSize << " levels and " << (size_t) pow(2, demoTreeSize) << " leaves:" << std::endl;
	// impractical to print at large sizes (and toString could start to introduce performance issues)
	// std::cout << tree->toString() << std::endl;
	if (printTree)
		printLargeTree(tree, numberOfSpacesToPrint);

	for (size_t i = 0; i < demoTreeSwaps; i++)
	{
		std::cout << "Swap " << i << "" << std::endl;
		tree->swapRandomNode();
		if (printTree)
			printLargeTree(tree, numberOfSpacesToPrint);
	}

	return 0;
}
