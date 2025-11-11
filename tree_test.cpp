#include <stdio.h>


#include "tree_test.h"
#include "tree.h"


void treeTest()
{
    TREE_INIT(tree);
    treeConstructor(&tree);

    akinatorStart(&tree);

    treeDestructor(&tree);
}

