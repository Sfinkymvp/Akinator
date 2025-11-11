#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "graph_generator.h"
#include "data.h"


static void generateNode(Node* node, FILE* graph_file, int rank, int* counter)
{
    assert(node); assert(graph_file); assert(counter);
   
    int id = ++(*counter); 

    fprintf(graph_file, "\tnode_%d [shape=Mrecord, fontname=\"Monospace\", ", id);
                          
    if (id == 1) fprintf(graph_file, "fillcolor=\"#00FF00\", color=\"#009100\", ");
    else         fprintf(graph_file, "fillcolor=\"#ACE6AC\", color=\"#608F60\", ");

    fprintf(graph_file, "penwidth=2.0, style=filled, label="
                         "\"{<pointer>%p | %s | {<left>",
                        node, node->data);

    if (node->left)  fprintf(graph_file, "%p", node->left);
    else             fprintf(graph_file, "NULL");

    fprintf(graph_file, " | <right>");

    if (node->right) fprintf(graph_file, "%p", node->right);
    else             fprintf(graph_file, "NULL");

    fprintf(graph_file, "}}\"];\n");

    if (node->left) {
        fprintf(graph_file, "\tnode_%d:left -> node_%d:pointer [rank=%d];\n", 
                id, *counter + 1, rank);
        generateNode(node->left, graph_file, rank + 1, counter);
    }

    if (node->right) {
        fprintf(graph_file, "\tnode_%d:right -> node_%d:pointer [rank=%d];\n", 
                id, *counter + 1, rank);
        generateNode(node->right, graph_file, rank + 1, counter);
    }

}


void generateGraph(BinaryTree* tree, const char* graph_filename)
{
    assert(tree); assert(tree->root); assert(graph_filename);

    FILE* graph_file = fopen(graph_filename, "w");
    assert(graph_file);

    fprintf(graph_file, "digraph Tree {\n");
    fprintf(graph_file, "\trankdir=TB\n");
    fprintf(graph_file, "\tgraph[splines=curved];\n");

    int counter = 0;
    int rank = 0;
    generateNode(tree->root, graph_file, rank, &counter);

    fprintf(graph_file, "}\n\n");

    assert(fclose(graph_file) == 0);
}

