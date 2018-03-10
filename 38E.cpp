#include <bits/stdc++.h>
#define INF 1e18
#define int long long
using namespace std;
struct marble {
	int x,c;
};
marble a[3001];
bool cmp(const marble& a,const marble& b) {
	return a.x<b.x;
}
int n,dp[3001][3001];
signed main() {
	//freopen("38E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for (int i=0;i<n;i++) cin>>a[i].x>>a[i].c;
	sort(a,a+n,cmp);
	/*
	DP[i][j]: The minimum money we will have spent at the ith marble, with the first stopping position
	as a[j].x
	- If we stick the ith marble, then DP[i][j] = min(DP[i - 1][k]) + a[i].c
	- If we don't stick the ith marble, DP[i][j] = DP[i - 1][j].
	*/
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) dp[i][j]=INF;
	}
	dp[0][0]=a[0].c;
	for (int i=1;i<n;i++) {
		int minval=INF;
		for (int j=0;j<i;j++) {
			dp[i][j]=min(dp[i][j],dp[i-1][j]+(a[i].x-a[j].x));
			minval=min(minval,dp[i-1][j]);
		}
		dp[i][i]=minval+a[i].c;
	}
	int ans=INF;
	for (int j=0;j<n;j++) ans=min(ans,dp[n-1][j]);
	cout<<ans;
}
