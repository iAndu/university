#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;
/*pas 1 potrivire FARA CONVERSIE prioritate  varianta non-template, apoi template fara parametrii,
        apoi template cu 1 parametru , apoi template cu mai multi parametrii
 pas 2 daca nu exista potrivire exacta- conversie DOAR la varianta non-template*/

template <class T> void fs(T t){cout<<"supraincarc template T"<<endl;}
template <> void fs(float pf){cout<<"supraincarcare template <>"<<endl;}
void fs(float pf){cout<<"supraincarcare non-template"<<endl;}



template <class T> void fs1(T p1,T p2){cout<<"supraincarc template1 T T "<<endl;}
template <> void fs1(int p1,int p2){cout<<"supraincarcare template <> int int"<<endl;}
void fs1(int p1,int p2){cout<<"supraincarcare non-template int int"<<endl;}

template <class T1,class T2> void fs2(T1 p1,T2 p2){cout<<"supraincarcare 2param T1 T2"<<endl;}
template <class T> void fs2(T p1,T p2){cout<<"supraincarc template 1param T "<<endl;}

template <class T> void fr(T &r){cout<<"template-ref"<<endl;}
template <class T> void frc(const T &r){cout<<"template-ref-const"<<endl;}

template <class T> void fpm(T p){*p='a';cout<<"template param modif"<<endl;}
template <class T> void fp(T p){cout<<"template param  nemodif"<<endl;}
void fpc(char *p){*p='a'; }

int main(int argc, char *argv[])
{ float fa=2.5;
  fs('a');// deducere T=char
  fs(2.5);//deducere T=double
  fs(fa);  //non-template pt float , prioritar fata de template<>, prioritar fata de template T
  fs<float>(fa); // template<> prioritar fata de template general cu T=float

 fs1(2,3.5);//Nu reuseste potrivire exacta nici non-template nici template(cu 0 param sau 1 param)- face conversie la non-template
 fs1<int>(2,3.5);// deducere explicita T=int -alege template<>

 fs2(2.5,3.5);// Prioritate cu template cu 1 parametru T fata de template cu 2 param T1 si T2- nu e ambiguitate

 //fr(1);  // ! nu pot apels const prin referinta
 frc(1); //pot apela const prin referinta care nu modifica

 char v[10];
 //fpm("ab");//T=const char * -nu permite modificarea zonei -la compilare!
 fpm(v);
 fp("ab");//T=const char *
 //fpc("ab"); // permite p="ab" dar instructiunea *p='b' da eroare la executie

 const char* cp;
 char *p;
 //p=cp; // eroare la compilare
  p="ab"; // totusi permis
 //*p='b'; //da eroare la executie

  system("PAUSE");
    return 0;
}
