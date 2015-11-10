/*
The Maze 
Goal:
The computer has to pretend to be inside a maze of a fixed size, chosen by the user, and to add, if necessary, exit/s, specifying graphically the shortest way. The maze can have squares (places from which it is possible to start or in which there is no way out) and it has to say whether there is or there is not a way out. 
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

// Costants
#define TRUE 1
#define FALSE 0
#define MIN 2
#define MAX 200
#define MURO -2
#define VUOTO -3
#define PERCORSO -4
#define START -5
#define FINE -6
#define MURI 3

// Global variables
int min[MAX][MAX], passi = INT_MAX , trovato = FALSE;
long long int percorsi = 0;

// Prototypes
void title();
void riempilabirinto(int mat[MAX][MAX], int l);
void stampalabirinto(int mat[MAX][MAX], int l);
void randfinish(int *x, int *y, int mat[MAX][MAX], int l);
void posiziona(int *x, int *y, int mat[MAX][MAX], int l);
void dirigi(int mat[MAX][MAX], int x, int y, int l, int cont);
void svuotaultimaposizione(int mat[MAX][MAX],int x, int y);
void copiamatrice(int mat[MAX][MAX], int copy[MAX][MAX], int l);

//Main
int main(){
  int l,lab[MAX][MAX],i,j,sy,sx,finex,finey;
  srand(time(NULL));
  title();
  do{
      printf("Specify how long the maze is from %d to %d:\n",MIN,MAX);
      scanf("%d",&l);
  }while(l<MIN||l>MAX);
  riempilabirinto(lab,l);
  randfinish(&finex,&finey,lab,l);
  printf("THE INITIAL MAZE:\n");
  stampalabirinto(lab,l);
  posiziona(&sx,&sy,lab,l);
  system("cls"); // Clears the screen
  title();
  printf("\n\n");
  stampalabirinto(lab,l);
  printf("\nPress ENTER to solve the maze! "); system("pause");
  
  dirigi(lab,sx,sy,l,0); //Start: position 0,0
    
  if(trovato==TRUE){ //End: prints the shortest way and the number of used steps if the maze has been solved.
	system("cls"); // Clears the screen in order to print then the solved maze.
    title();
    printf("\nMAZE SOLVED:\n");
    stampalabirinto(min,l); printf("\n\nI have picked for you the fastest way of %11d possible solutions.\nTo reach the exit, %d steps will be sufficient.\n\n",percorsi,passi);
  }
  else{
	  printf("No way was found to solve this maze.\n\n");
  }
  
  system("pause");
  return 0;
}

//Funzioni
void title(){
printf("\n\n");
printf(" .----------------.  .----------------.  .----------------.  .----------------. \n");
printf("| .--------------. || .--------------. || .--------------. || .--------------. |\n");
printf("| | ____    ____ | || |      __      | || |   ________   | || |  _________   | |\n");
printf("| ||_   \\  /   _|| || |     /  \\     | || |  |  __   _|  | || | |_   ___  |  | |\n");
printf("| |  |   \\/   |  | || |    / /\\ \\    | || |  |_/  / /    | || |   | |_  \\_|  | |\n");
printf("| |  | |\\  /| |  | || |   / ____ \\   | || |     .'.' _   | || |   |  _|  _   | |\n");
printf("| | _| |_\\/_| |_ | || | _/ /    \\ \\_ | || |   _/ /__/ |  | || |  _| |___/ |  | |\n");
printf("| ||_____||_____|| || ||____|  |____|| || |  |________|  | || | |_________|  | |\n");
printf("| |              | || |              | || |              | || |              | |\n");
printf("| '--------------' || '--------------' || '--------------' || '--------------' |\n");
printf(" +----------------'  '----------------'  '----------------'  '----------------' \n");
printf("\t\tCopyright © 2014 De Rosa, Marta & Gentile\n\n");
}

void riempilabirinto(int mat[MAX][MAX], int l){
	int i,j;
	for(i=0;i<l;i++){
		for(j=0;j<l;j++){
			if((rand()%MURI)==0){ mat[i][j] = MURO; }else{ mat[i][j] = VUOTO; }              
		}             
	}
}

void randfinish(int *x, int *y, int mat[MAX][MAX], int l){
    int dove;
    do{
        srand(time(NULL));
        dove=rand()%2;
        if(dove==1){  // On which side is the exit?
            *x=rand()%l;
            *y=rand()%2;
            if(*y==1){
                *y=l-1;
            }
        }
        else{
            *x=rand()%2;
            *y=rand()%l;
            if(*x==1){
                *x=l-1;
            }
        }
    }while((mat[*x][*y]==MURO)&&((*x>=l)||(*y>=l)||(*x<0)||(*y<0)));
    mat[*x][*y]=FINE;
}

void stampalabirinto(int mat[MAX][MAX], int l){
  int i,j;
  printf("\n "); for(i=0;i<l;i++){ printf("_"); } printf("\n");
  for(i=0;i<l;i++){
     printf("|");
     for(j=0;j<l;j++){ 
         if(mat[i][j]!=MURO){
			 if(mat[i][j]==PERCORSO){
				printf("%s","x");  //Path
			 }
			 else{
				if(mat[i][j]==START){
					printf("%s","S");  //Start
				}
				else{
					if(mat[i][j]==FINE){
						printf("%s","F");  //Exit
					}
					else{ 
						printf("%s",".");  //Blank space
					}
				}
			 }
		 }
		 else{ printf("%s","#"); } //Wall          
     }        
     printf("|\n");    
  }
  printf("|"); for(i=0;i<l;i++){ if(j==l){ printf("-"); }  } printf("|");
  printf("\n\n");  
}

void posiziona(int *x, int *y, int mat[MAX][MAX], int l){
    do{
        printf("Enter the row from which you would like to start: ");
        scanf("%d",x);  *x=*x-1;
        printf("Enter the column from which you would like to start: ");
        scanf("%d",y);  *y=*y-1;
        if(mat[*x][*y]==MURO){ printf("\nThe chosen cell is a wall.\n"); }
        if((*x>=l)||(*y>=l)||(*x<0)||(*y<0)){ printf("\nThe chosen cell is not in the maze.\n"); }
        if(mat[*x][*y]==FINE){ printf("\nThe chosen cell is the EXIT.\n"); }
    }while((mat[*x][*y]==MURO)||(mat[*x][*y]==FINE)||((*x>=l)||(*y>=l)||(*x<0)||(*y<0)));
    mat[*x][*y]=START;
}

void dirigi(int mat[MAX][MAX], int x, int y, int l, int cont){	
	int nuovo_percorso = FALSE;
	if((x<l)&&(y<l)&&(x>=0)&&(y>=0)&&(mat[x][y]!=PERCORSO)&&(mat[x][y]!=MURO)){  // Checks if the point is in the maze o if there is a wall or if I have already passed by.
		if((mat[x][y]!=FINE)&&(mat[x][y]!=START)){ mat[x][y]=PERCORSO; }
        nuovo_percorso = TRUE;
		if(mat[x][y]==FINE){  //Checks if I have reached the exit.
			trovato = TRUE;
			percorsi++;
			if(cont<passi){ // Checks if the chosen path is the shortest of all.
				passi=cont;
				copiamatrice(mat,min,l);
			}
		}
		else{
			dirigi(mat,x+1,y,l,cont+1);	//SOUTH
			dirigi(mat,x,y+1,l,cont+1);	//EAST
			dirigi(mat,x-1,y,l,cont+1);	//NORTH
			dirigi(mat,x,y-1,l,cont+1);	//WEST	
		}	
	}

	if(nuovo_percorso==TRUE){ // Checks if the crumb has been left now or in past.
		svuotaultimaposizione(mat,x,y);
	}
	return;
}

void svuotaultimaposizione(int mat[MAX][MAX],int x, int y){
  if(mat[x][y]==PERCORSO){
	mat[x][y] = VUOTO;
  }
}

void copiamatrice(int mat[MAX][MAX], int copy[MAX][MAX], int l){
   int i,j;
   for(i=0;i<l;i++){
       for(j=0;j<l;j++){
          copy[i][j]=mat[i][j];
       }      
   }    
}
