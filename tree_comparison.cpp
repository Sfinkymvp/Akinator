#include <stdio.h>
#include <assert.h>
#include <string.h>


#include "tree_comparison.h"
#include "tree.h"
#include "stack.h"


static TreeStatus findPathToNode(Node* node, Stack_t* stack, const char* data)
{
    assert(stack); assert(data);

    if (node == NULL)
        return TREE_NOT_FOUND;
    if (strcmp(node->data, data) == 0) {
            stackPush(stack, (PathStep){node, ANSWER_NONE});
        return TREE_OK;
    }

    TreeStatus status = findPathToNode(node->left, stack, data);
    if (status == TREE_OK) {
        stackPush(stack, (PathStep){node, ANSWER_YES});
        return TREE_OK;
    }
    
    status = findPathToNode(node->right, stack, data);
    if (status == TREE_OK) {
        stackPush(stack, (PathStep){node, ANSWER_NO});
        return TREE_OK;
    }

    return TREE_NOT_FOUND;
}


static void printGeneralProperties(Stack_t* object_path_1, Stack_t* object_path_2)
{
    assert(object_path_1); assert(object_path_2);
    assert(object_path_1->data); assert(object_path_2->data);

    PathStep step_1 = {};
    PathStep step_2 = {};
    stackPop(object_path_1, &step_1);
    stackPop(object_path_2, &step_2);

    while (step_1.node == step_2.node && step_1.answer == step_2.answer) {
        printf("%s\n", step_1.node->data);
        if (step_1.answer != ANSWER_NONE && step_2.answer != ANSWER_NONE) {
            stackPop(object_path_1, &step_1);
            stackPop(object_path_2, &step_2);
        } else
            break;
    }
}
static void printUniqueProperties(Stack_t* object_path)
{
    assert(object_path); assert(object_path->data);

    PathStep step = {};
    stackPop(object_path, &step);

    while (step.answer != ANSWER_NONE) {
        assert(step.answer != ANSWER_YES || step.answer != ANSWER_NO);
        if (step.answer == ANSWER_YES)
            printf("%s\n", step.node->data);
        else
            printf("not %s\n", step.node->data);

        stackPop(object_path, &step);
    }
}


static void printNodesComparision(Stack_t* object_path_1, Stack_t* object_path_2)
{
    assert(object_path_1); assert(object_path_2);
    assert(object_path_1->data); assert(object_path_2->data);

    printf("What both nodes have in common:\n");
    printGeneralProperties(object_path_1, object_path_2);

    printf("\nProperties of 1 node:\n");        
    printUniqueProperties(object_path_1);

    printf("\nProperties of 2 node:\n");
    printUniqueProperties(object_path_2);
}


TreeStatus compareNodes(BinaryTree* tree, const char* data_1, const char* data_2)
{
    assert(tree); assert(data_1); assert(data_2);

    Stack_t stack_1 = {};
    Stack_t stack_2 = {};
    stackCtor(&stack_1, START_CAPACITY);
    stackCtor(&stack_2, START_CAPACITY);

    if (findPathToNode(tree->root, &stack_1, data_1) == TREE_NOT_FOUND ||
        findPathToNode(tree->root, &stack_2, data_2) == TREE_NOT_FOUND) {
        stackDtor(&stack_1);
        stackDtor(&stack_2);
        return TREE_NOT_FOUND;
    }

    printf("Comparison of nodes '%s' and '%s'\n", data_1, data_2);
    printNodesComparision(&stack_1, &stack_2);

    stackDtor(&stack_1);
    stackDtor(&stack_2);
    return TREE_OK;
}


TreeStatus defineNode(BinaryTree* tree, const char* data)
{
    assert(tree); assert(data);

    Stack_t stack = {};
    stackCtor(&stack, START_CAPACITY);

    TreeStatus status = findPathToNode(tree->root, &stack, data);
    if (status != TREE_OK) {
        stackDtor(&stack);
        return status;
    }

    printf("Node '%s' definition:\n", data);
    printUniqueProperties(&stack);
    
    stackDtor(&stack);
    return TREE_OK;
}

