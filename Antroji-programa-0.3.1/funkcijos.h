using std::endl;
using std::cout;
double vid(mokiniai *mok)
{
    return std::accumulate(mok->Nd.begin(), mok->Nd.end(), 0.0)/mok->m;
};
double med(mokiniai *mok)
{
    std::sort(mok->Nd.begin(),mok->Nd.end());
    int m=mok->Nd.size();//kiek namu darbu

    (m%2==0)?//jei lyginis pazymiu skaicius, tai jie skaiciuojami paimant ju vidurki
        return float(mok->Nd[m/2-1]+mok->Nd[m/2])/2.://randa viduriniu vidurki
    return mok->Nd[(m-1)/2];//randa vidurini
}
double galutinis(mokiniai *mok, bool Vidur)
{
    double z;
    (Vidur)?
        z=vid(mok)://jei galutinis priklauso nuo vidurkio,
        z=med(mok);
    return 0.4*z+0.6*mok->egz;
}
int fcin(bool Pirmas,bool bevertis)//jei pirmas Nd arba egzamino pazymys, tai Pirmas=true.
{//man reikejo idet reiksme vien del to, nes fcin ir frand turi priimt vienodus imputus, o antra bool reiksme reikalinga tik frand funkcijai
    //Tada ivedus/ sugeneravus maziau nei 1, funkcija reikalaus, kad vel ivestumet/ generuos nauja
    int z;
    do
    {
        std::cin>>z;//ivedamas namu darbo arba egzamino pazymys
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
        z=rand()%12-1;//Kai nera pirmas namu darbas, reiksmes bus generuojamos kol sugeneruos -1 arba 0. 2/12 tikimybe, kad baigsis ciklas
    }
    while(Pirmas&&z<=0);//neuzbaigs generavimo isridenus 0 arba -1, kuomet dar nera kitu namu darbu pazymiu
    if(z>0)
        cout<<z<<" ";
    return z;
}
void ivestmok(std::vector<mokiniai> &mok, int &n)
{
    cout<<"Iveskite "<<n+1<<"'ojo mokinio varda ir pavarde"<<endl;
    mok.resize(n+1);
    std::cin>>mok[n].vard>>mok[n].pavard;

    int (*rfun)(bool),z;//nuo jo priklauso, bus naudotojo ar tikimybes imputas
    bool Rand=true;
    cout<<"Jei norit patys ivesti pazymius- iveskit 0. Ivedus kita skaiciu pazymiu skaicius ir reiksmes bus atsitiktines"<<endl;
    std::cin>>z;

    Rand=(z!=0);
    (Rand)?{//jei random, tai...
        rfun=frand;
        cout<<"Sugeneruotos reiksmes: ";}:
    {//jei ne, tai vartotojas ives naudodamas fcin funkcija
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
    (Rand)?{
        cout<<endl<<"Egzamino pazymys: ";
        z=frand(true);
    }:{
        cout<<endl<<"Iveskite egzamino pazymi: ";
        z=fcin(true);
    }
    mok[n].egz=z;
    n++;
    cout<<endl;
}
void komandos()
{
    cout<<"Pradeti naujo mokinio info ivedima- 1"<<endl;
    cout<<"Rodyti visu mokiniu vidurkius- 2"<<endl;
    cout<<"Rodyti visu mokiniu medianas- 3"<<endl;
    cout<<"Skaityti mokiniu info is failo- 4"<<endl;
    cout<<"Rodyti mokiniu info- 5"<<endl;
    cout<<"Baigti darba- 9"<<endl;
    cout<<"Rodyti komandas- 0"<<endl;
}
void skaitMok(std::vector<mokiniai> &mok, int &n)
{
    std::ifstream in("kursiokai.txt");
    std::string z;
    bool bol=true;
    int m=-3;
    while(bol)
    {//cin pav,m=-2; cin var,m=-1, cin ND1,m=0... cin ND5;m=4, cin Egz;m=5
        in>>z;
        m++;
        if(z[0]=='E')bol=false;//jei egzaminas
    }
    while(!in.eof())
    {
        mok.resize(n+1);
        in>>mok[n].vard>>mok[n].pavard;
        mok[n].m=m;
        mok[n].Nd.resize(m);
        for(int i=0;i<m;i++){in>>mok[n].Nd[i];}
        in>>mok[n].egz;
        n++;
    }
    in.close();
}
bool compare(const mokiniai &a,const mokiniai &b)
{
    if(a.vard==b.vard)return(a.pavard<b.pavard);
    else return (a.vard<b.vard);
}
void rykiavimas(std::vector<mokiniai> &mok)
{
    std::sort(mok.begin(),mok.end(),(compare));
}
void isved(std::vector<mokiniai> &mok, int &n, bool Vidur)
{
    srand(time(NULL));
    using std::string;
    rykiavimas(mok);
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
        cout<<mok[i].vard<<std::setw(S[0].length()-mok[i].vard.length()+mok[i].pavard.length());
        cout<<mok[i].pavard<<std::setw(S[1].length()-mok[i].pavard.length());
        cout<<" "<<std::setprecision(3)<<galutinis(&mok[i],Vidur)<<endl;
    }
}
void rodyt(const std::vector<mokiniai> &mok, int n)
{
    if(n!=0)cout<<"Visu mokiniu vardai, pavardes, Nd ir egzaminio pazymiai"<<endl;
    else cout<<"Nera ivesta ar nuskaityta mokiniu"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<mok[i].vard<<" "<<mok[i].pavard<<" ND: ";
        for(int j=0; j<mok[i].m; j++)cout<<mok[i].Nd[j]<<" ";
        cout<<"Egz: "<<mok[i].egz<<endl;
    }
}
