#include "../include/akinator.h"
#include "../include/utf8.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> 
#include <stdarg.h>


static const int  LEN_MENU = 100;
static const char *LINE_MENU_ONE   = "Режим отгадывания:                     введите (И)гра";
static const char *LINE_MENU_TWO   = "Режим получения информации об объекте: введите (о)пределение";
static const char *LINE_MENU_THREE = "Режим сравнения двух объектов:         введите (p)азличие";

void PrintStartMenu()
{
    #define PRINT_SEPARATOR()                                 \
    {                                                         \
        printf("|");                                          \
        for (int i = 0; i < LEN_MENU - 2; i++)                \
        {                                                     \
            printf("%c", '-');                                \
        }                                                     \
        printf("|\n");                                        \
    }
    
    PRINT_SEPARATOR();
    printf("|%*s|\n", -125, LINE_MENU_ONE);
    PRINT_SEPARATOR();
    printf("|%*s|\n", -149, LINE_MENU_TWO);
    PRINT_SEPARATOR();
    printf("|%*s|\n", -138, LINE_MENU_THREE);
    PRINT_SEPARATOR();
    printf("\n");
}

int RunAkinator(TreeNode *node, TreeNode *start_node)
{
    if ((node->data == NULL) || (start_node == NULL))
    {
        return ERROR_OUT;    
    }

    rune_t answer = '\0';

    if ((node->RightNode == NULL) && (node->LeftNode == NULL))
    {
        printf("Финиш! Это [%s], я угадал?[Д/н]: ", node->data);
        SPEAKER("Финиш! Это %s, я угадал?", node->data);

        answer = rune_getc();
        if ((answer == L'Д') || (answer == L'д') || (answer == 'Y') || (answer == 'y') || (answer == '\n'))
        {
            return 0;
        }
        else if ((answer == L'Н') || (answer == L'н') || (answer == 'N') || (answer == 'n'))
        {
            return AddElemTree(node, start_node);
        }
        else
        {
            return ERROR_OUT;
        }
    }
    else if ((node->RightNode != NULL) && (node->LeftNode != NULL))
    {
        printf("Это [%s]?[Д/н]: ", node->data);
        SPEAKER("Это %s?: ", node->data);

        answer = rune_getc();
        if ((answer == L'Д') || (answer == L'д') || (answer == 'Y') || (answer == 'y') || (answer == '\n'))
        {
            RunAkinator(node->LeftNode, start_node);
        }
        else if ((answer == L'Н') || (answer == L'н') || (answer == 'N') || (answer == 'n'))
        {
            RunAkinator(node->RightNode, start_node);
        }
        else
        {
            return ERROR_OUT;
        }
    }

    return 0;
}

int AddElemTree(TreeNode *node, TreeNode *main_node)
{
    char *new_obj = GetInput("Введите объект, который вы загадали: ");

    PRINT_DEBUG("Так был считан новый объект: [@%s@]]\n", new_obj);
    
    if (SearchElemTree(main_node, new_obj) != NULL)
    {
        printf("Такой объект уже есть\n");
        SPEAKER("Такой объект уже есть\n");
        free(new_obj);
        return 0;
    }
    
    node->RightNode = (TreeNode *)calloc(1, sizeof(TreeNode));
    node->LeftNode  = (TreeNode *)calloc(1, sizeof(TreeNode));
    
    node->LeftNode->data = (char *)calloc(strlen(new_obj) + 1, sizeof(char));
    
    node->RightNode->data = node->data;    
    node->LeftNode->data  = strcpy(node->LeftNode->data, new_obj);

    printf("Чем [%s] отличается от [%s]?\nОн ... ", node->LeftNode->data, node->RightNode->data);
    SPEAKER("Чем %s отличается от %s? Он ", node->LeftNode->data, node->RightNode->data);
    new_obj = GetInput("");
    
    PRINT_DEBUG("Так было считано различие: [@%s@]]\n", new_obj);

    node->data = (char *)calloc(strlen(new_obj) + 1, sizeof(char));
    node->data = strcpy(node->data, new_obj);

    free(new_obj);

    return 0;
}

char *GetInput(const char* str)
{
    char* obj = (char *)calloc(MAX_LEN_WORD_TREE, sizeof(char));

    printf("%s", str);
    SPEAKER("%s", str);

    fgets(obj, MAX_LEN_WORD_TREE, stdin);

    size_t len_elem = strlen(obj);
    PRINT_DEBUG("GetInput len_el_in = %lu\n", len_elem);

    while (obj[len_elem - 1] == '\n')
    {
        obj[len_elem - 1] = '\0';
        len_elem--;
    }
    PRINT_DEBUG("GetInput len_el_out = %lu\n", len_elem);

    return obj;
}

