#include <iostream>
#include <string.h>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <chrono>

#define vstud    std::vector<studentas>
//#include <vector>
#include "vec.h"
#include "klases.h"
#include "funkcijos.h"//talpina funkcijas, kad main mazesnis butu

using std::cout;
double vidurkis(std::vector<int>& nd_)//skaiciuoja vidurki
{
    return std::accumulate(nd_.begin(), nd_.end(), 0.0)/nd_.size();
};
void studentas::new_galutinis() //apskaiciuoja ir priskiria reiksme galutiniui
{
    galutinis_= 0.4*vidurkis(nd_)+0.6 * egzaminas_;
};
void studentas::readStudent(std::ifstream& in)//iveda vieno studento duomenis is failo
{
    in>>vardas_>>pavarde_;
    int a;
    in>>a;

    while(a!=0)//paskutinis nd_ ir egzaminas_ atskirti '0' failuose
    {
        nd_.push_back(a);
        in>>a;
    }
    in>>egzaminas_;
    new_galutinis();
};

int main()
{
    int A,B,n=1;
    std::string pav;//pav+kietekai+.txt, arba pav+lievi+.txt
    cout<<"Iveskite A ir B. Uzduotis bus atlikta su nuo 10^A iki 10^B studentu\n "<<
        "pavyzdziui, ivedus 2 ir 4, bus 100, 1000 ir 10000 studentu, A<=B: ";
    std::cin>>A>>B;//jei norit skaiciuot tik 1000, iveskit 3 3 ir pan.
    cout<<"\nLaikas milisekundemis";

    for(int i=0; i<=B; i++)
    {
        if(i>=A) //pirmiausiai n pasieks 10^A, tada prasides uzduoties atlikimas
        {

        cout<<"\n\n 10^"<<i//uzkomentuokit sekancia eilute jei norit naudot vienoda faila
            <<"\n pirminio failo generavimas: "<<genFile(n, "10^"+std::to_string(i)+".txt")//pirmojo failo generavimas
        ;

        pav="10^"+std::to_string(i);//
        vstud mok, kietekai;//vstud= vector<studentas>
//po uzduoties, mok=neislaike, kietekai=islaike
        cout<<"\n skaitymas is failo: "<<genVec(n,pav+".txt",mok);//skaitymo is failo trukme

        rykiavimas(mok);//default naudoju

        cout<<"\n rusiavimas i grupes: "<<splitVec(n,pav,mok,kietekai);//rusiavimo trukme
        cout<<"\n rasymas i failus: "<<rasymas(n,pav,mok,kietekai);//rasymo i kieteku ir lievu failus trukme

        mok.clear(),kietekai.clear();
        }
        n*=10;//po kiekvienos iteracijos, studentu skaicius dideja 10 kartu
    }
    cout<<'\n';
    return 0;
}

