#include <stdio.h>
#include <stdlib.h>

/* Sac à dos */


//procedure qui calcule le max entre deux valeurs

int max(int a, int b){

  if(a > b) {return a;}
  else{return b;}
}


//algo en lui-meme

int sacADos(int W, int* poids, int* utilite, int nbObjets){ //W represente la capacite max du sac

// tableau central de la programmation dynamique
int tab[nbObjets][W+1]; 
int w;

//initialisation de la table
for (w = 0; w < W + 1; w++){
  tab[0][w] = 0;
    }

//remplissage de la table selon les formules de la prog dyn
 int i, j;
 for (i = 1; i < nbObjets ; i++){
  for (j = 0; j < W + 1 ; j++) {
    if (j >= poids[i]) {
      tab[i][j] = max(tab[i-1] [j], (tab[i-1] [j-poids[i]] + utilite[i]));
    }
      else{
      tab[i][j] = tab[i-1] [j];
      }
    }
  }
//la valeur qui nous interesse
 printf(" poids : %d \n", W);
 printf("meilleure solution (utilite) : %d \n", tab[nbObjets -1] [W]);
 return (tab[nbObjets -1] [W]);
}


/* Partition */

int partition(int* poids, int nbObjets){ 


//calcul de la somme totale des poids
 int i, j;
int N = 0;
for(i = 0; i < nbObjets; i++ ) {N += poids[i];}

int tab[N]; 

//initialisation de la table de booleens

 tab[0] = 1;
 for(i = 1; i <= N; i ++ )  {tab[i] = 0;}


//remplissage de la table selon les formules de la prog dyn

 for(i = 0; i < nbObjets; i++ ){
   for(j = N - poids[i]; j >= 0; j-- ){
     if( tab[j] == 1 ) {
       tab[j + poids[i]] = 1;
     }
   }
 }

//la reponse qui nous interesse
 if(tab[N / 2] == 1){ 
   printf("vrai avec %d \n", N/2);
   }
 else{puts("faux");}

 return tab[N / 2];
}

/* Voyageur de commerce */

//procedure qui calcule le min entre deux valeurs

int min(int a, int b){

  if(a > b) {return b;}
  else{return a;}
}

//procedure qui calcule le min d'un tableau

int minT(int** tab, int taille){

  int i, j;
  int minimum = tab[0][0];
  for(i = 0; i < (taille - 1); i++){

    for(j = 0; j < taille; j++){ 

    minimum = min(tab[i][j], tab[i+1][j]);

    }

  }

  return minimum;

}

//algo du voyageur de commerce en lui-mêm

int salesman(int** poids, int nbObjets){ 
  int i, k, j, s;

  int C[nbObjets][nbObjets];

  //initialisation du tableau (avec de grosses valeurs pour les cases)

  for(i = 0; i < nbObjets; i++){

    for(j = 0; j < nbObjets; j++){

      C[i][j] = 9999999;

    }

  }

  //initialisation de la première ligne (cas de base récurrence)

  for(i = 1; i < nbObjets; i++){

    C[0][i] = poids[0][i];
  
  }
  
  //remplissage du tableau

  for(i = 1; i < nbObjets; i++){

    for( s = 2; s < nbObjets; s ++){

    if(s != i){
      C[s][i] = C[s-1][i] + poids[i][0];
    }
    
    }

  }

  //la valeur qui nous intéresse
  return minT(C, nbObjets);

}


int main(){

  /* instance sac a dos : on veut maximiser l'utilite */

  int n = 7;
  int W = 2;
  int p[n];
  int u[n];

  p[0] = 3; p[1] = 5; p[2] = 1; p[3] = 5; p[4] = 7; p[5] = 2; p[6] = 6;

  u[0] = 2; u[1] = 5; u[2] = 3; u[3] = 3; u[4] = 6; u[5] = 2; u[6] = 4; 


  puts("debut resolution sac a dos");

  sacADos(W, p, u, n);

  puts("fin resolution sac a dos");

/* instance partition : on veut savoir si on peut partager en deux*/

  int nPart = 2;
  int pPart[nPart];
  
  pPart[0] = 5; pPart[1] = 5; 
  
  puts("debut resolution partition");
  
  partition(pPart, nPart);

  puts("fin resolution partition");
  
/* instance voyageur de commerce : on veut minimiser la valeur du circuit hamiltonien */

//Remarque : tsp symétrique

  int nTSP = 3;

  int** pTSP[nTSP][nTSP];

  pTSP[0][0] = 0; pTSP[0][1] = 4; pTSP[0][2] = 3; 
  pTSP[1][0] = 4; pTSP[1][1] = 0; pTSP[1][2] = 3;
  pTSP[2][0] = 6; pTSP[2][1] = 3; pTSP[2][2] = 0;
 

  puts("debut resolution TSP");
  
  salesman(pTSP, nTSP);

  puts("fin resolution TSP ");

}
