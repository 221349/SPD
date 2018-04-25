#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <string>
//#include <conio.h>

using namespace std;
struct Element{
//	Element(int a,int b,int c):r(a), p(b), q(c){};
	int r,p,q;
	void czytaj(int a,int b,int c){r=a,p=b,q=c;};
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
//typedef priority_queue <Element, vector<Element>, Maxq> Kolejka_q;
//typedef priority_queue <Element, vector<Element>, MinR> Kolejka_r;
/* void WstawElement(Kolejka_q & kolejka_q, int a, int b, int c){
 	Element el;
	 el.r=a;
	 el.p=b;
	 el.q=c;
	 kolejka_q.push(el);
 }
  void WstawElement(Kolejka_r & kolejka_r, int a, int b, int c){
 	Element el;
	 el.r=a;
	 el.p=b;
	 el.q=c;
	 kolejka_r.push(el);
 } */
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

 	 int n,a,b,c,i;
	 plik >> n;
	 for (int j=0;j<n;j++){
		 plik >> a >> b >> c;
		 test.czytaj(a,b,c);
		 //Element test(a,b,c);
		// Kolejka_q.push(test);
		 Kolejka_r.push(test);
	//	 WstawElement(Kolejka_q,a,b,c);
	//	 WstawElement(Kolejka_r,a,b,c);
	 }
	 	/*
	 while (Kolejka_q.size()>0){
		 Element odczytany=Kolejka_q.top();
		 Kolejka_q.pop();
		 cout << odczytany.r << "  " << odczytany.p << "  " << odczytany.q << endl;
	 }
	 	 	cout << "RRRRRRR" << endl;
	 while (Kolejka_r.size()>0){

		 Element odczytany1=Kolejka_r.top();
		 Kolejka_r.pop();
		 cout << odczytany1.r << "  " << odczytany1.p << "  " << odczytany1.q << endl;
	 }
	*/

	 int t=0;
	 int Cmax=0;
	 Element e;
	 while (!Kolejka_q.empty() || !Kolejka_r.empty()){
		 while(!Kolejka_r.empty() && Kolejka_r.top().r<=t){
			 e=Kolejka_r.top();
			 Kolejka_q.push(e);
			 Kolejka_r.pop();
		 }
		 if (Kolejka_q.empty())
		 {
		 t=Kolejka_r.top().r;
		 }
		 	else {
			 e=Kolejka_q.top();
			 Kolejka_q.pop();
			 t=t+e.p;
			 Cmax=max(Cmax,t+e.q);
			 }
	 }
	 cout << Cmax;

 }
