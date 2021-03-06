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
	   let graphe = create in
	   fold add_edge_e graphe gbis
	     add_edge_e graphe arete1
	     add_edge_e graphe arete2
	     
	   
(* fonction qui somme les éléments d'une liste d'entiers *)
let rec somme = List.fold_left (+) 0

	   (* calcule la valeur d'un cycle *)
  
	 let valeurCycle g = somme (map label List.append(map_vertex succ_e v g))
	   
	     (* vérifie si un sommet v est de degré supérieur 2 *)
	   
	     let sup2 v g = out_degree g v > 2

(* vérifie si tous les sommets sont de degré 2 : ne marche pas *)

	     let tousDegre2 g = not (exists sup2 g);;

(* renvoi un sommet de degré > 2 s'il existe *)

	     let sommetSup2 v g = if out_degree g v > 2 then v else ();; 	       

(* choisi un sommet de degré > 2 *)

	     let choixSup2 g = List.hd (map_vertex sommetSup2 g);;
	       

(* algorithme de branch and bound en lui même *)
		     
	     let rec branchBound g x borneInf solution = 
	       let g' = copy g in
	       remove_vertex g x
	     let cycle = bellman_ford (relier x g'(spanningtree g)) x in
	     let valeur = valeurCycle cycle in
	     if valeur > borneInf then 
	       if tousDegre2 cycle then
		 solution = valeur
	       else
		 let y = choixSup2 g in
		 let aretesSucc = succ_e g y in 
		 let listeSolutions = map branche aretesSucc in
	     else()
	       solution = min listeSolutions
		 
		 
	     (* fonction qui enlève une arete e d'un graphe et fait le branchement dessus à partir de x *)
		 
	     and branche e g x borneInf solution = 
	       remove_edge_e g e;;
	     branchBound g x borneInf solution;;
	     
	     
	     (*
	      * Les tests !
 *)
	     
	     let g = Rand.graph ~v:10 ~e:20 ()
	     let () = show g
	     let beforeBB = Sys.time ()
	       let_ = branchBound g 3 1 1
	     let afterBB = Sys.time ()
	     let _ =
	       Printf.printf   "BranchBound : %f\n"
                 (afterBB -. beforeBB)
		 
