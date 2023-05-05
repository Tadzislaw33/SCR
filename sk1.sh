#!/bin/bash

zm=$( who | grep $1 | wc -l )

#echo $zm

if [ $zm -gt 0 ]
then
    echo $1 pracuje
else
    echo $1 nie pracuje
fi
