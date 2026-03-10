## Uppgift

1. Koppla in en LED matris till en arduino. För en rad, loopa igenom raden och tänd en LED i taget.
2. Vad behöver vi ändra för att vi ska släcka LEDerna efter oss så att vi bara har tre LEDs tända medan vi loopar?
3. Dagens labb: Ta bort delayen och lägg till millis och analogRead biblioteken. Lägg sen till kod för att styra denna "Snake". 

## Wokwi

Samma som till avr_joystick-branchen i avr_analog_inputs-repot: https://wokwi.com/projects/456953521227841537

## Branches

Detta repo innehåller flera grenar för de olika situationer vi kommer titta på



## make kommandon

* ```make``` - kompilerar programmet till bin-mappen, användbart om man vill ladda upp hex-filen till wokwi
* ```make isp``` - kompilerar programmet och flashar det till en inkopplad Arduino, förutsatt att man har kopplat in en Arduino till sin dator och satt rätt port (se kommentarer i Makefile)
* ```make clean``` - rensar genom att ta bort obj-mappen
* ```make fresh``` - rensar genom att ta bort alla obj-mappen samt bin-mappen
