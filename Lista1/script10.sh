#!/bin/bash

if [ ! -d ./PierwszyFolder ]; then
mkdir ./PierwszyFolder
echo "Stworzylem pierwszy"
fi
if [ ! -d ./DrugiFolder ]; then
mkdir ./DrugiFolder
echo "Stworzylem drugi"
fi
touch ./PierwszyFolder/plik1.c
touch ./PierwszyFolder/plik2.txt
touch ./PierwszyFolder/plik3.c

for arg in $@
do

echo "Czy chcesz przeniesc plik $arg z Pierwszego do Drugiego folderu?[t/n]"
read odp

if [ "$odp" = "t" ]; then
mv ./PierwszyFolder/$arg ./DrugiFolder/
fi

done

rm -r ./PierwszyFolder ./DrugiFolder
