#include "../include/akinator.h"
#include "../include/utf8.h"
#include "../include/mydef.h"
#include <stdio.h>
#include <malloc.h>

static const char *PATH_BASEDATA_CUR = "../data/basedata_cur"; 
static const char *PATH_BASEDATA_LST = "../data/basedata_lst"; 
// static const char *PATH_BASEDATA_BKP = "data/basedata_bkp"; 

static const char *PATH_GRAPHDATA_CUR = "../graphviz/graph_cur.dot"; 
static const char *PATH_GRAPHDATA_LST = "../graphviz/graph_lst.dot"; 

int main()
{
    rune_t answer = '\0';
    
    FILE* fp_sb = fopen(PATH_BASEDATA_CUR, "r");
    if (fp_sb == NULL)
    {
        PRINT_ERROR("Файл с базой не был открыт.\n");
        return ERROR_OUT;
    }
    
    // Создание стартового дерева из базы данных
    TreeNode *RootTree = CreateStartTree(fp_sb);
    fclose(fp_sb);
    if (RootTree == NULL)
    {
        PRINT_ERROR("Дерево не было создано\n");
        return ERROR_OUT;
    }

    // Стартовое меню игры
    printf("Начало игры, если готовы введите (Д)а: ");
    answer = rune_getc();
    
    while ((answer == L'Д') || (answer == L'д') || (answer == 'Y') || (answer == 'y') || (answer == '\n'))
    {
        PrintStartMenu();
        answer = rune_getc();
        if ((answer == L'И') || (answer == L'и') || (answer == '\n'))
        {
            RunAkinator(RootTree, RootTree);
        }
        else if ((answer == L'О') || (answer == L'о'))
        {
            CreateDescription(RootTree);
        }
        else if ((answer == L'Р') || (answer == L'р'))
        {
            CreateDifference(RootTree);
        }

        printf("\nВведите (Д)а, если хотите сыграть ещё раз или любой другой символ для завершения: ");
        answer = rune_getc();
    }
    
    // Дополнение файла graph_lst.dot и переопределение graph_cur.dot деревом из текущей игры 
    CREATE_GRAPH(RootTree, PATH_GRAPHDATA_CUR, "w");
    CREATE_GRAPH(RootTree, PATH_GRAPHDATA_LST, "a");

    // Дополнение файла basedata_lst и переопределение basedata_cur базой дерева с текущей игры
    SAVE_NEW_BASEDATA(RootTree, PATH_BASEDATA_CUR, "w");
    SAVE_NEW_BASEDATA(RootTree, PATH_BASEDATA_LST, "a");
    
    CleanTree(RootTree);
}
