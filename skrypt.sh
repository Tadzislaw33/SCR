#   Tadeusz Dworecki 259281 
#   Sprawozdanie Skrypt wykonujacy operacje na plikach ze zdjeciami 
#   30.11.2020

#!/bin/bash

#chmod u+x skrypt.sh dodawanie uprawnien

szerokosc=$2
wysokosc=$3
cd $1

#kopiowanie plikow
mkdir zdjecia
cp *.JPEG *.PNG zdjecia

#zmiana rozszerzenia +
for p in *.JPEG;
do 
    mv "$p" "$( echo $p | sed s/JPEG/jpeg/ )";
done 

for p in *.PNG;
do 
    mv "$p" "$( echo $p | sed s/PNG/png/ )";
done

#zmiana spacji na podkreslenie +
for p in *.jpeg;
do 
    mv "$p" "$( echo $p | tr -s ' ' | tr ' ' '_' )";
done 
 
for p in *.png;
do 
    mv "$p" "$( echo $p | tr -s ' ' | tr ' ' '_' )";
done

#zmiana rozmiaru +
mogrify -resize $wysokosc!x$szerokosc! *.jpeg 
mogrify -resize $wysokosc!x$szerokosc! *.png

#tworzenie archiwum +
tar -cf zdjecia.tar *.jpeg *.png

#sprzatanie w katalogu z plikow tymczasowych +
rm -rf *.jpeg *.png

#Aby przeprowadzic testy skryptu nalezy:                                                                   
# - nadac uprawnienia dla uzytkownika #chmod u+x skrypt.sh                                                 
#Skrypt wywoluje sie z 3 argumentami                                                                       
#(sciezka do folderu ze zdjeciami, szerokosc obrazu, wysokosc obrazu)                                      
#Przykladowa komenda wywolania skryptu:                                                                    
# ./skrypt.sh /home/tdworeck 200 120                                                                       
#Efektem wpisanej komendy bedzie:                                                                          
# - utworzenie archiwum plikow zdjeciowych zdjecia.tar                                                     
# - plikom zostana zmienione nazwy i rozszerzenia                                                          
# - zdjecia beda o rozmiarze 200x120                                                                       
# - utworzenie folderu zdjecia w ktorym znajda sie oryginalne pliki 

