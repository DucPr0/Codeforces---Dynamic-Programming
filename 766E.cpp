#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define bw(i,r,l) for (int i=r-1;i>=l;i--)
#define fw(i,l,r) for (int i=l;i<r;i++)
using namespace std;
int n,a[100001],dp[100001][21][2],ans[100001]; bool vis[100001]; vector<vector<int>> adjlist,child;
void dfs(int u) {
	vis[u]=true;
	fw (i,0,adjlist[u].size()) if (!vis[adjlist[u][i]]) {
		child[u].pb(adjlist[u][i]);
		dfs(adjlist[u][i]);
	}
}
void solve(int u) {
	ans[u]=0;
	fw (i,0,21) {
		if (a[u]&(1<<i)) {dp[u][i][1]=1; ans[u]+=(1<<i);}
		else dp[u][i][0]=1;
	}
	if (child[u].size()==0) return;
	//DP states save the amount of paths of such bits that ENDS at u
	fw (i,0,child[u].size()) {
		int v=child[u][i]; solve(v);
		fw (j,0,21) {
			ans[u]+=(dp[u][j][0]*dp[v][j][1]+dp[u][j][1]*dp[v][j][0])*(1<<j);
			if (!(a[u]&(1<<j))) {
				dp[u][j][0]+=dp[v][j][0];
				dp[u][j][1]+=dp[v][j][1];
			} else {
				dp[u][j][1]+=dp[v][j][0];
				dp[u][j][0]+=dp[v][j][1];
			}
		}
	}
}
signed main() {
	//freopen("766E.inp","r",stdin);
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; fw (i,0,n) cin>>a[i]; adjlist.resize(n); child.resize(n);
	fw (i,1,n) {int u,v; cin>>u>>v; u--; v--; adjlist[u].pb(v); adjlist[v].pb(u);}
	/*
	DP[i][j][2]: The number of paths in the subtree of i, with the jth bit turned on or off
	Time complexity: O(N * log2(1e6))
	Original states: Check the available and unavailable bits on a[i], then we will update DP accordingly
	*/
	dfs(0);
	solve(0);
	//fw (i,0,n) fw (j,0,21) fw (k,1,2) if (dp[i][j][k]) cout<<"dp["<<i+1<<"]["<<j<<"]["<<k<<"]="<<dp[i][j][k]<<"\n";
	int res=0;
	fw (i,0,n) res+=ans[i];
	cout<<res;
}
