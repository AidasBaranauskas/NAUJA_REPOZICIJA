// Reikia includinti visas priklausomybes: <iostream>, <string>, <vector>, "mediana.h"

#include <iostream>
#include <vector>
#include <string.h>
class studentas
{
private:
    std::string vardas_,
        pavarde_;

    std::vector<int> nd_;
    int egzaminas_;
    double galutinis_;

public:
    studentas() : egzaminas_(0) { }  // default konstruktorius default egzamino reiksme = 0
    //studentas(std::istream& is); dar nesuprantu, sios dalies paskirties
    std::string vardas() const
    {
        return vardas_;    // get'eriai, inline
    }
    std::string pavarde() const
    {
        return pavarde_;    // get'eriai, inline
    }
    int nd(int i) const
    {
        return nd_[i];    // get'eriai, inline by default
    }
    int egzaminas() const
    {
        return egzaminas_;    // get'eriai, inline
    }
    double galutinis() const
    {
        return galutinis_;    // get'eriai, inline
    }

    int nd_size() const
    {
        return nd_.size();    // get'eriai, inline
    }

    inline void new_galutinis();//pakeicia galutinis_ reiksme i nauja apskaiciuota
    inline void readStudent(std::ifstream& in);  // set'eriai

    inline void test();//egzaminas_=2; patikra, ar veikia

    friend std::ostream& operator<<(std::ostream& out, const studentas &a)
    {
        out<<a.vardas()+" "+a.pavarde();
        for(int i=0; i<a.nd_size(); i++)
            out<<" "<<a.nd(i);//friend funkcijos neturetu turet tiesiogines prieigos prie kintamuju
        out<<" 0 "<<a.egzaminas();
        return out;
    }

    friend bool operator==(const studentas &a, const studentas &b)//if(adresai vienodi) return true; else return (ar skiriasi parametrai);
    {
    if(&a==&b)return true;

    if(
        a.vardas()!=b.vardas()&&a.pavarde()!=b.pavarde()||//lygina vardus pavardes
        a.egzaminas()!=b.egzaminas()||                    //lygina egzaminus
        a.nd_size()!=b.nd_size()                          //lygina nd konteineriu dydzius
       )return false;//jei bent vienas is siu parametru skiriasi, return false

    for(int i=0; i<a.nd_size(); i++)
        if(a.nd(i)!=b.nd(i))return false;

    return true;//jei visos salygus iki dabar grazino false, parodo, kad visi parametrai vienodi
    }

    friend bool operator>(const studentas &a, const studentas &b)//ar a didesnis uz b
    {
        return a.galutinis()>b.galutinis();
    }

    friend bool operator<(const studentas &a, const studentas &b)//ar a mazesnis uz b
    {
        return a.galutinis()<b.galutinis();
    }

    friend bool operator>=(const studentas &a, const studentas &b)//ar a didesnis ar lygus b
    {
        return a.galutinis()>=b.galutinis();
    }

    friend bool operator<=(const studentas &a, const studentas &b)//ar a mazesnis ar lygus b
    {
        return a.galutinis()<=b.galutinis();
    }
};


