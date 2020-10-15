#!/bin/bash
#znajdz pliki i pokaz liste
find /home/mati/SCR -type f -name "*$1" -mtime -$2 -exec ls -la {} \;
#znajdz pliki i zrob archiwum
find /home/mati/SCR -type f -name "*$1" -mtime -$2 -exec tar -rvf $3 {} \;
 
