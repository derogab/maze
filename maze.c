/*
IL LABIRINTO DI MINOSSE

Obiettivo:
Sviluppare l'analisi e definire le procedure necessarie alla soluzione del seguente problema.
Il computer deve simulare di trovarsi all'interno di un labirinto di dimensioni prefissate e a scelta del candidato e a aggiungere l'eventuale/i uscita/e specificando il traagitto più breve anche in modo grafico. IL labirinto può prevedere piazze (cioè zone ampie in cui è possibile l'accesso o strade cieche) è necessario prevedere il labirinto non abbia uscite, cioè ancora cieco.
Il candidato forniti gli ulteriori dettagli necessari per lo sviluppo dell'analisi del problema, sviluppi con un linguaggio a sua scelta l'applicazione che risolvi l'esercizio.
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
      printf("Inserisci quanto e' lungo il labirinto da %d a %d:\n",MIN,MAX);
      scanf("%d",&l);
  }while(l<MIN||l>MAX);
  riempilabirinto(lab,l);
  randfinish(&finex,&finey,lab,l);
  printf("LABIRINTO INIZIALE:\n");
  stampalabirinto(lab,l);
  posiziona(&sx,&sy,lab,l);
  system("cls"); // Clear the screen
  title();
  printf("\n\n");
  stampalabirinto(lab,l);
  printf("\nPremi per risolvere il labirinto! "); system("pause");
  
  dirigi(lab,sx,sy,l,0); //Start: position 0,0
    
  if(trovato==TRUE){ //End: stampo il labirinto minore con il numero dei passi utilizzati se lo ho risolto.
	system("cls"); // Pulisco lo schermo per poi far stampare il labirinto risolto
    title();
    printf("\nLABIRINTO RISOLTO:\n");
    stampalabirinto(min,l); printf("\n\nHo selezionato per te il percorso piu' veloce tra %lld percorsi possibili.\nPer raggiungere la fine bastano soltanto %d passi.\n\n",percorsi,passi);
  }
  else{
	  printf("Nessun percorso trovato per risolvere questo labirinto.\n\n");
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
        if(dove==1){  // Su che lato è la fine?
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
				printf("%s","x");  //Percorso
			 }
			 else{
				if(mat[i][j]==START){
					printf("%s","S");  //Inizio
				}
				else{
					if(mat[i][j]==FINE){
						printf("%s","F");  //Fine
					}
					else{ 
						printf("%s",".");  //Spazio Vuoto
					}
				}
			 }
		 }
		 else{ printf("%s","#"); } //Muro          
     }        
     printf("|\n");    
  }
  printf("|"); for(i=0;i<l;i++){ if(j==l){ printf("-"); }  } printf("|");
  printf("\n\n");  
}

void posiziona(int *x, int *y, int mat[MAX][MAX], int l){
    do{
        printf("Inserisci la riga da cui partire: ");
        scanf("%d",x);  *x=*x-1;
        printf("Inserisci la colonna da cui partire: ");
        scanf("%d",y);  *y=*y-1;
        if(mat[*x][*y]==MURO){ printf("\nLa cella selezionata \212 un muro.\n"); }
        if((*x>=l)||(*y>=l)||(*x<0)||(*y<0)){ printf("\nLa cella selezionata \212 fuori dal labirinto.\n"); }
        if(mat[*x][*y]==FINE){ printf("\nLa cella selezionata \212 la FINE!.\n"); }
    }while((mat[*x][*y]==MURO)||(mat[*x][*y]==FINE)||((*x>=l)||(*y>=l)||(*x<0)||(*y<0)));
    mat[*x][*y]=START;
}

void dirigi(int mat[MAX][MAX], int x, int y, int l, int cont){	
	int nuovo_percorso = FALSE;
	if((x<l)&&(y<l)&&(x>=0)&&(y>=0)&&(mat[x][y]!=PERCORSO)&&(mat[x][y]!=MURO)){  // Controllo se il punto è nel labirinto o se c'è un muro o se sono già passato
		if((mat[x][y]!=FINE)&&(mat[x][y]!=START)){ mat[x][y]=PERCORSO; }
        nuovo_percorso = TRUE;
		if(mat[x][y]==FINE){  // Controlla se sono arrivato alla fine
			trovato = TRUE;
			percorsi++;
			if(cont<passi){ // Controllo se il percorso trovato è il più corto tra quelli trovati.
				passi=cont;
				copiamatrice(mat,min,l);
			}
		}
		else{
			dirigi(mat,x+1,y,l,cont+1);	//SUD
			dirigi(mat,x,y+1,l,cont+1);	//EST
			dirigi(mat,x-1,y,l,cont+1);	//NORD
			dirigi(mat,x,y-1,l,cont+1);	//OVEST	
		}	
	}

	if(nuovo_percorso==TRUE){ // Controllo se la briciola è stata messa adesso o in un viaggio precedente
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
