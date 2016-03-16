#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double f(double x) { return cos(x)-x+1; }  //Функция, нули которой ищем


int main() {
 double tmp,x0,x1,eps;
 int N=0;

 cout<<"eps=";
 cin>>eps;   //Точность
 cout<<"x0=";
 cin>>x0;    //Первое начальное приближение
 cout<<"x1=";
 cin>>x1;    //Второе начальное приближение

    while(fabs(x1-x0)>eps) {  //Выбран останов |x[n]-x[n+1]|<eps
     tmp=x1;
     x1=x1-(x1-x0)*f(x1)/(f(x1)-f(x0));
     x0=tmp;
     N++;
   }
      cout.setf(ios::scientific);
cout<<endl<<endl<<"x="<<x1<<endl<<"N="<<N<<endl;

cin>>N;
return 0;
}
