for chaque arête ei issue de y do
9:
G′ := G − {ei }
10 :
BranchAndBound(y, borne inférieure, G′ )

	 open Graph.Pack.Graph

	 (* relie x à ses deux voisins les plus proches en terme de coût*)
	 let relier x g =

(* calcule la valeur d'un cycle *)

	   let valeurCycle g =

(* vérifie si tous les sommets sont de degré 2 *)

	     let tousDegre2 g =

(* choisi un sommet de degré > 2 *)

	       let choixSup2 g = 

(* algorithme de branch and bound en lui même *)

	       let rec branchBound g x borneInf solution = 
	     remove_vertex g x
	 let arbre = spanningtree g in
	 let cycle = relier x g in
	 let val = valeurCycle cycle in
	 if val > borneInf then 
	   if tousDegre2 cycle then
	     solution = val
	   else
	     let y = choixSup2 g in

	 else()
	   
	   return solution




	   
