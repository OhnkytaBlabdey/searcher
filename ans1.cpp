#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<algorithm>
#include<iomanip>
#include<cassert>

/* cbuf -head |maze tree.txt|ans|cbuf -rear */
/* cbuf -head |maze tree.txt 2>log.txt|ans 2>nul|cbuf -rear */

using namespace std;
const int M=102;

int vis[M];
int val[M];
int first_child[M];
int next_child[M];
int finish[M];
int fa[M];
int tot;

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

void mark(int p)
{
	finish[p]=1;
	while(fa[p]){
		if(next_child[p]) break;
		p=fa[p];
		finish[p]=1;
	}
}

int select_son(int p)
{
	int res=1;
	int ct=1;
	p=first_child[p];
	
	if(!finish[p]){
		// if( !next_child[p] && !val[p]) mark(p);
		return 1;
	} // first_child
	
	res=0;
	int mp=p;
	
	while(next_child[p]){
		if(!finish[p] ) {
			res=ct;
			mp=p;
			// if(mp && !val[mp] && !next_child[mp] ) mark(mp);
			return res;
		}
		ct++;
		p=next_child[p];
	}
	if(!res) res=ct;
	// if(mp && !val[mp] && !next_child[mp] ) mark(mp);
	return res;
}

int get_son(int p,int i)
{
	assert(i<=val[p]);
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

void set_son(int c,int f)
{
	// vis[f]++;
	assert(c<M);
	fa[c]=f;
	if(first_child[f] == 0 ){
		first_child[f]=c;
	}
	else{
		int t=first_child[f];
		while(next_child[t]) t=next_child[t];
		next_child[t]=c;
	}
	// tot++;
}
FILE *fin=NULL;
FILE *fout=NULL;
FILE *flog=NULL;

inline void Read(int &a)
{
	fscanf(fin,"%d",&a);
}
inline void Out(int a)
{
	fprintf(fout," %3d",a);
}
inline void Line()
{
	fprintf(fout,"\n");
}
void load()
{
	const int m=M-1;
	Read(tot);
	for(int i=1;i<=m;i++) Read(vis[i]);
	for(int i=1;i<=m;i++) Read(val[i]);
	for(int i=1;i<=m;i++) Read(first_child[i]);
	for(int i=1;i<=m;i++) Read(next_child[i]);
	for(int i=1;i<=m;i++) Read(fa[i]);
	for(int i=1;i<=m;i++) Read(finish[i]);
}

void save()
{
	Out(tot); Line();
	for(int i=1;i<M;i++) Out(vis[i]); Line();
	for(int i=1;i<M;i++) Out(val[i]); Line();
	for(int i=1;i<M;i++) Out(first_child[i]); Line();
	for(int i=1;i<M;i++) Out(next_child[i]); Line();
	for(int i=1;i<M;i++) Out(fa[i]); Line();
	for(int i=1;i<M;i++) Out(finish[i]); Line();
}

void init()
{
	fill(first_child,first_child+M,0);
	fill(next_child,next_child+M,0);
	fill(val,val+M,0);
	fill(val,vis+M,0);
	fin=fopen("datas.txt","r");
	flog=fopen("paths.txt","a");
	//load
	if(fin!=NULL)
		load();
	else
		tot=1;
}

void release()
{
	fclose(fin);
	
	fout=fopen("datas.txt","w");
	//save
	save();
	fclose(fout);
	fprintf(flog,"\n");
	fclose(flog);
}



int main(int argc, char **argv)
{
	init();
	srand(time(0));
	int q,a,ne,cur=1;
	while(cin>>q && q){
		if(val[cur]!=q && val[cur]){
			cerr<<"unexpected"<<endl;
			abort();
			/* exit(2); */ //unexpected.
		}
		else if(val[cur]) {

			a=select_son(cur);
			ne=get_son(cur,a);
			vis[ne]++;
			cout<<a<<endl;
			fprintf(flog," %3d",a);
			
				cerr<<"cur tot "<<cur<<setw(6)<<tot<<" q  a "<<val[cur]<<setw(6)<<a<<endl;
			cur =ne;
			continue;
		}
		
		
		for(int i=1;i<=q;i++)
			set_son(++tot,cur);
		val[cur]=q;
		
		a=select_son(cur);
		ne=get_son(cur,a);
		vis[ne]++;
		cout<<a<<endl;
		
		fprintf(flog," %3d",a);

			cerr<<"cur next tot "<<cur<<setw(6)<<ne<<setw(6)<<tot<<" q  a "<<val[cur]<<setw(6)<<a<<endl;
		
		cur = ne;
		if(cur ==0) {cerr<<"err";abort();/* exit(2); */}

	}
	mark(ne);
	release();
	
	// int ct;
	// srand(time(0));
	// while(cin>>ct){
		// if(ct>1)
			// cout<<(rand()%ct+1)<<endl;
		// else
			// cout<<1<<endl;
	// }
	return 0;
}
