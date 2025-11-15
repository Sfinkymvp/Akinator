#include <stdio.h>
#include <assert.h>


#include "akinator_menu.h"
#include "tree.h"


UserChoice parseUserChoice()
{
    int choice = 0; 
    char chr = 0;
    
    printf("What do you want: [1]Guess, [2]Define object, [3]Compare objects,\n"
           "[4]Exit saving, [5]Exit without saving?\n");

    while (true) {
        if (scanf("%d%c", &choice, &chr) != 2 || chr != '\n') {
            printf("Akinator doesn't understand you\n"
                   "Try again [1/2/3/4/5]:\n");
            
            int c = 0; 
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            continue;
        }

        switch (choice) {
            case 1: return CHOICE_GUESS;
            case 2: return CHOICE_DEFINE;
            case 3: return CHOICE_COMPARE;
            case 4: return CHOICE_EXIT_SAVE;
            case 5: return CHOICE_EXIT_NO_SAVE;
            default: printf("Akinator doesn't understand you\n"
                            "Try again [1/2/3/4/5]:\n");
        }
    }
}


TreeStatus akinatorDefine(BinaryTree* tree)
{
    assert(tree);

    printf("What object do you want to define?\n"
           "Object: ");
    char object[BUFFER_SIZE] = {};
    TreeStatus status = readUserAnswer(object, BUFFER_SIZE);
    RETURN_IF_NOT_OK(status);

    status = defineNode(tree, object);
    if (status == TREE_NOT_FOUND) {
        printf("Akinator didn't find object '%s'\n", object);
        return TREE_OK;
    }

    return status;
}


TreeStatus akinatorCompare(BinaryTree* tree)
{
    assert(tree);

    char object_1[BUFFER_SIZE] = {};
    char object_2[BUFFER_SIZE] = {};

    printf("What objects do you want to compare?\n"
           "Object 1: ");
    TreeStatus status = readUserAnswer(object_1, BUFFER_SIZE);
    RETURN_IF_NOT_OK(status);

    printf("Object 2: ");
    status = readUserAnswer(object_2, BUFFER_SIZE);
    RETURN_IF_NOT_OK(status);

    status = compareNodes(tree, object_1, object_2);
    if (status == TREE_NOT_FOUND) {
        printf("akinator didn't find one of the objects\n");
        return TREE_OK;
    }

    return TREE_OK;
}


TreeStatus processUserChoice(BinaryTree* tree, UserChoice choice)
{
    assert(tree);

    switch (choice) {
        case CHOICE_GUESS:   return akinatorStart(tree);
        case CHOICE_DEFINE:  return akinatorDefine(tree);
        case CHOICE_COMPARE: return akinatorCompare(tree);
        case CHOICE_EXIT_SAVE:    return treeWriteToDisk(tree);
        case CHOICE_EXIT_NO_SAVE: return TREE_OK;
        default: printf("Invalid enum value '%d'\n", choice);
    }

    return TREE_INVALID_USER_CHOICE;
}
