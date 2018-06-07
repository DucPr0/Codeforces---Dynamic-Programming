#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[2][10001];
signed main() {
	//freopen("922E.inp","r",stdin);
	//freopen("922E.out","w",stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n,w,b,x,c[1001],cost[1001];
	cin>>n>>w>>b>>x;
	for (int i=0;i<n;i++) cin>>c[i];
	for (int i=0;i<n;i++) cin>>cost[i];
	/*
	DP[i][j]: j means the total number of birds summoned, and currently at tree[i]. Also, it means
	the maximum power we have gotten left
	So our new capacity is W + j * B.
	*/
	memset(dp,-1,sizeof(dp));
	dp[0][0]=w;
	for (int it=0;it<n;it++) {
		int i;
		if (it%2==0) i=1;
		else i=0;
		//For each previous bird states, find the answer for our current one.
		/*
		If the previous state is DP[i-1][j], then we will take k birds in tree i-1 and recharge.
		*/
		for (int j=0;j<=10000;j++) {
			if (dp[it%2][j]==-1) continue;
			//cout<<"dp["<<it<<"]["<<j<<"]="<<dp[it%2][j]<<"\n";
			for (int k=0;k<=c[it];k++) {
				if (dp[it%2][j]-cost[it]*k<0) break;
				dp[i][j+k]=max(dp[i][j+k],min(dp[it%2][j]-k*cost[it]+x,w+(k+j)*b));
			}
		}
	}
	int pos=n%2,ans=0;
	for (int i=0;i<=10000;i++) {
	//	if (dp[pos][i]!=-1) cout<<"dp["<<i<<"]="<<dp[pos][i]<<"\n";
		if (dp[pos][i]!=-1) ans=max(ans,i);
	}
	cout<<ans;
}

