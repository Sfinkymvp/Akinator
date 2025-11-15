#ifndef _AKINATOR_MENU_H_
#define _AKINATOR_MENU_H_


#include "data.h"


TreeStatus akinatorDefine(BinaryTree* tree);


TreeStatus akinatorCompare(BinaryTree* tree);


UserChoice parseUserChoice();


TreeStatus processUserChoice(BinaryTree* tree, UserChoice choice);


#endif // _AKINATOR_MENU_H_
