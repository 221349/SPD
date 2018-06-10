#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b)
{
	if (a < b) return b;
	return a;
}
int min(int a, int b)
{
	if (a < b) return a;
	return b;
}

class dane {
public:
	int nrZadania;
	vector<int> czasyNaMaszynie;
	int czasCalkowity;
	void wyliczCzasCalkowity()
	{
		czasCalkowity = 0;
		for (long unsigned int i = 0; i < czasyNaMaszynie.size(); i++) czasCalkowity += czasyNaMaszynie[i];
	}
	bool operator < (const dane& zad) const { return (czasCalkowity < zad.czasCalkowity); }
};

vector<dane> wektorZadan;

int obliczCmax(vector<dane> wektorZadan, vector<int> tablicaPi, int liczbaZadan, int liczbaMaszyn);

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

	int liczbaZadan = 0;
	int liczbaMaszyn = 0;

	plik >> liczbaZadan;
	plik >> liczbaMaszyn;

	for (int i = 1; i <= liczbaZadan; i++)
	{
		dane temporary;
		for (int j = 0; j < liczbaMaszyn; j++)
		{
			int czastmp;
			plik >> czastmp;
			temporary.czasyNaMaszynie.push_back(czastmp);
		}
		temporary.nrZadania = i;
		temporary.wyliczCzasCalkowity();
		wektorZadan.push_back(temporary);
	}
	sort(wektorZadan.rbegin(), wektorZadan.rend());
	vector<int> tablicaPi;
	int cMax;
	tablicaPi.push_back(0);
	vector<int> tablicaPiGwiazdka;
	for (long unsigned int i = 1; i < wektorZadan.size(); i++)
	{
		cMax = 0;
		for (long unsigned int j = 0; j < i + 1; j++)
		{
			tablicaPi.insert(tablicaPi.begin() + j, i);
			int cc = obliczCmax(wektorZadan, tablicaPi, liczbaZadan, liczbaMaszyn);
			if (cc < cMax)
			{
				cMax = cc;
				tablicaPiGwiazdka = tablicaPi;
			}
			tablicaPi.erase(tablicaPi.begin() + j);
		}
		tablicaPi = tablicaPiGwiazdka;
	}
	cout << cMax << endl;
	return 0;
}



int obliczCmax(vector<dane> wektorZadan, vector<int> tablicaPi, int liczbaZadan, int liczbaMaszyn)
{
	int * tablicaMaszyn = new int[liczbaMaszyn];
	for (int i = 0; i < liczbaMaszyn; i++) tablicaMaszyn[i] = 0;
	for (long unsigned int i = 0; i < tablicaPi.size(); i++)
	{
		for (int j = 0; j < liczbaMaszyn; j++)
		{
			if (j > 0 && tablicaMaszyn[j - 1] > tablicaMaszyn[j]) tablicaMaszyn[j] = tablicaMaszyn[j - 1];
			tablicaMaszyn[j] += wektorZadan[tablicaPi[i]].czasyNaMaszynie[j];
		}
	}
	int cMax = tablicaMaszyn[liczbaMaszyn - 1];
	delete[] tablicaMaszyn;
	return cMax;
}
