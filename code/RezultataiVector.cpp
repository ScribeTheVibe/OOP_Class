#include "Headers.h"

int main()
{
    vector<studentas> s;
    studentas tempS;
    int m, n, p;
    srand(time(NULL));

    cout << "Pasirinkite programos eiga\n";
    cout << "1 - ranka ivedami duomenys\n";
    cout << "2 - is failo ivedami duomenys\n";
    cout << "3 - automatiskai sugeneruoti pazymius\n";
    cout << "4 - sugeneruoti studentu vardus, pavardes ir pazymius\n";
    cout << "5 - baigti darba\n";
    cout << "6 - sugeneruoti 5 duomenu failus\n";
    cout << "7 - atlikti duomenu apdorojima (vector / list / deque)\n\n";

    m = saugusInt("Pasirinkimas: ", 1, 7);
    cout << endl;

    if (m == 5)
        return 0;

    if (m == 6)
    {
        generuotiVisusFailus();
        return 0;
    }

    if (m == 7)
    {
        cout << "\n===== TYRIMAS: Duomenu apdorojimas (vector vs list vs deque) =====\n";

        int sor;
        cout << "\nPasirinkite rusiavima\n"
             << "1 - nerusiuoti\n2 - pagal varda zemyn\n3 - pagal pavarde zemyn\n"
             << "4 - pagal Galutinis (vid.) zemyn\n5 - pagal Galutinis (med.) zemyn\n"
             << "6 - pagal varda aukstyn\n7 - pagal pavarde aukstyn\n"
             << "8 - pagal Galutinis (vid.) aukstyn\n9 - pagal Galutinis (med.) aukstyn\n\n";
        sor = saugusInt("Pasirinkimas: ", 1, 9);

        string files[] = {
            "output/studentai_1000.txt",
            "output/studentai_10000.txt",
            "output/studentai_100000.txt",
            "output/studentai_1000000.txt",
            "output/studentai_10000000.txt"
        };

        for (const auto &f : files)
            testas_duomenuApdorojimas(f, sor);

        return 0;
    }

    // ── Modes 1, 2, 3, 4 ─────────────────────────────────────────────────────

    if (m == 1 || m == 3)
    {
        string input;

        while (true)
        {
            tempS = studentas();

            cout << "\nIveskite studento varda (exit - baigti): ";
            cin >> input;
            if (input == "exit")
                break;

            tempS.vardas = input;
            cout << "Iveskite pavarde: ";
            cin >> tempS.pavarde;

            if (m == 1)
            {
                cout << "Iveskite pazymius (exit - baigti):\n";
                while (true)
                {
                    cin >> input;
                    if (input == "exit")
                        break;

                    bool valid = true;
                    for (char c : input)
                        if (!isdigit(c))
                            valid = false;

                    if (!valid) { cout << "Blogas ivedimas.\n"; continue; }

                    int paz = stoi(input);
                    if (paz < 0 || paz > 10) { cout << "Pazymys 0-10.\n"; continue; }

                    tempS.pazimys.push_back(paz);
                    tempS.vidurkis += paz;
                }
            }
            else
            {
                p = saugusInt("Iveskite pazymiu kieki: ", 1, 1000);
                for (int j = 0; j < p; j++)
                {
                    int paz = rand() % 11;
                    tempS.pazimys.push_back(paz);
                    tempS.vidurkis += paz;
                }
            }

            if (tempS.pazimys.empty())
            {
                cout << "Studentas neturi pazymiu — praleistas.\n";
                continue;
            }

            tempS.vidurkis /= tempS.pazimys.size();

            if (m == 1)
                tempS.rezultatas = saugusInt("Egzamino rezultatas: ", 0, 10);
            else
                tempS.rezultatas = rand() % 11;

            tempS.mediana = skaiciuotiMediana(tempS.pazimys);
            tempS.galVid  = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;
            tempS.galMed  = tempS.mediana  * 0.4 + tempS.rezultatas * 0.6;

            s.push_back(tempS);
        }
    }
    else if (m == 4)
    {
        n = saugusInt("Iveskite studentu kieki: ", 1, 1000000);
        p = saugusInt("Iveskite pazymiu kieki: ",  1, 1000);

        s.reserve(n);

        for (int i = 0; i < n; i++)
        {
            tempS = studentas();
            tempS.vardas   = vardai  [rand() % 15];
            tempS.pavarde  = pavardes[rand() % 15];

            for (int j = 0; j < p; j++)
            {
                int paz = rand() % 11;
                tempS.pazimys.push_back(paz);
                tempS.vidurkis += paz;
            }

            tempS.vidurkis  /= p;
            tempS.rezultatas = rand() % 11;
            tempS.mediana    = skaiciuotiMediana(tempS.pazimys);
            tempS.galVid     = tempS.vidurkis * 0.4 + tempS.rezultatas * 0.6;
            tempS.galMed     = tempS.mediana  * 0.4 + tempS.rezultatas * 0.6;

            s.push_back(tempS);
        }
    }
    else // m == 2
    {
        if (!nuskaitytiIsFailo("kursiokai.txt", s))
        {
            cout << "Failas tuscias arba netinkamas formatas.\n";
            return 0;
        }
    }

    // ── Output ────────────────────────────────────────────────────────────────

    vector<studentas> gerai, blogai;
    isskirtiStudentus(s, gerai, blogai);

    cout << "\nPasirinkite isvedima\n"
         << "1 - i terminala\n2 - i faila\n\n";
    m = saugusInt("Pasirinkimas: ", 1, 2);

    int sor;
    cout << "\nPasirinkite rusiavima\n"
         << "1 - nerusiuoti\n2 - pagal varda zemyn\n3 - pagal pavarde zemyn\n"
         << "4 - pagal Galutinis (vid.) zemyn\n5 - pagal Galutinis (med.) zemyn\n"
         << "6 - pagal varda aukstyn\n7 - pagal pavarde aukstyn\n"
         << "8 - pagal Galutinis (vid.) aukstyn\n9 - pagal Galutinis (med.) aukstyn\n\n";
    sor = saugusInt("Pasirinkimas: ", 1, 9);

    if (sor != 1)
    {
        sortS(gerai,  sor);
        sortS(blogai, sor);
    }

    if (m == 1)
    {
        cout << "\n===== GALVOCIAI  (galutinis >= 5.0) =====\n\n";
        cout << std::left << setw(20) << "Vardas" << setw(20) << "Pavarde"
             << setw(17) << "Galutinis (vid.)" << setw(17) << "Galutinis (med.)" << "\n\n";
        for (const auto &st : gerai)
            cout << std::left << setw(20) << st.vardas << setw(20) << st.pavarde
                 << setw(17) << std::fixed << std::setprecision(2) << st.galVid
                 << setw(17) << std::fixed << std::setprecision(2) << st.galMed << "\n";

        cout << "\n===== VARGSIUKAI (galutinis < 5.0) =====\n\n";
        cout << std::left << setw(20) << "Vardas" << setw(20) << "Pavarde"
             << setw(17) << "Galutinis (vid.)" << setw(17) << "Galutinis (med.)" << "\n\n";
        for (const auto &st : blogai)
            cout << std::left << setw(20) << st.vardas << setw(20) << st.pavarde
                 << setw(17) << std::fixed << std::setprecision(2) << st.galVid
                 << setw(17) << std::fixed << std::setprecision(2) << st.galMed << "\n";
    }
    else
    {
        issaugotiStudentus(gerai,  "output/galvociai.txt");
        issaugotiStudentus(blogai, "output/vargsiukai.txt");
        cout << "Issaugota: galvociai.txt, vargsiukai.txt\n";
    }

    cout << "\n\nIveskite 'close' jog uzdaryti programa\n";
    string close;
    while (true)
    {
        cin >> close;
        if (close == "close")
            break;
    }
    return 0;
}