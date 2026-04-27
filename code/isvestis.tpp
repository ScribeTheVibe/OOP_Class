#include "isvestis.h"

template<class Konteineris>
void isvestis(Konteineris &A, bool medianos, bool failas, const std::string &failoPavadinimas = "rezultatai.txt")
{
    std::string out;

    setw("Vardas", 20, out);
    setw("Pavardė", 21, out);
    out += "Galutinis (Vid.) / Galutinis (Med.)\n";
    out += std::string(75, '-') + "\n";
    for(const Studentas &X : A)
    {
        int vardoPlotis = 20 + lietuviskosRaides(X.vardas);
        int pavardesPlotis = 20 + lietuviskosRaides(X.pavarde);
        
        setw(X.vardas, vardoPlotis, out);
        setw(X.pavarde, pavardesPlotis, out);
        if (medianos)
        {
            setw("x.xx", 19, out);
            out += std::format("{:.2f}", X.galutinis);
            out += '\n';
        }
        else
        {
            setw(std::format("{:.2f}", X.galutinis), 19, out);
            out += "y.yy\n";
        }
    }
    if(failas){
        std::ofstream fout(failoPavadinimas);
        fout << out;
        fout.close();
    } else {
        std::cout << out;
    }
}