#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::sort;


struct studentas {
    string vardas, pavarde;
    vector<int> pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
};

int main()
{
    vector<studentas> s;
    studentas tempS;
    int n, p;
    cout<<"Iveskite studentu kieki"<<endl;
    cin>>n;
    cout<<"Iveskite pazymiu kieki"<<endl;
    cin>>p;
    s.reserve(n);

    int temp;
    for(int i=0; i<n; i++)
    {
        cout<<"Iveskite "<<i+1<<" studento varda"<<endl;
        cin>>tempS.vardas;
        cout<<"Iveskite "<<i+1<<" studento pavarde"<<endl;
        cin>>tempS.pavarde;
        for(int j=0; j<p; j++)
        {
            cout<<"Iveskite pazymi"<<endl;
            cin>>temp;
            tempS.pazimys.push_back(temp);
            tempS.vidurkis += temp;
        }
        cout<<"Iveskite egzamino rezultata"<<endl;
        cin>>tempS.rezultatas;
        sort(tempS.pazimys.begin(), tempS.pazimys.end());
        if(p % 2 == 0)
        {
            tempS.mediana = (tempS.pazimys[p/2 - 1] + tempS.pazimys[p/2]) / 2.0;
        }
        else
        {
            tempS.mediana = tempS.pazimys[p/2];
        }
        tempS.vidurkis /= p;
        s.push_back(tempS);
        tempS.pazimys.clear();
        tempS.vidurkis = 0;
    }
    
    for(int i=0; i<s.size(); i++)
    {
        cout<<s[i].vardas<<" "<<s[i].pavarde<<" galutinis rezultatas:"<<endl;
        cout<<s[i].vidurkis*0.4+s[i].rezultatas*0.6<<endl;
        cout<<s[i].vardas<<" "<<s[i].pavarde<<" mediana:"<<endl;
        cout<<s[i].mediana<<endl;
    }
    return 0;
}
