if [ "$#" -ne "1" ]
then
	echo "broj argumenata nije 1"
else
	if test -f $1
		then
			cat $1
	elif test -d $1
		then
			cd $1;
			ls -a
	else
		echo "losi parametri"
	fi
fi