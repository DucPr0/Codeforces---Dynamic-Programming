#include <bits/stdc++.h>
#define pb push_back
#define INF 1061109567
#define bw(i,l,r) for (int i=r-1;i>=l;i--)
#define fw(i,l,r) for (int i=l;i<r;i++)
using namespace std;
int n,r,dep[200001],dp[200001][2]; bool vis[200001],good[200001];
vector<vector<int>> adjlist,child;
void dfs(int u) {
	vis[u]=true;
	fw (i,0,adjlist[u].size()) if (!vis[adjlist[u][i]]) {
		child[u].pb(adjlist[u][i]);
		good[adjlist[u][i]]=good[u];
		if (adjlist[u].size()>2) good[adjlist[u][i]]=false; //Starting from here we can't merge
		//them with dep
		dep[adjlist[u][i]]=dep[u]+1;
		dfs(adjlist[u][i]);
	}
}
void solve(int u) {
	if (child[u].size()==0) {
		dp[u][0]=dp[u][1]=0;
		return;
	}
	int def=-1,bad=0,ind;
	fw (i,0,child[u].size()) {
		int v=child[u][i]; solve(v); int tmp=dp[v][0];
		if (dp[v][0]==-1&&dp[v][1]==-1) {dp[u][0]=dp[u][1]=-1; return;} 
		if (tmp==-1) {bad++; ind=v;}
		else {
			if (tmp+1!=dep[u]&&def==-1) def=tmp;
			if (tmp+1!=dep[u]&&def!=-1&&tmp!=def) {dp[u][0]=dp[u][1]=-1; return;}
			//This present us with 2 different def values, which declares invalid on both states
		} 
	}
	if (bad>1) dp[u][1]=-1;
	else if (bad==0) dp[u][1]=def+1;
	else {
		if (def!=-1) dp[u][1]=-1;
		else dp[u][1]=dp[ind][1]+1;
	}
	if (good[u]) dp[u][0]=dp[u][1];
	else {
		bad=0,def=-1;
		fw (i,0,child[u].size()) {
			int v=child[u][i],tmp=dp[v][0];
			if (tmp==-1) bad=1;
			else {
				if (def==-1) def=tmp;
				if (tmp!=def) bad=1;
			}
		}
		if (bad>0) dp[u][0]=-1;
		else dp[u][0]=def+1;
	}
}
signed main() {
	//freopen("765E.inp","r",stdin);
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; adjlist.resize(n); child.resize(n);
	fw (i,1,n) {int u,v; cin>>u>>v; u--; v--; adjlist[u].pb(v); adjlist[v].pb(u);}
	/*
	DP[i][0]: If we can create a path from the subtree of i with all the normal conditions
	DP[i][1]: If we can create a path from the subtree of i, the path from it leading upwards is
	a straight line (we can merge paths with dep)
	How to calculate the states:
	- DP[i][1]: Check through all the children. This is splitted into 3 cases:
	+) >= 2 of them has DP[v][0] = -1. Declare the state as invalid (-1)
	+) None of them has DP[v][0] = -1. Return def + 1.
	+) Exactly 1 of them have DP[v][0] = -1 and DP[v][1] valid. If def exist, then the state
	is considered invalid. Else, DP[i][1] = DP[ind][1] + 1.
	- DP[i][0]: If good[i] is true, then this state is considered the same as DP[i][1]. Else, pass
	through all children again, and it's splitted in 2 cases:
	+) At least 1 of the state has a DP[v][0] = -1. The state is immediately invalid.
	+) None of the state have a DP[v][0] = -1. Answer is def + 1.
	*/
	fw (i,0,n) if (adjlist[i].size()==1) {r=i; break;}
	memset(vis,false,sizeof(vis)); dep[r]=0; good[r]=true; dfs(r);
	//cout<<"r="<<r+1<<"\n";
	solve(r); int ans=dp[r][0]; if (ans>0) while (!(ans&1)) ans>>=1;
	//fw (i,0,n) fw (j,0,2) cout<<"Dp["<<i+1<<"]["<<j<<"]="<<dp[i][j]<<"\n";
	cout<<ans;
}
