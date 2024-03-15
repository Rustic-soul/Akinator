
# Включение файла с флагами компиляции для DEBUG режима 
. ./flags

# Переход в главную директорию akinator/
cd ..

if [[ $1 =~ "od" ]]; then
    cd src/
    gcc $CFLAGS -c main.c     -o ../obj/main.o
    gcc $CFLAGS -c akinator.c -o ../obj/akinator.o
    cd ..
    gcc $CFLAGS obj/*.o -o bin/akinator
fi

if [[ $1 =~ "or" ]]; then
    cd src/
    gcc -O2 -c main.c     -o ../obj/main.o
    gcc -O2 -c akinator.c -o ../obj/akinator.o
    cd ..
    gcc -O2 obj/*.o -o bin/akinator
fi

if [[ $1 =~ "p" ]]; then
    bin/akinator  
fi

if [[ $1 =~ "g" ]]; then
    dot -Tsvg graphiz/graph.dot > graphiz/graph.svg
fi 

if [[ $1 =~ "f" ]]; then
    firefox graphiz/graph.svg
fi 
