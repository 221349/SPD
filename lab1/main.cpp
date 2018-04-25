#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;


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
  int n,r,p;
  int i,j,k,temp;
  int m;

  if(plik.good()==false)
  {
      cout<<"Blad otwarcia pliku\n";
      return 1;
  }
  else
  {
    plik >> n; //wczytanie n
    m=2; //ilosc kolumn - zawsze dwa bo mamy tylko dwie kolumny
    if(argc == 3)
    {
      cout<<"Liczba wczytanych zadan: "<<n<<endl;
    }

    double **tab_czas = new double *[n]; //alokacja pamieci
    for (i =0; i < n; ++i)
    {
         tab_czas[i] = new double[m]; //alokacja pamieci
         for (j = 0; j < m; ++j) //wpisanie wartosci do tablicy
         tab_czas[i][j] = 0;
    }

    for(i=0;i<n;i++)       //petle wczytujace dane z pliku do tablicy dwuwymiarowej
    {
      for(j=0;j<m;j++)
      {
          plik >> tab_czas[i][j];
          if(argc == 3)
          {
            cout<<tab_czas[i][j]<<"   "; //wyswietlenie
          }
      }
      if(argc == 3)
      {
        cout<<endl;
      }
    }

    //sortowanie tablicy ze wzgledu na r

    for (k=0; k<n-1; k++)
      for (int i=0; i<n-1; i++)
      {
           if (tab_czas[i][0]>tab_czas[i+1][0])    //sortowanie babelkowe
          {
              swap(tab_czas[i][0],tab_czas[i+1][0]);  //jesli pierwszy termin jest wiekszy niz drugi - zamien
              swap(tab_czas[i][1],tab_czas[i+1][1]);  //nie zapomnij zamienic tez czasu obslugi
          }
      }


      if(argc == 3)
      {
        cout<<endl<<endl;
      }
    for(i=0;i<n;i++)
    {
      for(j=0;j<m;j++)
      {
        if(argc == 3)
        {
          cout<<tab_czas[i][j]<<"   "; //wyswietlenie
        }
      }
      if(argc == 3)
      {
        cout<<endl;
      }
    }


    //OBLICZANIE CMAX

    int suma=0;

    for(i=0;i<n;i++)
    {
      if(suma < tab_czas[i][0])  //Sprawdza czy jakies zadanie jest juz dostepne
      {
        suma = tab_czas[i][0];   //Jak nie to dodaje przerwe pomi�dzy suma a dostepnoscia czyli suma=dostepnosc
      }
      suma += tab_czas[i][1];
    }

    if(argc == 3)
    {
      cout<<endl<<"Cmax: ";
    }
    cout << suma;
  }
  return 0;
}
