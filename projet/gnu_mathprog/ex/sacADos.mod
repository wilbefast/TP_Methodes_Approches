#modele de sac a dos
#donnees
param n ; #nombre d’objets
param C{i in 1..n}; #utilite de l’objet i
param A{i in 1..n}; #poids de l’objet i
param B; #capacite du sac
#variables
var x{1..n} binary;
#objectif
maximize f :sum {i in 1..n} C[i]*x[i] ;
#contraintes
subject to
capacite : sum{i in 1..n} A[i]*x[i] <= B ;
printf "------Debut de la resolution -----\n";
solve;
printf "------Fin de la resolution -----\n";
display x;
end;
