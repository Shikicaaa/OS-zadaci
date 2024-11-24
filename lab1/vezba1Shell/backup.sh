if [ $# != 1 ]
then
	echo "SAMO JEDAN"
elif [ ! -d $1 ]
then
	echo "NIJE DIREKTORIJUM"
else
	mkdir -p KOPIJA
	cd $1
	for f in *.c 
	do
		echo $f
		cp "$f" "./KOPIJA/$f.bak"
	done
fi
