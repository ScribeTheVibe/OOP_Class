#ifndef MAIN_H
#define MAIN_H

#include "ivestis.h"
#include "isvestis.h"
#include "apdorojimas.h"
#include "random.h"
#include "Timer.h"
#include "main.tpp"
#include <deque>
#include <list>

#ifdef _WIN32
#include <windows.h>
#endif

void failoApdorojimas(const std::string& failoPavadinimas, int rezervas, int& ndKiekis, bool medianos, int rPasirinkimas, bool failas);

#endif