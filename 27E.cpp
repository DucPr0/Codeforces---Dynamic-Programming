#include <bits/stdc++.h>
#define int double
#define INF 1e18+1
using namespace std;
int dp[12][1001][2];
vector<vector<int>> divisors;
int calc_pow(int a,signed n) {
	if (n==1) return a;
	if (n%2==0) {
		int temp=calc_pow(a,n/2);
		return temp*temp;
	} else {
		int temp=calc_pow(a,(n-1)/2);
		return temp*temp*a;
	}
}
signed main() {
	//freopen("27E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cout.precision(19);
	signed n;
	cin>>n;
	/*
	If our number can be factored into numbers: p1 ^ a1 * p2 ^ a2 * ... * pn ^ an, then the number of
	divisors are: (a1 + 1) * (a2 + 1) * ... * (an + 1)
	As 1000 = 2 ^ 3 * 5 ^ 3, we see that there are at most 6 different a values. So we only take the
	first 6 prime numbers: 2, 3, 5, 7, 11 and 13.
	Now our job is to divide these numbers in order to create a smallest number.
	DP[i][j]: We are at the ith prime number, with j left to use. It means the minimal number we have
	created.
	From a state of DP[i][j], there are a 2 choices we can make:
	- Move onto the prime next number, which means DP[i + 1][j]
	- Give our current prime number a certain value, which means run (k + 1) as a divisor of j
	So DP[i][j / (k + 1)] = DP[i][j] * a[i] ^ k.
	Only transferred items are qualified to run a k value. So, we will save another state to tell us
	if this current item is a transferred one or not.
	*/
	divisors.resize(n+1);
	for (int i=2;i<=n;i++) {
		for (int j=1;j<=n/i;j++) {
			divisors[i*j].push_back(i);
		}
	}
	int a[]={2,3,5,7,11,13,17,19,23,29,31};
	for (signed i=0;i<10;i++) for (signed j=n;j>=1;j--) {
		dp[i][j][0]=dp[i][j][1]=INF;
	}
	dp[0][n][0]=1;
	for (signed i=0;i<10;i++) {
		for (signed j=n;j>1;j--) {
			for (signed stat=0;stat<2;stat++) {
				if (dp[i][j][stat]!=INF) {
					dp[i+1][j][0]=min(dp[i+1][j][0],dp[i][j][stat]);
					if (!stat) {
						//It's transferred
						for (int k=0;k<divisors[j].size();k++) {
							signed divi=divisors[j][k];
							divi--;
							dp[i][j/(divi+1)][1]=min(dp[i][j/(divi+1)][1],dp[i][j][0]*calc_pow(a[i],divi));
						}
					}
				}
			}
		}
	}
	int ans=INF;
	for (signed i=0;i<10;i++) {
		ans=min(ans,dp[i][1][0]);
		ans=min(ans,dp[i][1][1]);
	}
	cout<<ans;
}
