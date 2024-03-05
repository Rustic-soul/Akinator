
. ./flags

PATH_START_TREE="data/basedata.txt"
PATH_NEW_TREE="data/basedata.txt"
PATH_NEW_GRAPH="graphiz/newgraph.dot"

cd ../

if [[ $1 =~ "p" ]]; then
    gcc $CFLAGS src/*.c -o bin/main -lmystack_without_info && \
    ./bin/main $PATH_START_TREE $PATH_NEW_TREE $PATH_NEW_GRAPH  
fi 

if [[ $1 =~ "g" ]]; then
    dot -Tsvg graphiz/graph.dot > graphiz/graph.svg
fi 

if [[ $1 =~ "f" ]]; then
    firefox graphiz/graph.svg
fi 
