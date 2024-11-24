if test "$#" -ne "1"
then
	echo "NE RADI KOMSO"
else
	if test -f $1
	then
		cat $1
	elif test -d $1
	then
		cd cat $1; ls -a
	else
		echo "E PA NIJE NISTA"
	fi
fi
