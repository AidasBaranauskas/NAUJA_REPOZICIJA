
#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <numeric>//pries tai programa veike be numeric, tik per mano kompa...

using std::cout;
using std::endl;
using std::string;
using std::string;
using std::cin;
struct mokiniai
{
    string vard,pavard;
    std::vector<int> Nd;
    int egz;
};
int n=0;//kelintas mokinys, n+1=kiek mokiniu
double vid(const mokiniai &mok);
double med(mokiniai *mok);
double galutinis(mokiniai *mok, bool Vidur);//kai vidur=true, skaiciuoja galutini naudojant vidurki
void isved(bool Vidur, std::vector<mokiniai> &mok);//kai false, tada su mediena
int fcin(bool Pirmas);//vartotojas iveda mokiniu pazymius
int frand(bool Pirmas);//Nd skaicius, pazymiai ir egz rezultatas sugeneruojamas
void ivestmok(std::vector<mokiniai> &mok);
void komandos();

void skaitMok(std::vector<mokiniai> &mok);
void rodyt(std::vector<mokiniai> &mok);
void rykiavimas(std::vector<mokiniai> &mok);
bool compare(const mokiniai &a,const mokiniai &b);
int main()
{
    std::vector<mokiniai> mok;
    komandos();//isvedamos komandu reiksmes i ekrana
    int z;//komandos intas naudojant meniu
    while(true)//norejau loop, bet nenorejau inversijos
    {
        cout<<endl<<"iveskite komanda: ";
        cin>>z;
        cout<<endl;
        switch(z)
        {
        case 0:
        {
            komandos();
            break;
        }
        case 1:
        {
            ivestmok(mok);
            break;
        }
        case 2:
        {
            isved(true,mok);   //default reiksme yra true, todel vidurkis
            break;
        }
        case 3:
        {
            isved(false,mok);    //jei false, tai bus mediana
            break;
        }
        case 4:
        {
            skaitMok(mok);//skaito is failo
            break;
        }
        case 5:
        {
            rodyt(mok);//rodo visu mokiniu info
            break;
        }
        default : break;
        }
    }
    return 0;
}
int fcin(bool Pirmas)//jei pirmas Nd arba egzamino pazymys, tai Pirmas=true.
{
    //Tada ivedus/ sugeneravus maziau nei 1, funkcija reikalaus, kad vel ivestumet/ generuos nauja
    int z;
    do
    {
        cin>>z;//ivedamas namu darbo arba egzamino pazymys
    }
    while(Pirmas&&z<=0);//apsauga, kad neuzbaigtu Nd ivedimo ciklo neivedus ne vieno namu darbo
    return z;
}
int frand(bool Pirmas)
{
    //generuoja skaicius nuo -1 iki 10, isridenus -1 ar 0 baigiasi ciklas
    int z;
    do
    {
        //nuo -1 iki 12.
        z=rand()%12-1;//Kai nera pirmas namu darbas, reiksmes bus generuojamos kol sugeneruos -1 arba 0. 2/12 tikimybe, kad baigsis ciklas
    }
    while(Pirmas&&z<=0);//neuzbaigs Nd generavimo ciklo usridenus 0 arba -1, kuomet dar nera kitu namu darbu pazymiu
    if(z>0)
        cout<<z<<" ";//taip pat grazins tinkama reiksme egzaminui, nes negalima gaut 0 arba -1
    return z;
}
void ivestmok(std::vector<mokiniai> &mok)
{
    cout<<"Iveskite "<<n+1<<"'ojo mokinio varda ir pavarde"<<endl;
    mok.resize(n+1);
    cin>>mok[n].vard>>mok[n].pavard;

    int (*rfun)(bool),z;//nuo jo priklauso, bus naudotojo ar tikimybes imputas
    bool Rand=true;
    cout<<"Jei norit patys ivesti pazymius- iveskit 0. Ivedus kita skaiciu pazymiu skaicius ir reiksmes bus atsitiktines"<<endl;
    cin>>z;

    Rand=(z!=0);
    if(Rand) //jei random, tai...
    {
        rfun=frand;
        cout<<"Sugeneruotos reiksmes: ";
    }
    else //jei ne, vartotojas ives naudodamas fcin funkcija
    {
        rfun=fcin;
        cout<<"Iveskite Nd pazymius. Ivedus maziau nei 1 baigsis ivestis: ";
    }

    mok[n].Nd.push_back(rfun(true));//bent vienas namu darbas
    while(true)
    {
        z=rfun(false);
        if(z<=0)
            break;
        mok[n].Nd.push_back(z);
    }
    if(Rand)
    {
        cout<<endl<<"Egzamino pazymys: ";
        z=frand(true);
    }
    else
    {
        cout<<endl<<"Iveskite egzamino pazymi: ";
        z=fcin(true);
    }
    mok[n].egz=z;
    n++;
}
void skaitMok(std::vector<mokiniai> &mok)
{
    std::ifstream in("kursiokai.txt");
    string z;
    bool bol=true;
    int m=-3;
    while(bol)
    {
        in>>z;
        m++;
        if(z[0]=='E')bol=false;//jei egzaminas
    }
    while(!in.eof())
    {
        mok.resize(n+1);
        in>>mok[n].vard>>mok[n].pavard;
        mok[n].Nd.resize(m);
        for(int i=0;i<m;i++){in>>mok[n].Nd[i];}
        in>>mok[n].egz;
        n++;
    }
    in.close();
}
void komandos()
{
    cout<<"Pradeti naujo mokinio info ivedima- 1"<<endl;
    cout<<"Rodyti visu mokiniu vidurkius- 2"<<endl;
    cout<<"Rodyti visu mokiniu medianas- 3"<<endl;
    cout<<"Skaityti mokiniu info is failo- 4"<<endl;
    cout<<"Rodyti mokiniu info- 5"<<endl;
    cout<<"Rodyti komandas- 0"<<endl;
}
double vid(const mokiniai &mok)//perduodu kaip struktura, nes nenaudoju vektoriaus savybiu
{
    return std::accumulate(mok.Nd.begin(), mok.Nd.end(), 0.0)/mok.Nd.size();
};
double med(mokiniai *mok)
{
    std::sort(mok->Nd.begin(),mok->Nd.end());
    int m=mok->Nd.size();

    return m%2==0?float(mok->Nd[m/2-1]+mok->Nd[m/2])/2.
           :mok->Nd[(m-1)/2];
}
double galutinis(mokiniai *mok, bool Vidur)
{
    double z=Vidur ? vid(*mok) : med(mok);
    return 0.4*z+0.6*mok->egz;
}
void isved(bool Vidur, std::vector<mokiniai> &mok)
{
    rykiavimas(mok);
    srand(time(NULL));//norejau ji det i frand, bet tada visi pazymiai vienodi. Jei ivestmok- visi mokiniai vienodi
    string S[3]= {"Pavarde","Vardas","Galutinis"};
    if(Vidur)//jei skaiciuos naudojant vidurki...
        S[2]+="(Vid.)";
    else
        S[2]+="(Med.)";
    int varilg=S[0].length(),pavilg=S[1].length();
    for(int i=0; i<n; i++)
    {
        if(mok[i].vard.length()>varilg)
            varilg=mok[i].vard.length();
        if(mok[i].pavard.length()>pavilg)
            pavilg=mok[i].pavard.length();
    }
    const string tarpas(varilg-S[0].length(),' '),tarpas2(pavilg-S[1].length(),' ');
    S[0]+=tarpas+' ';
    S[1]+=tarpas2+' ';
    const string SS=S[0]+S[1]+S[2];
    cout<<endl<<SS<<endl;
    for(int i=0; i<SS.length()+5; i++)
        cout<<'-';
    cout<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<mok[i].vard<<std::setw(S[0].length()-mok[i].vard.length()+mok[i].pavard.length())
            <<mok[i].pavard<<std::setw(S[1].length()-mok[i].pavard.length())
            <<" "<<std::setprecision(3)<<galutinis(&mok[i],Vidur)<<endl;
        //cia visur viena eilute
    }
}
//kambariokas padejo debuginant.
void rodyt(std::vector<mokiniai> &mok)
{
    if(n!=0)cout<<"Visu mokiniu vardai, pavardes, Nd ir egzaminio pazymiai"<<endl;
    else cout<<"Nera ivesta ar nuskaityta mokiniu"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<mok[i].vard<<" "<<mok[i].pavard<<" ND: ";
        for(int j=0; j<mok[i].Nd.size(); j++)cout<<mok[i].Nd[j]<<" ";
        cout<<"Egz: "<<mok[i].egz<<endl;
    }
}
bool compare(const mokiniai &a,const mokiniai &b)
{
  //  if(a==b)
  if(a.vard==b.vard)return(a.pavard<b.pavard);
    return (a.vard<b.vard);
}
void rykiavimas(std::vector<mokiniai> &mok)
{
    std::sort(mok.begin(),mok.end(),(compare));
}
