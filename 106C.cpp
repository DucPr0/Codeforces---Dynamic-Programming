#include <bits/stdc++.h>
using namespace std;
int dp[11][101][1001];
int maxi[11][1001];
int main() {
	//freopen("106C.inp","r",stdin);
	int n,m,c[11],d[11],a[11],b[11];
	cin>>n>>m>>c[0]>>d[0];
	for (int i=1;i<=m;i++) cin>>a[i]>>b[i]>>c[i]>>d[i];	
	memset(dp,0,sizeof(dp));
	for (int j=0;c[0]*j<=n;j++) {
		dp[0][0][n-c[0]*j]=d[0]*j;
		maxi[0][n-c[0]*j]=max(maxi[0][n-c[0]*j],dp[0][0][n-c[0]*j]);
	}
	/*
	dp[i][j][k]: We are at the ith stuffing, with j grams left for it only and k grams of dough left.
	maxi[i][k] stores the maximum J value at the ith stuffing, with k grams of dough left
	Algorithm:
	- For each state, we can choose to do make more of the current stuffing, or move onto the next one.
	- So we have gotten dp[i][j][k] as a state:
	+ It's resulted from moving on. So dp[i][j][k] = maxi[i-1][k] with J running from
	0 to a[i-1].
	+ It's resulted from adding 1 more stuffing, so dp[i][j][k] = max(dp[i][j][k], dp[i][j+b[i]][k+c[i]]
																					+ d[i])
	*/
	for (int i=1;i<=m;i++) {
		for (int k=n;k>=0;k--) {
			for (int j=a[i];j>=0;j--) {
				dp[i][j][k]=maxi[i-1][k];
				if (j+b[i]<=a[i]&&k+c[i]<=n) dp[i][j][k]=max(dp[i][j][k],dp[i][j+b[i]][k+c[i]]+d[i]);
				maxi[i][k]=max(maxi[i][k],dp[i][j][k]);
				//cout<<"dp["<<i<<"]["<<j<<"]["<<k<<"]="<<dp[i][j][k]<<"\n";
			}
		}
	}
	int ans=0;
	for (int k=0;k<=n;k++) {
		for (int j=0;j<=a[m];j++) ans=max(ans,dp[m][j][k]);
	}
	cout<<ans;
}
