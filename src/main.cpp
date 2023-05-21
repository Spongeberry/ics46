#include "bst.h"
#include "avltree.h"
#include <iostream>

int main()
{
    AVLTree tree;

    // Insert elements
    tree.insert("aa");
    tree.insert("bb");
    tree.insert("vv");
    tree.insert("cc");
    tree.insert("tt");

    // Print tree
    cout << "AVLTree after insertion:\n";
    BST::pre_order_print(cout, tree.root);

    // Remove an element
    //tree.remove("test");

    // Print tree after deletion
    cout << "\nAVLTree after removing 'test':\n";
    //tree.print(cout);

    //measure_BSTs("src/shortrandom.txt");
    //measure_BSTs("src/random.txt");
    //measure_BSTs("src/shortsorted.txt");
    //measure_BSTs("src/sorted.txt");
}
