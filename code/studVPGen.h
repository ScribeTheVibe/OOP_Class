#ifndef studVPGen_H
#define studVPGen_H

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <chrono>
#include <random>
#include "studentas.h"

typedef std::uniform_int_distribution<int> int_distribution;

void gen_map(Studentas& A);

#endif