#include "studVPGen.h"

using std::string;
using std::map;
using std::mt19937;
using hrClock = std::chrono::high_resolution_clock; 

void gen_map(Studentas& A)
{
    mt19937 mt(static_cast<unsigned long>(hrClock::now().time_since_epoch().count()));

    std::uniform_int_distribution<int> varduDist(100, 109);
    std::uniform_int_distribution<int> pavMoteruDist(200, 209);
    std::uniform_int_distribution<int> pavVyruDist(300, 309);

    string vardas, pavarde;

    map<int, string> vardai, pavardes_m, pavardes_v;
  
    vardai[100] = "Irma";
    vardai[101] = "Alma";
    vardai[102] = "Irena";
    vardai[103] = "Egle";
    vardai[104] = "Jolanta";
    vardai[105] = "Petras";
    vardai[106] = "Jonas";
    vardai[107] = "Ignas";
    vardai[108] = "Darius";
    vardai[109] = "Simas";

    pavardes_m[200] = "Kazlauskienė";
    pavardes_m[201] = "Petrauskienė";
    pavardes_m[202] = "Jankauskaitė";
    pavardes_m[203] = "Žukauskaitė";
    pavardes_m[204] = "Stankevičiūtė";
    pavardes_m[205] = "Vaitkutė";
    pavardes_m[206] = "Paulauskaitė";
    pavardes_m[207] = "Urbonaitė";
    pavardes_m[208] = "Kavaliauskienė";
    pavardes_m[209] = "Mockutė";

    pavardes_v[300] = "Kazlauskas";
    pavardes_v[301] = "Petrauskas";
    pavardes_v[302] = "Jankauskas";
    pavardes_v[303] = "Žukauskas";
    pavardes_v[304] = "Stankevičius";
    pavardes_v[305] = "Vaitkus";
    pavardes_v[306] = "Paulauskas";
    pavardes_v[307] = "Urbonas";
    pavardes_v[308] = "Kavaliauskas";
    pavardes_v[309] = "Mockus";
  
    vardas = vardai[varduDist(mt)];
  
    if (!vardas.empty() && vardas.back() == 's')
    {
        pavarde = pavardes_v[pavVyruDist(mt)];
    }
    else
    {
        pavarde = pavardes_m[pavMoteruDist(mt)];
    }
    
    A.vardas = vardas;
    A.pavarde = pavarde;
}