#include <bits/stdc++.h>
#define INF 1000000007
#define pb push_back
#define bw(i,r,l) for (int i=r-1;i>=l;i--)
#define fw(i,l,r) for (int i=l;i<r;i++)
using namespace std;
struct edge {int u,v,x;};
int n,m,dp[100001],posi[100001];
typedef pair<int,int> ii;
edge e[100001]; vector<int> a[100001],temp[100001];
struct st {
	vector<int> t;
	//This segment tree will be intialized for sum queries. Lazy operations will be addition ones.
	void init(int sz) {t.resize(sz); fw (i,0,t.size()) t[i]=0;}
	int get(int l,int r,int s,int e,int node) {
		if (l>r||l>e||r<s) return 0;
		if (s<=l&&r<=e) return t[node];
		int mid=(l+r)/2;
		return max(get(l,mid,s,e,node*2),get(mid+1,r,s,e,node*2+1));
	}
	void upd(int l,int r,int pos,int node,int val) {
		if (l==r) {t[node]=val; return;}
		int mid=(l+r)/2;
		if (pos<=mid) upd(l,mid,pos,node*2,val);
		else upd(mid+1,r,pos,node*2+1,val);
		t[node]=max(t[node*2],t[node*2+1]);
	}
} t[100001];
bool cmp(int &a,int &b) {return e[a].x<e[b].x;}
signed main() {
	//freopen("960.inp","r",stdin);
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	fw (i,0,m) {cin>>e[i].u>>e[i].v>>e[i].x; e[i].u--; e[i].v--;}
	fw (i,0,m) {
		a[e[i].v].pb(e[i].x);
		temp[e[i].v].pb(i);
	}
	fw (i,0,n) {
		sort(a[i].begin(),a[i].end());
		sort(temp[i].begin(),temp[i].end(),cmp);
	}
	fw (i,0,n) {
		//int sz=t[i].getsz(0,a[i].size()-1,1);
		t[i].init(4*a[i].size()+5);
		fw (j,0,a[i].size()) posi[temp[i][j]]=j;
	}
	fw (i,0,m) {
		int tmp=lower_bound(a[e[i].u].begin(),a[e[i].u].end(),e[i].x)-a[e[i].u].begin();
		tmp--;
		tmp=t[e[i].u].get(0,a[e[i].u].size()-1,0,tmp,1);
		dp[i]=tmp+1;
		t[e[i].v].upd(0,a[e[i].v].size()-1,posi[i],1,dp[i]);
	}
	int ans=0;
	fw (i,0,m) ans=max(ans,dp[i]);
	cout<<ans;
}
