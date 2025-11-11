#ifndef _DATA_H_
#define _DATA_H_


extern const char* UNKNOWN_STRING;
extern const char* error_messages[];


const int BUFFER_SIZE = 256;
extern const char* DUMP_DIRECTORY;


typedef enum {
    TREE_OK = 0,
    TREE_RESTART,
    TREE_ERR,
    TREE_NULL_DATA_POINTER,
    TREE_ROOT_HAS_PARENT,
    TREE_MISSING_PARENT,
    TREE_PARENT_CHILD_MISMATCH,
    TREE_INVALID_BRANCH_STRUCTURE,
    TREE_OUT_OF_MEMORY,
    TREE_INPUT_READ_ERROR,
    TREE_OUTPUT_FILE_OPEN_ERROR
} TreeStatus;


typedef struct Node Node;
struct Node {
    char* data;
    Node* left;
    Node* right;
#ifdef DEBUG
    Node* parent;
#endif // DEBUG
};


#ifdef DEBUG

typedef struct {
    TreeStatus status;
    const char* message;
    const char* file;
    const char* function;
    int line;
} DumpInfo;


typedef struct {
    const char* name;
    const char* file;
    const char* function;
    int line;
} TreeCreationInfo;


typedef struct {
    FILE* file;
    char directory[BUFFER_SIZE];
    int image_counter;
} TreeDumpState;


typedef struct {
    TreeCreationInfo creation;
    TreeDumpState dump;
} TreeDebugInfo;

#endif // DEBUG


typedef struct {
    Node* root;
#ifdef DEBUG
    TreeDebugInfo debug;
#endif // DEBUG
} BinaryTree;


#endif // _DATA_H_
