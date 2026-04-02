#include "clients_db.h"

/*
Config must strictly be formated as:
---------------------------------------------------------------------------------------------------------
"CLIENT_NAME, PRICE_PAID, DISPLAY_OPTION, NUM_BILLBOARDS, BILLBOARD_TEXT_1, EFFECT_TEXT_1, ... EFFECT_n\n"
---------------------------------------------------------------------------------------------------------
Rules:
- All fields must be populated
- Maximum client name length: 49 characters
- Maximum billboard text length: 49 characters
- NUM_BILLBOARDS must match the number of BILLBOARD_TEXT/EFFECT pairs
- one_even_odd_min requires at least 2 billboards

Valid DISPLAY_OPTION values:
- one_random
- one_even_odd_min

Valid EFFECT values:
- fixed
- scroll
- blink
*/

const char clients_db[] PROGMEM = 
    "Hederlige Harrys Bilar,5000,one_random,3,Kop bil hos Harry,scroll,En god bilaffar (for Harry!),fixed,Hederlige Harrys Bilar,blink\n"
    "Farmor Ankas Pajer AB,3000,one_random,2,Kop paj hos Farmor Anka,scroll,Skynda innan Marten atit allt,fixed\n"
    "Svarte Petters Svartbyggen,1500,one_even_odd_min,2,Lat Petter bygga at dig,scroll,Bygga svart? Ring Petter,scroll\n"
    "Långbens Detektivbyrå,4000,one_random,2,Mysterier? Ring Langben,fixed,Langben fixar biffen,fixed\n"
    "Self promotion,1000,one_random,1,Synas har? IOT:s Reklambyra,fixed\n"
;
