read sta
while [ "$sta" != "KRAJ" ]
do
	if [ -f $sta ]
	then
		cat $sta >> ./spoj.dat
	else 
		echo "UNETO IME NE PRESTAVLJA COFIJA"
	fi
	read sta
done
