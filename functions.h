#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "define.h"
#include <windows.h>




void display(char** grid);
void saveGrid(char** grid);
void inputGrid();




//game of life Computation Function

void gameoflife(char** grid){
    int irow,icol,frow,fcol,i,j,k,row,col; //Here irow and icol are left boxes and frow and fcol are right boxes
    int neighbours;
    int gnCtr=0;
    int key;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);




    /*Copy present grid to temporary grid to simulate complete singular life*/
    char** temp_grid;
    temp_grid = malloc(ROWN * sizeof(char*));
    for(i = 0;i< ROWN;i++){
        temp_grid[i] = malloc(COLN * sizeof(char));
    }

    if(temp_grid == NULL){
        printf("Out of heap memory");
    }
    while(1){
        /*Copy present grid to temporary grid to simulate complete singular life*/
        for(i = 0;i < ROWN; i++  ){
                for(j = 0; j < COLN; j++  ){
                     temp_grid[i][j]= grid[i][j];
                }
        }



    /*traverse each element in temp grid to check for their states and change accordingly in original grid*/
    for(row = 0;row < ROWN;row++ ){
        for(col = 0;col < COLN;col++){


                    neighbours = 0; //reset no. of neighbours


                    irow = row-1;
                    icol = col-1;
                    frow = row + 1;
                    fcol = col + 1;

                    /* This is tho eliminate out of boundary checking*/
                    if(irow < 0 ){
                        irow = irow + 1  ;
                    }
                    if(icol < 0 ){
                        icol = icol + 1;
                    }
                    if(frow > (ROWN-1) ){
                        frow = frow - 1;
                    }
                    if(fcol > (COLN-1) ){
                        fcol = fcol - 1;
                    }



                    /*This is the part where the checking is implemented*/
                    for(i = irow; i <=frow; i++  ){
                        for(j = icol; j <=fcol; j++){
                              if(temp_grid[i][j] == LIVE ){
                                neighbours = neighbours + 1;
                              }
                        }
                    }

            if(temp_grid[row][col] == LIVE ){

                        if((neighbours-1) < 2) {
                            grid[row][col] = DEAD;

                        }
                        else if ((neighbours-1) > 3){
                            grid[row][col] = DEAD;
                        }
                        else{
                            grid[row][col] = LIVE;
                        }
            }
            if(temp_grid[row][col] == DEAD){
                    if(neighbours == 3){
                        grid[row][col] = LIVE;
                    }
                    else{
                        grid[row][col] = DEAD;
                    }
            }
        }
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN );
    printf("Generation: %d\n\n",gnCtr++);
    printf("Press q to stop or key to pause\n");
    display(grid);

     if(kbhit()){
        key = getch();
        if(key=='q'){break;}
        getch();
     }
    }
    free(temp_grid);

}



///DISPLAY GRID
void display(char** grid){


    int i;
    int j;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos;
    pos.X=0;
    pos.Y=0;

    WORD fColor;

    //seed for random color
    srand(time(0));

    SetConsoleCursorPosition(hConsole,pos);



    for( i = 0; i < ROWN; i++){
        for(j = 0; j < COLN; j++){

            fColor = rand()%15 + 1;


            if(grid[i][j] == DEAD ){
                SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
                putchar(space);
                //putchar(' ');

            }
            else if(grid[i][j] == LIVE){
                SetConsoleTextAttribute(hConsole,fColor| BACKGROUND_BLUE);
                putchar(on);
                //putchar(' ');
            }
            else{}
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN );

        putchar('\n');
    }
}




///SAVE GRID TO FILE
void saveGrid(char** grid){


    int i;
    int j;
    char reader;
    int val;
    char choice;
    FILE* fp;

    char filename[100];
    printf("Enter the name of the file you want to save the grid to:\n");
    gets(filename);

    fp = fopen(filename,"w");
    if(fp == NULL ){
        fprintf(stderr,"The grid file you enterred doesn't exist!!!\nDo you want to create one?(y/n)");
        return;

    }
        for( i = 0; i < ROWN; i++){
            for(j = 0; j < COLN; j++){
                reader = grid[i][j];

                fputc(reader,fp);
            }
        }
     printf("Grid saved to file %s\n",filename);
     printf("Press any key to load the file\n");
     getch();
     fclose(fp);

}


///DRAW A CUSTOM GRID
void drawGrid(char** grid){

    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    char key;
    COORD pos;
    COORD footer;
    int x=0,y=0;
    int i,j;

    int pen = 0;
    //int eraser = 0;



    //initialize blank grid
    for(i=0;i<ROWN;i++){
        for(j=0;j<COLN;j++){
            grid[i][j]=DEAD;
        }
    }
    display(grid);



    pos.X = 0;
    pos.Y = 0;

    footer.X = 0;
    footer.Y = ROWN+1;

    SetConsoleCursorPosition(hConsole,footer);
    printf("DRAW THE GRID\n");
    printf("Press p to turn the pen ON/OFF\n");
    printf("Press q to stop\n");


    SetConsoleCursorPosition(hConsole,pos);

    while(1){
        SetConsoleCursorPosition(hConsole,pos);
        if(kbhit()){


                    key = getch();

                     if(key=='q'){
                        break;
                     }

                    //Logic to move the cursor
                    switch(key){
                        case 'w': y--;break;
                        case 's': y++;break;
                        case 'a': x--;break;
                        case 'd': x++;break;
                        case 'p':
                        default:break;
                    }
                    if(x>=0){
                        pos.X = abs(x%COLN);
                    }
                    else{
                        pos.X = COLN - (abs(x%COLN));
                    }
                    if(y>=0){
                        pos.Y = abs(y%ROWN);
                    }
                    else{
                        pos.Y = ROWN - (abs(y%ROWN)+1);
                    }

                    //SetConsoleCursorPosition(hConsole,pos);
                    //SetConsoleTextAttribute(hConsole,BACKGROUND_RED);

                    //putchar('D');


                    if(key=='p'){
                        if(pen==1){
                            pen = 0;
                        }
                        else{
                            pen =1;
                        }
                    }

                    if(pen == 1){
                            SetConsoleCursorPosition(hConsole,pos);
                            SetConsoleTextAttribute(hConsole,BACKGROUND_GREEN);
                            putchar(on);
                                //print LIVE on the grid
                            grid[pos.Y][pos.X] = LIVE;
                    }
                    else{
                            if(grid[pos.X][pos.Y] == LIVE){
                                SetConsoleCursorPosition(hConsole,pos);
                                SetConsoleTextAttribute(hConsole,BACKGROUND_GREEN);
                                putchar(on);
                            }
                            else{
                                SetConsoleCursorPosition(hConsole,pos);
                                SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE);
                                putchar(space);
                            }
                    }
                }

    }
}


///INPUT GRID FROM SAVED GRID FILE
void inputGrid(char** grid){


    int i;
    int j;
    char reader;
    int val;
    char choice;
    FILE* fp;

    char filename[100];
    while(1){
        system("cls");
        printf("Enter the name of the gridFile you want to open:\n");
        gets(filename);

        fp = fopen(filename,"r");
        if(fp == NULL ){
            fprintf(stderr,"The grid file you enterred doesn't exist!!!\n");
            fprintf(stderr,"Press any key to enter again....\n");
            getch();
        }
        else{
            break;
        }
    }
    for( i = 0; i < ROWN; i++){
        for(j = 0; j < COLN; j++){
            reader = fgetc(fp);
            grid[i][j] = reader;

            if(reader == '\n'){
                fgetc(fp);
            }

        }
    }
    fclose(fp);

}







#endif // _FUNCTIONS_H_
