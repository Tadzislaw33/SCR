#!/bin/bash

# skrypt informujacy o sumarycznej wielkosci i liczbie plikow w
# biezacym katalogu 

echo -n "Sumaryczna wielkosc plikow: "
du -sh
echo -n "Plikow w sumie: "
ls -lR|grep ^-|wc -l
