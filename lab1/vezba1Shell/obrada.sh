if test "$#" -ne "1"
then
	echo "MORAS DA IMAS 1 PARAMETAR"
elif [ -f $1 ]
then
	case $1 in
		*.c)
			gcc $1;;
		*.h)
			cat $1;;
		*)
			rm $1;;
	esac
fi
