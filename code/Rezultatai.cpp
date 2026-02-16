#include <iostream>
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::sort;

struct studentas {
    string vardas, pavarde;
    int* pazimys;
    int rezultatas = 0;
    double vidurkis = 0;
    double mediana = 0;
};

int main()
{
    int n, p;

    cout << "Iveskite studentu kieki" << endl;
    cin >> n;

    cout << "Iveskite pazymiu kieki" << endl;
    cin >> p;

    studentas* s = new studentas[n];

    for(int i = 0; i < n; i++)
    {
        cout << "Iveskite " << i+1 << " studento varda" << endl;
        cin >> s[i].vardas;

        cout << "Iveskite " << i+1 << " studento pavarde" << endl;
        cin >> s[i].pavarde;

        s[i].pazimys = new int[p];

        for(int j = 0; j < p; j++)
        {
            cout << "Iveskite pazymi" << endl;
            cin >> s[i].pazimys[j];

            s[i].vidurkis += s[i].pazimys[j];
        }

        cout << "Iveskite egzamino rezultata" << endl;
        cin >> s[i].rezultatas;

        sort(s[i].pazimys, s[i].pazimys + p);
        if(p % 2 == 0)
        {
            s[i].mediana =
                (s[i].pazimys[p/2 - 1] + s[i].pazimys[p/2]) / 2.0;
        }
        else
        {
            s[i].mediana = s[i].pazimys[p/2];
        }
        s[i].vidurkis /= p;
    }

    for(int i = 0; i < n; i++)
    {
        cout<<s[i].vardas<<" "<<s[i].pavarde<<" galutinis rezultatas:"<<endl;
        cout<< s[i].vidurkis * 0.4 + s[i].rezultatas * 0.6<< endl;
        cout<<s[i].vardas<<" "<<s[i].pavarde<<" mediana:"<<endl;
        cout<<s[i].mediana<<endl;
    }

    for(int i = 0; i < n; i++)
    {
        delete[] s[i].pazimys;
    }

    delete[] s;

    return 0;
}
