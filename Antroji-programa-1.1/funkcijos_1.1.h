using std::endl;
using std::cout;
#include "random.hpp"

using namespace std::chrono;
int rrand(int a,int b)
{
    using Random=effolkronium::random_static;
    return Random::get(a,b);
}
void rykiavimas(std::vector<studentas> &mok)
{
    std::sort(mok.begin(),mok.end(),(compare));
}
std::string genVard()//generuoja varda arba pavarde
{
    std::string vardas{rrand('A','Z')};//vardas arba pavarde prasideda didziaja raide
    do
    {
        vardas+=rrand('a','z');//likosios raides mazosios
    }
    while(rrand(0,4)!=0); //vardo ilgis bus atsitiktinis, 1/5 tikimybe, kad baigs cikla
    return vardas;
}
void genFile(const int n, const std::string pav)//pradini faila kuria
{
    std::ofstream out(pav);//visi_10^i.txt, failo pav sako mokiniu skaiciu jame
    for(int j=0; j<n; j++)
    {
        out<<genVard()<<" "<<genVard()<<" ";
        do
        {
            out<<rrand(1,10)<<" ";
        }//atsitiktinis Nd skaicius
        while(rrand(0,3)!=0); //jei salyga neispildyta, baigs generuot Nd pazymius. Bus bent vienas Nd pazymys
        out<<"0 "<<rrand(1,10)<<endl;//0 indikuoja Nd paz pabaiga, po jo egzamino pazymys
    }
    out.close();
}
void gen(const int n, const std::string pav, std::vector<studentas> &mok)//skaito is failo i studentas
{
    std::ifstream in(pav);
    studentas *stud;//laikinas objektas
    mok.resize(n);
    for(int i=0; i<n; i++)
    {
        stud=&mok[i];
        stud->readStudent(in);
    }
    in.close();
}
auto splitVec(const int n, const std::string pav, std::vector<studentas> &mok)
{
    int z=n/2,
    puse=z;//z yra nariu skaicius per kuriuos pajudes tikrinima reiksme mok[z].galutinis,
    //vis mazes dvigubai bet nebus mazesnis nei 1
    double riba=5;
    bool islaike;//true jei islaike
    do //suzinau, ties kuriuo mok elementu prasideda neislaike studentai
    {
        puse=puse/2+puse%2;
        islaike=(mok[z].galutinis()>=riba);//suprantu, kad si vieta per paini, bet jos darbas yra itin priarteti prie ribos, riba pasiekiama antrama while loop'e
        (islaike)? z-=puse: z+=puse;
    }while(puse!=1||!islaike);//baigiasi while jei arti ribos tarp islaikusiu ir ne
    //ir jei islaike
    while(mok[z].galutinis()<riba)//beveik visada suksis 0-1 karta, kartais 5
        z++;//kadangi pries si cikla islaike, tai mok[z].galutinis>=5,
        //todel islaikymo riba nebus persokta ir nesisuks iki failo pabaigos
    std::vector<studentas> kietekai(n-z);
    std::move(mok.begin()+z,mok.end(),kietekai.begin());
    mok.erase(mok.begin()+z,mok.end());

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

/////////////////////////////////////failu generavimas
    //int a=0;//kiek kartu mokinys klaidingai surusiuotas
    std::ofstream out(pav+" vector_lievi.txt");
    for(int i=0; i<mok.size(); i++)
    {
        out<<mok[i].vardas()<<" "<<mok[i].pavarde()<<" "<<mok[i].nd(0)<<" ";
        for(int j=0; j<mok[i].nd_size(); j++)
            out<<mok[i].nd(j)<<" ";
        out<<mok[i].egzaminas()<</*" "<<mok[i].galutinis()<<*/endl;
        //if(mok[i].galutinis()>=5.0)a++;
    }
    //if(a!=0){cout<<endl<<"kietekai per zemai: "<<a;a=0;}
    out.close();//jei bus bent viena klaida, tai isvedimo laukas rodys klaidu skaiciu
    //del efektyvumo, gal reikejo uzkomentuoti sia dali...

    std::ofstream out2(pav+" vector_kietekai.txt");
    for(int i=0; i<kietekai.size(); i++)
    {
        out2<<kietekai[i].vardas()<<" "<<kietekai[i].pavarde()<<" "<<kietekai[i].nd(0)<<" ";
        for(int j=0; j<kietekai[i].nd_size(); j++)
            out2<<kietekai[i].nd(j)<<" ";
        out2<<kietekai[i].egzaminas()<</*" "<<kietekai[i].galutinis()<<*/endl;//uzkomentavau patikra bei galutinio ivertinimo isvedima
        //if(kietekai[i].galutinis()<5.0)a++;
    }
    //if(a!=0)cout<<endl<<"lievi per aukstai: "<<a;
    out2.close();
    mok.clear(),kietekai.clear();
    return t1;//grazino laiku uztrukta generuojant failus
}
void uzduotis(const int n, const std::string pav)
{
    std::vector<studentas> mok;
    auto t1=high_resolution_clock::now();
    gen(n,pav+".txt",mok);
    cout<<endl<<"vector: skaitymas is failo: "<<duration_cast<milliseconds>
    (high_resolution_clock::now()-t1).count();//skaitymo is failo trukme

    rykiavimas(mok);

    t1=high_resolution_clock::now();
    cout<<",   rusiavimas i grupes: "<<duration_cast<milliseconds>
        (splitVec(n,pav,mok)-t1).count();//rusiavimo trukme
}

