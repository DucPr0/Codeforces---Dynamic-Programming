#include <bits/stdc++.h>
#define INF 1e9
#define int long long
#define for(i,l,r) for (int i=l;i<r;i++)
using namespace std;
int dp[101][101];
int taken[101][101];
/*
DP[i][j] stores the cost of row i up to column j.
We can find the minimum row in O(K ^ 2) for each, which takes a total of O(N * K ^ 2)
We also need a way to store used segments.
*/
signed main() {
	//freopen("10B.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n,k;
	cin>>n>>k;
	int mid=(k-1)/2;
	memset(dp,0,sizeof(dp));
	memset(taken,0,sizeof(taken));
	for (i,0,k) for (j,0,k) dp[i][j]=(j?dp[i][j-1]:0)+abs(i-mid)+abs(j-mid);
	while (n--) {
		int m,ans=INF,l,row;
		cin>>m;
		for (i,0,k) for (j,0,k-m+1) {
			if (taken[i][j+m-1]-(j?taken[i][j-1]:0)==0) {
				int cost=dp[i][j+m-1]-(j?dp[i][j-1]:0);
				if (cost<ans) {
					ans=cost;
					row=i;
					l=j;
				}
			}
		}
		if (ans!=INF) {
			int curr=0;
			for (i,l,k) {
				if (curr<m) curr++;
				taken[row][i]+=curr;
			}
			cout<<row+1<<" "<<l+1<<" "<<l+m<<"\n";
		}
		else cout<<"-1\n";
	}
}
