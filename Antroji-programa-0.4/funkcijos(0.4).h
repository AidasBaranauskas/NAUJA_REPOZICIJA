std::string genVard()
{
    int z;
    std::string vardas;
    vardas[0]=rand()%26+65;//vardas arba pavarde prasideda didziaja raide

    do
    {
    vardas+=rand()%26+97;//likosios raides mazosios
    z=rand()%4;//1/4 tikimybe, kad baigsis ciklas, todel vardo ilgis atsitiktinis
    }while(z!=0);
    return vardas;
}
void uzduotis()//sito failo funkcijos naudoja nauja mok reiksme
{
    using namespace std::chrono;
    int z2=5;//jei z2=2, tai bus 2 saraso failai su 10 ir 100 mokiniu
    for(int i=0; i<z2; i++)//i=0,mok(10),i=1,mok(100)...i=4,mok(100000)
    {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    std::string txt;
    int z=1;
    for(int j=0; j<=i; j++)
        {
            z*=10;//kiek studentu 10-10 000
            txt+='0';//koks pavadinimas. Failai bus "studentai.10"-"studentai.100000"
        }
    std::vector<mokiniai> mok(z);
    std::ofstream out("studentai.1"+txt+".txt");
    for(int j=0; j<z; j++)//ciklas suksis 10-100000 kartu
    {//norejau naudot atskira funkcija, bet tingejau jai perduot "out"
        mok[j].vard=genVard();//duoda varda
         out<<mok[j].vard<<" ";
        mok[j].pavard=genVard();//duoda varda
         out<<mok[j].pavard<<" ";

        int z3=frand(true,false);
        mok[j].Nd.push_back(z3);
         out<<z3<<" ";
        mok[j].m++;
        while(true)
        {
            z3=frand(false,false);//gali but 0 ar -1, taip uzbaigiant cikla
            if(z3<=0)//antras false pasako, kad nebus sakomos reiksmes i konsole
                break;
            mok[j].Nd.push_back(z3);
             out<<z3<<" ";

            mok[j].m++;
        }
    z3=frand(true,false);
    mok[j].egz=z3;
     out<<z3<<std::endl;
    }//generavimas baigiasi
    out.close();
    rykiavimas(mok);
    //prasideda antra 0.4 uzduoties dalis, kuri sukuria dar 2 failus

    bool Z[z];//vietoj antro vectoriaus kurimo, surusiuosi sita naudojant bool'a. Default reiksme yra false arba tiksliau, nera daugiau nei 5. Atmintis bus tobulai naudojama
    std::ofstream ger("studentaiGer.1"+txt+".txt");//mainais, skaitymas vektoriaus uztruks ilgiau del bool patikros
    std::ofstream blo("studentaiBlog.1"+txt+".txt");//kai balas maziau arba lygu 5.0
    for(int j=0; j<z; j++)
    {
        if(galutinis(&mok[j],true)>5.0)
        {
            Z[i]=true;
             ger<<mok[j].vard<<" "<<mok[j].pavard<<std::endl;
        }
        else
        {
             blo<<mok[j].vard<<" "<<mok[j].pavard<<std::endl;
        }
    }
    ger.close();
    blo.close();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2-t1).count();
    std::cout<<std::endl<<duration;
    }//for'o pabaiga ir po kiekvieno ciklo, sukurti 3 failai
}//labai tikiuos, kad atmintis atlaisvinama po ciklo
