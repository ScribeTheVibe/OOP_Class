template<class Konteineris>
Konteineris skaitymasIsFailo(const std::string &failoPavadinimas, int &ndKiekis, int rezervas){
    Konteineris studentai;
    if constexpr(requires(Konteineris konteineris){konteineris.reserve(0);})
        studentai.reserve(rezervas);
    std::string eil;
    std::string t="";

    std::ifstream open_f(failoPavadinimas);
    if (!open_f.is_open()) throw std::runtime_error("Klaida: failas \"" + failoPavadinimas + "\" nerastas.");

    if(!std::getline(open_f, eil)) throw std::runtime_error("Klaida: failas tuščias arba netinkantis");
    std::istringstream antraste(eil);
    antraste >> t >> t;
    while(antraste >> t){
        if(t == "Egz." || t == "Egzaminas") break;
        ndKiekis++;
    }

    std::string vardas, pavarde;
    int paz;
    
    while (open_f >> vardas >> pavarde) {
        Studentas studentas;
        studentas.vardas = std::move(vardas);
        studentas.pavarde = std::move(pavarde);

        for(int i = 0; i < ndKiekis; i++){
            if(!(open_f >> paz)) throw std::runtime_error("Klaida: netinkami pažymiai faile.");
            studentas.nd.push_back(paz);
        }
        if(!(open_f >> studentas.rez)) throw std::runtime_error("Klaida: netinkamas egzamino rezultatas faile.");

        studentai.push_back(std::move(studentas));
    }

    open_f.close();
    return studentai;
}