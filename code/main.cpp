#include "main.h"

int main()
{
    try
    {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif
        bool veikimas = true;
        
        while (veikimas)
        {
            int pasirinkimas = menu();
            bool failas = false;
            bool medianos = false;
            
            if (pasirinkimas < 5)
            {
                failas = !failoUzklausa();
                medianos = medianosUzklausa();
            }
            else if (pasirinkimas == 5)
            {
                medianos = medianosUzklausa();
            }

            switch (pasirinkimas)
            {
                case 1:
                {
                    std::vector<Studentas> studentai = ivestiStudentus();
                    skaiciavimas(studentai, medianos);
                    isvestis(studentai, medianos, failas);
                    break;
                }
                case 2:
                {
                    std::vector<Studentas> studentai = ivestiStudentusRandom(pasirinkimas);
                    skaiciavimas(studentai, medianos);
                    isvestis(studentai, medianos, failas);
                    break;
                }
                case 3:
                {
                    std::vector<Studentas> studentai = ivestiStudentusRandom(pasirinkimas);
                    skaiciavimas(studentai, medianos);
                    isvestis(studentai, medianos, failas);
                    break;
                }
                case 4:
                {
                    int ndKiekis = 0;
                    int rezervas = 0;
                    std::string fPasirinkimas;
                    bool egzistuojaFailai = true;
                    
                    failoPasirinkimas(rezervas, egzistuojaFailai, fPasirinkimas);
                    if (egzistuojaFailai == false)
                    {
                        break;
                    }
                    
                    int rPasirinkimas = rusiavimoPasirinkimas();
                    failoApdorojimas(fPasirinkimas, rezervas, ndKiekis, medianos, rPasirinkimas, failas);
                    break;
                }
                case 5:
                {
                    int ndKiekis = 0;
                    int rezervas = 0;
                    std::string fPasirinkimas;
                    bool egzistuojaFailai = true;
                    
                    failoPasirinkimas(rezervas, egzistuojaFailai, fPasirinkimas);
                    if (egzistuojaFailai == false)
                    {
                        break;
                    }
                    
                    int tipoPasirinkimas = gautiTipoPasirinkima();
                    int tPasirinkimas = testavimoPasirinkimas();
                    int sPasirinkimas = strategijosPasirinkimas();
                    
                    if (tPasirinkimas <= 0)
                    {
                        throw std::invalid_argument("Testavimo skaičius turi būti daugiau už 0!");
                    }
                    
                    switch (tipoPasirinkimas)
                    {
                        case 1:
                        {
                            failoTestavimas<std::vector<Studentas>>(fPasirinkimas, rezervas, tPasirinkimas, sPasirinkimas, ndKiekis, medianos);
                            break;
                        }
                        case 2:
                        {
                            failoTestavimas<std::deque<Studentas>>(fPasirinkimas, rezervas, tPasirinkimas, sPasirinkimas, ndKiekis, medianos);
                            break;
                        }
                        case 3:
                        {
                            failoTestavimas<std::list<Studentas>>(fPasirinkimas, rezervas, tPasirinkimas, sPasirinkimas, ndKiekis, medianos);
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case 6:
                {   
                    int studentuKiekis = studentuPasirinkimas();
                    int ndKiekis = ndPasirinkimas();
                    int tPasirinkimas = testavimoPasirinkimas();
                    
                    if (tPasirinkimas <= 0)
                    {
                        throw std::invalid_argument("Testavimo skaičius turi būti daugiau už 0!");
                    }
                    
                    double trukme = 0;
                    for (int i = 0; i < tPasirinkimas + 1; i++)
                    {
                        if (i != 0)
                        {
                            Timer t;
                            failoGeneravimas(studentuKiekis, ndKiekis);
                            trukme += t.elapsed();
                        }
                        else
                        {
                            failoGeneravimas(studentuKiekis, ndKiekis);
                        }
                    }
                    std::cout << "Failų(-o) generavimas vidutiniškai užtruko: " << trukme / tPasirinkimas << " s\n";
                    break;
                }
                case 7:
                {
                    std::cout << "Darbas su programa baigtas.";
                    veikimas = false;
                    return 0;
                }
                default:
                {
                    return 0;
                }
            }
        }
    }
    catch (const std::exception& klaida)
    {
        std::cerr << klaida.what() << "\n";
        return 1;
    }
    return 0;
}

void failoApdorojimas(const std::string& failoPavadinimas, int rezervas, int& ndKiekis, bool medianos, int rPasirinkimas, bool failas)
{
    Timer t;
    std::vector<Studentas> studentai = skaitymasIsFailo<std::vector<Studentas>>(failoPavadinimas, ndKiekis, rezervas);
    double skaitymoTrukme = t.elapsed();
    
    t.reset();
    skaiciavimas(studentai, medianos, ndKiekis);
    double skaiciavimoTrukme = t.elapsed();
    
    t.reset();
    rusiavimasSkirstymas(studentai, rPasirinkimas);
    double rusiavimoTrukme = t.elapsed();
    
    t.reset();
    isvestis(studentai, medianos, failas);
    double isvedimoTrukme = t.elapsed();
    
    std::cout << "Failo nuskaitymas į studentai vektorių užtruko: " << skaitymoTrukme << " s\n";
    std::cout << "Rezultatų skaičiavimas užtruko: " << skaiciavimoTrukme << " s\n";
    std::cout << "Duomenų rūšiavimas pagal pasirinktą parametrą užtruko: " << rusiavimoTrukme << " s\n";
    std::cout << "Studentų išvedimas užtruko: " << isvedimoTrukme << " s\n";
    std::cout << "Bendra trukmė: " << skaitymoTrukme + skaiciavimoTrukme + rusiavimoTrukme + isvedimoTrukme << " s\n";
}