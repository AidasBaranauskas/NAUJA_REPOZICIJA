using std::endl;
using std::cout;
#include "random.hpp"

#define time     high_resolution_clock::time_point
#define now      high_resolution_clock::now
#define duration duration_cast<milliseconds>
//vstud = vector<studentas>
//define'inau main'e
using namespace std::chrono;
int rrand(int a,int b)
{
    using Random=effolkronium::random_static;
    return Random::get(a,b);
}
void rykiavimas(vstud &mok)
{
    std::sort(mok.begin(),mok.end());//operatoriai < > == realizuoti
}
std::string genVard()//generuoja varda arba pavarde
{
    std::string vardas{rrand('A','Z')};//vardas arba pavarde prasideda didziaja raide.
    do
    {
        vardas+=rrand('a','z');//likosios raides mazosios
    }
    while(rrand(0,4)!=0); //vardo ilgis bus atsitiktinis, 1/5 tikimybe, kad baigs cikla
    return vardas;
}
auto genFile(const int n, const std::string pav)//pradini faila kuria
{
    time t1 = now();

    std::ofstream out(pav);//visi_10^i.txt, failo pav sako mokiniu skaiciu jame
    for(int j=0; j<n; j++)
    {
        out<<genVard()<<" "<<genVard()<<" ";
        do
        {
            out<<rrand(1,10)<<" ";
        }//atsitiktinis Nd skaicius
        while(rrand(0,3)!=0); //jei salyga neispildyta, baigs generuot Nd pazymius. Bus bent vienas Nd pazymys
        out<<"0 "<<rrand(1,10)<<'\n';//0 indikuoja Nd paz pabaiga, po jo egzamino pazymys
    }
    out.close();

    return duration(now()-t1).count();
}
auto genVec(const int n, const std::string pav, vstud &mok)//skaito is failo i studentas
{
    time t1 = now();

    std::ifstream in(pav);
    //studentas *zmok;//laikinas objektas
    studentas *z=&mok[0];
    int abc=0;
    for(int i=0; i<n; i++)
    {
        studentas zmok;
        zmok.readStudent(in);

        z=&mok[0];
        mok.push_back(zmok);

        if(z!=&mok[0])abc++;
    }
    cout<<"\n Realokavimo kartai: "<<abc;
    in.close();

    return duration(now()-t1).count();
}
auto splitVec(const int n, const std::string pav, vstud &mok, vstud &kietekai)
{
    time t1 = now();
    int z=n/2,//z tiklas= mok[z] neislaike, mok[z+1] islaike
    puse=z;//puse yra skaicius, kuriuo z bus mazinamas arba didinamas kol labai priartes tiksla
    double riba=5;//minimalus galutinis pazymys norint islaikyti.
    bool islaike;//true jei islaike
    do
    {
        puse=puse/2;
        islaike=(mok[z].galutinis()>=riba);
        (islaike)? z-=puse: z+=puse;
    }while(puse>1);//baigiasi jei arti tikslo

    while(mok[z].galutinis()<riba){z++;}//jei zemesnis nei ribinis pazymes- paaukstes
    while(mok[z].galutinis()>riba){z--;}//jei aukstesnis nei ribinis pazymys- sumazes. Sie 2 ziklai tik kelis kartus suksis
    //Galejau juos nuo pradziu naudot, bet virsutine dalis pagreitina

    kietekai.resize(n-z);

    std::move(mok.begin()+z,mok.end(),kietekai.begin());
    mok.erase(mok.begin()+z,mok.end());

    return duration(now()-t1).count();
}
auto rasymas(const int n, const std::string pav, vstud &mok, vstud &kietekai)
{
    time t1 = now();

    std::ofstream out(pav+" lievi.txt");//rasymas lievuju i failus
    for(int i=0; i<mok.size(); i++)
        out<<mok[i]<<endl;

    out.close();


    std::ofstream out2(pav+" kietekai.txt");//rasymas kieteku i failus
    for(int i=0; i<kietekai.size(); i++)
        out2<<kietekai[i]<<endl;

    out2.close();
    return duration(now()-t1).count();
}
//uzduotis() sujungta su main, nes atskiros funkcijos naudojimas atrode nereikalingas
