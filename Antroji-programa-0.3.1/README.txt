# Antroji-programa v0.3.1
Visas funkcijas perkėliau į header failą "funkcijos.h"
0.3.cpp talpina tik meniu
Try-catch panaudotas main'e 0.3.cpp faile. Strukturos vis dar naudojamos, tik dabar ji įdėta header faile "struct.h"

# Funkcijos pridėtos praeitose versijose 
(v0.2.1)
Naujos komandos pridėtos į meniu:
"Skaityti mokiniu info is failo- 4
Rodyti mokiniu info- 5;
Komanda 4 atlieka užduotį, komanda 5 tik dėl patogumo egzistuoja ir ji išveda visa mokinių info.

Programą sukūriau rementis šiuo pradiniu variantu:
Pavardė     Vardas      ND1  ND2   ND3  ND4  ND5  Egzaminas
Vardas1     Pavardė1    8    9     10   6    10   9
Vardas2     Pavardė2    7    10    8    5    4    6
...
Programa neveiks, be šios eilutės
Pavardė     Vardas      ND1  ND2   ND3  ND4  ND5  Egzaminas
Gali būt ir daugiau ar mažiau ND.
Išvestis išrykiuota pagal vardą/pavardę.

(v0.1.1)
Naudoju meniu, todėl programoje reikia klausyti nurodymų
Įvestos komandos yra skaičiai, kurie naudotojui su jų paskirtimis išvedami į konsolę programos pradžioje arba įvedus 0, kol esama meniu.
"
    Pradeti naujo mokinio info ivedima- 1
    Rodyti visu mokiniu vidurkius- 2
    Rodyti visu mokiniu medianas- 3
    Baigti darba- 9
    Rodyti komandas- 0
"
Programa nenaudoja C masyvo, tik vektorius. Pažymiai bus intervale [1;10]
Įvedus 0, išvedama
  "Iveskite {mokinių skaičius + 1}'ojo mokinio varda ir pavarde"
Įvedus dvi simbolių sekas, išves:
  "Jei norit patys ivesti pazymius- iveskit 0. Ivedus kita skaiciu pazymiu skaicius ir reiksmes bus atsitiktines"
Įvedus ne nulį:
sugeneruotas atsitiktinis skaičius namų darbų su jų bei egzamino pažymiais. Jie išvedami į konsolę atskirti tarpo simbolių:
  "Sugeneruotos reiksmes: {Nd paž 1}... {Nd paž 2}
  Egzamino pazymys: {egz paž}"
Grąžinama į meniu.
Įvedus 0:
  "Iveskite Nd pazymius. Ivedus maziau nei 1 baigsis ivestis: "
Po bent vieno Nd pažymio ir 0:
  "Iveskite egzamino pazymi: "
Po egzamino pažymio įvesties grąžinama į meniu

Iš meniu įvedus 2, lygiuotai išvedami mokinių vardai, pavardės ir galutiniai rezultatai pagal Nd vidurkį.
Iš meniu įvedus 3, bus tas pats kaip ir įvedus 2, tik galutinis priklausys nuo Nd medianos.
Iš meniu įvedus 9, baigiamas darbas
