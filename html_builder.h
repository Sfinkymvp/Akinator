#ifndef _HTML_BUILDER_H_
#define _HTML_BUILDER_H_


#include "data.h"


#define GENERATE_ERROR_MESSAGE(status, message) \
    ("[" #status "] " message)


void treeDump(BinaryTree* tree, TreeStatus status, const char* file, 
              const char* function, int line, const char* format, ...);


#endif // _HTML_BUILDER_H_
