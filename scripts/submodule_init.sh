
# Переход в главную директорию akinator/
cd ..

# Инициализация подмодулей проекта
git submodule init 
git submodule update

# Создание объектных файлов библиотеки
cd libutf8/ 
gcc -O2 -c utf8_func.c -o ../obj/utf8_func.o
