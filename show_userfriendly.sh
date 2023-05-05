#!/bin/bash

if [ "$HOSTNAME" = "diablo" ]; then
PING_COM="/usr/sbin/ping"
else
PING_COM="ping"
fi

#export DISPLAY=:0.0

# sprawdzamy czy userfriendly się odzywa, jeśli nie kończymy
$PING_COM -c 1 userfriendly.org > /dev/null || exit 1

# w katalogu domowym usuwamy ewentualnie istniejący katalog pomoczniczy uf_temp
# i tworzymy nowy, pusty
cd $HOME
test -d uf_temp && rm -rf uf_temp
mkdir uf_temp
cd uf_temp

# kiedyś było łatwo :( ale się zmieniło :(
#wget -q -A gif -nd -r -l1 http://userfriendly.org/index.php?data=random

# pobieramy stronkę z odnośnikiem do losowo wybranego komiksu
wget -q http://www.userfriendly.org/cgi-bin/randomcart.cgi

# szukamy w pobranej stronce linii z adresem komiksu (dwa pierwsze grepy),
# rozdzielamy pola do osobnych linii (sed),
# wybieramy linię z adresem (trzeci grep)
# i z niej adres bez cudzysłowów (awk i ostatni cut)
# z którego pobieramy obrazek (wget)
wget -q `cat randomcart.cgi |grep cartoons|grep gif|sed  's/[[:space:]]/\n/g'|grep src|awk -F 'src=' '{print $2}'|cut -d '"' -f2`
#wget -q `cat randomcart.cgi |grep cartoons|grep gif|sed  's/[[:space:]]/\n/g'|grep src|cut -d= -f 2|sed 's/"//g'`

# wyświetlamy obrazek
/usr/bin/eog *.gif
