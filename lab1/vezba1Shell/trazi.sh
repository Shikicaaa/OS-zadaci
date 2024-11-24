if [ $# != 2 ]
then
	echo "Potrebno je 2 argumenta (direktorijum) (rec/recenica koja se trazi)"
elif [ ! -d $1 ]
then
	echo "Prvi argument (direktorijum) nije pravilno unet ili ne postoji"
else
	for fname in "$1/"*
	do
		grep $2 $fname > /dev/null
		if [ $? != 0 ]
		then
			echo "Datoteka $fname sadrzi $2"
		else
			echo "Datoteka $fname ne sadrzi $2"
		fi
	done
fi
