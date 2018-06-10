#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

class dane{
public:
    int p,r,q;
	dane(int y, int x, int z);
};

struct poR
{
	bool operator ()( const dane& x, const dane& y )
	{
		return x.r > y.r;
	}
	//bool operator < (const dane& x, const dane& y){
};
struct poQ
{
	bool operator ()( const dane& x, const dane& y )
	{
		return x.q < y.q;
	}
};
//priority_queue <dane> kolejkaPriorytetowa;
//priority_queue <dane> wektorG;
priority_queue<dane, vector<dane>, poQ> wektorG;
priority_queue<dane, vector<dane>, poR> wektorN;
//priority_queue <dane> wektorN;

dane::dane(int x, int y, int z)
{
	p = y;
	r = x;
	q = z;
}

int znajdzMinR(vector <dane> wektor, int wariant){
    int tmp=wektor[0].r, tmp2=0;
    for (long unsigned int i=0; i < wektor.size(); i++){
        if(wektor[i].r<tmp) {
            tmp=wektor[i].r;
            tmp2=i;
        }
    }
    if (wariant==1) return tmp;
    if (wariant==2) return tmp2;
    return 0;
}

int znajdzMaxR(vector <dane> wektor, int wariant){
    int tmp=wektor[0].q, tmp2=0;
    for (long unsigned int i=0; i<wektor.size(); i++){
        if(wektor[i].q>tmp) {
            tmp=wektor[i].q;
            tmp2=i;
        }
    }
    if (wariant==1) return tmp;
    if (wariant==2) return tmp2;
    return 0;
}

int main(int argc, char *argv[])
{
	  char * filename= new char[32];
    fstream plik;
    if(argc > 1)
    {
      plik.open(argv[1], ios::in);
    }
    else
    {
      cout<<"Input path: ";
      cin >> filename;
      plik.open(filename, ios::in);
    }
    int liczbaDanych=0;
    int r,p,q;
    int t=0, k=0, cMax=0;
    plik >> liczbaDanych;
    vector <dane> tablicaPi;
    cout << liczbaDanych << endl;
    int a=0, b=0, c=0;

    for (int i=0; i < liczbaDanych; i++){
        plik >> r;
        plik >> p;
        plik >> q;
        //cout << r << "\t" << p << "\t" << q << endl;   ////////Data display
        dane Dane(r,p,q);
        wektorN.push(Dane);
    }

    while(wektorG.empty()==false || wektorN.empty()==false){
        while(wektorN.empty()==false && wektorN.top().r<= t){
            //e=znajdzMinR(wektorN,2);
            wektorG.push(wektorN.top());
            wektorN.pop();
        }
         if (wektorG.empty() == true){
                t = wektorN.top().r;
                continue;
        }
        //e = znajdzMaxR(wektorG, 2);
        dane Dane1(0,0,0);
        Dane1 = wektorG.top();
        wektorG.pop();
        k = k+1;
        tablicaPi.push_back(Dane1);
        t=t+Dane1.p;
        if (cMax <= t+Dane1.q)
        {
            cMax=t+Dane1.q;
            b=k;
        }
    }
    int sum=0;
    cout<<endl;
    for (int j=b; j>=1; j--)
    {
        sum=0;
        for (int s=j; s<=b; s++) sum+=tablicaPi[s-1].p;
        sum+=tablicaPi[b-1].q + tablicaPi[j-1].r;

        cout<<sum<<endl;
        if(cMax==sum)
        {
            a=j;
            //break;
        }
    }
   for (int j=a; j<=b; j++)
    {
        if(tablicaPi[j-1].q<tablicaPi[b-1].q) c=j;
    }
    cout << "s";
    cout << cMax <<" "<<a<<" "<<b<<" "<<c<< endl;
    return 0;
}
