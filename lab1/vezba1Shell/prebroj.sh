if [ $# != 1 ]
then
	echo "SAMO 1 argument"
elif [ ! -d $1 ]
then
	echo "nije DIREKTORIJUM"
else
	count=0
	for f in *
	do
		if [ -f $f ]
		then
			if [ -s $f ]
			then
				count=$((count+1))
			fi
		fi
	done
	echo "broj nepraznih fajlova je: $count"
					
fi
