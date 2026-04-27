#include "random.h"
#include "studVPGen.h"
#include "ivestis.h"

Studentas skaitymasRandom()
{
    Studentas A;
    gen_map(A);
    namuDarbuRezultataiRandom(A, namuDarbuRezultataiIvestisRandom());
    egzaminoRezultatasRandom(A);
    return A;
}

bool skaitymasRandom(Studentas &A)
{
    std::string eilute;
    std::cout << "Įveskite studento vardą bei pavardę (ENTER - nutraukti įvedimą): ";

        // perskaito eilute ir jei perskaitymas nesekmingas, tai ziuri ar std::cin.eof, jei taip, tai programa uzbaigiama, jei ne, tai isvalo ivesties stream'o veliaveles ir vel prasoma ivesti
    if (!std::getline(std::cin, eilute))
    {
        cinEOFgaudymas();
        return false;
    } // jei enter - iseina
    if(eilute.empty())
    {
        return false;
    }
    while(!studentoVardoPavardesIvestis(A, eilute))
    {
        std::cout << "Įveskite studento vardą bei pavardę (ENTER - baigti): ";
        if(!std::getline(std::cin, eilute) || eilute.empty()) return false;
    }
    namuDarbuRezultataiRandom(A, namuDarbuRezultataiIvestisRandom());
    egzaminoRezultatasRandom(A);
    return true;
}

void egzaminoRezultatasRandom(Studentas &A)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1,10);
    A.rez = dist(rng);
}

int namuDarbuRezultataiIvestisRandom()
{    
    int N = maxNdKiekis;
    return gautiSkaiciu("Įveskite norimą generuoti namų darbų rezultatų kiekį: ", 0, N);
}

int randomStudentuKiekis()
{    
    int N = 100;
    return gautiSkaiciu("Įveskite norimą generuoti studentų kiekį: ", 0, N);
}

void namuDarbuRezultataiRandom(Studentas &A, int ndKiekis)
{
    static std::mt19937 rng(std::random_device{}()); // static - sukuriama karta ir kad nebutu per naujo kuriamas rng bei seed'inamas
    std::uniform_int_distribution<int> dist(1,10); // skaicius nuo 1 iki 10 isskirstymas, tai jei pvz sugeneruota random skaiciu 12312581 idedame i dist, ji priskiria kazkuriam skaiciui nuo 1 iki 10 imtinai
    for(int i = 0; i < ndKiekis; i++){
        A.nd.push_back(dist(rng));
    }
}

std::vector<Studentas> ivestiStudentusRandom(int pasirinkimas)
{
    std::vector<Studentas> studentai;
    switch(pasirinkimas)
    {
        case 2:
        {
            while(true)
            {
                Studentas A;
                if(!skaitymasRandom(A)){
                    break;
                }
                studentai.push_back(A);
            }
            return studentai;
        }
        case 3:
        {
            int studKiekis = randomStudentuKiekis();
            studentai.reserve(studKiekis);
            for(int i = 0; i < studKiekis; i++)
            {
                studentai.push_back(skaitymasRandom());
            }
            break;
        }
        default:
        {
            std::cout << "ivestiStudentusRandom default atvejis" << std::endl;
        }
    }
    return studentai;
} 