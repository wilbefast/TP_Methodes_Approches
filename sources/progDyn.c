#include <stdio.h>
#include <stdlib.h>

/* Utilitaires */

//procedure qui calcule le max entre deux valeurs

int max(int a, int b){

  if(a > b) {return a;}
  else{return b;}
}

//procedure qui calcule le min entre deux valeurs

int min(int a, int b){
  
  if(a > b) {return b;}
  else{return a;}
}

//procedure qui calcule le min d'un tableau 

int minT(int** tab, int taille, int* colonne, int ligne){
  
  int j;
  
  int minimum = tab[ligne][0];
  
  for(j = 0; j < taille; j ++){
    
    if(tab[ligne][j] < minimum) {
      minimum = tab[ligne][j];
      *colonne = j;
    }
  }
  return minimum;
}

//allocation dynamique

int** multi_malloc(size_t dim1, size_t dim2) { 
  size_t i; 
  int** tab = malloc(sizeof *tab * dim1); 
  tab[0] = malloc(sizeof *tab[0] * dim1 * dim2); 
  for(i = 1; i < dim1; i++) {
    tab[i] = tab[i-1] + dim2; 
  }
  return tab;
}

//désaloccation
void multi_free(int** tab){ 
  free(tab[0]); 
  free(tab);
}

/* Sac à dos */

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

//extraction du minimum dans la matrice de poids + recuperation du pere

int minExtract(int** poids, int** pere, int k, int l, int nbObjets, int val){
  
  int i, j;
  // au dernier tour, cad qd l = nbObjets, on a le droit de prendre le sommet 0 
  //on verifiera egalement qu'on ne prend pas un sommet deja choisi
  int mini = 9999999;
  
  for(j = 0; j < nbObjets; j ++){
    
    for (i = 0; i < nbObjets; i ++){	
      
      if(pere[k][i] != j &&  l !=  nbObjets && j != 0){
	mini = min(mini, poids[val][j]);
      }
      else if (pere[k][i] != j &&  l ==  nbObjets){
	mini = min(mini, poids[val][j]);
      }
    }
  }
  pere[k][val] = j;	
  return mini;
}


//algo du voyageur de commerce en lui-meme

int salesman(int** poids, int nbObjets){ 
  int i, k, j;
  
  //allocation des tableaux
  
  int** C = multi_malloc(nbObjets, nbObjets);
  int** pere = multi_malloc(nbObjets - 1, nbObjets);  //la premiere dimension désigne le chemin
  
  //initialisation de la premiere ligne (cas de base recurrence)
  
  for(i = 1; i < nbObjets; i ++){
    
    C[0][i] = poids[0][i];
    C[i][i] = 99999;
    
  }
  
  //initialisation du tableau des peres : on decide que le pere du premier objet est lui meme
  
  for( i = 0; i < nbObjets - 1; i++){
    
    for( j = 0; j < nbObjets; j++){
      if(j == i+1){
	pere[i][j] = i+1;
      }
      else{
	pere[i][j] = -1;
      }
    }
  }
  
  //remplissage du tableau C
  
  int l;
  
  for(k = 1; k < nbObjets -1 ; k++){ //k designe le chemin
      
    int ancien = pere[k-1][k];
      
    for(l = 1; l < nbObjets; l++){ // 1 car on a deja initialise la ligne 0 avec la base de la recurrence	
	
      C[l][k] = C[l-1][k] + (minExtract(poids, pere, k, l, nbObjets, pere[k-1][ancien])); // le dernier argument est le sommet duquel on part, cad le "pere" de la case d'avant
      ancien = pere[k-1][ancien];
      printf(" C[%d][%d]= %d \n", l, k, C[l][k]);
    }
   
    puts("Tableau tsp rempli");
      
  }
    
  //valeur du plus petit cycle
  int pluspetit, cpt;
  int colonne = 0;
  int old;
  pluspetit = minT(C, nbObjets, &colonne, nbObjets - 1);
  printf("Valeur du cycle : %d \n", pluspetit);
    
  //ordre de parcours des sommets du cylcle
  old = pere[colonne][0]; 
  for(cpt = 0; cpt < nbObjets; cpt ++){
    printf("%d - ", old);
    old = pere[colonne][old];
  }
  printf("\n");
    
  multi_free(C);
  multi_free(pere);
    
  return 1;
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
  
  //Remarque : tsp symetrique
  
  int nTSP = 3;
  
  
  int** pTSP = multi_malloc(nTSP, nTSP);
  
  pTSP[0][0] = 0; pTSP[0][1] = 4; pTSP[0][2] = 3; 
  pTSP[1][0] = 4; pTSP[1][1] = 0; pTSP[1][2] = 3;
  pTSP[2][0] = 3; pTSP[2][1] = 3; pTSP[2][2] = 0;
  
  
  puts("debut resolution TSP");
  
  salesman(pTSP, nTSP);
  puts("tsp appele");
  
  puts("fin resolution TSP ");
  
  multi_free(pTSP);
  
  
  return 0;
  
}
