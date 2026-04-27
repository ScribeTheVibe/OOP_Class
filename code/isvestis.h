#ifndef ISVESTIS_H
#define ISVESTIS_H

#include "studentas.h"
#include "apdorojimas.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <format>

int menu();

int rusiavimoPasirinkimas();

int gautiTipoPasirinkima();

int testavimoPasirinkimas();

int strategijosPasirinkimas();

int studentuPasirinkimas();

int ndPasirinkimas();

bool medianosUzklausa();

bool failoUzklausa();

int lietuviskosRaides(const std::string& eilute);

void failoPasirinkimas(int &rezervas, bool &egzistuoja, std::string &failoPavadinimas, const std::string& vieta = ".");

#endif