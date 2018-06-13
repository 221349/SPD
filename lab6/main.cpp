#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> T; //tablica nastepnikow technologicznych
vector<int> A; //tablica nastepnikow maszynowych
vector<int> P; //tablica czasow wykonywania
vector<int> Lp; //tablica z liczba poprzednikow
vector<int>PT; //tablice poprzednikow
vector<int>PA;
vector<bool>statusy; //true jesli zadanie nie zostalo jeszcz wrzucone do kolejki
vector<int>S;  //tablica z czasami rozpoczecia zadania
vector<int>C;  //tablica z czasami zakonczenia
vector<int>kolejka; //kolejka wykonywania zadań


int n; //liczba operacji
int maszyny; // liczba maszyn
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
		return false;
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
	file >> maszyny;

}
void wyznacz_poprzednikow()
{
	for (int i = 0; i < n + 1; i++)
		PT.push_back(0);

	for (int i = 0; i < n+1; i++)
		PA.push_back(0);

	for (int i = 1; i < n+1; i++)
	{
		PT[T[i]] = i;
		PA[A[i]] = i;
	}
}
void inicjuj_tablice()
{
	bool tmp = true;
	for (int i = 0; i < n + 1; i++)
		Lp.push_back(0);
	for (int i = 0; i < n + 1; i++)
		C.push_back(0);
	for (int i = 0; i < n + 1; i++)
		S.push_back(0);
	for (int i = 0; i < n + 1; i++)
		statusy.push_back(tmp);
}
void wyznacz_Lp()      //funkcja wyznaczajaca tablice z liczba poprzednikow
{

	for (int i = 1; i <n+1 ; i++)
	{
		for (int j = 1; j < n+1; j++)
		{
			if (T[j] == i)
			{
				Lp[i] += 1;
			}
			if (A[j] == i)
			{
				Lp[i] += 1;
			}
		}
	}
}

void harmonogram()
{
	for (int i = 1; i < n+1 ;i++)
	{

		if (Lp[i] == 0 && statusy[i]==true)        //zadanie, ktore nie ma poprzednika i statusu ze jest juz w kolejce
		{
			kolejka.push_back(i);
			S[kolejka.back()] = max(C[PA[kolejka.back()]], C[PT[kolejka.back()]]);  //wyznaczanie czasu rozpoczecia
			C[kolejka.back()] = S[kolejka.back()] + P[kolejka.back()];     //czasu zakonczenia
			statusy[kolejka.back()] = false;
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

	if (kolejka.size() < n)
		harmonogram();
}
void Cmax()                       //wyznaczenie funkcji celu, zadanie ktore ma najwieksza wartosc w tablicy czasow zakonczenia
{
	int max=0;
	for(int i=1;i<n+1;i++)
	{
		if(C[i]>max)
		max=C[i];
	}
	cout<<max<<endl;
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
	loadFromFile(argc, argv[1]);
	inicjuj_tablice();
	wyznacz_poprzednikow();
	wyznacz_Lp();
	harmonogram();
	wyswietl();
	Cmax();


	return 0;
}
