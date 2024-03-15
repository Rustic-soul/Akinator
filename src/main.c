#include "../include/akinator.h"
#include "../include/utf8.h"
#include <stdio.h>
#include <malloc.h>

// static const char* PATH_BASEDATA_CUR = "../data/datatest_cur"; 
// static const char PATH_BASEDATA_BKP[] = "../data/basedata_bkp"; 
// static const char PATH_BASEDATA_LST[] = "../data/basedata_lst"; 

// static const char PATH_GRAPHDATA_CUR[] = "../graphiz/graph_cur.dot"; 
// static const char PATH_GRAPHDATA_LST[] = "../graphiz/graph_lst.dot"; 

int main() {
    rune_t answer = '\0';
    
    printf("Да чтож это такое\n");
    // Создание стартового дерева из базы данных
    
    FILE* fp_sb = fopen("../data/basedata_cur", "r");
    if (fp_sb == NULL) {
        PRINT_ERROR("Файл с базой не был открыт.\n");
        return ERROR_OUT;
    }
    
    printf("К созданию дерева подошли\n");
    TreeNode *RootTree = CreateStartTree(fp_sb); 
    fclose(fp_sb);
    printf("Cоздание дерева завершили \n");
    
    // Стартовое меню игры
    printf("Начало игры, если готовы введите (Д)а: ");
    answer = rune_getc();
    
    while ((answer == L'Д') || (answer == L'д') || (answer == 'Y') || (answer == 'y') || (answer == '\n'))
    {
        RunAkinator(RootTree);
            
        printf("\nВведите (Д)а, если хотите сыграть ещё раз или любой другой символ для завершения: ");
        answer = rune_getc();
    }
    
    // Дополнение файла newgraph.dot деревом из текущей игры 
    // CREATE_GRAPH(RootTree, PATH_GRAPHDATA_CUR);

    // Дополнение файла newbasedata.txt базой дерева с текущей игры
    // SAVE_NEW_BASEDATA(RootTree, PATH_GRAPHDATA_LST);
    
    CleanTree(RootTree);
}
