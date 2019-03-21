#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define lll
using namespace std;
const int maxn=0x800;

namespace storage{
	int pa[maxn];// parent node
	int son[maxn];// first son node
	int val[maxn];// reserved
	int able[maxn];// how many sons are available
	int _count[maxn];// p 's sons's count
	int count;// always point to null
	
	int roulette[256];
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
			val[count]=1;
			able[count++]=-1;
		}
		val[p]+=ct;
		int x=pa[p];
		do{
			val[x]+=ct;
			x=pa[x];
		}while(x);
	}
	
	inline void disable(int x)
	{
		able[x]=0;
		int p=pa[x];
		if(p==0) return;
		able[p]--;
		if(able[p]==0) disable(p);
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
	#ifdef lll
		{
		cerr <<"available count"<<" "<<_availables_count<<endl;
		for(int i=0;i<_availables_count;++i) cerr<<" "<<_availables[i];
		cerr<<endl;
		}
	#endif
		return _availables_count;
	}
	
	/// return an index (from 1 on)
	int select_son(int p)
	{
		if(!get_available_sons(p)){
			cerr<<"Error : no available node to select. "<<endl;
			abort();
		}
		int res;
		
		/* /// random select a son
		res=_availables[(rand()+_availables_count)%_availables_count]; */
		/* /// minimize val[s]
		res=_availables[0];
		int s;
		for(int i=0;i<_availables_count;++i){
			s=_availables[i];
			if(val[s]>val[res]) res=s;
		} */
		
		/// select son equally by their decendents
		if(_availables_count>256){
			cerr<<"Error : too many choices to select."<<endl;
			abort();
		}
		
		cerr<<"roulette ";
		for(int i=0;i<_availables_count;++i){
			if(!i) roulette[i]=val[ _availables[i] ];
			else {
				roulette[i]=roulette[i-1] + val[ _availables[i] ];
			}
			cerr<<" "<<roulette[i];
		}
		cerr<<endl;
		int ct=roulette[_availables_count-1];
		int choice= rand()%ct;
		cerr<<"ct "<<ct<<" choice "<<choice<<endl;
		for(int i=0;i<_availables_count;++i){
			if(roulette[i]>=choice){
				res=_availables[i];
				break;
			}
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
	srand(time(0));
	int now=0;
	int ct,chs;
	while(cin>>ct && ct){
		if( storage::son_count(now)==0 ){
			storage::add(now, ct);
		#ifdef lll
			cerr <<"add "<<" "<<now<<" "<<ct<<endl;
		#endif
		}else{
			if( storage::son_count(now)!=ct ){
				cerr<<"Error : node count not fit to former data. "<<endl;
				release();
				abort();
			}
		}
		/* ++storage::val[now]; */
		chs=storage::select_son(now);
		cout<<chs<<endl;
	#ifdef lll
		cerr <<now<<", "<<chs<<endl;
	#endif
		fprintf(flog," %3d",chs);
		now=storage::getson(now, chs);
	}
	/* ++storage::val[now]; */
	storage::disable(now);
	release();
	return 0;
}