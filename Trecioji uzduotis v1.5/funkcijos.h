using std::endl;
using std::cout;
#include "random.hpp"

#define time     high_resolution_clock::time_point
#define now      high_resolution_clock::now
#define duration duration_cast<milliseconds>
#define vstud    std::vector<studentas>//                   vstud=vector<studentas>
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
        out<<"0 "<<rrand(1,10)<<endl;//0 indikuoja Nd paz pabaiga, po jo egzamino pazymys
    }
    out.close();

    return duration(now()-t1).count();
}
auto gen(const int n, const std::string pav, vstud &mok)//skaito is failo i studentas
{
    time t1 = now();

    std::ifstream in(pav);
    studentas *rmok;//laikinas objektas
    mok.resize(n);
    for(int i=0; i<n; i++)
    {
        rmok=&mok[i];
        rmok->readStudent(in);
    }
    in.close();

    return duration(now()-t1).count();
}
auto splitVec(const int n, const std::string pav, vstud &mok, vstud &kietekai)
{
    time t1 = now();

    int z=n/2,//z tiklas yra kelintas studentas pirmas islaike
    puse=z;//puse yra skaicius, kuriuo z artes link tikslo

    //puse vis mazes dvigubai kol bus lygus 1
    double riba=5;//minimalus galutinis pazymys norint islaikyti.
    bool islaike;//true jei islaike
    do
    {
        puse=puse/2+puse%2;
        islaike=(mok[z].galutinis()>=riba);
        (islaike)? z-=puse: z+=puse;
    }while(puse!=1||!islaike);//baigiasi jei arti tikslo tarp islaikusiu ir ne
    //ir jei islaike
    while(mok[z].galutinis()<riba)
        z++;//kadangi pries si cikla islaike, tai mok[z].galutinis>=5,
        //todel islaikymo riba nebus persokta ir nesisuks iki failo pabaigos
        //cout<<endl<<endl<<endl<<n<<" "<<z<<endl;
    kietekai.resize(n-z);//pakeitus resize i reserve, rusiavimas veiks 30% greiciau... bet crash'ins dirbant su butent 10 studentu. Vis dar nesuprantu kodel
    std::move(mok.begin()+z,mok.end(),kietekai.begin());
    mok.erase(mok.begin()+z,mok.end());

    return duration(now()-t1).count();
}
auto rasymas(const int n, const std::string pav, vstud &mok, vstud &kietekai)
{
    time t1 = now();

    std::ofstream out(pav+" vector_lievi.txt");//rasymas lievuju i failus
    for(int i=0; i<mok.size(); i++)
        out<<mok[i]<<endl;

    out.close();


    std::ofstream out2(pav+" vector_kietekai.txt");//rasymas kieteku i failus
    for(int i=0; i<kietekai.size(); i++)
        out2<<kietekai[i]<<endl;

    out2.close();
    return duration(now()-t1).count();
}
void uzduotis(const int n, const std::string pav)
{
    vstud mok, kietekai;
    cout<<endl<<"skaitymas is failo: "<<gen(n,pav+".txt",mok)<<endl;//skaitymo is failo trukme
    rykiavimas(mok);
    cout<<"rusiavimas i grupes: "<<splitVec(n,pav,mok,kietekai)<<endl;//rusiavimo trukme
    cout<<"rasymas i failus: "<<rasymas(n,pav,mok,kietekai);//rasymo i kieteku ir lievu failus trukme
    mok.clear(),kietekai.clear();
}

