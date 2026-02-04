#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


struct studentas {
    string vardas = "D", pavarde = "K";
    int *pazimys;
    //vector<int> pazimys;
    int rezultatas = 0;
};

int main()
{
    studentas a;
    studentas b;
    studentas c;
    
    a.pazimys = new int[5];
    b.pazimys = new int[5];
    c.pazimys = new int[5];
    
    for(int i=0; i<2; i++)
    {
        cin>>a.pazimys[i];
        cin>>b.pazimys[i];
        cin>>c.pazimys[i];
    }
    
    // int temp;
    // for(int i=0; i<2; i++)
    // {
    //     cin>>temp;
    //     a.pazimys.push_back(temp);
    //     cin>>temp;
    //     b.pazimys.push_back(temp);
    //     cin>>temp;
    //     c.pazimys.push_back(temp);
    // }
    
    for(int i=0; i<2; i++)
    {
        a.rezultatas += a.pazimys[i];
        b.rezultatas += b.pazimys[i];
        c.rezultatas += c.pazimys[i];
    }
    cout<<a.rezultatas/2.0*0.4+5*0.6<<endl;
    cout<<b.rezultatas/2.0*0.4+10*0.6<<endl;
    cout<<c.rezultatas/2.0*0.4+0*0.6<<endl;
    
    delete(a.pazimys);
    delete(b.pazimys);
    delete(c.pazimys);
    return 0;
}
