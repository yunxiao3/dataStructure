#include <iostream>

using namespace std;





int pre[] = {1,2,3,4,5,6};
int in[] = {3,2,4,1,6,5};
int post[6];	




void slove(int preL, int inL, int postL, int N){


	if (N == 0) return ;
	
	if (N == 1) {
		post[postL] = pre[preL];
		return;
	}

	post[postL + N - 1] = pre[preL];

	int i ;

	for (i = 0 ;i < N ;i ++)
		if(in[i + inL] == pre[preL])
			break;

	slove(preL + 1, inL, postL ,i );
	slove(preL + i + 1,inL + i + 1, postL + i , N - i - 1 );


}




int main()
{

	slove(0,0,0,6);
	
	for (int i = 0; i < 6; ++i)
	{
		cout << post[i]<<endl;
	}
	
	return 0;
}

