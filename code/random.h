#ifndef RANDOM_H
#define RANDOM_H
#include "studentas.h"
#include <random>

Studentas skaitymasRandom();

bool skaitymasRandom(Studentas &A);

void egzaminoRezultatasRandom(Studentas &A);

int namuDarbuRezultataiIvestisRandom();

int randomStudentuKiekis();

void namuDarbuRezultataiRandom(Studentas &A, int ndKiekis);

std::vector<Studentas> ivestiStudentusRandom(int pasirinkimas);

#endif