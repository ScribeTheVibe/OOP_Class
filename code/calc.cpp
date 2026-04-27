#include "calc.h"
#include <algorithm>
#include <numeric>
#include <iostream>

double galutinisVid(const Studentas &A){
    if(A.nd.empty()) return 0.6*A.rez;

    int sum = std::accumulate(A.nd.begin(), A.nd.end(), 0);

    double vid = (double)sum / maxNdKiekis;
    return 0.4 * vid + 0.6 * A.rez;
}


double galutinisMed(Studentas &A){
    if(A.nd.empty()) return 0.6*A.rez;

    A.nd.resize(maxNdKiekis, 0);
    std::sort(A.nd.begin(), A.nd.end());

    double med =
        (maxNdKiekis % 2 == 0)
        ? (A.nd.at(maxNdKiekis/2) + A.nd.at(maxNdKiekis/2 - 1)) / 2.0
        : A.nd.at(maxNdKiekis/2);

    return 0.4 * med + 0.6 * A.rez;
}

double galutinisVidF(Studentas &A, int ndKiekis){
    if(A.nd.empty()) return 0.6*A.rez;

    int sum = std::accumulate(A.nd.begin(), A.nd.end(), 0);
    
    double vid = (double)sum / ndKiekis;
    return 0.4 * vid + 0.6 * A.rez;
}


double galutinisMedF(Studentas &A, int ndKiekis){
    if(A.nd.empty()) return 0.6*A.rez;

    A.nd.resize(ndKiekis, 0);
    std::sort(A.nd.begin(), A.nd.end());

    double med =
        (ndKiekis % 2 == 0)
        ? (A.nd.at(ndKiekis/2) + A.nd.at(ndKiekis/2 - 1)) / 2.0
        : A.nd.at(ndKiekis/2);

    return 0.4 * med + 0.6 * A.rez;
}