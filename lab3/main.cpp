#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <string>
//#include <conio.h>

using namespace std;

class Element{
public:
	int r,p,q;
	void czytaj(fstream &file){
		file >> r >> p >> q;
	}
};

class Sortowanie_q{
public:
	inline bool operator()(const Element& el1, const Element& el2){
		return el1.q < el2.q;
	}
};
class Sortowanie_r{
public:
	inline bool operator()(const Element& el1, const Element& el2){
		return el1.r > el2.r;
	}
};

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

 	priority_queue <Element, vector<Element>, Sortowanie_q> Kolejka_q;
 	priority_queue <Element, vector<Element>, Sortowanie_r> Kolejka_r;
 	Element test;

 	int n;
	plik >> n;
	for (int j = 0 ; j < n; j++){
	 	test.czytaj(plik);
	 	Kolejka_r.push(test);
	}
	int t = 0;
	int Cmax = 0;
	Element e;
	Element l;
	while (!Kolejka_q.empty() || !Kolejka_r.empty()){
	 	while(!Kolejka_r.empty() && Kolejka_r.top().r <= t){
		 	e = Kolejka_r.top();
			Kolejka_q.push(e);
			Kolejka_r.pop();
			if (e.q > l.q){        //e.q pierwsze zadanie z uszeregowanej kolejki    l.q czas dostarczenia zadania ktore jest na maszynie
      	l.p = t - e.r;      // czas zadania jaki pozosta� jak przerwalismy		.p = czas wykonania		.r = termin dostepnosci
        t = e.r;            // t jest terminem dostepnosci zadania
			 	if (l.p > 0){          // jezeli czas pozosta� na G to wrzucamy l do kolejki g
         	Kolejka_q.push(l);
			 	}
			}
		}

		if (Kolejka_q.empty()){
		 	t = Kolejka_r.top().r;
		}
		else {
		 	e = Kolejka_q.top();
			Kolejka_q.pop();
			l = e;                 //naszym aktualnym zadaniem jest to co by�o pierwszym elmentem uszeregowanym na kolejce G
			t = t + e.p;
			Cmax = max(Cmax, t + e.q);
	 	}
	}
	cout << Cmax;
	return 0;
}
