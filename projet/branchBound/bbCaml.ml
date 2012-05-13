open Graph.Pack.Graph

(* fonctions de comparaison *)

let compare f a b = f a - f b

let compareValeur = compare int

let min l = List.hd (List.sort compareValeur l)

	 (* relie x à ses deux voisins les plus proches en terme de coût*)
	 let relier x g =

(* calcule la valeur d'un cycle *)

	   let valeurCycle g =

(* vérifie si tous les sommets sont de degré 2 *)

	     let tousDegre2 g =

(* choisi un sommet de degré > 2 *)

	       let choixSup2 g = 

(* fonction qui enlève une arete e d'un graphe et fait le branchement dessus à partir de x*)

		 let rec branche e g x borneInf solution = 
		   remove_edge_e g e
		     branchBound g x borneInf solution
		     

(* algorithme de branch and bound en lui même *)
		     
		 and  branchBound g x borneInf solution = 
		   remove_vertex g x
	 let arbre = spanningtree g in
	 let cycle = relier x g in
	 let val = valeurCycle cycle in
	 if val > borneInf then 
	   if tousDegre2 cycle then
	     solution = val
	   else
	     let y = choixSup2 g in
	     let aretesSucc = succ_e g y in 
	     let listeSolutions = map branche aretesSucc in
	 else()
	   solution = min listeSolutions
	     return solution
	     



	   
