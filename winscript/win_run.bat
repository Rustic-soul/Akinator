
:: Работа со стэком
cd ..
:: Подключение дополнительного модуля - stack
git submodule init 
git submodule update

:: Изменение конфигурации stack
copy include\stack.h stack\include\

:: Создание объектного файла stack.o
cd stack\src
gcc -c stack.c -o ..\..\obj\stack.o
cd ..\..\scripts

:: Сборка акинатора
cd ..

gcc -c src\main.c -o obj\main.o
gcc -c src\akinator.c -o obj\akinator.o

gcc obj\stack.o obj\main.o obj\akinator.o -o bin\akinator.exe

