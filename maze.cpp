#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstdio>

using namespace std;
const int M=102;

// int val[M];
int first_child[M];
int next_child[M];

bool is_son(int p,int c)
{
	if(first_child[p]==c) return true;
	p=first_child[p];
	while(next_child[p]) {
		if(next_child[p]==c) return true;
		p=next_child[p];
	}
	return false;
}

inline int sons(int p)
{
	int ct=0;
	if(!first_child[p]) return 0;
	ct++; p=first_child[p];
	while(next_child[p]){
		ct++;
		p=next_child[p];
	}
	return ct;
}

int get_son(int p,int i)
{
	int ct=0;
	if(!first_child[p]) return 0;
	ct++;
	if(i==ct) return first_child[p];
	p=first_child[p];
	while(next_child[p]){
		ct++;
		if(i==ct) return next_child[p];
		p=next_child[p];
	}
	return 0;
}

void build(int c,int f)
{
	if(f==c) return;
	if(first_child[f] == 0 ){
		first_child[f]=c;
		// cout<<setw(6)<<f<<setw(6)<<c<<endl;
	}
	else{
		int t=first_child[f];
		while(next_child[t]) t=next_child[t];
		next_child[t]=c;
		// cout<<setw(6)<<f<<setw(6)<<t<<setw(6)<<c<<endl;
	}
}
FILE *fin=NULL;

void Read(int &a)
{
	fscanf(fin,"%d",&a);
}

int main(int argc,char ** argv)
{
	if(argc==2){
		// freopen(argv[1],"r",stdin);
		fin=fopen(argv[1],"r");
	}
	int f,c,m; //father child maxn
	fill(first_child,first_child+M,0);
	fill(next_child,next_child+M,0);
	Read(m);
	// Read(c);Read(f);
	// cin>>m;
	// cin>>c>>f; //0 0
	for(int i=0;i<m;i++){
		// cin>>c>>f;
		Read(c);Read(f);
		build(c,f);
	}
	
	int cur=1;
	do{
		// cout<<"[debug] cur "<<cur<<endl;
		int ct=sons(cur);
		cerr<<cur<<endl;
		cout<<ct<<endl;
		
		if(ct==0) break;
		int tmp;
		do{
			cin>>tmp;
		} while( tmp>ct || tmp <1 );
		cur=get_son(cur,tmp);
	}while( cur != m-1);
	if(cur==m) cerr<<"you win"<<endl;
	else cerr<<"you lose"<<endl;
	cout<<0<<endl;
	if(argc==2 && fin!=NULL){
		fclose(fin);
	}
	return 0;
}
// 3 5 19 48 99
// 3 2 2 2 1

/*
100 65 30 21 5 2 1
2 1 4 1 3 1
*/