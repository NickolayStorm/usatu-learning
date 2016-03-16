#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double f(double x) { return cos(x)-x+1; } //�������, ���� ������� ����
double df(double x) { return -sin(x)-1; } //Ÿ �����������

int main() {
 double tmp,x,eps;
 int N=0;

 cout<<"eps=";
 cin>>eps;   //��������
 cout<<"x0=";
 cin>>x;     //��������� �����������
 tmp=x+2*eps;
    while(fabs(x-tmp)>eps) { //������ ������� |x[n]-x[n+1]|<eps
     tmp=x;
     x=x-f(x)/df(x);
     N++;
   }
   cout.setf(ios::scientific);
cout<<endl<<endl<<"x="<<x<<endl<<"N="<<N<<endl;
cin>>N;
return 0;
}
