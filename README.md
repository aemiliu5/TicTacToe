# TicTacToe
> A simple Tic-Tac-Toe game played entirely through the command line, written in C.

Currently tested and working on Windows and Linux.

## Compilation
Compilation in Windows should be straightforward.  
Compilation in Linux is done through the following command: `gcc ttt.c -o ttt -lncursesw`.

## Troubleshooting
In case of an error message saying you don't have the <curses.h> file, you can use the following command on Ubuntu:
```sudo apt-get install libncursesw5-dev libncurses-dev ncurses-dev``` then update and upgrade your packages.

On other distributions, try searching for the curses library on the package manager of your choice.