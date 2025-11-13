#ifndef _TREE_IO_H_
#define _TREE_IO_H_


#include "data.h"


TreeStatus treeWriteToDisk(BinaryTree* tree);


TreeStatus treeLoadFromDisk(BinaryTree* tree);


TreeStatus readNode(BinaryTree* tree, Node** node, int* position);


#endif // _TREE_IO_H_
