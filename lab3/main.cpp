#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <string>
#include <conio.h>

using namespace std;
struct Element{
	int r, p, q;
	void czytaj(int a,int b,int c){r = a, p = b, q = c;};
};

struct Sortowanie_q{
	bool operator()(const Element& el1, const Element& el2){				// < od najwiekszego do najmniejszego
		return el1.q < el2.q;												// > od najmniejszego do najwiekszego
	}
};
struct Sortowanie_r{
	bool operator()(const Element& el1, const Element& el2){				// < od najwiekszego do najmniejszego
		return el1.r > el2.r;												// > od najmniejszego do najwiekszego
	}
};

 int main(){
 	priority_queue <Element, vector<Element>, Sortowanie_q> Kolejka_q;
 	priority_queue <Element, vector<Element>, Sortowanie_r> Kolejka_r;
 	 Element test;

 	 int n, a, b, c;
	 fstream plik;
	 plik.open("SCHRAGE7.dat");
	 plik >> n;
	 for (int j = 0 ; j < n; j++){
		 plik >> a >> b >> c;
		 test.czytaj(a, b, c);
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
                l.p = t - e.r;      // czas zadania jaki pozosta³ jak przerwalismy		.p = czas wykonania		.r = termin dostepnosci
                t = e.r;            // t jest terminem dostepnosci zadania
			 if (l.p > 0){          // jezeli czas pozosta³ na G to wrzucamy l do kolejki g
             Kolejka_q.push(l);
			 }
			 }
		 }
		 if (Kolejka_q.empty())
		 {
		 t = Kolejka_r.top().r;
		 }
		 	else {
			 e = Kolejka_q.top();
			 Kolejka_q.pop();
			 l = e;                 //naszym aktualnym zadaniem jest to co by³o pierwszym elmentem uszeregowanym na kolejce G
			 t = t + e.p;
			 Cmax = max(Cmax, t + e.q);
			 }
	 }
	 cout << Cmax;
 }
