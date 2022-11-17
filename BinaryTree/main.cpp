#include "BinaryTree.h"

int main()
{
	BinaryTree<int> tree = {22,55,11,88,99,66};
	tree.insert(120);
	tree.delete_node(55);
	std::cout << tree.find_max() << std::endl << std::endl;
	std::cout << tree.find_min() << std::endl << std::endl;
	std::cout << tree.find(22) << std::endl << std::endl;
	std::cout << tree.isEmpty() << std::endl << std::endl;
	BinaryTree<int> tree1;
	tree1 = std::move(tree);
	BinaryTree<int> tree2(tree1);
	BinaryTree<int> tree3(std::move(tree2));
	tree3 = tree1;
	tree3.inorder_print();
	


	return 0;
}