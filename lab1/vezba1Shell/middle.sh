if [ $# != 3 ]
then
	echo "broj argumenata nije dogovarajuc"
elif [ ! -f $3 ]
then
	echo "morate kao 3. arugment da zadate datoteku"
else
	tail -n+$1 $3 | head -n$(($2-$1+1))
fi

