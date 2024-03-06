cd ..

# Подкючение допмодуля - stack
git submodule init 
git submodule update

# Изменение конфигурации stack
cd stack/include
rm ./stack.h
cp ../../include/stack.h 

# Создание объектного файла stack.o
cd ../src
gcc -c stack.c -o ../../obj/stack.o

# Создание объектного файла utf8_func.o
cd ../../libutf8/ 
gcc -c utf8_func.c -o ../obj/utf8_func.o
