#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include "./stack.h"

static const char CRINGE_WORD[] = "абобус";


struct TreeNode {
    char *data;

    TreeNode *RightNode;
    TreeNode *LeftNode;
};

struct Array {
    char   *arr_ptr;
    size_t size_arr;
};

int RunAkinator(TreeNode *root);
int AddElemTree(TreeNode *root);
int PreorderPrintTree(TreeNode *root, FILE *fp);
int CleanTree(TreeNode *root);
void CleanBuffer();

int CreateStartTree(TreeNode *root, char *arr, Stack *stk);
int CreateGraph(TreeNode *node, FILE *fp);

struct Array *ctor_struct_arr(FILE *fp_src);
size_t search_size_file(FILE *fp_src);


#endif // !AKINATOR_H
