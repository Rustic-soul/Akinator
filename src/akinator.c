#include "../include/akinator.h"
#include "../include/stack.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

static const char *CRINGE_WORD = "абобус";

int RunAkinator(TreeNode *root)
{
    if (root->data == NULL)
    {
        root->data = (char *)malloc(strlen(CRINGE_WORD) + 1);
        strcpy(root->data, CRINGE_WORD);
        return RunAkinator(root);    
    }

    if (!root->RightNode && !root->LeftNode)
    {
        fprintf(stdout, "Финиш! Это [%s], я угадал?[y/n]: ", root->data);
        int answer = getchar();
        
        if (answer != '\n')
            CleanBuffer();

        if ((answer == 'y') || (answer == 'Y') || (answer == '\n'))
            return 0;
        else if ((answer == 'n') || (answer == 'N') || (answer == '.'))
            return AddElemTree(root);
        else
            return 1;
    }
    else if (root->RightNode && root->LeftNode)
    {
        fprintf(stdout, "Это [%s]?[y/n]: ", root->data);
        int answer = getchar();
        
        if (answer != '\n')
            CleanBuffer();
        
        if ((answer == 'y') || (answer == 'Y') || (answer == '\n'))
            RunAkinator(root->LeftNode);
        else if ((answer == 'n') || (answer == 'N') || (answer == '.'))
            RunAkinator(root->RightNode);
        else
            return 1;
    }

    return 0;
}

int AddElemTree(TreeNode *root)
{
    root->RightNode       = (TreeNode *)calloc(1, sizeof(TreeNode));
    root->RightNode->data = root->data;

    char new_obj[1000] = "VENOM";
    fprintf(stdout, "Введите объект, который вы загадали: ");
    fgets(new_obj, 1000, stdin);

    root->LeftNode  = (TreeNode *)calloc(1, sizeof(TreeNode));
    size_t len_str  = strlen(new_obj);
    if (new_obj[len_str - 1] == '\n')
    {
        len_str--;
        new_obj[len_str] = '\0';
    }
    
    root->LeftNode->data = (char *)malloc(len_str + 1);
    strcpy(root->LeftNode->data, new_obj);

    char new_question[1000] = "VENOM";
    fprintf(stdout, "Чем [%s] отличается от [%s]? Он ...\n", new_obj, root->data);
    fgets(new_question, 1000, stdin);
    
    len_str = strlen(new_question);
    if (new_question[len_str - 1] == '\n')
    {
        len_str--;
        new_question[len_str] = '\0';
    }

    root->data = (char *)malloc(len_str + 1);
    strcpy(root->data, new_question);

    return 0;
}

int PreorderPrintTree(TreeNode *root, FILE *fp)
{
    if (!root)
        return 1;
    #define PATH_OUT stdout

    if (fp)
    {
        #undef PATH_OUT
        #define PATH_OUT fp
    }


    fprintf(PATH_OUT, "(");
    fprintf(PATH_OUT, " \"%s\" ", root->data);

    if (root->LeftNode)
        PreorderPrintTree(root->LeftNode, fp);

    if (root->RightNode)
        PreorderPrintTree(root->RightNode, fp);

    fprintf(PATH_OUT, ")");

    return 0;
}

int CreateGraph(TreeNode *root, FILE *fp)
{
    if (root->LeftNode)
    {
        fprintf(fp, "\t\"%s\" -> \"%s\"\n", root->data, root->LeftNode->data);
        CreateGraph(root->LeftNode, fp);
    } 
    if (root->RightNode)
    {
        fprintf(fp, "\t\"%s\" -> \"%s\"\n", root->data, root->RightNode->data);
        CreateGraph(root->RightNode, fp);
    }

    return 0;
}

TreeNode* CreateStartTree(FILE *fp)
{
    // Создание корня дерева
    TreeNode *root = (TreeNode *)calloc(1, sizeof(TreeNode));
    if (fp == NULL)
        return root;
        
    // Создание массива с базой данных
    struct Array *src_array = ctor_struct_arr(fp);
    char *arr = src_array->arr_ptr; 

    // Инициализация Stack для хранения адресов узлов 
    Stack *stk = (Stack *)calloc(1, sizeof(Stack));
    StackCtor(stk, STACK_START_CAP);
    
    // Cоздания дерева из базы данных
    StackPush(stk, root);
    char *str = (char *)malloc(MAX_LEN_WORD_TREE);

    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] == '"')
        {
            i++;
            int j = 0;
            while (arr[i] != '\"')
            {
                str[j] = arr[i];
                j++; i++;
            }
            str[j] = '\0';

            PRINT_INFO("[%s]\n", str);

            if (root->data != NULL)
            {
                root->LeftNode = (TreeNode *)calloc(1, sizeof(TreeNode));
                root = root->LeftNode;
            }
            
            if (arr[i+2] != ')')
                StackPush(stk, root);
            
            root->data = (char *)malloc(strlen(str) + 1);
            strcpy(root->data, str);
        }
        else if (arr[i] == ')')
        {
            TreeNode *tmp = root;
            
            if (stk->size == 0)
                break;
            
            StackPop(stk, &root);
            
            if (tmp == root->LeftNode)
            {
                StackPush(stk, root);
                root->RightNode = (TreeNode *)calloc(1, sizeof(TreeNode));
                root = root->RightNode;
            }
        }
    }

    free(src_array->arr_ptr);
    free(src_array);
    free(str);

    StackDtor(stk);
    free(stk);
    
    return root;
}

struct Array *ctor_struct_arr(FILE *fp_src)
{
    struct Array *new_struct_arr = (struct Array*)malloc(sizeof(struct Array));

    long   start_ptr_file = ftell(fp_src);
    size_t sz_file        = search_size_file(fp_src);
    char   *array         = (char*)calloc(sz_file + 1, sizeof(char));

    fread(array, sizeof(char), sz_file, fp_src);

    new_struct_arr->arr_ptr  = array;
    new_struct_arr->size_arr = sz_file;
    
    fseek(fp_src, start_ptr_file, SEEK_SET);
    return new_struct_arr;
}

size_t search_size_file(FILE *fp_src)
{
    assert(fp_src != NULL);

	long start_ftell = ftell(fp_src);
    fseek(fp_src, 0, SEEK_END);
    
    size_t size_file = (size_t)ftell(fp_src);
    fseek(fp_src, start_ftell, SEEK_SET);

    return size_file;
}


int CleanTree(TreeNode *root)
{
    if (root->LeftNode)
        CleanTree(root->LeftNode);

    if (root->RightNode)
        CleanTree(root->RightNode);

    free(root->data);
    free(root);    

    return 0;
}

void CleanBuffer() { for(int c = getchar (); c != '\n' && c != EOF; c = getchar ()); }
