@echo off
REM Включение файла с флагами компиляции для DEBUG режима
call .\flags

REM Переход в главную директорию akinator/
cd ..

REM Запуск игры
IF %1 == "-play" (
    bin\Akinator
    exit /B 0
)

REM Создание картинки с деревом акинатора
IF %1 == "-picture" (
    setlocal enabledelayedexpansion
    for /F "delims=" %%A in ('type graphviz\graph_cur.dot') do set FIRST_LINE=%%A
    endlocal
    if not "%FIRST_LINE:~0,7%" == "digraph" (
        more +1 graphviz\graph_cur.dot > graphviz\graph_cur.tmp
        move /Y graphviz\graph_cur.tmp graphviz\graph_cur.dot
    )
    dot -Tsvg graphviz\graph_cur.dot > graphviz\graph.svg
    exit /B 0
)

REM Инициализация подмодулей проекта
IF %1 == "-submodule" (
    git submodule init
    git submodule update --remote
    exit /B 0
)

REM Создание объектного файла библиотеки для работы с UTF-8
IF %1 == "-lib" (
    gcc -O2 -c lib\libutf8\src\utf8_func.c -o obj\utf8_func.o
    exit /B 0
)

REM Обработка флагов компиляции программы
SET FLAGS=""

IF "%1" == "-debug" (
    SET "FLAGS=%CFLAGS% -DDEBUG"
)

IF "%1" == "-release" (
    SET "FLAGS=-O2"
)

IF "%2" == "-speak" (
    SET "FLAGS=%FLAGS% -DSPEAKER"
)

REM Создание объектных файлов акинатора
gcc %FLAGS% -c src\main.c -o obj\main.o
gcc %FLAGS% -c src\akinator.c -o obj\akinator.o

REM Создание исполняемого файла игры
gcc %FLAGS% obj\*.o -o bin\Akinator
