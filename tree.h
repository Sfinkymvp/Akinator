#ifndef _TREE_H_
#define _TREE_H_


#include "data.h"


#ifdef DEBUG

#include "html_builder.h"


#define TREE_INIT(name)                          \
    BinaryTree name = {};                        \
    name.debug.creation = (TreeCreationInfo) {   \
        #name, __FILE__, __func__, __LINE__      \
    }


#define TREE_DUMP(tree, status, format, ...)     \
    treeDump(tree, status, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__)


#define TREE_VERIFY(tree, format, ...)                      \
    do {                                                    \
        TreeStatus status = treeVerify(tree);               \
        TREE_DUMP(tree, status, format, ##__VA_ARGS__);     \
        if (status != TREE_OK) {                            \
            return status;                                  \
        }                                                   \
    } while (0)

#endif // DEBUG


TreeStatus treeVerify(BinaryTree* tree);


TreeStatus akinatorStart(BinaryTree* tree);


TreeStatus treeConstructor(BinaryTree* tree);


void treeDestructor(BinaryTree* tree);


void printTree(Node* node);


#endif // _TREE_H_
