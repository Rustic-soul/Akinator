. ./flags

PATH_START_TREE="data/basedata.txt"
PATH_NEW_TREE="data/basedata.txt"
PATH_NEW_GRAPH="graphiz/newgraph.dot"

cd ..

if [[ $1 =~ "o" ]]; then
    gcc -c src/main.c -o obj/main.o
    gcc -c src/akinator.c -o obj/akinator.o
fi


if [[ $1 =~ "p" ]]; then
    gcc obj/*.o -o bin/akinator
    bin/akinator $PATH_START_TREE $PATH_NEW_TREE $PATH_NEW_GRAPH  
fi

if [[ $1 =~ "g" ]]; then
    dot -Tsvg graphiz/graph.dot > graphiz/graph.svg
fi 

if [[ $1 =~ "f" ]]; then
    firefox graphiz/graph.svg
fi 
