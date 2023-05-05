#!/bin/bash

# skrypt sprawdzajacy okresowo, czy jest zalogowany uzytkownik o podanym loginie
# wywolanie:  czy_jest login_uzytkownika

argc=$#            #dane, by pokazac sposob tworzenia zmiennych
                   #wokol operatora przypisania = nie moze byc zadnej spacji!!!

# sprawdzamy, czy podano wymagany argument 
if [ $argc -ne 1 ]; then  # [ ] - alternatywny sposob wywolywania polecenia test
                     # operator != porowna argumenty traktujac je jako napisy!!!
    echo "Wywolanie: $0 login_uzytkownika"
    exit 1
fi

# alternatywne sposoby sprawdzenia czy podano wymagany argument
#test $argc -ne 1 &&   echo "Wywolanie: $0 login_uzytkownika" && exit 1
#test $argc -eq 1 || { echo "Wywolanie: $0 login_uzytkownika" && exit 1; }


# dopoki nie ma uzytkownika usypiaj
while test `who |grep $1 |wc -l` -eq 0;
do
    sleep 2;
done

# uzytkownik pojawil sie - poinformuj
echo
echo -----------------
echo $1 pracuje
echo -----------------

exit 0
