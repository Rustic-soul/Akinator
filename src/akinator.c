#include "../include/akinator.h"
#include "../include/utf8.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int RunAkinator(TreeNode *root) {
    if (root->data == NULL) {
        return ERROR_OUT;    
    }

    rune_t answer = '\0';

    if ((root->RightNode == NULL) && (root->LeftNode == NULL)) {
        printf("Финиш! Это [%s], я угадал?[Д/н]: ", root->data);
        answer = rune_getc();
        
        if ((answer == L'Д') || (answer == L'д') || (answer == 'Y') || (answer == 'y') || (answer == '\n'))
            return 0;
        else if ((answer == L'Н') || (answer == L'н') || (answer == 'N') || (answer == 'n'))
            return 6;
            // return AddElemTree(root);
        else
            return 1;
    }
    else if ((root->RightNode != NULL) && (root->LeftNode != NULL))
    {
        printf("Это [%s]?[Д/н]: ", root->data);
        answer = rune_getc();
        
        if ((answer == L'Д') || (answer == L'д') || (answer == 'Y') || (answer == 'y') || (answer == '\n'))
            RunAkinator(root->LeftNode);
        else if ((answer == L'Н') || (answer == L'н') || (answer == 'N') || (answer == 'n'))
            RunAkinator(root->RightNode);
        else
            return 1;
    }

    return 0;
}

// int AddElemTree(TreeNode *root)
// {
//     root->RightNode       = (TreeNode *)calloc(1, sizeof(TreeNode));
//     root->RightNode->data = root->data;
//
//     char new_obj[1000] = "VENOM";
//     fprintf(stdout, "Введите объект, который вы загадали: ");
//     fgets(new_obj, 1000, stdin);
//
//     root->LeftNode  = (TreeNode *)calloc(1, sizeof(TreeNode));
//     size_t len_str  = strlen(new_obj);
//     if (new_obj[len_str - 1] == '\n')
//     {
//         len_str--;
//         new_obj[len_str] = '\0';
//     }
//     
//     root->LeftNode->data = (char *)malloc(len_str + 1);
//     strcpy(root->LeftNode->data, new_obj);
//
//     char new_question[1000] = "VENOM";
//     fprintf(stdout, "Чем [%s] отличается от [%s]? Он ...\n", new_obj, root->data);
//     fgets(new_question, 1000, stdin);
//     
//     len_str = strlen(new_question);
//     if (new_question[len_str - 1] == '\n')
//     {
//         len_str--;
//         new_question[len_str] = '\0';
//     }
//
//     root->data = (char *)malloc(len_str + 1);
//     strcpy(root->data, new_question);
//
//     return 0;
// }
//
// int PreorderPrintTree(TreeNode *root, FILE *fp)
// {
//     if (!root)
//         return 1;
//     #define PATH_OUT stdout
//
//     if (fp)
//     {
//         #undef PATH_OUT
//         #define PATH_OUT fp
//     }
//
//
//     fprintf(PATH_OUT, "(");
//     fprintf(PATH_OUT, " \"%s\" ", root->data);
//
//     if (root->LeftNode)
//         PreorderPrintTree(root->LeftNode, fp);
//
//     if (root->RightNode)
//         PreorderPrintTree(root->RightNode, fp);
//
//     fprintf(PATH_OUT, ")");
//
//     return 0;
// }
//
// int CreateGraph(TreeNode *root, FILE *fp)
// {
//     if (root->LeftNode)
//     {
//         fprintf(fp, "\t\"%s\" -> \"%s\"\n", root->data, root->LeftNode->data);
//         CreateGraph(root->LeftNode, fp);
//     } 
//     if (root->RightNode)
//     {
//         fprintf(fp, "\t\"%s\" -> \"%s\"\n", root->data, root->RightNode->data);
//         CreateGraph(root->RightNode, fp);
//     }
//
//     return 0;
// }

TreeNode* CreateStartTree(FILE *fp) {
    // Создание корня дерева
    TreeNode *root = (TreeNode *)calloc(1, sizeof(TreeNode));
    if (fp == NULL) {
        return root;
    }

    // Создание массива с базой данных
    rune_t *rune_arr = RuneFread(fp);

    // Инициализация Stack для хранения адресов узлов 
    // Stack *stk = (Stack *)calloc(1, sizeof(Stack));
    // StackCtor(stk, STACK_START_CAP);
    
    // Cоздания дерева из базы данных
    // StackPush(stk, root);
    char*   str = (char*)  calloc(MAX_LEN_WORD_TREE, sizeof(char));
    rune_t* tmp = (rune_t*)calloc(MAX_LEN_WORD_TREE, sizeof(rune_t));

    for (int i = 0, j = 0; rune_arr[i] != '\0'; i++) {
        if (rune_arr[i] == '$') {
            i++; j = 0;
            while (rune_arr[i] != '$') {
                tmp[j] = rune_arr[i];
                j++; i++;
            }
            tmp[j] = '\0';
            rune_to_utf8(tmp, str, MAX_LEN_WORD_TREE);
            printf("Данныые узла: {{%s}}\n", str);

            if (root->data != NULL) {
                root->LeftNode = (TreeNode*)calloc(1, sizeof(TreeNode));
                root->LeftNode->PreviousNode = root;
                root = root->LeftNode;
            }
                        
            root->data = (char*)calloc(strlen(str) + 1, sizeof(char));
            strcpy(root->data, str);
            printf("Сейчас root указывает на --> [[%s]]\n", root->data);
        } else if (rune_arr[i] == ')') {
            if (root->PreviousNode != NULL) {
                if (root == root->PreviousNode->LeftNode) {
                    root = root->PreviousNode;
                    root->RightNode = (TreeNode*)calloc(1, sizeof(TreeNode));
                    root->RightNode->PreviousNode = root;
                    root = root->RightNode;
                } else
                    root = root->PreviousNode;
            } else 
                break;

            printf("Сейчас root указывает на --> >>%s<<\n", root->data);
        }
    }

    free(rune_arr);
    free(str);
    free(tmp);

    // StackDtor(stk);
    // free(stk);
    
    return root;
}

rune_t* RuneFread(FILE* fp) {
    size_t sz_file = search_size_file(fp); 
    printf("Размер файла = %lu\n", sz_file);

    char* char_arr   = (char*)  calloc(sz_file + 1, sizeof(char));
    rune_t* rune_arr = (rune_t*)calloc(sz_file + 1, sizeof(rune_t));

    fread(char_arr, sizeof(char), sz_file, fp);
    utf8_to_rune(char_arr, rune_arr);
    
    printf("Так считали char массив\n");
    printf("***%s***\n", char_arr);

    free(char_arr);

    return rune_arr;
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

// void CleanBuffer() { for(int c = getchar (); c != '\n' && c != EOF; c = getchar ()); }
