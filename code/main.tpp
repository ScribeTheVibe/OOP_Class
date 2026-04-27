#include "main.h"
#include "apdorojimas.tpp"
#include "isvestis.tpp"

template <class Konteineris>
void skirstymoPasirinkimas(int sPasirinkimas, Konteineris& studentai, Konteineris& galvociai, Konteineris& vargsiukai);

template <class Konteineris>
void failoTestavimas(const std::string& failoPavadinimas, int rezervas, int tPasirinkimas, int sPasirinkimas, int& ndKiekis, bool medianos)
{
    double skaitymoTrukme = 0;
    double skaiciavimoTrukme = 0;
    double rusiavimoTrukme = 0;
    double skirstymoTrukme = 0;
    double isvedimoTrukme1 = 0;
    double isvedimoTrukme2 = 0;
    
    ndKiekis = 0;
    Konteineris studentai = skaitymasIsFailo<Konteineris>(failoPavadinimas, ndKiekis, rezervas);
    skaiciavimas<Konteineris>(studentai, medianos, ndKiekis);
    rusiavimasSkirstymas(studentai, 5);
    
    Konteineris vargsiukai;
    Konteineris galvociai;
    
    if constexpr (requires(Konteineris konteineris) { konteineris.reserve(0); })
    {
        galvociai.reserve(studentai.size());
        vargsiukai.reserve(studentai.size());
    }
    
    skirstymoPasirinkimas(sPasirinkimas, studentai, galvociai, vargsiukai);
    
    for (int i = 0; i < tPasirinkimas; i++)
    {   
        ndKiekis = 0;
        Timer t;
        
        Konteineris studentai = skaitymasIsFailo<Konteineris>(failoPavadinimas, ndKiekis, rezervas);
        skaitymoTrukme += t.elapsed();
        
        t.reset();
        skaiciavimas<Konteineris>(studentai, medianos, ndKiekis);
        skaiciavimoTrukme += t.elapsed();
        
        t.reset();
        rusiavimasSkirstymas(studentai, 5);
        rusiavimoTrukme += t.elapsed();
        
        t.reset();
        Konteineris vargsiukai;
        Konteineris galvociai;
        
        if constexpr (requires(Konteineris konteineris) { konteineris.reserve(0); })
        {
            galvociai.reserve(studentai.size());
            vargsiukai.reserve(studentai.size());
        }
        
        skirstymoPasirinkimas(sPasirinkimas, studentai, galvociai, vargsiukai);
        skirstymoTrukme += t.elapsed();
    }
    
    std::cout << "Failo nuskaitymas į studentai konteinerį vidutiniškai užtruko: " << skaitymoTrukme / tPasirinkimas << " s\n";
    std::cout << "Duomenų rūšiavimas didėjančiai vidutiniškai užtruko: " << rusiavimoTrukme / tPasirinkimas << " s\n";
    std::cout << "Studentų skirstymas pagal pažymius vidutiniškai užtruko: " << skirstymoTrukme / tPasirinkimas << " s\n";
    std::cout << "Bendra trukmė: " << skaitymoTrukme + skaiciavimoTrukme + rusiavimoTrukme + skirstymoTrukme + isvedimoTrukme1 + isvedimoTrukme2 << " s\n";
}

template <class Konteineris>
void skirstymoPasirinkimas(int sPasirinkimas, Konteineris& studentai, Konteineris& galvociai, Konteineris& vargsiukai)
{
    switch (sPasirinkimas)
    {
        case 0:
        {
            skirstymas(studentai, galvociai, vargsiukai);
            break;
        }
        case 1:
        {
            skirstymasStrat1(studentai, galvociai, vargsiukai);
            break;
        }
        case 2:
        {
            skirstymasStrat2(studentai, vargsiukai);
            break;
        }
        case 3:
        {
            skirstymasStrat3(studentai, vargsiukai);
            break;
        }
        default:
        {
            break;
        }
    }
}