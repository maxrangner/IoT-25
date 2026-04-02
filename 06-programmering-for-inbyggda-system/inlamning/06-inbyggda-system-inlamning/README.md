# Billboard Manager

## Uppgift och kriterier:
- Skapa ett system för att visa reklammeddelanden på en LCD.
- Kunderna kan välja olika typer av sätt deras meddelanden kan visas.
- Antalet totala visningar ska spegla hur mycket kunden betalat för sin reklamplats i relation till de andra kunderna.
- Varje reklamskylt ska visas i 20 sekunder.
- Samma kund får inte visas två gånger i rad.

## Design:
### Moduluppdelning

Systemet är uppdelat i flera moduler:
- display
- client_manager
- millis/timer
- main
- utils
- lcd
- clients_db

Detta följer principen separation of concerns, vilket gör att:
- varje modul har ett tydligt ansvar
- koden blir lättare att testa
- koden blir lättare att ändra
- systemet blir mer överskådligt

Denna typ av uppdelning är standard i större embedded-projekt.

### LCD Drivare
Använder en drivare specifikt för en DH44780-display. Genom att använda en separat drivrutin hålls displaykoden isolerad från resten av systemets logikdelar.

### Main
Systemet lever i `main`, som har en initieringsfas där vi sätter variabler samt initierar komponenter:
- display
- timer
- client_manager
- slumpgenerator

Efter initiering kliver systemet in i en oändlig icke-blockerande loop. En icke-blockerande design används för att unvika `delay` så att flera funktioner kan köras utan att blockera. Detta gör så att systemet kan:
- hålla exakt visningstid per reklam
- samtidigt hantera animationer
- unvika att låsa CPU:n

### Konfiguration via config.h
Tidsintervall och andra konstanter ligger i config.h.

Detta gör att:
- konfiguration separeras från logik
- värden kan ändras utan att ändra programkod
- koden blir mer underhållbar

### Klientdatabas
AVR har mycket begränsat SRAM, dit strängar normalt kopieras vid uppstart. För att minska minnesanvändningen lagras klientdatabasen istället i flashminnet via PROGMEM, vilket minskar risk för stack/heap-problem. Data läses byte för byte med pgm_read_byte och kopieras endast vid initiering av programmet.

### Ingen dynamisk minnesallokering
Systemet använder ingen heap och inga malloc-anrop. Detta är medvetet eftersom dynamisk allokering på små mikrokontrollers kan ge:
- fragmentering
- svårdebuggade fel
- oförutsägbart minnesbeteende

Alla datastrukturer har därför fast storlek och allokeras utan heap, vilket ger ett mer stabilt system.

### Viktat slumpmässigt urval av klient
Klienter väljs med en viktad slumpalgoritm där sannolikheten beror på hur mycket kunden betalat.

Algoritmen:
- Summerar alla klienters betalning
- Genererar ett slumpvärde mellan 0 och totalsumman
- Itererar klienterna och ackumulerar deras pris
- Den klient där summan passerar slumptalet väljs
- Om den valda kunden var samma som senast visad görs ett nytt viktat försök tills en annan kund väljs

Denna metod valdes eftersom den:
- är enkel att implementera
- kräver ingen dynamisk minnesallokering
- har låg komplexitet O(n)
- är deterministisk och stabil

Detta gör den lämplig för små embedded-system.

### Slumpgenerator
AVR saknar hårdvarubaserad slumpgenerator, därför används analogt brus från en flytande pin. Detta XORas med Timer0 vid retur för ökad slumpmässighet.

### Konfigurationsantaganden
Klientdatabasen parsas utan avancerad felhantering och förutsätter därför att konfigurationen är strikt giltig.

Det innebär att:
- alla fält måste vara ifyllda
- antal klienter måste rymmas inom `MAX_NUM_CLIENTS`
- antal reklamskyltar per kund måste rymmas inom `MAX_BILLBOARDS`
- klientnamn och reklamtexter måste rymmas inom sina buffertar
- `NUM_BILLBOARDS` måste matcha antalet `BILLBOARD_TEXT`/`EFFECT`-par
- `one_even_odd_min` kräver minst två reklamskyltar

## Datastrukturer
- fasta arrays → förutsägbart minne
- enums → tydligare kod

### Client
Klienter sparas i en struct som innehåller:
- namn
- pris
- visningsläge
- antal reklamskyltar
- array med reklammeddelanden

Struct används istället för dynamiska objekt eftersom:
- minnesstorlek blir känd vid kompilering
- ingen heap behövs

### Billboard
Varje reklamskylt innehåller:
- text
- enum för effekt

Enums används för att göra koden tydligare och säkrare än att använda siffror.

### Texteffekter
Tre effekter finns:
- statisk
- rullande
- blinkande

Effekten sparas i Billboard-strukturen och tolkas av display_billboard().

Effekterna fungerar tack vare den icke-blockerande designen, vilket gör att animation kan köras samtidigt som systemet håller korrekt visningstid.
