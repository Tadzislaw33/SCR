# skrypt dla dowolnej liczby argumentów wyświetli informacje o kazdym z nich 
# traktowanym jako nazwa pliku

for i in $@;
do
    if [ -f $i ]
    then
        echo Plik istnieje
    else
        echo Plik nie istnieje
    fi
    if [ "$(ls -A $i)" ]
    then
        echo katalog
    else
        echo katalog jest pusty
    fi
done
