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
};

int main()
{
    studentas *s = new studentas[3];
    
    int temp;
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            cin>>temp;
            s[j].pazimys.push_back(temp);
        }
    }
    
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            s[j].rezultatas += s[j].pazimys[i];
        }
    }

    ofstream O ("Rezultatai.txt");
    for(int i=0; i<3; i++)
    {
        O<<s[i].rezultatas/2.0*0.4+10*0.6<<endl;
    }
    return 0;
}
