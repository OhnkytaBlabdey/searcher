#include<cstdio>
#include<cstdlib>
#include<ctime>

int rnd(int n)
{
	if(n<2) return 1;
	return rand()%n+1;
}

int main()
{
	// FILE *fout=fopen("tree.txt")
	srand(time(0));
	int m=100;
	printf("%d\n",m);
	for(int i=0;i<m;i++){
		printf(" %d %d\n",i+1,rnd(i));
	}
	return 0;
}