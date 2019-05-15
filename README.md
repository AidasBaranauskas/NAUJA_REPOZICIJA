# NAUJA_REPOZICIJA v1.1
Programos dalys: 1.1.cpp, funkcijos.h, studentas.h, random.hpp.

Mokinių skaičius su kuriuo dirbs programa priklauso nuo dviejų įvestų sveikųjų skaičių. Jei įvestis 1 ir 5, tai dirbs programa su 10, 100, 1.000, 10.000 ir 100.000 studentų. Įvedus tą patį skaičių dukart pavyzdžiui 6, dirbs tik su 10^6 studentų.

Lyginimas v1.0 su v1.1.
Kadangi v1.0 buvo klaidinga tuo, kad galutinis buvo apskauciuojamas failo generavimo metu, bei įvestas gale pažymių sąrašo (po egzamino), tai privedė prie greitesnio v1.0 veikimo greičio (nes galutinio skaičiavimas šiuo atveju neįskaičiuojamas laike, priešingai nei v1.1).

Naudojau vienoda fail'ą visiem šiem patikrinimam, kuris turėjo 1^6 studentų. Laikas milisekundėmis. 
v1.0, du bandymai:
"vector: skaitymas is failo: 8421,   rusiavimas i grupes: 531"
"vector: skaitymas is failo: 8124,   rusiavimas i grupes: 531"
v1.1, du bandymai:
"vector: skaitymas is failo: 4874,   rusiavimas i grupes: 531"
"vector: skaitymas is failo: 4874,   rusiavimas i grupes: 515"

Skaitymas iš failo žymiai pagreitėjo, bet ne rūšiavimas, nes šis abiejose versijose naudojo vienodą funkciją ir tiek structųra, tiek
"studentas" klasė talpinti vectoriuje

Optimizavimo flag'ai visiškai napagreitino matuojamų procesų.
01
"vector: skaitymas is failo: 4859,   rusiavimas i grupes: 531"

02
"vector: skaitymas is failo: 4890,   rusiavimas i grupes: 515"
"vector: skaitymas is failo: 4874,   rusiavimas i grupes: 546"

03
"vector: skaitymas is failo: 4890,   rusiavimas i grupes: 531"

1.0 versijoje naudojau tikrintoją, kuris kietekų ir lievų fail'ų kūrimo metu tikrino ir skaičiavo, kiek studentų prastai surūšiuoti. Taip pat išvesdavo galutinį rezultatą į šiuos failus. Dėl greitesnio (nors ir neskaičiuojamo) darbo, užkomentavau šias dalis.