char *GetPath(TreeNode* node, int* depth)
{
    int len_path = 0;
    char *path = (char *)calloc(MAX_DEPTH_TREE, sizeof(char));
    while (node->PreviousNode != NULL)
    {
        if (node == node->PreviousNode->LeftNode)
        {
            path[len_path] = 1;
        }
        else
        {
            path[len_path] = 0;
        }
        
        node = node->PreviousNode;
        len_path++;
    }
    *depth = len_path;
    
    return path;
}

void PrintSimilarity(char *path1, int *len_path1, char *path2, int *len_path2, TreeNode **node1, TreeNode **node2)
{
    assert(path1 != NULL);
    assert(path2 != NULL);
    assert(node1 != NULL);
    assert(node2 != NULL);

    while ((*len_path1 >= 1) && (*len_path2 >= 1) && (path1[*len_path1 - 1] == path2[*len_path2 - 1]))
    {
        int is_left   = (path1[*len_path1 - 1] == 1);
        int last_el   = (*len_path1 >= 2) ? (path1[*len_path1 - 2] != path2[*len_path2 - 2]) : ((*len_path1 == 1) || (*len_path2 == 1));
        int penult_el = (*len_path1 >= 3) ? (path1[*len_path1 - 3] != path2[*len_path2 - 3]) : ((*len_path1 == 2) || (*len_path2 == 2));
        char *prefix  = (is_left ? "" : "не ");
        
        if (last_el)
        {
            printf("%s%s.", prefix, (*node1)->data);
        }
        else if (penult_el)
        {
            printf("%s%s и ", prefix, (*node1)->data);
        }
        else
        {
            printf("%s%s, ", prefix, (*node1)->data);
        }

        *node1 = (is_left ? (*node1)->LeftNode : (*node1)->RightNode);
        *node2 = (is_left ? (*node2)->LeftNode : (*node2)->RightNode);

        (*len_path1)--;
        (*len_path2)--;
    }
    printf("\n");
}

void PrintWay(char *path, int len_path, TreeNode* node)
{
    while (len_path >= 1)
    {
        int is_left  = (path[len_path - 1] == 1);
        char *prefix = (is_left ? "" : "не ");

        if (len_path == 2)
        {
            printf("%s%s и ", prefix, node->data);
        }
        else if (len_path == 1)
        {
            printf("%s%s.", prefix, node->data);
        }
        else
        {
            printf("%s%s, ", prefix, node->data);
        }

        node = (is_left ? node->LeftNode : node->RightNode);
        len_path--;
    }
    printf("\n");   
}

int CreateDifference(TreeNode* node)
{
    assert(node != NULL);

    char *elem1 = GetInput("Введите первый объект для сравнения: ");
    char *elem2 = GetInput("Введите второй объект для сравнения: ");

    TreeNode *tmp1 = SearchElemTree(node, elem1);
    TreeNode *tmp2 = SearchElemTree(node, elem2);

    if ((tmp1 == NULL) || (tmp2 == NULL))
    {
        char *prefix = ((tmp1 == NULL) && (tmp2 == NULL) ? " и " : "");

        printf("%s%s%s нет в программе, если хотите, вы можете добавить, запустив программу в режиме [Игра]\n",
               ((tmp1 == NULL) ? elem1 : ""), prefix, ((tmp2 == NULL) ? elem2 : ""));

        free(elem1);
        free(elem2);
        return 0;
    }

    int  len_path1 = 0;
    int  len_path2 = 0;
    char *path1 = GetPath(tmp1, &len_path1);
    char *path2 = GetPath(tmp2, &len_path2);
    tmp1 = node;
    tmp2 = node;

    PRINT_DEBUG("len_path1 = %d\n", len_path1);
    PRINT_DEBUG("len_path2 = %d\n", len_path2);

    printf("[%s] и {%s} схожи тем, что они: ", elem1, elem2);
    PrintSimilarity(path1, &len_path1, path2, &len_path2, &tmp1, &tmp2);
    
    printf("И отличаются тем, что:\n");
    
    printf("[%s] - ", elem1);
    PrintWay(path1, len_path1, tmp1);

    printf("А {%s} - ", elem2);
    PrintWay(path2, len_path2, tmp2);
    
    free(path1);
    free(path2);
    free(elem1);
    free(elem2);

    return 0;
}

int CreateDescription(TreeNode* node)
{
    assert(node != NULL);

    char* elem = GetInput("Введите объект, определение которого вы хотите получить: ");
    
    TreeNode *tmp = SearchElemTree(node, elem);
    if (tmp == NULL)
    {
        printf("%s нет в программе, если хотите, вы можете добавить, запустив программу в режиме [Игра]\n", elem);
        free(elem);
        return 0;
    }

    int  len_path = 0;
    char *path    = GetPath(tmp, &len_path);

    PRINT_DEBUG("len_path = %d\n", len_path);
        
    printf("%s это - ", elem);
    PrintWay(path, len_path, node);

    free(elem);
    free(path);

    return 0;
}

