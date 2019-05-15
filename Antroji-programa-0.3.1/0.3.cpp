#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <exception>
#include <cctype>
#include <fstream>
#include <numeric>

#include "struct.h"
#include "funkcijos.h"

using std::endl;
using std::cout;

int main()//main susidaro is kintamuju sukurimo, ivesties, blogos ivesties filtravimas su try-catch ir meniu, panaudojancio ivesti.
{
    komandos();//isvedamos komandu (iveskit 0, kad rodytu komandas ir t.t.) reiksmes i konsole
    int n=0;//kelintas mokinys, n+1=kiek mokiniu
    std::vector<mokiniai> mok;
    int z;//switch'o tikrinamas skaicius
    std::string z2;//pirmiau ivedama sio reiksme, veliau ji verciama i z jei z2 sudarytas tik is skaiciu
    bool a=true;

    while(a)//norejau loop, bet nenorejau inversijos
    {
        z=0;
        cout<<endl<<"iveskite komanda: ";
        try{
        std::cin>>z2;//ivedu string'a, kuris gal nera sveikasis skaicius
        cout<<endl;
        for(int i=0; i<z2.size(); i++)//tikrinsiu, ar ivestis yra skaicius
        {
            (z2[i]<'0'||z2[i]>'9')?
            throw z2//jei randu bent viena neskaiciu, apleidziu switch'a
            : z=z*10+(z2[i]-48);//perkurio string'a i int'a. Kadangi tai char'ai, reikia atimt 48. Atsiprasau, kad iki dabar net nepatikrinau, ar si eilute veikia ir kreipiau demesi tik i try-catch gebejima rast bloga ivesti
            //cout<<z<<" ";
       }
        switch(z)
        {
        case 0://vel rodo komandas
        {komandos();        break;}

        case 1://ivesti mokinius
        {ivestmok(mok,n);   break;}

        case 2://pagal vidurki
        {isved(mok,n,true); break;}

        case 3://pagal mediana
        {isved(mok,n,false);break;}

        case 4://skaito is failo
        {skaitMok(mok,n);   break;}

        case 5://rodo mokiniu info
        {rodyt(mok,n);      break;}

        case 9://baigti darba
        {a=false;           break;}

        default :
        {                   break;}
        }//switch pabaiga
        }//try pabaiga
        catch(std::string& a)//suprantu, kad man net nereik perduoti z2, nes jis vis dar prieinamas, bet neturejau ka kita paduoti siai funkcijai
        {
            cout<<a<<" nera tinkama ivestis"<<endl;
        }//nera itin geras try-catch pritaikymas, nes tai galejau pasiekt naudojant ir if'us.
    }//skaiciau apie exception'us bet nemokejau ju normaliai pritaikyt. "std::length_error" gali nutikt, bet atrodo neracionalu, kad kas nors netycia ivestu toki milziniska string'a ir nezinotu kas blogai.
    return 0;//vis del to, visko buna, kitu atvejo sis exception'as neegzistuotu
}
