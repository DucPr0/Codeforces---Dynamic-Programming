#include <bits/stdc++.h>
#define for(i,l,r) for (int i=l;i<r;i++)
#define int long long
#define INF 1e18
using namespace std;
int dp[2005][2005],n,t[2005],c[2005];
signed main() {
	//freopen("19B.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for (i,0,n) { cin>>t[i]>>c[i]; t[i]++; }
	//Call DP[i][j]: The minimum cost required to obtain a total time of j, with us at the ith item
	//We see in order to add the current item into our total time, we just have to t[i]++
	//Final answer: DP[n][n]
	for (i,0,n+1) for (j,0,n+1) dp[i][j]=INF;
	dp[0][0]=0;
	for (i,0,n) for (j,0,n+1) if (dp[i][j]<INF) {
		dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
		dp[i+1][min(j+t[i],n)]=min(dp[i+1][min(j+t[i],n)],dp[i][j]+c[i]);
	}
	cout<<dp[n][n];
}