TreeNode* SearchElemTree(TreeNode *node, char *elem)
{
    if (node == NULL)
    {
        return NULL;
    }
    
    PRINT_DEBUG("Поиск... Элемент узла{{%s}}\n", node->data);
    
    if (strcmp(node->data, elem) == 0)
    {
        return node;
    }
    
    TreeNode* tmp = SearchElemTree(node->LeftNode, elem);
    if (tmp == NULL)
    {
        tmp = SearchElemTree(node->RightNode, elem);
    }
    
    return tmp;
}

int PreorderPrintTree(TreeNode *node, FILE *fp)
{
    if (node == NULL)
    {
        return ERROR_OUT;
    }

    fprintf(fp, "(");
    fprintf(fp, " $%s$ ", node->data);

    if (node->LeftNode)
        PreorderPrintTree(node->LeftNode, fp);

    if (node->RightNode)
        PreorderPrintTree(node->RightNode, fp);

    fprintf(fp, ")");

    return 0;
}

int CreateGraph(TreeNode *node, FILE *fp)
{
    if (node->LeftNode)
    {
        fprintf(fp, "\t\"%s\" -> \"%s\"\n", node->data, node->LeftNode->data);
        CreateGraph(node->LeftNode, fp);
    } 
    if (node->RightNode)
    {
        fprintf(fp, "\t\"%s\" -> \"%s\"\n", node->data, node->RightNode->data);
        CreateGraph(node->RightNode, fp);
    }

    return 0;
}

TreeNode* CreateStartTree(FILE *fp)
{
    // Создание корня дерева
    TreeNode *root = (TreeNode *)calloc(1, sizeof(TreeNode));
    if (fp == NULL)
    {
        return root;
    }

    // Создание массива с базой данных
    rune_t *rune_arr = RuneFread(fp);
    
    // Создание дерева из базы данных
    char*   str = (char *)  calloc(MAX_LEN_WORD_TREE, sizeof(char));
    rune_t* tmp = (rune_t *)calloc(MAX_LEN_WORD_TREE, sizeof(rune_t));

    for (int i = 0; rune_arr[i] != '\0'; i++)
    {
        if (rune_arr[i] == '$')
        {
            i++;
            int j = 0;
            while (rune_arr[i] != '$')
            {
                tmp[j++] = rune_arr[i++];
            }
            tmp[j] = '\0';

            rune_to_utf8(tmp, str, MAX_LEN_WORD_TREE);
            PRINT_DEBUG("Создание дерева... Новый элемент: <<%s>>\n", str);

            if (root->data != NULL)
            {
                root->LeftNode = (TreeNode *)calloc(1, sizeof(TreeNode));
                root->LeftNode->PreviousNode = root;
                root = root->LeftNode;
            }
                        
            root->data = strdup(str);
        }
        else if (rune_arr[i] == ')')
        {
            if (root->PreviousNode != NULL)
            {
                if (root == root->PreviousNode->LeftNode)
                {
                    root = root->PreviousNode;
                    root->RightNode = (TreeNode *)calloc(1, sizeof(TreeNode));
                    root->RightNode->PreviousNode = root;
                    root = root->RightNode;
                }
                else
                {
                    root = root->PreviousNode;
                }
            }
            else
            {
                break;
            } 
        }
    }

    free(rune_arr);
    free(str);
    free(tmp);

    return root;
}

rune_t* RuneFread(FILE* fp)
{
    size_t sz_file = search_size_file(fp); 
    PRINT_DEBUG("Считывание базы из файла... Размер файла = %lu\n", sz_file);

    char* char_arr   = (char *)  calloc(sz_file + 1, sizeof(char));
    rune_t* rune_arr = (rune_t *)calloc(sz_file + 1, sizeof(rune_t));

    fread(char_arr, sizeof(char), sz_file, fp);
    utf8_to_rune(char_arr, rune_arr);
    
    PRINT_DEBUG("Так считали char массив:\n");
    PRINT_DEBUG("***%s***\n", char_arr);

    free(char_arr);

    return rune_arr;
}

size_t search_size_file(FILE *fp)
{
    if (fp == NULL)
        return 0;

    long start_ftell = ftell(fp);
    fseek(fp, 0, SEEK_END);

    size_t size_file = (size_t)ftell(fp);
    fseek(fp, start_ftell, SEEK_SET);

    PRINT_DEBUG("Нахождение размера файла... Размер = %lu\n", size_file);
    
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

void Speaker(char* format, ...)
{
    char array[1000]       = {};
    char for_speaker[1050] = {};

    va_list ptr;
    va_start(ptr, format);
    vsprintf(array, format, ptr);
    va_end(ptr);

    sprintf(for_speaker, "espeak-ng -s 150 -a 200 -v Russian \"%s\"", array);
    system(for_speaker);
}
