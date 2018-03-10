#include <bits/stdc++.h>
#define int long long
#define INF 1e9
using namespace std;
int a[1501][1501],dp[1501][1501],sum[1501][1501],r,c;
int maxi[1501][1501],maxi2[1501][1501];
/*
dp[i][j]: The maximum sum we can get if on row i we chose j columns.
maxi[i][j]: The maximum DP member from 0 to j on row i.
maxi2[i][j]: The maximum DP member from j to c - 1 on row i.
*/
signed main() {
	//freopen("46E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>r>>c;
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			cin>>a[i][j];
			if (j==0) sum[i][j]=a[i][j];
			else sum[i][j]=sum[i][j-1]+a[i][j];
		}
	}
	for (int i=0;i<=r;i++) {
		for (int j=0;j<=c;j++) {
			dp[i][j]=-INF;
			maxi[i][j]=-INF;
			maxi2[i][j]=-INF;
		}
	}
	for (int i=0;i<c;i++) {
		dp[0][i]=sum[0][i];
		if (i==0) maxi[0][i]=dp[0][i];
		else maxi[0][i]=max(maxi[0][i-1],dp[0][i]);
	}
	for (int i=c-1;i>=0;i--) {
		if (i==c-1) maxi2[0][i]=dp[0][i];
		else maxi2[0][i]=max(maxi2[0][i+1],dp[0][i]);
	}
	for (int i=1;i<r;i++) {
		for (int j=0;j<c;j++) {
			//If i is odd then the last row have a smaller c value, otherwise. Since we are calculating
			//from 0 that rule is flipped.
			//As we look there, basically, we are looking for the maximum dp[i-1] value. We can do this
			//in O(1), by creating a table.
			if (i%2==0) {
				/*for (int run=0;run<j;run++) {
					dp[i][j]=max(dp[i][j],dp[i-1][run]+sum[i][j]);
				}*/
				if (j>0) dp[i][j]=maxi[i-1][j-1]+sum[i][j];
				else dp[i][j]=-INF;
			} else {
				/*for (int run=j+1;run<c;run++) {
					dp[i][j]=max(dp[i][j],dp[i-1][run]+sum[i][j]);
				}*/
				dp[i][j]=maxi2[i-1][j+1]+sum[i][j];
			}
			if (j==0) maxi[i][j]=dp[i][j];
			else maxi[i][j]=max(maxi[i][j-1],dp[i][j]);
		}
		for (int j=c-1;j>=0;j--) {
			if (j==c-1) maxi2[i][j]=dp[i][j];
			else maxi2[i][j]=max(maxi2[i][j+1],dp[i][j]);
		}
	}
	int ans=-INF;
	for (int i=0;i<c;i++) {
		ans=max(ans,dp[r-1][i]);
	}
	cout<<ans;
}

