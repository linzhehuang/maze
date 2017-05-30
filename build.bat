@echo off
set target=maze.exe
set sources=map.c bfs.c dijkstra.c interface.c callback.c
set cflags=`pkg-config --libs --cflags gtk+-3.0`
set cmd_show=-mwindows

if exist %target% (
  del *.exe
)
echo Building...
sh -c "gcc -o %target% %sources% %cflags% %cmd_show%"
if exist %target% (
  cls
  %target%&exit
) else (
  echo Error
  pause>nul
)