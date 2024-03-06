cd ..

# Подкючение допмодуля - stack
git submodule add https://github.com/russian-engineer/stack.git

# Изменение конфигурации stack
cd stack/include

str1=$(grep "typedef"    stack.h | grep "elem_t")
str2=$(grep "VENOM_ELEM" stack.h)
str3=$(grep "ELEM_MOD"   stack.h)

str11="typedef struct TreeNode TreeNode;\n\ntypedef TreeNode* elem_t;"

str22="static const elem_t VENOM_ELEM = NULL;"
str33="#define ELEM_MOD \"%p\""

sed -i "s/${str1}/${str11}/g" stack.h
sed -i "s/${str2}/${str22}/g" stack.h
sed -i "s/${str3}/${str33}/g" stack.h

# Копирование загловочного файла stack.h в папку с заголовочными файлами акинатора
cp stack.h ../../include/

# Создание объектного файла stack.o
cd ../src
gcc -c stack.c -o ../../obj/stack.o
