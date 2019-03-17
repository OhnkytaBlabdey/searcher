#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>


using namespace std;
const int maxn=0x800;

namespace storage{
	int pa[maxn];// parent node
	int son[maxn];// first son node
	int val[maxn];// reserved
	int able[maxn];// how many sons are available
	int _count[maxn];// p 's sons's count
	int count;// always point to null
	
	int _availables[maxn];// buffer for result
	int _availables_count;// count + 1

	inline void init()
	{
		memset(pa,-1,maxn*sizeof(int));
		memset(son,0,maxn*sizeof(int));
		memset(val,0,maxn*sizeof(int));
		memset(able,-1,maxn*sizeof(int));
		memset(_count,0,maxn*sizeof(int));
		// able[0]=1;
	}
	
	inline void add(int p, int ct)
	{
		son[p]=count;
		able[p]=ct;
		_count[p]=ct;
		for(int i=0;i<ct;++i) {
			pa[count]=p;
			able[count++]=-1;
		}
	}
	
	inline void disable(int x)
	{
		able[x]=0;
		int p=pa[x];
		if(p==0) return;
		if(able[x]==1 || able[x]==0){
			able[x]=0;
			disable(p);
			return;
		}
		able[x]--;
	}
	
	// return k th son's index
	inline int getson(int p,int k)
	{
		return son[p]+k-1;
	}
	
	inline int getfather(int x)
	{
		return pa[x];
	}
	
	inline int son_count(int p)
	{
		return _count[p];
	}
	
	inline int get_available_sons(int p)
	{
		int s;
		_availables_count=0;
		for(int i=0;i<_count[p];++i){
			s=son[p]+i;
			if(able[s]) _availables[_availables_count++]=s;
		}
		// cerr <<"available count"<<" "<<_availables_count<<endl;
		// for(int i=0;i<_availables_count;++i) cerr<<" "<<_availables[i];
		// cerr<<endl;
		return _availables_count;
	}
	
	/// return an index (from 1 on)
	int select_son(int p)
	{
		if(!get_available_sons(p)){
			cerr<<"Error : no available node to select. "<<endl;
			abort();
		}
		// ++val[p];
		int res=_availables[0];
		int s;
		for(int i=0;i<_availables_count;++i){
			s=_availables[i];
			if(val[s]>val[res]) res=s;
		}
		return res-son[p]+1;
	}
	
};
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
	const int m=maxn-1;
	Read(storage::count);
	for(int i=0;i<=m;i++) Read(storage::pa[i]);
	for(int i=0;i<=m;i++) Read(storage::son[i]);
	for(int i=0;i<=m;i++) Read(storage::val[i]);
	for(int i=0;i<=m;i++) Read(storage::able[i]);
	for(int i=0;i<=m;i++) Read(storage::_count[i]);
}
void save()
{
	const int m=maxn-1;
	Out(storage::count); Line();
	for(int i=0;i<=m;i++) Out(storage::pa[i]); Line();
	for(int i=0;i<=m;i++) Out(storage::son[i]); Line();
	for(int i=0;i<=m;i++) Out(storage::val[i]); Line();
	for(int i=0;i<=m;i++) Out(storage::able[i]); Line();
	for(int i=0;i<=m;i++) Out(storage::_count[i]); Line();
}

void init()
{
	storage::init();
	fin=fopen("datas.txt","r");
	flog=fopen("paths.txt","a");
	//load
	if(fin!=NULL)
		load();
	else
		storage::count=1;// root node
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

int main()
{
	init();
	srand(0);
	int now=0;
	int ct,chs;
	while(cin>>ct && ct){
		if( storage::son_count(now)==0 ){
			storage::add(now, ct);
			// cerr <<"add "<<" "<<now<<" "<<ct<<endl;
		}else{
			if( storage::son_count(now)!=ct ){
				cerr<<"Error : node count not fit to former data. "<<endl;
				release();
				abort();
			}
		}
		++storage::val[now];
		chs=storage::select_son(now);
		cout<<chs<<endl;
		fprintf(flog," %3d",chs);
		now=storage::getson(now, chs);
	}
	++storage::val[now];
	storage::disable(now);
	release();
	return 0;
}