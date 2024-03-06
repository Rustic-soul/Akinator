cd ..

set PATH_START_TREE=data\basedata.txt
set PATH_NEW_TREE=data\basedata.txt
set PATH_NEW_GRAPH=graphiz\newgraph.dot

chcp 65001
bin\akinator.exe %PATH_START_TREE% %PATH_NEW_TREE% %PATH_NEW_GRAPH%
