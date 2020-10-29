#!/bin/bash

#   Jesli przechwyci sygnal konca, nie wykona go
# i wyswietli echo.
#   Wypisane cyfry blokuja sygnaly 1-15, jednak
# $kill -SIGKILL PID
# zabija proces, bo sygnal_9 nie moze byc uwieziony.
trap 'echo "Trap sygnalu kill"' 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

#Wyswietla date co sekunde
while true
do
  date
  sleep 1
done


