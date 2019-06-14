# NAUJA_REPOZICIJA v4
1. penkios klasės funkcijos
= atlaisvina atmintį perrašomos reikšmės ir prilygina naujo objekto duomenis reikšmei
dešinėje '=' operatoriaus.
[] meta exception'ą jei blogo nario prašo.
push_back
reserve: naudoja daugmaz grow() koda, nes nepavyko jo pernaudot.
uncreate atlaisvina atmintį.
grow: dvigubina rezervuotą(kartu ir inicializuotą) atmintį pasiekus limitą.

2. push_back (skaitymo) greičio palyginimas
vector klasė nukopijuota nuo skaidrių su keliais pakeitimais.
Generavimas fail'o naudoja kokybišką rand funkciją daug kartu, todel
fail'o generavimo dalis užtrunka virs 80% trukmės. Laikas milisekundėmis.
Naudojau vieną fail'a abiem vektoriams:
mano (skaidriu) vector:
 10^5 (studentų skaičius standartine išraiška)
 Realokavimo kartai: 18
 skaitymas is failo: 695 695 698

 10^6
 Realokavimo kartai: 21 
 skaitymas is failo: 7185 6767 7049

std vector:
 10^5
 Realokavimo kartai: 18
 skaitymas is failo: 694 683 687 682

 10^6
 Realokavimo kartai: 21
 skaitymas is failo: 7074 7030 7309 7128

Isvada: std vector greitis apie toks pat naudojant push_back funkcija.
3. realokavimo kartu palyginimas
Realokavimo kartai irgi vienodi, bet nusprendžiau nerašyt 18 ir 21 per daug kartų.
Kompas nepaveža 10^7 ir daugiau studentų (sugeneruoja failą, bet pasiekia limitą su push_back)
todel su 10^7 ir daugiau užduoties neatlikau.
 
Programa turi arba turėjo klaidą- kartais throw'indavo atminties priskyrimo erorus arba crash'ino be throw'ų. 
Tai įvoky 2 kartus, kelis bandymus paleisti programą iš eilės, bet kai bandžiau pakartot, net endless loop
nepakartojo šių erorų. Tikiuosi, kad jums pasileis. Šiandien veikia, tai norėčiau manyt, kad ištaisiau.

Uzduotis 3 nėra įkelta, bet jos reikalavimai išpildyti 4.3 (šioje) versijoje iki 1.5 (doxygen ir unit testing neatlikti). Bandysiu įkelt


