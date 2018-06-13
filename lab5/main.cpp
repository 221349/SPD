#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class dane {
public:
    vector<int> czasnamaszynie;
    int czascalk;
    void wyliczczascalk()
    {
        czascalk = 0;
        for (long unsigned int i = 0; i < czasnamaszynie.size(); i++) czascalk += czasnamaszynie[i];
    }
    bool operator < (const dane& zad) const { return (czascalk < zad.czascalk); }
};

int obliczCmax(vector<dane> wektorZadan, vector<int> tab1, int liczbaZadan, int liczbaMaszyn)
{
    int * tablicaMaszyn = new int[liczbaMaszyn];
    for (int i = 0; i < liczbaMaszyn; i++) tablicaMaszyn[i] = 0;

    for (long unsigned int i = 0; i < tab1.size(); i++)
    {
        for (int j = 0; j < liczbaMaszyn; j++)
        {
            if(j > 0){
                if (tablicaMaszyn[j - 1] > tablicaMaszyn[j]) tablicaMaszyn[j] = tablicaMaszyn[j - 1];
            }
            tablicaMaszyn[j] += wektorZadan[tab1[i]].czasnamaszynie[j];
        }
    }
    int cMax = tablicaMaszyn[liczbaMaszyn - 1];
    delete[] tablicaMaszyn;
    return cMax;
}

int main(int argc, char *argv[])
{
	char * filename= new char[32];
  ifstream plik;
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
    int liczbaZadan = 0;
    int liczbaMaszyn = 0;

    vector<dane> wektorZadan;

    plik >> liczbaZadan;
    plik >> liczbaMaszyn;

    for (int i = 1; i <= liczbaZadan; i++)
    {
        dane temp;
        for (int j = 0; j < liczbaMaszyn; j++)
        {
            int czastemp;
            plik >> czastemp;
            temp.czasnamaszynie.push_back(czastemp);
        }
        temp.wyliczczascalk();
        wektorZadan.push_back(temp);
    }

    sort(wektorZadan.rbegin(), wektorZadan.rend());
    vector<int> tab1;
    int cMax;
    tab1.push_back(0);
    vector<int> tab2;
    for (long unsigned int i = 1; i < wektorZadan.size(); i++)
    {
        cMax = 1000000;
        for (long unsigned int j = 0; j < i + 1; j++)
        {
            tab1.insert(tab1.begin() + j, i);
            int cm = obliczCmax(wektorZadan, tab1, liczbaZadan, liczbaMaszyn);
            if (cm < cMax)
            {
                cMax = cm;
                tab2 = tab1;
            }
            tab1.erase(tab1.begin() + j);
        }
        tab1 = tab2;
    }
    cout <<"Cmax: "<<cMax << endl;

    return 0;
}
