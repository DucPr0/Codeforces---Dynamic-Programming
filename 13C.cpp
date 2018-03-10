#include <bits/stdc++.h>
#define int long long
#define INF 1e18
using namespace std;
int n,a[5001],b[5001],dp[2][5001],mini[2][5001];
signed main() {
	//freopen("13C.inp","r",stdin);
	cin>>n;
	for (int i=0;i<n;i++) {
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b,b+n);
	/*
	To solve this problem, we have to prove the optimal subsequence is one that all elements of it
	are contained in the original sequence.
	Proof: We will have a b[] array as after all of the operations. Let's say n - 1 elements are contained
	in the original sequence, while there's a value that isn't. Let's say it's an indice i.
	Looking at indices i - 1 and i + 1. There are 3 cases that happen:
	+ The original a[] value of it lies between the b[i - 1] and b[i + 1] values. So, the most optimal
	choice is to leave it alone.
	+ The original a[] value is smaller than b[i - 1]. So, we only increase it to b[i - 1], which exist
	in the original sequence
	+ The original a[] value is bigger than b[i + 1]. So, we only decrease it to b[i + 1], which exist
	in the original sequence.
	So we have proven that the new sequence will have elements that are all contained in the old one.
	Call DP[i][j]: The minimum changes need to end at the ith element, with b[j] as the finale.
	*/
	for (int i=0;i<n;i++) {
		dp[0][i]=abs(a[0]-b[i]);
		if (i==0) mini[0][i]=dp[0][i];
		else mini[0][i]=min(mini[0][i-1],dp[0][i]);
	}
	for (int it=1;it<n;it++) {
		int i;
		if (it%2) i=0;
		else i=1;
		for (int j=0;j<n;j++) {
			//We have to get the minimum k value in O(1), by using a min array
			//mini[i][j] stores the minimum value on row i, up to column j.
			//for (int k=0;k<=j;k++) {
			//	dp[it%2][j]=min(dp[it%2][j],dp[i][k]+abs(a[it]-b[j]));
			//}
			dp[it%2][j]=mini[i][j]+abs(a[it]-b[j]);
			if (j==0) mini[it%2][j]=dp[it%2][j];
			else mini[it%2][j]=min(mini[it%2][j-1],dp[it%2][j]);
		}
	}
	int pos,ans=INF;
	pos=(n-1)%2;
	for (int i=0;i<n;i++) {
		ans=min(ans,dp[pos][i]);
	}
	cout<<ans;
}
