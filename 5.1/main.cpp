#include <iterator>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <stdio.h>

using std::string;
using std::cout;
string trint(string s, int x)
{
    for(int i=x; i<s.size()-1; i++)
    {
        s[i]=s[i+1];
    }
    s.resize(s.size()-1);
    return s;
};
string next_word(std::istream &in)//nuskaito viena zodi
{
    string s;
    in>>s;
    for(int i=0; i<s.size(); i++)
    {
        if(s[i]>='A' && s[i]<= 'Z')//jei didzioji raide
            s[i] -=('A'-'a');//bus paversta mazaja


        else if(s[i]<'a'||s[i]>'z'){//jei taip pat nera mazoji
        s=trint(s,i);//tai reikia istrint
        i--;//kadangi buvo panaikintas elementas, i jo vieta kitas idetas, todel ji reikia tikrint
        }
    }
    return s;
};
int main()
{
    std::map<string,int> words;

    std::ifstream in("input.txt");
    string s;

    while(!in.eof()){
        s=next_word(in);
        if(s.size()!=0)words[s]++;
    }
    in.close();

    //cout<<txt;
    /*uzduotys:
    kiek kiekvienas pasikartoja
    output'as isoriniame faile skirtingi zodziai ir kiek kartu pamineti
    */
    std::ofstream out("output.txt");
    for(std::map<std::string,int>::iterator i = words.begin(); i!=words.end(); ++i)
        out<<i->first<<' '<<i->second<<std::endl;
    out.close();
   return 0;
}

