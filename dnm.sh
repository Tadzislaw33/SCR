#!/bin/bash

# skrypt zamieniajacy nazwy plikow na pisane malymi literami
#####################################################################
#                                                                   #
# UWAGA!!!                                                          #
# Nadpisuje pliki jesli nazwy docelowe pokrywaja sie z istniejacymi #
#                                                                   #
#####################################################################

for i in $1;
do
    mv $i `echo $i|tr [:upper:] [:lower:]`;
done

# pojedyncze apostrofy to &( )

