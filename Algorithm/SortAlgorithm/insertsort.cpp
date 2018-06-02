#include<iostream>
using namespace std;
int main(){
 string a;
int i, j;
 getline(cin,a);
 i = a.length() - 1;
 while(i >= 0){
	while(a[i] != ' ' && i >=0)
		i--;
	j = i + 1;
	while(a[j] !=' ' && j < a.length())
	  {cout<<a[j];
		j++;
		}
	cout<<" ";
	i--; 


 }
return 0;
}
