#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[37],base[19];
int dp[37][19][19];
char recur[37][19][19];
void recursion(int i,int j,int k) {
	if (i==n) return;
	if (recur[i][j][k]=='H') {
		cout<<"H";
		recursion(i+1,j-1,k);
	} else {
		cout<<"M";
		recursion(i+1,j,k-1);
	}
}
signed main() {
	//freopen("31E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	string s;
	cin>>n>>s;
	n=2*n;
	for (int i=0;i<n;i++) a[i]=s[i]-'0';
	base[0]=1;
	for (int i=1;i<19;i++) base[i]=base[i-1]*10;
	/*
	DP[i][j][k]: We are at the ith digit, with j digits assigned to the first person and k digits assigned
	to the second person. It means the maximum sum at this state.
	Instead of running from 0 to n, we run backwards from n - 1 down to 0, because we can get the
	new sums without having to know the actual numbers themselves.
	Intial states: DP[n][0][0] = 0
	*/
	memset(dp,-1,sizeof(dp));
	dp[n][0][0]=0;
	for (int i=n;i>0;i--) {
		int insert=a[i-1];
		for (int j=0;j<=n/2;j++) {
			for (int k=0;k<=n/2;k++) {
				if (dp[i][j][k]!=-1) {
					//We will insert this digit into 1 of the 2 numbers
					if (dp[i][j][k]+insert*base[j]>dp[i-1][j+1][k]) {
						dp[i-1][j+1][k]=dp[i][j][k]+insert*base[j];
						recur[i-1][j+1][k]='H';
						//We gave it to the first person.
					}
					if (dp[i][j][k]+insert*base[k]>dp[i-1][j][k+1]) {
						dp[i-1][j][k+1]=dp[i][j][k]+insert*base[k];
						recur[i-1][j][k+1]='M';
					}
				}
			}
		}
	}
	recursion(0,n/2,n/2);
}
