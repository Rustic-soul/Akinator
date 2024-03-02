#include "../include/akinator.h"
#include <wchar.h>


int main()
{
    TreeNode RootTree = {NULL, NULL, NULL};

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

    CleanTree(&RootTree);
}
