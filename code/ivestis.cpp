#include "ivestis.h"

bool gautiPatvirtinima(const std::string &pranesimas)
{
    std::string ivestis;
    while (true) {
        std::cout << pranesimas << " (y/n): ";
        
        if (!std::getline(std::cin, ivestis)) {
            cinEOFgaudymas();
            continue;
        }

        size_t pirmas = ivestis.find_first_not_of(" \t");
        if (pirmas == std::string::npos) {
            std::cout << "Neteisinga įvestis! Prašome įvesti tik 'y' arba 'n'.\n";
            continue;
        }
        
        size_t paskutinis = ivestis.find_last_not_of(" \t");
        ivestis = ivestis.substr(pirmas, (paskutinis - pirmas + 1));

        if (ivestis.length() == 1) {
            char pasirinkimas = static_cast<char>(std::tolower(static_cast<unsigned char>(ivestis[0])));
            if (pasirinkimas == 'y') return true;
            if (pasirinkimas == 'n') return false;
        }

        std::cout << "Neteisinga įvestis! Prašome įvesti tik 'y' arba 'n'.\n";
    }
}

std::vector<Studentas> ivestiStudentus()
{
    std::vector<Studentas> studentai;
    Studentas s;
    while (skaitymas(s)) {
        studentai.push_back(s);
    }
    return studentai;
}

bool skaitymas(Studentas &A)
{
    std::string eilute;
    std::cout << "Įveskite studento vardą bei pavardę (ENTER - nutraukti įvedimą): ";

    if (!std::getline(std::cin, eilute) || eilute.empty()) {
        if (std::cin.eof()) cinEOFgaudymas();
        return false;
    }

    while (!studentoVardoPavardesIvestis(A, eilute)) {
        std::cout << "Įveskite studento vardą bei pavardę (ENTER - baigti): ";
        if (!std::getline(std::cin, eilute) || eilute.empty()) return false;
    }

    namuDarbuRezultatuIvestis(A);
    egzaminoRezultatoIvestis(A);
    return true;
}

bool studentoVardoPavardesIvestis(Studentas &A, const std::string& eilute)
{
    std::istringstream iss(eilute);
    std::string vardas, pavarde, ekstra;

    if (!(iss >> vardas >> pavarde)) {
        std::cout << "Įveskite vardą ir pavardę (du žodžiai)!\n";
        return false;
    }

    if (iss >> ekstra) {
        std::cout << "Įvesta per daug žodžių — reikia tik vardo ir pavardės!\n";
        return false;
    }

    A.vardas = vardas;
    A.pavarde = pavarde;
    return true;
}

void namuDarbuRezultatuIvestis(Studentas &A)
{
    std::cout << "Įveskite " << maxNdKiekis << " namų darbų rezultatų." << std::endl;
    A.nd.clear(); 
    
    while (A.nd.size() < maxNdKiekis) {
        int balas = gautiSkaiciu("Įveskite namų darbų rezultatą nuo 1 iki 10 (ENTER - baigti): ", 1, 10, true);
        if (balas == -1) break; 
        A.nd.push_back(balas);
    }

    if (A.nd.size() == maxNdKiekis) {
        std::cout << "Įvestas didžiausias namų darbų rezultatų kiekis" << std::endl;
    }
}

void egzaminoRezultatoIvestis(Studentas &A)
{
    A.rez = gautiSkaiciu("Įveskite egzamino rezultatą (1-10): ", 1, 10);
}

int gautiSkaiciu(const std::string &pranesimas, int min, int max, bool galiButiTuscia)
{
    std::string ivestis;
    while (true) {
        std::cout << pranesimas;

        if (!std::getline(std::cin, ivestis)) {
            cinEOFgaudymas();
            continue;
        }

        if (galiButiTuscia && ivestis.empty()) return -1;

        try {
            if (!arTikSkaicius(ivestis)) throw std::invalid_argument("Ne skaicius");

            int skaicius = std::stoi(ivestis);

            if (skaicius >= min && skaicius <= max) {
                return skaicius;
            } 
            
            std::cout << "Klaida, skaičius turi būti tarp " << min << " ir " << max << "!\n";
        } catch (...) {
            std::cout << "Klaida, įveskite sveikąjį skaičių!\n";
        }
    }
}

bool arTikSkaicius(const std::string& eilute)
{
    return !eilute.empty() && std::all_of(eilute.begin(), eilute.end(), [](unsigned char c) {
        return std::isdigit(c) || std::isspace(c);
    });
}

void cinEOFgaudymas()
{
    if (std::cin.eof()) {
        throw std::runtime_error("Įvesties pabaiga (EOF). Darbas su programa baigtas");
    }
    std::cin.clear();
}