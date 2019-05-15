#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <chrono>
#include <random>
#include "studentas.h"
#include "funkcijos.h"

using std::cout;
/*studentas::studentas(std::istream& is)
{
    readStudent(is);
};//*/
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
    while(a!=0)//Nd ir egzamino pazymiai atskirti '0'
    {
        nd_.push_back(a);
        in>>a;
    }
    in>>egzaminas_;
    new_galutinis();
};
/*void studentas::test()
{
    egzaminas_=2;
}//*/
/*formatas mok failo yra toks
vardas pavarde nd1 nd2 ... ndn 0 egz
*/
bool compare(const studentas& a, const studentas& b) {//ar pirmas mazesnis uz antra
    return a.galutinis()<b.galutinis();
};
int main()
{
    int a,b,n=1;
    cout<<"Iveskite A ir B, zinant, kad uzduotis bus atlikta su nuo 10^A iki 10^B mokiniu"<<std::endl<<
    "pavyzdziui: jei A=2, B=4, bus 100, 1000 ir 10000 mokiniu: ";
    std::cin>>a>>b;
    cout<<"Laikas milisekundemis"<<endl;
    for(int i=0; i<a; i++)n*=10;//pradine reiksme n=n^a
    for(int i=a; i<=b; i++)//iki n^b
    {
        cout<<std::endl<<"10^"<<i;
        //genFile(n, "10^"+std::to_string(i)+".txt");//failo pagrindinio generavimas. Šios dalies trukmė nematuojama
        uzduotis(n, "10^"+std::to_string(i));//likusi uzduoties dalis: matuojama, kaip ilgai skaitė iš failo ir rūšiavo
        n*=10;
    }
    return 0;
}
