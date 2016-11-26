#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "functions.h"







//HANDLE WINAPI CreateConsoleScreenBuffer(DWORD,DWORD,CONST SECURITY_ATTRIBUTES*,DWORD,LPVOID);


int main(){
    int i,counter = 0;
    char ch;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    char** grid;
    grid = malloc(ROWN * sizeof(char*));
    for(i = 0;i< ROWN;i++){
        grid[i] = malloc(COLN * sizeof(char));
    }

    SetConsoleTitleA("GAME OF LIFE");
    //SetConsoleActiveScreenBuffer(hConsole);

    while(1){
        system("cls");
        SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|BACKGROUND_BLUE);
        printf("GAME OF LIFE BY SURAJ THAKURI\n");
        display(grid);
        printf("Press any key to start");
        getch();
        system("cls");


        printf("Press 'y' to use a grid file OR any other key to draw a new grid:\n");
        ch = getch();

        if(ch == 'y'){
            inputGrid(grid);
        }
        else{
            drawGrid(grid);
        }


       // drawGrid(grid);
        system("cls");
        display(grid);

        printf("Enter y to save the grid OR any other key not to save it:\n");
        ch = getch();

        if(ch == 'y'){
            saveGrid(grid);

        }



        system("cls");
        display(grid);
        printf("Press any key to start\n");
        system("cls");


        gameoflife(grid);
    }

    free(grid);
    return 0;

}
