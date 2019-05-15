# Antroji-programa v0.1.1
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
