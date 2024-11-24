read datoteka
while [ "$datoteka" != "KRAJ" ]; do
	if [ -f "$datoteka" ]; then
		cat "$datoteka" >> ./spoj.dat
	else
		ls -a
		echo "Ne radi lepo"
	fi
	read datoteka
done
