# NAUJA_REPOZICIJA v4
1. penkios klases funkcijos
operatoriai:
a=b atlaisvina atminti a ir prilygina naujo objekto duomenis b
[] mete exception'a jei blogo nario iesko
push_back
reserve: naudoja daugmaz grow() koda, nes nepavyko jo pernaudot
uncreate: clear default operatorius
grow: dvigubina rezervuota atminti pasiekus limita

2. push_back (skaitymo) greicio palyginimas
vector klase nukopijuota nuo skaidriu su keliais pakeitimais.
Generavimas failo naudoja kokybiska rand funkcija daug kartu, todel
si dalis programos uztrunka virs 80% laiko. Laikas milisekundemis.
Naudojau viena faila abiem vektoriams:
mano (skaidriu) vector:
 10^5
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
Realokavimo kartai irgi vienodi. Kompas nepaveza 10^7 ir daugiau.


(is skaidriu nukopijuota, kur per kiekviena relocate'a auga rezervuota vieta dvigubai). 
Programa turi klaida- kartais, duoda atminties priskyrimo erorus (skirtingus) ir crash'ina 
kelis kartus iseiles, bet dazniausiai net endless loop to nepasiekia. Tikiuosi, kad jums pasileis.
Siandien veikia, tai noreciau manyt, kad istaisiau...

4. 