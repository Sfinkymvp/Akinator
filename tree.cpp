#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "tree.h"
#include "data.h"


const char* UNKNOWN_STRING = "unknown";


static void openDumpFile(BinaryTree* tree)
{
    assert(tree);

    static int dump_counter = 1; 

    snprintf(tree->debug.dump.directory, BUFFER_SIZE, "%s/tree_dump_%03d",
             DUMP_DIRECTORY, dump_counter);

    char command[BUFFER_SIZE * 3] = {};
    snprintf(command, BUFFER_SIZE * 3, "rm -rf %s && mkdir -p %s",
             tree->debug.dump.directory, tree->debug.dump.directory);
    system(command);

    char filename[BUFFER_SIZE * 2] = {};
    snprintf(filename, BUFFER_SIZE * 2, "%s/tree_dump_%03d.html",
             tree->debug.dump.directory, dump_counter);

    tree->debug.dump.file = fopen(filename, "w");
    assert(tree->debug.dump.file);

    dump_counter++;
}


static TreeStatus nodeVerify(Node* node)
{
    assert(node);

    if (node->data == NULL)
        return TREE_NULL_DATA_POINTER;
    if (node->parent == NULL)
        return TREE_MISSING_PARENT;
    if (node->parent->left != node && node->parent->right != node)
        return TREE_PARENT_CHILD_MISMATCH;

    TreeStatus status = TREE_OK;
    if (node->left == NULL && node->right == NULL) {
        return TREE_OK;
    } else if (node->left != NULL && node->right != NULL) {
        status = nodeVerify(node->left);
        if (status != TREE_OK)
            return status;
        status = nodeVerify(node->right);
        if (status != TREE_OK)
            return status;
        return TREE_OK;
    }
    
    return TREE_INVALID_BRANCH_STRUCTURE;
}


TreeStatus treeVerify(BinaryTree* tree)
{
    assert(tree);
    assert(tree->root);

    TreeStatus status = TREE_OK;
    if (tree->root->parent != NULL)
        return TREE_ROOT_HAS_PARENT;
    if (tree->root->data == NULL)
        return TREE_NULL_DATA_POINTER;
    if (tree->root->left) {
        status = nodeVerify(tree->root->left);
        if (status != TREE_OK)
            return status;
    }
    if (tree->root->right) {
        status = nodeVerify(tree->root->right);
        if (status != TREE_OK)
            return status;
    }

    return TREE_OK;
}


static TreeStatus akinatorAddElement(Node* node, char* new_data, char* different)
{
    assert(node); assert(new_data); assert(different);

    node->left = (Node*)calloc(1, sizeof(Node));
    if (node->left == NULL)
        return TREE_OUT_OF_MEMORY;
    node->left->data = strdup(new_data);
    if (node->left->data == NULL)
        return TREE_OUT_OF_MEMORY;
 
    node->right = (Node*)calloc(1, sizeof(Node));
    if (node->right == NULL)
        return TREE_OUT_OF_MEMORY;
    node->right->data = node->data;

    node->data = strdup(different);
    if (node->data == NULL)
        return TREE_OUT_OF_MEMORY;

#ifdef DEBUG
    node->left->parent = node;
    node->right->parent = node;
#endif // DEBUG

    return TREE_OK;
}


static TreeStatus readUserAnswer(char* buffer, int size)
{
    assert(buffer);

    if (fgets(buffer, size, stdin) == NULL)
        return TREE_INPUT_READ_ERROR;
    buffer[strcspn(buffer, "\n")] = '\0';

    return TREE_OK;
}


static TreeStatus processWrongGuess(Node* node)
{
    char answer_buffer[BUFFER_SIZE] = {};
    char difference_buffer[BUFFER_SIZE] = {};

    printf("What is it?\n");
    TreeStatus status = readUserAnswer(answer_buffer, BUFFER_SIZE);
    RETURN_IF_NOT_OK(status);

    if (strcmp(node->data, UNKNOWN_STRING) == 0) {
        free(node->data);
        node->data = strdup(answer_buffer);
        if (node->data == NULL)
            return TREE_OUT_OF_MEMORY;

        return TREE_RESTART;
    }        

    printf("How is %s different from %s\n", answer_buffer, node->data);
    status = readUserAnswer(difference_buffer, BUFFER_SIZE);
    RETURN_IF_NOT_OK(status);

    status = akinatorAddElement(node, answer_buffer, difference_buffer);
    RETURN_IF_NOT_OK(status);
    
    return TREE_RESTART;    
}


static TreeStatus akinatorGuessing(Node* node)
{
    assert(node); assert(node->data);

    char answer_buffer[BUFFER_SIZE] = {};

    printf("Is this %s?\n", node->data);
    TreeStatus status = readUserAnswer(answer_buffer, BUFFER_SIZE);
    RETURN_IF_NOT_OK(status);
    
    if (strcmp(answer_buffer, "yes") == 0) {
        if (node->left == NULL)
            return TREE_OK;
        else
            return akinatorGuessing(node->left);
    } else {
        if (node->right == NULL)
            return processWrongGuess(node);
        else
            return akinatorGuessing(node->right);
    }
}


static void deleteBranch(Node* node)
{
    assert(node); assert(node->data);

    if (node->left) {
        deleteBranch(node->left);
        node->left = NULL;
    }
    if (node->right) {
        deleteBranch(node->right);
        node->right = NULL;
    }
    free(node->data);
    free(node);
}


TreeStatus akinatorStart(BinaryTree* tree)
{
    assert(tree);

    if (tree->root == NULL) {
        tree->root = (Node*)calloc(1, sizeof(Node));
        if (tree->root == NULL)
            return TREE_OUT_OF_MEMORY;
        
        tree->root->parent = NULL;   
        tree->root->data = strdup(UNKNOWN_STRING);
        if (tree->root->data == NULL)
            return TREE_OUT_OF_MEMORY;
    }

    TREE_VERIFY(tree, "Before launching akinatorGuessing");

    TreeStatus status = akinatorGuessing(tree->root);
    if (status == TREE_RESTART)
        return akinatorStart(tree);
    else
        return status;
}


TreeStatus treeConstructor(BinaryTree* tree)
{
    assert(tree != NULL);

    tree->root = NULL;
#ifdef DEBUG
    tree->debug.dump.image_counter = 1;
    openDumpFile(tree);
#endif // DEBUG

    return TREE_OK;
}


void treeDestructor(BinaryTree* tree)
{
    assert(tree);
    
    if (tree->root == NULL)
        return;

    deleteBranch(tree->root);
    tree->root = NULL;
}


