#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

double f(double x) { return cos(x)-x+1; }  //�������, ���� ������� ����


int main() {
 double tmp,x0,x1,eps;
 int N=0;

 cout<<"eps=";
 cin>>eps;   //��������
 cout<<"x0=";
 cin>>x0;    //������ ��������� �����������
 cout<<"x1=";
 cin>>x1;    //������ ��������� �����������

    while(fabs(x1-x0)>eps) {  //������ ������� |x[n]-x[n+1]|<eps
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
