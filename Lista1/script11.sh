#!/bin/bash

#znajdz, w /etc, pliki, <1kB, mlodsze niz 3dni, pokaz szczegoly 
find /etc -type f -size -1k -mtime -3 -exec ls -la {} \;

echo "=========================================================="
#znajdz, w /etc, pliki, <250kB, mlodsze niz 90dni, starsze niz 30dni
find /etc -type f -size -250k -mtime -90 -mtime +30 -exec ls -la {} \;

echo "=========================================================="
#znajdz oba poprzednie na raz: flaga -o w nawiasach to OR
find /etc -type f \( -size -250k -mtime -90 -mtime +30 -o -size -1k -mtime -3 \) -exec ls -la {} \;

