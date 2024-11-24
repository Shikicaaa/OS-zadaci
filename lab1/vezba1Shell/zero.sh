if [ $# != 1 ]
then
	echo "SAMO 1 argument"
else
	for f in $( locate $1 )
	do
		[ -f $f ] && [ -s $f ] || echo $f
	done
					
fi
