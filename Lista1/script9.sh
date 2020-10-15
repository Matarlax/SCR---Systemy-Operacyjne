#!/bin/bash

#wlacz sledzenie wykonywanych polecen
set -x
#stworz nowy plik
touch nowyplik.txt
#stworz nowy folder
mkdir NowyFolder
#przenies plik do stworzonego folderu
mv nowyplik.txt ./NowyFolder
#zmien nazwe pliku
mv ./NowyFolder/nowyplik.txt ./NowyFolder/zmienionyplik.txt
#wyswietl zawartosc folderu
ls -l
#odbierz mozliwosc otwierania NowyFolder
chmod -x NowyFolder
#wyswietl jeszcze raz zeby sprawdzic czy zadzialalo
ls -l
#przywroc mozliwosc otwierania NowyFolder
chmod +x NowyFolder
#stworz link symboliczny w bierzacym folderze do zmienionyplik.txt
ln -s ./NowyFolder/zmienionyplik.txt linkdopliku
#wyczysc stworzone pliki
rm -r NowyFolder
rm linkdopliku
#zakoncz monitorowanie polecen
set +x
