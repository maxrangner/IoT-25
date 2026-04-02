# Billboard Manager

Ett inbyggt system för att visa viktade reklamannonser på en HD44780 LCD-display, riktat mot ATmega-baserade mikrokontrollers.

Repo: [https://github.com/maxrangner/IoT-25/tree/main/06-programmering-for-inbyggda-system/inlamning/06-inbyggda-system-inlamning](https://github.com/maxrangner/IoT-25/tree/main/06-programmering-for-inbyggda-system/inlamning/06-inbyggda-system-inlamning)

Wokwi-simulering: [https://wokwi.com/projects/460192993891021825](https://wokwi.com/projects/460192993891021825)

---

## Bygg och flasha

**Krav:** `avr-gcc`, `avr-objcopy`, `avrdude`, `make`

| Kommando | Beskrivning |
|----------|-------------|
| `make` | Bygg release |
| `make clean` | Rensa byggfiler |

---

## Uppgift och kriterier

| Krav |
|------|
| Visa reklammeddelanden på en LCD |
| Kunder kan välja bland flera olika texteffekter |
| Visningstid proportionell mot betalning |
| Varje reklamskylt visas i 20 sekunder |
| Samma kund visas aldrig två gånger i rad |

---

## Design

### Moduluppdelning

Systemet är uppdelat i tydligt avgränsade moduler:

| Modul | Ansvar |
|-------|--------|
| `main` | Initiering och huvudloop |
| `client_manager` | Klienturval och billboard-val |
| `display` | Rendering av effekter på LCD |
| `lcd` | HD44780-drivrutin |
| `utils` | Hjälpfunktioner och parsing av klientdatabas |
| `millis` | Mjukvarutimer via Timer0 |
| `clients_db` | Klientdata lagrad i flash (PROGMEM) |

Detta följer principen av tydlig ansvarsindeling. Varje modul har ett tydligt ansvar, koden blir lättare att testa och ändra, och systemet blir mer överskådligt. Denna typ av uppdelning är standard i större embedded-projekt.

---

### Huvudloop

Systemet initierar komponenter:

1. Mjukvarutimer (`millis`)
2. Slumpgenerator
3. Klienthanterare (`client_manager`)
4. Display

Efter initiering körs en oändlig icke-blockerande loop. Designvalet att undvika `delay` gör att systemet kan:

- hålla exakt visningstid per reklam
- köra animationer parallellt
- aldrig låsa CPU:n

---

### Konfiguration

Tidsintervall och andra statiska värden samlas i `config.h`, separerat från logiken. Värden kan justeras utan att programkoden behöver ändras.

---

### Klientdatabas och PROGMEM

AVR har mycket begränsat SRAM. För att undvika att fylla upp SRAM med strängar lagras klientdatabasen i flashminnet via `PROGMEM`. Data läses byte för byte med `pgm_read_byte` och kopieras till SRAM endast vid initiering.

---

### Ingen dynamisk minnesallokering

Systemet använder ingen heap och inga `malloc`-anrop. Dynamisk allokering på små mikrokontrollers kan ge fragmentering, svårdebuggade fel och oförutsägbart minnesbeteende. Alla datastrukturer har fast storlek och allokeras statiskt.

---

### Viktat slumpmässigt urval

Klienter väljs med en viktad slumpalgoritm där sannolikheten är proportionell mot betalat pris.

Algoritm:
1. Summera alla klienters pris
2. Generera ett slumptal mellan `0` och totalsumman
3. Iterera klienterna och ackumulera deras pris
4. Välj den klient där den ackumulerade summan passerar slumptalet
5. Om den valda kunden var samma som senast visad — gör ett nytt försök

Metoden kräver ingen dynamisk minnesallokering och är stabil för embedded-miljöer.

---

### Slumpgenerator

AVR saknar hårdvarubaserad slumpgenerator. Istället samplas analogt brus från en flytande pin via ADC och XORas med Timer0-räknaren vid retur för ökad slumpmässighet.

---

### Konfigurationsantaganden

Klientdatabasen parsas utan felhantering och förutsätter att konfigurationsfilen är korrekt. Instruktionerna i `clients_db.h` måste följas strikt.

---

## Datastrukturer

### `Client`

```
name | price | display option | number of billboards | billboards[]
```

Sparas som en struct med fast storlek så att minnesstorlek känd vid kompilering, ingen heap behövs.

### `Billboard`

```
text | effect (enum)
```

### Visningsläge

Styr hur en kunds reklamskyltar väljs:

| Läge | Beteende |
|------|----------|
| `one_random` | En slumpmässigt vald skylt visas varje gång |
| `one_even_odd_min` | Växlar mellan skylt 1 och 2 beroende på jämna/udda minuter sedan uppstart |

### Texteffekter

| Effekt | Beteende |
|--------|----------|
| `fixed` | Statisk text |
| `scroll` | Text rullar in från höger |
| `blink` | Text blinkar med jämna intervall |

Effekterna fungerar tack vare den icke-blockerande designen. Animation och visningstid hanteras samtidigt utan konflikter.
