#include <stdio.h>


#include "tree_test.h"
#include "tree.h"


TreeStatus treeTest()
{
    TREE_INIT(tree);
    TreeStatus status = treeConstructor(&tree);
    REPORT_IF_NOT_OK(status);

    status = akinatorStart(&tree);
    REPORT_IF_NOT_OK(status);
    
    treeDestructor(&tree);
    return TREE_OK;
}

