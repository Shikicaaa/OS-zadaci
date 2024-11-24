if [ $# != 1 ]
then
	echo "Potrebno je uneti argument putanje do direktorijuma ili direktorijum"
elif [ ! -d $1 ]
then
	echo "Potrebno je uneti argument putanje do direktorijuma ili direktorijum"
else
	echo "Unesi ekstenziju: "
	read extenzija
	if [ -f ./headers ]
	then
		rm headres
	fi
	for fname in "$1/*.$extenzija"
	do
		echo "Dodajem prve dve linije datoteke $fname"
		head -2 $fname >> headers
	done
fi
