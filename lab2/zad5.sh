# skrypt wysyla wiadomosci email na rozne adresy 

while read adres
do
    echo "Tresc maila" | mail -s "Temat maila" $adres
done < adresy.txt
