#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <chrono>
#include <random>

#include "klases.h"//zmogus ir studentas klases
#include "funkcijos.h"

using std::cout;
double vidurkis(std::vector<int>& nd_)//skaiciuoja vidurki
{
    return std::accumulate(nd_.begin(), nd_.end(), 0.0)/nd_.size();
};
void studentas::new_galutinis() //apskaiciuoja ir priskiria reiksme galutiniui
{
    galutinis_= 0.4*vidurkis(nd_)+0.6 * egzaminas_;
};
void studentas::readStudent(std::ifstream& in)
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
    int a,b,n=1;
    cout<<"Iveskite A ir B, zinant, kad uzduotis bus atlikta su nuo 10^A iki 10^B mokiniu"<<std::endl<<
        "pavyzdziui: jei A=2, B=4, bus 100, 1000 ir 10000 mokiniu: ";
    std::cin>>a>>b;
    cout<<std::endl<<"Laikas milisekundemis";
    for(int i=0; i<a; i++)
        n*=10;//pradine reiksme n=n^a
    for(int i=a; i<=b; i++)//iki n^b
    {
        cout<<std::endl<<std::endl<<"10^"<<i<<endl<<"pirminio failo generavimas: "<<genFile(n, "10^"+std::to_string(i)+".txt");//pagrindinio failo generavimas

        uzduotis(n, "10^"+std::to_string(i));//skaitymas, rusiavimas, rasymas i naujus failus
        n*=10;
    }
    return 0;
}
/*int main2()
{


    return 0;
}//*/





