#!/bin/bash
# Vérification du nombre de paramètres (erreur #1)
if [ $# -eq 2 ]
then
# Le premier paramètre doit être un dossier (erreur #2)
	if [ -d $1 ]
	then
# Le second paramètre doit être un dossier (erreur #3)
		if [ -d $2 ]
		then
# Lancement du programme sur tous les fichiers de solution communs aux deux dossiers
			solution_prefix="S_"
			extension=".txt"
			input_prefix_length_1=`echo $1/$solution_prefix | wc -c`
			counter=0
			counter_diff=0
			for input_1 in $1/$solution_prefix*$extension
			do
				input_length_1=`echo $input_1 | wc -c`
				input_suffix_length=$((input_length_1 - input_prefix_length_1 + 1))
				input_suffix=`echo $input_1 | tail -c $input_suffix_length`
				input_2=$2/$solution_prefix$input_suffix
				if [ -f $input_2 ]
				then
					counter=$((++counter))
					diff_length=`diff $input_1 $input_2 | wc -l`
					if [ $diff_length -ne 0 ]
					then
						counter_diff=$((++counter_diff))
						echo $solution_prefix$input_suffix
					fi
				fi
			done
			if [ $counter -ne 0 ]
			then
				echo "Total = $counter_diff/$counter ($((100*counter_diff/counter))%)"
			else
				echo "Total = 0/0"
			fi
# Gestion de l'erreur #3
		else
			echo "*** Erreur : \"$2\" n'existe pas ou n'est pas un dossier ! ***"
		fi
# Gestion de l'erreur #2
	else
		echo "*** Erreur : \"$1\" n'existe pas ou n'est pas un dossier ! ***"
	fi
# Gestion de l'erreur #1
else
	echo "Invocation du programme :"
	echo "$0 nom_dossier_solutions_1 nom_dossier_solutions_2"
	echo "	nom_dossier_solutions_1	Nom du premier dossier contenant des solutions"
	echo "	nom_dossier_solutions_2	Nom du deuxieme dossier contenant des solutions"
	echo "Nommage des fichiers de solution :	S_*.txt"
fi
