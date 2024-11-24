if [ "$#" -ne "1" ]
then
	echo "Nema dovoljan broj argumenata"
elif [ -f $1 ]
then
	case "$1" in
		*.c) 
			gcc $1;;
	
		*.h)
			cat $1;;
		*)
			rm $1;;
	esac
else
	echo "uneti argument nije datoteka"
fi