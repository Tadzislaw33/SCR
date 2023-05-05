# skrypt informujacy o sumarycznej liczbie plikow w biezacym katalogu 

argument=$1
if test "$argument" = ""
then
echo -n "Plikow w sumie: "
ls -lR|grep ^-|wc -l
fi

if test "$argument" = "-a"
then
echo -n "Plików w sumie z ukrytymi: "
ls -laR|grep ^-|wc -l
fi
