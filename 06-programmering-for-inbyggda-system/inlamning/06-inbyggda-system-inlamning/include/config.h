#ifndef CONFIG_H
#define CONFIG_H

#define NUM_CLIENTS 5
#define NUM_MAX_BILLBOARD_CHAR 50
#define CONFIG_FILE "../client_config.csv"
#define CONFIG_PARSE_BUFFER_SIZE 256

static char clients_db[] = {
    "Hederlige Harrys Bilar,5000,one_random,3,Köp bil hos Harry,scroll,En god bilaffär (för Harry!),fixed,Hederlige Harrys Bilar,blink\n"
    "Farmor Ankas Pajer AB,3000,one_random,2,Köp paj hos Farmor Anka,scroll,Skynda innan Mårten ätit alla pajer,fixed\n"
    "Svarte Petters Svartbyggen,1500,one_even_odd_min,2,Låt Petter bygga åt dig,scroll,Bygga svart? Ring Petter,scroll\n"
    "Långbens Detektivbyrå,4000,one_random,2,Mysterier? Ring Långben,fixed,Långben fixar biffen,fixed\n"
    "Self promotion,1000,one_random,1,Synas här? IOT:s Reklambyrå,fixed\n"
};

#endif