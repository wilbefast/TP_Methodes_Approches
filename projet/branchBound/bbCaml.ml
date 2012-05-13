Require : un sommet racine, une borne inférieure, un graphe G
1 : faire ACPM G − {x}
2 : relier x à ses deux voisins les plus proches en terme de coût
3 : if valeur du cycle > borne inférieure then
4:
if tous les sommets sont de degré 2 then
5:
mettre à jour le solution courante
6:
else
7:
choisir un sommet y de degré ≥ 2
8:
for chaque arête ei issue de y do
9:
G′ := G − {ei }
10 :
BranchAndBound(y, borne inférieure, G′ )
11 :
end for
12 :
end if
13 : end if
14 : retourner la plus petite des solutions acceptables

	 open 
