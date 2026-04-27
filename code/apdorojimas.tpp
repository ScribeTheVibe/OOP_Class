#include "apdorojimas.h"
#include "studVPGen.h"
#include "random.h"
#include <fstream>
#include <list>

template<class Konteineris>
void skaiciavimas(Konteineris& A, bool medianos, int ndKiekis)
{
    auto funkcija = medianos ? galutinisMedF : galutinisVidF;

    for (Studentas& X : A)
    {
        X.galutinis = funkcija(X, ndKiekis);
    }
}

template<class T, class Konteineris>
void rusiavimasPagal(Konteineris& studentai, T lambdaFunkcija, bool didejanciai = true)
{
    if constexpr (std::is_same_v<Konteineris, std::list<Studentas>>)
    {
        if (didejanciai)
        {
            studentai.sort([lambdaFunkcija](const Studentas& A, const Studentas& B) {
                return lambdaFunkcija(A) < lambdaFunkcija(B);
            });
        }
        else
        {
            studentai.sort([lambdaFunkcija](const Studentas& A, const Studentas& B) {
                return lambdaFunkcija(A) > lambdaFunkcija(B);
            });
        }
    }
    else
    {
        std::sort(studentai.begin(), studentai.end(),
            [didejanciai, lambdaFunkcija](const Studentas& A, const Studentas& B) {
                return didejanciai ? lambdaFunkcija(A) < lambdaFunkcija(B) : lambdaFunkcija(A) > lambdaFunkcija(B);
            }
        );
    }
}

template<class Konteineris>
void rusiavimasSkirstymas(Konteineris& studentai, int rPasirinkimas)
{
    switch (rPasirinkimas)
    {
        case 1: 
            rusiavimasPagal(studentai, [](const Studentas& studentas) { return studentas.vardas; }); 
            break;
        case 2: 
            rusiavimasPagal(studentai, [](const Studentas& studentas) { return studentas.vardas; }, false); 
            break;
        case 3: 
            rusiavimasPagal(studentai, [](const Studentas& studentas) { return studentas.pavarde; }); 
            break;
        case 4: 
            rusiavimasPagal(studentai, [](const Studentas& studentas) { return studentas.pavarde; }, false); 
            break;
        case 5: 
            rusiavimasPagal(studentai, [](const Studentas& studentas) { return studentas.galutinis; }); 
            break;
        case 6: 
            rusiavimasPagal(studentai, [](const Studentas& studentas) { return studentas.galutinis; }, false); 
            break;
        default:
            break;
    }
}

template<class Konteineris>
void skirstymas(Konteineris& studentai, Konteineris& galvociai, Konteineris& vargsiukai)
{
    for (Studentas& A : studentai)
    {
        if (A.galutinis < 5)
        {
            vargsiukai.push_back(std::move(A));
        }
        else
        {
            galvociai.push_back(std::move(A));
        }
    }
}

template<class Konteineris>
void skirstymasStrat1(Konteineris& studentai, Konteineris& galvociai, Konteineris& vargsiukai)
{
    for (Studentas& A : studentai)
    {
        if (A.galutinis < 5)
        {
            vargsiukai.push_back(A);
        }
        else
        {
            galvociai.push_back(A);
        }
    }
}

template<class Konteineris>
void skirstymasStrat2(Konteineris& studentai, Konteineris& vargsiukai)
{
    auto it = std::lower_bound(studentai.begin(), studentai.end(), 5, [](const Studentas& A, int skaic) {
        return A.galutinis < skaic;
    });
    
    vargsiukai.insert(vargsiukai.begin(), std::make_move_iterator(studentai.begin()), std::make_move_iterator(it));
    studentai.erase(studentai.begin(), it);
}

template<class Konteineris>
void skirstymasStrat3(Konteineris& studentai, Konteineris& vargsiukai)
{
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& A) {
        return A.galutinis >= 5;
    });
    
    vargsiukai.insert(vargsiukai.begin(), std::make_move_iterator(it), std::make_move_iterator(studentai.end()));
    studentai.erase(it, studentai.end());
}