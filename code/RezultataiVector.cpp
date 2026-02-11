#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ofstream;
using std::cin;
using std::endl;


struct studentas {
    string vardas = "D", pavarde = "K";
    vector<int> pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
};

int main()
{
    vector<studentas> s;
    studentas tempS;
    int n, p;
    cin>>n>>p;
    s.reserve(n);

    int temp;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<p; j++)
        {
            cin>>temp;
            tempS.pazimys.push_back(temp);
            tempS.vidurkis += temp;
        }
        tempS.vidurkis /= p;
        s.push_back(tempS);
        tempS.pazimys.clear();
        tempS.vidurkis = 0;
    }

    std::cout<<"test";

    ofstream O ("Rezultatai.txt");
    for(int i=0; i<s.size(); i++)
    {
        O<<s[i].vidurkis*0.4+s[i].rezultatas*0.6<<endl;
    }
    return 0;
}
