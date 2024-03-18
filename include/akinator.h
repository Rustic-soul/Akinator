#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include "utf8.h"
#include "mydef.h"

#define MAX_LEN_WORD_TREE 1000
#define MAX_DEPTH_TREE    1000

static const int ERROR_OUT = 1;

typedef struct TN {
    char* data;

    struct TN* PreviousNode;
    struct TN* RightNode;
    struct TN* LeftNode;
} TreeNode;

char *GetInput(const char* str);
char *GetPath(TreeNode* node, int* depth);
void PrintSimilarity(char *path1, int *len_path1, char *path2, int *len_path2, TreeNode **node1, TreeNode **node2);
void PrintWay(char *path, int len_path, TreeNode* node);


int       RunAkinator      (TreeNode *node, TreeNode *start_node);
int       CreateDescription(TreeNode *node);
int       CreateDifference (TreeNode *node);
int       AddElemTree      (TreeNode *node, TreeNode *main_node);
int       CleanTree        (TreeNode *node);
TreeNode *SearchElemTree   (TreeNode *node, char *elem);
TreeNode *CreateStartTree  (FILE *fp_sb);

void Speaker(char* format, ...);
int  PreorderPrintTree(TreeNode *node, FILE *fp);
int  CreateGraph      (TreeNode *node, FILE *fp);
void PrintStartMenu   ();

size_t search_size_file(FILE *fp_src);
rune_t* RuneFread(FILE *fp);

#ifdef SPEAKER
    #undef SPEAKER
    #define SPEAKER(str ...) Speaker(str);
#else
    #define SPEAKER(str ...) {};
#endif

#define SAVE_NEW_BASEDATA(node, fname, mod)                         \
{                                                                   \
    FILE *fp_nb = fopen(fname, mod);                                \
    if (fp_nb == NULL)                                              \
    {                                                               \
        PRINT_ERROR("Файл не был открыт\n");                        \
    }                                                               \
    else                                                            \
    {                                                               \
        fprintf(fp_nb, "%s %s\n", __DATE__, __TIME__);              \
        PreorderPrintTree(node, fp_nb);                             \
        fprintf(fp_nb, "\n\n");                                     \
        fclose(fp_nb);                                              \
    }                                                               \
}

#define CREATE_GRAPH(node, fname, mod)                              \
{                                                                   \
    FILE *fp_gt = fopen(fname, mod);                                \
    if (fp_gt == NULL)                                              \
    {                                                               \
        PRINT_ERROR("Файл не был открыт\n");                        \
    }                                                               \
    else                                                            \
    {                                                               \
        fprintf(fp_gt, "%s %s\n", __DATE__, __TIME__);              \
        fprintf(fp_gt, "digraph {\n");                              \
        CreateGraph(node, fp_gt);                                   \
        fprintf(fp_gt, "}\n\n");                                    \
        fclose(fp_gt);                                              \
    }                                                               \
}

#endif // !AKINATOR_H