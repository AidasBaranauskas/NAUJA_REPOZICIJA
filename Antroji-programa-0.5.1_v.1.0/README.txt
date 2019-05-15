# Antroji-programa v0.5.1 ir v1
Ši programa išpildo 0.5 ir 1.0 reikalavimus, dėl to tikiuos, kad jos užteks
Programos dalys: 1.0.cpp, funkcijos.h, struct.h, random.hpp.
Beveik viskas vyks funcijos.h faile.

Programa pirmiausiai paprašo dviejų kintamųjų įvesties:
    "Iveskite A ir B, zinant, kad uzduotis bus atlikta su nuo 10^A iki 10^B mokiniu
    pavyzdziui: jei B=2, A=4, bus 100, 1000 ir 10000 mokiniu: "
Jie turi būti naturalieji skaičiai (sveiki ir teigiami), pirmas pažesnis už antrą.

Matuojami procesai bus milisekundžių formatu:
    "Laikas milisekundemis"

Programa daugiau pasirinkimų neduos. Jei įvesti du skaičiai yra A ir B, o X yra skaičius intervale [A;B] nuo A artėjantis iki B (A=2, B=4, X=2,3,4), tai generuojami failai tokiu formatu:
10^X.txt, 
10^X vector_lievi.txt, 10^X vector_kietekai.txt,
10^X list_lievi.txt, 10^X list_kietekai.txt,
10^X deque_lievi.txt, 10^X deque_kietekai.txt,

Pirmas (10^X.txt) failas yra pirminis, jį skaitys ir perkopijuos surūšiąvus į kitus failus.
Jis turi 10^X+1 eilučių su mokinių info, paskutinė eilutė tuščia.
Vardas ir pavardė sudaryti iš atsitiktinių angliškų raidžių, tik pirmosios yra didžioji. Ilgis irgi atsitiktinis, bet kiekviena raidė po pirmos turi pastovią tikimybę užbaigti raidžių generaciją.
Tada eina atsitiktinis skaičius ND pažymių, simbolis '0' atskyrimui, egzamino pažymys ir galutinis su iki
penkiais skaičiais po kablelio, apskaičiuotas naudojus ND vidurkį. Pvz:

Fqxajcahpkqxybdmqi Hlo 8 3 6 5 0 7 6.4
Aik Kadyyotyae 6 0 7 6.6
Cprvd Gzdwbht 1 2 7 0 6 4.93333
Fqlhdhxxs Fsp 7 9 0 4 5.6
Stjscyimoebasz Yd 1 8 1 2 3 0 4 3.6
Zccferwyxav Biptppuxrx 9 0 3 5.4

Kiti 6 failai vaizduoja surūšiuotų mokinių info beveik tuo pačiu formatu- nenaudojamas '0' simbolis tarp paskutinio ND ir egzamino įvertinimų.

Po abiejų skaičių įvesties, į konsolę išvedama:
    "
    10^X
    vector: skaitymas is failo: T,   rusiavimas i grupes: T
    list: skaitymas is failo: T,   rusiavimas i grupes: T
    deque: skaitymas is failo: T,   rusiavimas i grupes: T"
,kai T yra atitinkami laikai milisekundėmis. Tai bus išvedama B-A+1 kartų.

Programoje yra patikra, kuri išveda kiek kartu kietekai ar lievi yra netinkamuose failuose dėl rūšiavimo klaidos. Tikrina ne failus, bet jų kūrimo procesą.

Deque ir vector funkcijos beveik identiškos, skiriasi tik pavadinimai konteineriu, todel nera komentaru deque dalyje.
