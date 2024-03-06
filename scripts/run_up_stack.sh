cd ..

# Подкючение допмодуля - stack
git submodule init 
git submodule update

# Изменение конфигурации stack
cp include/stack.h stack/include/

# Создание объектного файла stack.o
cd stack/src
gcc -c stack.c -o ../../obj/stack.o
