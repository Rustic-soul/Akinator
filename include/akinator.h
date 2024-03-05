#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include "./stack.h"

static const size_t STACK_START_CAP   = 100;
static const size_t MAX_LEN_WORD_TREE = 10000;
     
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

TreeNode* CreateStartTree(FILE *fp_sb);
int CreateGraph(TreeNode *node, FILE *fp);

struct Array *ctor_struct_arr(FILE *fp_src);
size_t search_size_file(FILE *fp_src);

#ifdef INFO
    #define PRINT_INFO(str ...) printf(str);
#else
    #define PRINT_INFO(str ...) {};
#endif //! INFO

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

#define CHECK_OPEN_FILE(fp)                                                                     \
    if (fp == NULL)                                                                             \
    {                                                                                           \
        fprintf(stderr, "Error: File dont open\n");                                             \
        fprintf(stderr, "FILE: %s; FUNC: %s; LINE: %d; \n", __FILE__, __func__, __LINE__);      \
    }

#define CHECK_ARGC(argc)                                                \
    if (argc != 4)                                                      \
        PRINT_ERROR("Error: Wrong number of input parameters\n");
    
#define PRINT_ERROR(str ...)                                                            \
{                                                                                       \
    fprintf(stderr, str);                                                               \
    fprintf(stderr, "FILE: %s; FUNC: %s; LINE: %d; \n", __FILE__, __func__, __LINE__);  \
}


#endif // !AKINATOR_H
