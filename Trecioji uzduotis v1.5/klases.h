#include <iostream>
//#include <vector>
#include <string.h>
class zmogus
{
protected:
    std::string vardas_,
                pavarde_;
public:
    std::string vardas() const {return vardas_;}
    std::string pavarde() const {return pavarde_;}
    virtual void f() = 0;//sios funkcijos veliau nepritaikysiu po perrasymo
};


class studentas: public zmogus
{
private:
    std::vector<int> nd_;
    int egzaminas_;
    double galutinis_;

public:
    void f(){}//panaikinu abstraktuma
    studentas() : egzaminas_(0) { }

    //////////GET'ERIAI
    int nd(int i) const      {return nd_[i];}
    int egzaminas() const     {return egzaminas_;}
    double galutinis() const {return galutinis_;}
    int nd_size() const      {return nd_.size();}

    ///////////SET'ERIAI
    inline void new_galutinis();//apskaiciuoja ir pakeicia galutinis_ reiksme
    inline void readStudent(std::ifstream& in);  // skaito is failo siuo formatu:
    //vardas, pavarde, nd_[0], ... nd_[n], 0, egzaminas_// visi sveikieji skaiciai

    ///////////OPERATOR'IAI
    friend std::ostream& operator<<(std::ostream& out, const studentas &a)
    {
        out<<a.vardas()+" "+a.pavarde();
        for(int i=0; i<a.nd_size(); i++)
            out<<" "<<a.nd(i);//friend funkcijos neturetu turet tiesiogines prieigos prie kintamuju
        out<<" 0 "<<a.egzaminas();
        return out;
    }

    friend bool operator==(const studentas &a, const studentas &b)//ar a adresas arba visi parametrai lygus b
    {
    if(&a==&b)return true;

    if(
        a.vardas()!=b.vardas()&&a.pavarde()!=b.pavarde()||//lygina vardus pavardes
        a.egzaminas()!=b.egzaminas()||                    //lygina egzaminus
        a.nd_size()!=b.nd_size()                          //lygina nd konteineriu dydzius
       )return false;//jei bent vienas is siu parametru skiriasi, return false
    for(int i=0; i<a.nd_size(); i++)//jei ne, tikrins namu darbus
        if(a.nd(i)!=b.nd(i))return false;

    return true;//jei net namu darbai vienodi, tai reiskia vienodi, nors adresai ir skiriasi
    }
    //////////////////lygina galutinius ivertinimus
    friend bool operator>(const studentas &a, const studentas &b)//ar a didesnis uz b
        {return a.galutinis()>b.galutinis();}

    friend bool operator<(const studentas &a, const studentas &b)//ar a mazesnis uz b
        {return a.galutinis()<b.galutinis();}

    friend bool operator>=(const studentas &a, const studentas &b)//ar a didesnis ar lygus b
        {return a.galutinis()>=b.galutinis();}

    friend bool operator<=(const studentas &a, const studentas &b)//ar a mazesnis ar lygus b
        {return a.galutinis()<=b.galutinis();}
};
