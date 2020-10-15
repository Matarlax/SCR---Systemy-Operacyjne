#!/bin/bash

#przyjmuje wartosc 1-7, dzien tygodnia, 1=pon
dzien="$(date +%u)"

#jesli wieksze niz piatek
if [ $dzien -gt 5 ]; then
  echo "Weekend."
else
  echo "Dzien roboczy."
fi
