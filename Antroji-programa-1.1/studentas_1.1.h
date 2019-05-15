// Reikia includinti visas priklausomybes: <iostream>, <string>, <vector>, "mediana.h"

#include <iostream>
#include <vector>
#include <string.h>
class studentas {
private:
    std::string vardas_,
                pavarde_;

    std::vector<int> nd_;
    int egzaminas_;
    double galutinis_;

public:
    studentas() : egzaminas_(0) { }  // default konstruktorius default egzamino reiksme = 0
    //studentas(std::istream& is); dar nesuprantu, sios dalies paskirties
    std::string vardas() const { return vardas_; }    // get'eriai, inline
    std::string pavarde() const { return pavarde_; }  // get'eriai, inline
    int nd(int i) const { return nd_[i]; }  // get'eriai, inline by default
    int egzaminas() const { return egzaminas_; }  // get'eriai, inline
    double galutinis() const { return galutinis_; }  // get'eriai, inline

    int nd_size() const { return nd_.size(); }  // get'eriai, inline

    inline void new_galutinis();//pakeicia galutinis_ reiksme i nauja apskaiciuota
    inline void readStudent(std::ifstream& in);  // set'eriai

    //inline void test();//egzaminas_=2; patikra, ar veikia
};

bool compare(const studentas&, const studentas&);

