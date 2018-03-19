#include <bits/stdc++.h>
#define INF 1e9
#define for(i,l,r) for (int i=l;i<r;i++)
using namespace std;
typedef pair<int,int> ii;
char flag[501][501];
int dp[501][26][26];
ii recur[501][26][26];
int n,m;
void recursion(int i,int X,int Y) {
	if (!i) {
		for (j,0,m) if (j%2) cout<<char(Y+'a'); else cout<<char(X+'a');
		cout<<"\n";
		return;
	}
	recursion(i-1,recur[i][X][Y].first,recur[i][X][Y].second);
	for (j,0,m) if (j%2) cout<<char(Y+'a'); else cout<<char(X+'a');
	cout<<"\n";
}
signed main() {
	//freopen("18E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for (i,0,n) for (j,0,m) { cin>>flag[i][j]; flag[i][j]-='a'; }
	/*
	IDEA: We see that since a row can be most of 2 colors, let the colors used be X and Y, then the row
	is either XYXY... or YXYX...
	So call DP[i][X][Y]: The minimum steps to fill row i with XY...
	*/
	for (i,0,n) for (X,0,26) for (Y,0,26) if (X!=Y) {
		int steps=0;
		for (j,0,m) { int cmp=(j%2?Y:X); if (flag[i][j]!=cmp) steps++; }
		dp[i][X][Y]=INF;
		for (X1,0,26) for (Y1,0,26) if (X1!=Y1&&X1!=X&&Y1!=Y)
				if ((i?dp[i-1][X1][Y1]:0)+steps<dp[i][X][Y]) {
					dp[i][X][Y]=(i?dp[i-1][X1][Y1]:0)+steps;
					recur[i][X][Y]=ii(X1,Y1);
				}
		//cout<<"dp["<<i<<"]["<<char(X+'a')<<"]["<<char(Y+'a')<<"]="<<dp[i][X][Y]<<"\n";
	}
	int ans=INF;
	ii finale;
	for (X,0,26) for (Y,0,26) if (X!=Y) if (dp[n-1][X][Y]<ans) {
		ans=dp[n-1][X][Y];
		finale=ii(X,Y);
	}
	cout<<ans<<"\n";
	recursion(n-1,finale.first,finale.second);
}
