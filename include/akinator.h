#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static const int  RUS_YES       = 208;
static const int  RUS_NO        = 209;
static const char CRINGE_WORD[] = "абобус";

typedef struct TreeNode TreeNode;

struct TreeNode {
    char *data;

    TreeNode *RightNode;
    TreeNode *LeftNode;
};

int RunAkinator(TreeNode *root);
int AddElemTree(TreeNode *root);
int CleanTree(TreeNode *root);
void CleanBuffer();

#endif // !AKINATOR_H
