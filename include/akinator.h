#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include "./utf8.h"

static const size_t STACK_START_CAP   = 100;
static const size_t MAX_LEN_WORD_TREE = 10000;

static const int ERROR_OUT = 1;

typedef struct TreeNode TreeNode;
struct TreeNode {
    char *data;

    TreeNode *PreviousNode;
    TreeNode *RightNode;
    TreeNode *LeftNode;
};

int RunAkinator(TreeNode *root);
int AddElemTree(TreeNode *root);
int PreorderPrintTree(TreeNode *root, FILE *fp);
int CleanTree(TreeNode *root);
void CleanBuffer();
rune_t* RuneFread(FILE* fp);

TreeNode* CreateStartTree(FILE *fp_sb);
int CreateGraph(TreeNode *node, FILE *fp);

struct Array *ctor_struct_arr(FILE *fp_src);
size_t search_size_file(FILE *fp_src);

#define SAVE_NEW_BASEDATA(root, fname)              \
{                                                   \
    FILE *fp_nb = fopen(fname, "w");                \
    CHECK_OPEN_FILE(fp_nb);                         \
                                                    \
    fprintf(fp_nb, "%s %s\n", __DATE__, __TIME__);  \
    PreorderPrintTree(root, fp_nb);                 \
    fprintf(fp_nb, "\n\n");                         \
                                                    \
    fclose(fp_nb);                                  \
}

#define CREATE_GRAPH(root, fname)                       \
{                                                       \
    FILE *fp_gt = fopen(fname, "a");                    \
    CHECK_OPEN_FILE(fp_gt);                             \
                                                        \
    fprintf(fp_gt, "%s %s\n", __DATE__, __TIME__);      \
    fprintf(fp_gt, "digraph {\n");                      \
    CreateGraph(root, fp_gt);                           \
    fprintf(fp_gt, "}\n\n");                            \
                                                        \
    fclose(fp_gt);                                      \
}    

#define PRINT_ERROR(str ...)                                                                 \
{                                                                                            \
    fprintf(stderr, "Ошибка: " str);                                                         \
    fprintf(stderr, "Файл: %s; Функция: %s; Строка: %d; \n", __FILE__, __func__, __LINE__);  \
}


#endif // !AKINATOR_H
