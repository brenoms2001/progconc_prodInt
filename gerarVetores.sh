#!/bin/bash

#Código para facilitar a criação de arquivos de teste
gcc -o gerador -Wall gerador.c
if [ -z "$1" ]; then
    for ((i=5; i<20; i+=5))
    do
        ./gerador $i
    done
    
else
    ./gerador $1
fi