#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string.h>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <chrono>
#include <random>
#include "struct.h"
#include "random.hpp"
#include "funkcijos.h"

int main()
{
    int a,b,n=1;
    std::cout<<"Iveskite A ir B, zinant, kad uzduotis bus atlikta su nuo 10^A iki 10^B mokiniu"<<std::endl<<
    "pavyzdziui: jei A=2, B=4, bus 100, 1000 ir 10000 mokiniu: ";
    std::cin>>a>>b;
    std::cout<<"Laikas milisekundemis"<<endl;
    for(int i=0; i<a; i++)n*=10;//pradine reiksme n=n^a
    for(int i=a; i<=b; i++)
    {
        std::cout<<std::endl<<"10^"<<i;
        genFile(n, "10^"+std::to_string(i)+".txt");//failu pavadinimai bus 10^i.txt
        uzduotis(n, "10^"+std::to_string(i));

        n*=10;
    }
    return 0;
}
