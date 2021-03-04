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
	std::cout << " === Populate Tree ===" << std::endl << std::endl;

	/*
	 * Get an empty tree of whatever type (this tree will automatically manage its memory)
	 */
	auto tree = HipsTree<size_t>::getTree();
	std::cout << "Empty tree: " << tree->toString() << std::endl;

	/*
	 * Populate a tree using a vector (will throw an error if length of vector is not power of 2)
	 */
	tree->populateByVector({0, 1, 2, 3});
	std::cout << "Tree populated: " << tree->toString() << std::endl;

	/*
	 * Get a tree with values already filled in (will also throw an error if length of vector is not power of 2)
	 */
	tree = HipsTree<size_t>::getTree({5, 6, 7, 8});
	std::cout << "New tree populated: " << tree->toString() << std::endl << std::endl;

	std::cout << " === Node swapping ===" << std::endl << std::endl;

	/*
	 * Swap random node at specific level starting from the root
	 */
	tree->swapRandomLevel(0);
	std::cout << "Tree with root node swapped: " << tree->toString() << std::endl;
	tree->swapRandomGrandchildrenLevel(0);
	std::cout << "Tree with grandchild swap at root: " << tree->toString() << std::endl;

	/*
	 * Swap random node at random level
	 */
	tree->swapRandom();
	std::cout << "Tree with a random node swapped: " << tree->toString() << std::endl << std::endl;

	std::cout << " === Accessing nodes/values ===" << std::endl << std::endl;

	/*
	 * Get a vector of pointers to leaves (can use to modify the value of a leaf in tree)
	 * If your nodes were holding an object instead of a primitive, you could call methods on that object to modify it
	 */
	tree->populateByVector({0, 1, 2, 3, 4, 5, 6, 7});

	// this is the vector
	auto leaves = tree->inOrderLeaves();
	std::cout << "Leaf nodes by vector: ";
	for (const auto& leaf : leaves)
		std::cout << leaf->getValue() << " ";
	std::cout << std::endl;

	// change a value of a node
	leaves.at(2)->setValue(400);
	// get values from tree to show a value in the tree changed
	leaves = tree->inOrderLeaves();
	std::cout << "Leaf nodes by vector after a value changed: ";
	for (const auto& leaf : leaves)
		std::cout << leaf->getValue() << " ";
	std::cout << std::endl;

	/*
	 * Get a vector of leaf values (can not be used to modify value of a leaf in tree)
	 */
	// this is the vector
	auto leafValues = tree->inOrderValues();
	std::cout << "Leaf values by vector: ";
	for (const auto& value : leafValues)
		std::cout << value << " ";
	std::cout << std::endl;

	/*
	 * Access leaves by iterator (can be used to modify value of a leaf - can only access one element at a time but uses
	 * less memory than getting the whole vector)
	 */
	auto treeIterator = tree->getIterator();
	std::cout << "Leaf nodes by iterator: ";
	while (treeIterator.hasNext())
		std::cout << treeIterator.next()->getValue() << " ";
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
	const bool printTree = true;
	const size_t numberOfSpacesToPrint = 32;

	std::vector<size_t> values;
	for (size_t i = 0; i < (size_t) pow(2, demoTreeSize); i++)
		values.push_back(i);
	tree->populateByVector(values);

	std::cout << "Initial tree with " << demoTreeSize << " levels and " << (size_t) pow(2, demoTreeSize) << " leaves:" << std::endl;
	if (printTree)
		printLargeTree(tree, numberOfSpacesToPrint);

	for (size_t i = 0; i < demoTreeSwaps; i++)
	{
		std::cout << "Grandchild swap " << i << "" << std::endl;
		tree->swapRandomGrandchildrenLevel(rand() % (tree->getDepth() - 2));
		if (printTree)
			printLargeTree(tree, numberOfSpacesToPrint);
	}

	return 0;
}
