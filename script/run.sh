
. ./flags

cd ../
gcc $CFLAGS src/*.c -o bin/main -lmystack_with_info && ./bin/main 

