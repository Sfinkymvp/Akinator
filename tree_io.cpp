#include <stdio.h>


#include "tree_io.h"
#include "data.h"
#include "tree.h"
#include "html_builder.h"


static void printTree(Node* node, FILE* output_file)
{
    assert(node);

    printf("(");

    if (node->left)
        printTree(node->left);
    fprintf(otput_file, "%s", node->data);
    if (node->right)
        printTree(node->right);
        
    printf(")");
}


TreeStatus treeWriteToDisk(BinaryTree* tree)
{
    TREE_VERIFY(tree, "Before write tree to disk");

    FILE* output_file = fopen("tree_out", "w");
    if (output_file == NULL)
        return TREE_OUTPUT_FILE_OPEN_ERROR;

    printTree(tree->root, output_file);

    if (fclose(output_file != 0))
        return TREE_OTPUT_FILE_OPEN_ERROR;

    return TREE_OK;
}
