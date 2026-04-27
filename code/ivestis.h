#ifndef IVESTIS_H
#define IVESTIS_H

#include "studentas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ivestis.tpp"

bool gautiPatvirtinima(const std::string &pranesimas);

std::vector<Studentas> ivestiStudentus();

bool skaitymas(Studentas &A);

bool studentoVardoPavardesIvestis(Studentas &A, const std::string &eilute);

void namuDarbuRezultatuIvestis(Studentas &A);

void egzaminoRezultatoIvestis(Studentas &A);

int gautiSkaiciu(const std::string &pranešimas, int min, int max, bool galiButiTuscia = false);

bool arTikSkaicius(const std::string &s);

template<class Konteineris>
Konteineris skaitymasIsFailo(const std::string &failoPavadinimas, int &ndKiekis, int rezervas);

void cinEOFgaudymas();

#endif