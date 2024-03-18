# Включение файла с флагами компиляции для DEBUG режима 
. ./flags

# Переход в главную директорию akinator/
cd ..


# Запуск игры
if [[ $1 =~ "play" ]]; then
    cd bin
    ./Akinator
    exit 0
fi


# Создание картинки с деревом акинатора
if [[ $1 =~ "picture" ]]; then
    cd graphviz
    FIRST_LINE=$(head -1 graph_cur.dot)
    if [[ ! $FIRST_LINE =~ "digraph" ]]; then
        sed -i -e "1d" graph_cur.dot
    fi
    dot -Tsvg graph_cur.dot > graph.svg
    exit 0
fi


# Инициализация подмодулей проекта
if [[ $1 =~ "submodule" ]]; then
    git submodule init
    git submodule update --remote
    exit 0
fi


# Создание объектного файла библиотеки для работы с UTF-8
if [[ $1 =~ "lib" ]]; then
    gcc -O2 -c lib/libutf8/src/utf8_func.c -o obj/utf8_func.o
    exit 0
fi


# Обработка флагов компиляции программы
FLAGS=""

if [[ $1 =~ "debug" ]]; then
    FLAGS+=$CFLAGS
    FLAGS+=" -DDEBUG"
fi

if [[ $1 =~ "release" ]]; then
    FLAGS+=" -O2"
fi

if [[ $2 =~ "speak" ]]; then
    FLAGS+=" -DSPEAKER"
fi

# Создание объектных файлов акинатора
gcc $FLAGS -c src/main.c     -o obj/main.o
gcc $FLAGS -c src/akinator.c -o obj/akinator.o

# Создание исполняемого файла игры
gcc $FLAGS obj/*.o -o bin/Akinator
