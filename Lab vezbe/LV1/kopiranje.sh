if test $# -le 8
then
	case $# in
		2 | 4 | 6 | 8) 
		while [ $# != 0 ]
		do
			cp $1 $2
			shift 2
		done;;
	0 | 1 | 3 | 5| 7)
		echo "Nevalidni argumenti";;
	esac
else
	echo "Greska"
fi