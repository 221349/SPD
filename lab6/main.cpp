#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int n; //liczba operacji

vector<int> T; //tablica nastepnikow technologicznych
vector<int> A; //tablica nastepnikow maszynowych
vector<int> P; //tablica czasow wykonywania

vector<int> Lp; //tablica z liczba poprzednikow
vector<int>PT; //tablice poprzednikow
vector<int>PA;
vector<bool>statusy; //true jesli zadanie nie zostalo jeszcz wrzucone do kolejki
vector<int>S;  //tablica z czasami rozpoczecia zadania
vector<int>C;  //tablica z czasami zakonczenia
int kolejka = 0; //kolejka wykonywania zadań


bool loadFromFile(int argc, char *argv) // załadowanie pliku do struktury
{
	char * filename= new char[32];
  fstream file;
  if(argc > 1)
  {
    file.open(argv, ios::in);
  }
  else
  {
    cout<<"Input path: ";
    cin >> filename;
    file.open(filename, ios::in);
  }

	int tmp = 0;

	if (file.good())
		cout << "Udalo sie otworzyc plik" << endl;
	else
	{
		cout << "Nie udalo sie otworzyc pliku" << endl;
		return 1;
	}
	file >> n;
	T.push_back(0);
	A.push_back(0);
	P.push_back(0);
	for (int i = 0; i < n; i++)
	{
		file>> tmp;
		T.push_back(tmp);
	}
	for (int i = 0; i < n; i++)
	{
		file >> tmp;
		A.push_back(tmp);
	}
	for (int i = 0; i < n; i++)
	{
		file >> tmp;
		P.push_back(tmp);
	}

	return 0;
}

void inicjuj_tablice()
{
	Lp.resize(n + 1);
	C.resize(n + 1);
	S.resize(n + 1);
	for (int i = 0; i < n + 1; i++)
		statusy.push_back(1);
}

void wyznacz_poprzednikow()
{
	PT.resize(n + 1);
	PA.resize(n + 1);

	for (int i = 1; i < n+1; i++)
	{
		PT[T[i]] = i;
		PA[A[i]] = i;
	}
}

void wyznacz_Lp()      //funkcja wyznaczajaca tablice z liczba poprzednikow
{

	for (int i = 1; i <n+1 ; i++)
	{
		if(PT[i] != 0) Lp[i]++;
		if(PA[i] != 0) Lp[i]++;
	}
}

void harmonogram()
{
	for (int i = 1; i < n+1 ;i++)
	{

		if ((Lp[i] == 0) && (statusy[i] == 1))        //zadanie, ktore nie ma poprzednika i statusu ze jest juz w kolejce
		{
			kolejka++;
			S[i] = max(C[PA[i]], C[PT[i]]);  //wyznaczanie czasu rozpoczecia
			C[i] = S[i] + P[i];     //czasu zakonczenia
			statusy[i] = 0;
			for(int j=1;j<n+1;j++)          //aktualizacja tablicy z liczba poprzednikow
			{
				if(PA[j]==i)
				Lp[j]-=1;
				if(PT[j]==i)
				Lp[j]-=1;
			}
			break;
		}
	}

	if(kolejka < n) harmonogram();
}
void Cmax()                       //wyznaczenie funkcji celu, zadanie ktore ma najwieksza wartosc w tablicy czasow zakonczenia
{
	int max=0;
	for(int i=1;i<n+1;i++)
	{
		if(C[i]>max) max=C[i];
	}
	cout << max << endl;
}
void wyswietl()        //wyswietlanie wynikow rozpoczecia i zakonczenia
{
	for (int i = 1; i <n+1; i++)
	{
		cout << S[i] << " " << C[i] << " " << endl;
	}
}

int main(int argc, char *argv[])
{
	if(loadFromFile(argc, argv[1])) return 1;
	inicjuj_tablice();
	wyznacz_poprzednikow();
	wyznacz_Lp();
	harmonogram();
	wyswietl();
	Cmax();


	return 0;
}
