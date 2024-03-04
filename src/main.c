#include "../include/akinator.h"
#include <stdio.h>
#include <malloc.h>

int main()
{
    FILE *fp_out   = fopen("data/newbasedata2.txt", "w");
    FILE *fp_graph = fopen("graphiz/output.dot", "w");
    FILE *fp_src_tree = fopen("data/newbasedata.txt", "r");

    TreeNode RootTree = {NULL, NULL, NULL};
    struct Array *src_array = ctor_struct_arr(fp_src_tree);

    Stack stk1 = {};
    StackCtor(&stk1, 10);

    CreateStartTree(&RootTree, src_array->arr_ptr, &stk1); 
    
    free(src_array->arr_ptr);
    free(src_array);
    fclose(fp_src_tree);
    StackDtor(&stk1);

    printf("Начало игры, если готовы введите (Y)es: ");
    int cmd = getchar();
    CleanBuffer();

    while ((cmd == 'Y') || (cmd == 'y'))
    {
        RunAkinator(&RootTree);
        printf("Введите (Y)es, если хотите сыграть ещё раз или (N)o для завершения: ");
        cmd = getchar();
        CleanBuffer();
    }
    
    fprintf(fp_graph, "digraph {");
    CreateGraph(&RootTree, fp_graph);
    fprintf(fp_graph, "}");
    fclose(fp_graph);

    PreorderPrintTree(&RootTree, fp_out);
    fclose(fp_out);
    CleanTree(&RootTree);
}
