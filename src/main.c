#include "../include/akinator.h"
#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
    CHECK_ARGC(argc);
    
    // Создание стартового дерева из базы данных
    FILE *fp_sb = fopen(argv[1], "r");
    CHECK_OPEN_FILE(fp_sb);

    TreeNode *RootTree = CreateStartTree(fp_sb); 
    fclose(fp_sb);
    
    // Стартовое меню игры
    printf("Начало игры, если готовы введите (Y)es: ");
    int cmd = getchar();

    if (cmd != '\n')
        CleanBuffer();
    
    while ((cmd == 'Y') || (cmd == 'y') || (cmd == '\n'))
    {
        RunAkinator(RootTree);
        printf("\nВведите (Y)es, если хотите сыграть ещё раз или (N)o для завершения: ");
        cmd = getchar();
        printf("{{{{{{{%c}}}}}}}\n", cmd);
        
        if (cmd != '\n')
            CleanBuffer();
    }
    
    // Дополнение файла newgraph.dot деревом из текущей игры 
    CREATE_GRAPH(RootTree, argv[3]);

    // Дополнение файла newbasedata.txt базой дерева с текущей игры
    SAVE_NEW_BASEDATA(RootTree, argv[2]);
    
    CleanTree(RootTree);
}
