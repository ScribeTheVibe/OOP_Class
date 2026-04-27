#ifndef APDOROJIMAS_H
#define APDOROJIMAS_H

#include <algorithm>
#include "studentas.h"
#include "calc.h"

void skaiciavimas(std::vector<Studentas>& A, bool medianos);

void failoGeneravimas(int studentuKiekis, int ndKiekis);

void setw(const std::string& tekstas, int plotis, std::string& out);

#endif