# Projet de CIR3 - Audran TOURNEUR

# Langage de programmation AUTOUR

Le code compile avec la commande "make" dans ce dossier et est prévu pour un environnement Linux, la SDL est une dépendence requise.
Note : l'utilisation de la SDL via WSL est possible mais non-triviale à cause de l'affichage graphique, il est préférable d'utiliser un vrai système Linux ou bien ou machine virtuelle si WSL ne fonctionne pas.

Ce langage permet de faire des simulations graphiques sur un écran virtuel de 50x50 pixels en faisant appel à la SDL.
Le typage est dynamique.

Le code source est présent dans src/
Les exemples de code écrits dans le langage AUTOUR sont dans demo/

Par défault, l'exemple demo/jeu_de_la_vie.autour est lancé

Après la première invocation de make, l'éxécutable généré "autour" peut être utilisé directement pour lancer les autres exemples de code.
Par exemple :
	./autour demo/jeu_de_la_vie.autour
	./autour demo/colorier.autour
	./autour demo/polynome.autour

De plus, deux vidéos présentes dans le dosiser video/ présentent rapidement toutes les fonctionnalités du langage