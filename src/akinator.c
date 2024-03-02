#include "../include/akinator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        CleanBuffer();

        if ((answer == 'y') || (answer == 'Y'))
            return 0;
        else if ((answer == 'n') || (answer == 'N'))
            return AddElemTree(root);
        else
            return 1;
    }
    else if (root->RightNode && root->LeftNode)
    {
        fprintf(stdout, "Это [%s]?[y/n]: ", root->data);
        int answer = getchar();
        CleanBuffer();
        
        if ((answer == 'y') || (answer == 'Y'))
            RunAkinator(root->LeftNode);
        else if ((answer == 'n') || (answer == 'N'))
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

int CleanTree(TreeNode *root)
{
    if (root->LeftNode)
    {
        CleanTree(root->LeftNode);
        free(root->LeftNode);
    }

    if (root->RightNode)
    {
        CleanTree(root->RightNode);
        free(root->RightNode);
    }
    
    free(root->data);

    return 0;
}

void CleanBuffer() { for(int c = getchar (); c != '\n' && c != EOF; c = getchar ()); }
