#!/bin/bash

#wymagany program mutt
#sudo apt update && sudo apt install -y mutt

#sciezka do plikow: obecna_lokacja/folder_z_plikami
sciezka=$(pwd)/Script2_Pliki

#dla kazdego maila w pliku adresy.txt
for mail in $(cat $sciezka/adresy.txt)
do
 #wyslij zawartosc tresc.txt i wszystkie pliki spec*.pdf
 cat $sciezka/tresc.txt | mutt -s "Zapytanie ofertowe" $mail -a $sciezka/spec*.pdf
done
