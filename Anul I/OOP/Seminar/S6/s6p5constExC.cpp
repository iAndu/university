#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class pers
{
 const int cnp;
 char * const nume;
 const char * const data;
 char prenume[20];
 const char * nickname;
static int nrp;
public:
pers(int c, char *n, char *p, char *d, char *nn):cnp(c),
nume(new char[10]),data(strcpy(new char[strlen(d)+1],d))
 {//data=d; //pentru ca pointerul este const
  //strcpy(data,d); //pentru ca pointerul nu modifica zona
  strcpy(nume,n); // nu va putea lua un nume mai lung de 10 char
  strcpy(prenume,p); // nu poate proteja si zona -ar trebui initializat in constructor -toti cei 20 membrii
  char *temp=new char[strlen(nn)+1];
  strcpy(temp,nn);
  nickname=temp;

  nrp++;
  }
~pers(){nrp--;}

int get_cnp() const {return cnp;} // nu pot modifica datele obiectului apelat
void set_nume(char *n,char *nn)
  {strcpy(nume,n);
  char *temp =new char[10];
  strcpy(temp, nn);
  nickname =temp;
  }
char * get_nume()const {return nume;} // pt a nu modifica numele

};
int pers::nrp=0; // se poate da si alta valoare
int main()
{ int *ii;
 float *cc;
 ii=(int *)cc;
 int nr,c;
 char n[10],p[10],nn[10],d[10];
/* cin>>c>>n>>p;
  pers vp[2]={pers(c,p,n),pers(c,p,n)};
ar trebui apelat constructorul pentru toate obiectele la declarare
-se creaza toate odata nu doar cate sunt necesare*/
pers *vp[2];
  cin>>nr;
for(int i=0;i<nr;i++)
{cin>>c>>p>>n;
vp[i]=new pers(c,p,n,d,nn);
}
return 0;
}




