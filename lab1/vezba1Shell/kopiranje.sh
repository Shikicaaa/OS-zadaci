case $# in
	2 | 4 | 6 | 8)
		while [ $# != 0 ]
		do
			if [ -f $1 ]
			then
				cp $1 $2
				echo "KOPIRAO SE FAJL"
			fi
			shift 2
		done;;
	0 | 1 | 3 | 5 | 7)
		echo "NEVALIDNI ARGUMENTI";;
esac
