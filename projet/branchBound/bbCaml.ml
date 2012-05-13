(* Pour compiler pr de vrai : ocamlc nomdufichier.ml Graph.cma 
 * Pour compiler : ocaml nomdufichier.ml 
 * Pour exécuter : ocaml nomdufichier.cmo
 * puis open Nomdufichier;; et taper les fctions qu'on veut exécuter
 *)

open Graph.Pack.Graph
  
(* fonctions de comparaison *)
  
let compare f a b = f a - f b

let compareLabel f a b = f (label a) - f (label b)  

let compareValeur = compare int
  
let min l = List.hd (List.sort compareValeur l)

	 (* relie x à ses deux voisins les plus proches en terme de coût*)
  
	 let relier x g gbis=
	   let listAretes x g = succ_e x g in
	   let listTriee = List.sort compareLabel listAretes in
	   let arete1 = List.hd listTriee in
	   let arete2 = List.hd (List.tl listTriee) in
	   add_edge_e gbis arete1
	   add_edge_e gbis arete2
	    
	   
(* fonction qui somme les éléments d'une liste d'entiers *)
let rec somme = List.fold_left (+) 0

	   (* calcule la valeur d'un cycle *)
  
	 let valeurCycle g = somme (map label List.append(map_vertex succ_e v g))
	   
	     (* vérifie si un sommet v est de degré supérieur 2 *)
	   
	     let sup2 v g = out_degree g v > 2

(* vérifie si tous les sommets sont de degré 2 : ne marche pas *)

	     let tousDegre2 g = 
	       let listeBool = map_vertex sup2 g in ;;
	     not (exists (fun x -> true) listeBool);;

(* renvoi un sommet de degré > 2 s'il existe *)

	     let sommetSup2 v g = if out_degree g v > 2 then v else ();; 	       

(* choisi un sommet de degré > 2 *)

	     let choixSup2 g = List.hd (map_vertex sommetSup2 g);;

(* fonction qui enlève une arete e d'un graphe et fait le branchement dessus à partir de x *)

	       let rec branche e g x borneInf solution = 
		 remove_edge_e g e;;
	       branchBound g x borneInf solution;;
	       

(* algorithme de branch and bound en lui même *)
		     
		 and  branchBound g x borneInf solution = 
		 let ginit = copy g in;;
	       remove_vertex g x;;
	       let arbre = spanningtree g in;; 
	       let cycle = relier x ginit g in ;;
	       let val = valeurCycle cycle in;;
	       if val > borneInf then 
		 if tousDegre2 cycle then
		   solution = val
		 else
		   let y = choixSup2 g in
		   let aretesSucc = succ_e g y in 
		   let listeSolutions = map branche aretesSucc in
	       else()
		 solution = min listeSolutions
		   
	     



	   
