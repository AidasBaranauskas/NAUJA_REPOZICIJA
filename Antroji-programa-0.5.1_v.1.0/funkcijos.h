using std::endl;
using std::cout;
using namespace std::chrono;
int rrand(int a,int b)
{
    using Random=effolkronium::random_static;
    return Random::get(a,b);
}
double vid(const mokiniai &mok)//skaiciuoja vidurki
{
    return std::accumulate(mok.Nd.begin(), mok.Nd.end(), 0.0)/mok.Nd.size();
};
double galutinis(const mokiniai &mok)//skaiciuoja galutini
{
    return 0.4*vid(mok)+0.6 * mok.egz;
}
bool compare(const mokiniai &a, const mokiniai &b)//lygina galutinius ivertinimus
{
    return a.galutinis<b.galutinis;
}
void rykiavimas(std::vector<mokiniai> &mok)
{
    std::sort(mok.begin(),mok.end(),(compare));
}
void rykiavimas2(std::deque<mokiniai> &mok)//del TEMPLATE nenaudojimo, programa pailgejo ir turi
//beveik identiskas dalis, isskaitant deque funkcija (ji lygi vector nes nepritaikiau deque savybiu)
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
    mokiniai mok;//talpino vieno mokinio info, nes reikes jo galutini suskaiciuot
    for(int j=0; j<n; j++)
    {
        out<<genVard()<<" "<<genVard()<<" ";//vardas, pavarde
        do
        {
            mok.Nd.push_back(rrand(1,10));
            out<<mok.Nd.back()<<" ";
        }
        while(rrand(0,3)!=0); //jei salyga neispildyta, tai baigs generuot Nd pazymius. Bus bent vienas Nd pazymys
        mok.egz=(rrand(1,10));
        out<<"0 "<<mok.egz<<" "<<galutinis(mok)<<endl;//0 indikuoja Nd paz pabaiga, po jo Egzamino paz.
        //del patikros, teko ir galutini ten ideti. Uz sios funkcijos ribu galitinio daugiau neteks skaiciuot

        mok.Nd.clear();//tik ND keiciami naudojant PUSH_BACK, kitos reiksmes perrasomos kitu
    }
    out.close();
}
void gen(const int n, const std::string pav, auto *mok)//sukuria viena mokiniai ir push_back ji duotam konteineriui
{
    std::ifstream in(pav);
    int a;//vieno ND reiksme arba '0'
    for(int i=0; i<n; i++)
    {
        mokiniai *rmok=new mokiniai;
        in>>rmok->vard>>rmok->pavard;
        in>>a;
        while(a!=0)//Nd ir egzamino pazymiai atskirti '0'
        {
            rmok->Nd.push_back(a);
            in>>a;
        }
        in>>rmok->egz>>rmok->galutinis;

        mok->push_back(*rmok);
    }
    in.close();
}
auto splitVec(const int n, const std::string pav, std::vector<mokiniai> &mok)
{
    int z=n/2,
    puse=z;//z yra nariu skaicius per kuriuos pajudes tikrinima reiksme mok[z].galutinis,
    //vis mazes dvigubai bet nebus mazesnis nei 1
    double riba=5;
    bool islaike;//true jei islaike
    do //suzinau, ties kuriuo mok elementu prasideda neislaike
    {
        puse=puse/2+puse%2;
        islaike=(mok[z].galutinis>=riba);
        (islaike)? z-=puse: z+=puse;
    }while(puse!=1||!islaike);//baigiasi while jei itin arti ribos tarp islaikusiu ir ne,
    //ir jei islaike
    while(mok[z].galutinis<riba)//beveik visada suksis 0-1 karta, kartais 5
        z++;//kadangi pries si cikla islaike, tai mok[z].galutinis>=5,
        //todel sis ciklas nesisuks iki failo pabaigos praleidus islaikymo riba
    std::vector<mokiniai> kietekai(n-z);
    std::move(mok.begin()+z,mok.end(),kietekai.begin());
    mok.erase(mok.begin()+z,mok.end());

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

/////////////////////////////////////failu generavimas
    int a=0;//kiek kartu mokinys klaidingai surusiuotas
    std::ofstream out(pav+" vector_lievi.txt");
    for(int i=0; i<mok.size(); i++)
    {
        out<<mok[i].vard<<" "<<mok[i].pavard<<" "<<mok[i].Nd[0]<<" ";
        for(int j=0; j<mok[i].Nd.size(); j++)
            out<<mok[i].Nd[j]<<" ";
        out<<mok[i].egz<<" "<<mok[i].galutinis<<endl;
        if(mok[i].galutinis>=5.0)a++;
    }
    if(a!=0){cout<<endl<<"kietekai per zemai: "<<a;a=0;}//bent karta turi klysti, kad sia klaida mestu
    out.close();

    std::ofstream out2(pav+" vector_kietekai.txt");
    for(int i=0; i<kietekai.size(); i++)
    {
        out2<<kietekai[i].vard<<" "<<kietekai[i].pavard<<" "<<kietekai[i].Nd[0]<<" ";
        for(int j=0; j<kietekai[i].Nd.size(); j++)
            out2<<kietekai[i].Nd[j]<<" ";
        out2<<kietekai[i].egz<<" "<<kietekai[i].galutinis<<endl;
        if(kietekai[i].galutinis<5.0)a++;
    }
    if(a!=0)cout<<endl<<"lievi per aukstai: "<<a;
    out2.close();
    mok.clear(),kietekai.clear();
    return t1;//grazino laiku uztrukta generuojant failus
}
auto splitList(const int n, const std::string pav, std::list<mokiniai> &mok)
{
    double riba=5;
    std::list<mokiniai>::iterator it=mok.begin(),it2=it;

    advance(it,n/9*5);//5/9 tikimybe islaikyti, del to arti mok(n*5/9) elemento yra riba
    // skiriati islaikusius ir ne
    //Pamirsau pasakyt bet viskas isrykiuota didejimo tvarka. galutinis(it)<galutinis(it++)

    while(it->galutinis>=riba)//kol islaike iesko neislaikusiu
        it--;
    while(it->galutinis<riba)//kol neislaike iesko islaikusiu
        it++;//vienas is siu ciklu suksis tik karta, bet rezultatas bus tas pats
        //nepriklausomai nuo advance pasiekto elemento islaikymo
    std::list<mokiniai> kietekai;
    kietekai.splice(kietekai.begin(),mok,it,mok.end());//rykiavimas baigtas

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    /////////////////// failu generavimas
    int a=0;
    std::ofstream out(pav+" list_lievi.txt");
    for(it=mok.begin(); it!=mok.end(); it++)
    {
        out<<it->vard<<" "<<it->pavard<<" "<<it->Nd[0]<<" ";
        for(int j=0; j<it->Nd.size(); j++)
            out<<it->Nd[j]<<" ";
        out<<it->egz<<" "<<it->galutinis<<endl;
        if(it->galutinis>=5.0)a++;
    }
    if(a!=0){cout<<endl<<"kietekai per zemai: "<<a;a=0;}
    out.close();

    std::ofstream out2(pav+" list_kietekai.txt");
    for(it=kietekai.begin(); it!=kietekai.end(); it++)
    {
        out2<<it->vard<<" "<<it->pavard<<" "<<it->Nd[0]<<" ";
        for(int j=0; j<it->Nd.size(); j++)
            out2<<it->Nd[j]<<" ";
        out2<<it->egz<<" "<<it->galutinis<<endl;
        if(it->galutinis<5.0)a++;
    }
    if(a!=0)cout<<endl<<"lievi per aukstai: "<<a;
    out2.close();

    mok.clear(),kietekai.clear();
    return t1;
}
auto splitDeque(const int n, const std::string pav, std::deque<mokiniai> &mok)
{//naudosiu vector koda nes deque savybiu nepritaikiau
    int z=n/2, puse=z;
    double riba=5;
    bool islaike;
    do
    {
        puse=puse/2+puse%2;
        islaike=(mok[z].galutinis>=riba);
        (islaike)? z-=puse: z+=puse;
    }while(puse!=1||!islaike);
    while(mok[z].galutinis<riba)
        z++;
    std::deque<mokiniai> kietekai(n-z);
    std::move(mok.begin()+z,mok.end(),kietekai.begin());
    mok.erase(mok.begin()+z,mok.end());


    high_resolution_clock::time_point t1 = high_resolution_clock::now();

/////////////////////////////////////failu generavimas
    int a=0;
    std::ofstream out(pav+" deque_lievi.txt");
    for(int i=0; i<mok.size(); i++)
    {
        out<<mok[i].vard<<" "<<mok[i].pavard<<" "<<mok[i].Nd[0]<<" ";
        for(int j=0; j<mok[i].Nd.size(); j++)
            out<<mok[i].Nd[j]<<" ";
        out<<mok[i].egz<<" "<<mok[i].galutinis<<endl;
        if(mok[i].galutinis>=5.0)a++;
    }
    if(a!=0){cout<<endl<<"kietekai per zemai: "<<a;a=0;}
    out.close();

    std::ofstream out2(pav+" deque_kietekai.txt");
    for(int i=0; i<kietekai.size(); i++)
    {
        out2<<kietekai[i].vard<<" "<<kietekai[i].pavard<<" "<<kietekai[i].Nd[0]<<" ";
        for(int j=0; j<kietekai[i].Nd.size(); j++)
            out2<<kietekai[i].Nd[j]<<" ";
        out2<<kietekai[i].egz<<" "<<kietekai[i].galutinis<<endl;
        if(kietekai[i].galutinis<5.0)a++;
    }
    if(a!=0)cout<<endl<<"lievi per aukstai: "<<a;
    out2.close();

    mok.clear(),kietekai.clear();
    return t1;
}
void uzduotis(const int n, const std::string pav)
{
    std::vector<mokiniai> mok;
    auto t1=high_resolution_clock::now();
    gen(n,pav+".txt",&mok);
    cout<<endl<<"vector: skaitymas is failo: "<<duration_cast<milliseconds>
    (high_resolution_clock::now()-t1).count();//skaitymo is failo trukme

    rykiavimas(mok);

    t1=high_resolution_clock::now();
    cout<<",   rusiavimas i grupes: "<<duration_cast<milliseconds>
        (splitVec(n,pav,mok)-t1).count();//rusiavimo trukme

////////////////////////
    std::list<mokiniai> mok2;
    t1=high_resolution_clock::now();
    gen(n,pav+".txt",&mok2);
    cout<<endl<<"list: skaitymas is failo: "<<duration_cast<milliseconds>
    (high_resolution_clock::now()-t1).count();

    mok2.sort(compare);

    t1=high_resolution_clock::now();
    cout<<",   rusiavimas i grupes: "<<duration_cast<milliseconds>
        (splitList(n,pav,mok2)-t1).count();

/////////////////////////
    std::deque<mokiniai> mok3;
    t1=high_resolution_clock::now();
    gen(n,pav+".txt",&mok3);
    cout<<endl<<"deque: skaitymas is failo: "<<duration_cast<milliseconds>
    (high_resolution_clock::now()-t1).count();

    rykiavimas2(mok3);

    t1=high_resolution_clock::now();
    cout<<",   rusiavimas i grupes: "<<std::setprecision(5)<<duration_cast<milliseconds>
        (splitDeque(n,pav,mok3)-t1).count();
}

