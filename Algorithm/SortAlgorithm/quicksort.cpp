#include<iostream>
#include<cstdio>
using namespace std;
int a[1000];


void quicksort(int first, int last){
	
	 int i,j,t,temp; 
    if(first>last) 
       return; 
                                
    temp=a[first]; //temp中存的就是基准数 
    i=first; 
    j=last; 
	
	while(i != j){
		
		while(a[j] >= temp && i < j)
			j --;
		while(a[i] <= temp  && i < j)
			i ++;
		if(i < j){
		t = a[j];
		a[j] = a[i];
		a[i] = t;
		}
	}
	a[first]=a[i]; 
    a[i]=temp; 
	
	quicksort(first,i-1);
	quicksort(i+1,last);

}



int main(){
 int i,j,t,n; 
    //读入数据 
    scanf("%d",&n); 
    for(i=1;i<=n;i++) 
                   scanf("%d",&a[i]); 
    quicksort(1,n); //快速排序调用 
                             
    //输出排序后的结果 
    for(i=1;i<=n;i++) 
        printf("%d ",a[i]); 

  
return 0;
}