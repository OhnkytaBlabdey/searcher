#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>


using namespace std;
const int maxn=0x80000;

namespace storage{
	int pa[maxn];
	int son[maxn];
	int val[maxn];
	int able[maxn];
	int count;// always point to null

	inline void init()
	{
		memset(pa,0,maxn*sizeof(int));
		memset(son,0,maxn*sizeof(int));
		memset(val,0,maxn*sizeof(int));
		memset(able,0,maxn*sizeof(int));
		// able[0]=1;
	}
	
	inline void add(int p, int ct)
	{
		son[p]=count;
		able[p]=ct;
		for(int i=0;i<ct;++i) {
			pa[count]=p;
			able[count++]=0;
		}
	}
	
	inline void disable(int x)
	{
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
	
};

int main()
{
	
	return 0;
}