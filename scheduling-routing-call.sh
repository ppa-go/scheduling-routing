#!/bin/bash
# Vérification du nombre de paramètres (erreur #1)
if [ $# -eq 3 -o $# -eq 4 ]
then
# Le premier paramètre doit être un fichier exécutable (erreur #2)
	if [ -x $1 ]
	then
# Le second paramètre doit être un dossier (erreur #3)
		if [ -d $2 ]
		then
# Le troisième paramètre doit être un dossier, éventuellement à créer
# Le troisième paramètre ne doit pas être un fichier (erreur #4)
			if [ ! -f $3 ]
			then
# Si le troisième paramètre représente un dossier à créer, alors il faut le créer
				if [ ! -d $3 ]
				then
					echo
					echo "Creation du dossier \"$3\" : En cours"
					mkdir $3
# Vérification de la création du dossier représenté par le troisième paramètre (erreur #5)
					if [ -d $3 ]
					then
						echo "Creation du dossier \"$3\" : OK"
# Gestion de l'erreur #5
					else
						echo "*** Erreur : echec lors de la creation du dossier \"$3\" ***"
						exit
					fi
				fi
# Lancement du programme sur tous les fichiers d'instance
				input_prefix="$2/I_"
				output_prefix="$3/S_"
				extension=".txt"
				input_prefix_length=`echo $input_prefix | wc -c`
				echo
				for input in $input_prefix*$extension
				do
					echo "Instance : \"$1\""
					input_length=`echo $input | wc -c`
					suffix_length=$((input_length - input_prefix_length))
					output=$output_prefix`echo $input | tail -c $suffix_length`
					if [ $# -eq 3 ]
					then
						./$1 $input $output
					else
						./$1 $input $output $4
					fi
					echo "Termine !"
					echo
				done
# Gestion de l'erreur #4
			else
				echo "*** Erreur : \"$3\" existe mais n'est pas un dossier ! ***"
			fi
# Gestion de l'erreur #3
		else
			echo "*** Erreur : \"$2\" n'existe pas ou n'est pas un dossier ! ***"
		fi
# Gestion de l'erreur #2
	else
		echo "*** Erreur : le fichier \"$1\" n'est pas executable ! ***"
	fi
# Gestion de l'erreur #1
else
	echo "Invocation du programme :"
	echo "$0 nom_executable nom_dossier_instances nom_dossier_solutions [nombre_mutations]"
	echo "	nom_executable       	Nom du fichier executable associe au programme \"scheduling-routing\""
	echo "	nom_dossier_instances	Nom du dossier contenant les instances"
	echo "	nom_dossier_solutions	Nom du dossier dans lequel ecrire les solutions"
	echo "	nombre_mutations     	[optionnel] Nombre de mutations par iteration (le meme pour toutes les instances)"
	echo "Nommage des fichiers d'instance :	I_*.txt"
fi
