#include <bits/stdc++.h>
#define INF 1e9+7
#define fw(i,l,r) for (int i=l;i<r;i++)
#define bw(i,l,r) for (int i=r-1;i>=l;i--)
#define min(x,y) x=x<y?x:y
using namespace std;
int n,m=0,beg[200001][21],last[200001][21],dp[21][(1<<20)+1],ans=0,cost[200001];
/*
Naive DP idea: Call DP[i][j]: Minimum S value with B ending at the ith substring and C ending at the
jth substring. Having i > j, because DP[i][j] = DP[j][i]
- j != i - 1 => DP[i][j] = DP[i - 1][j] + len(i - 1, i) (*)
- j = i - 1 => DP[i][j] = min(DP[i - 1][k] + len(k, j)); (0 <= k < j) (**)
This idea is impossible since space and time complexity adds up to O(N ^ 2)
Now, call DP[j][mask]: The minimum cost with the last j characters of C being mask.
The algorithm works like this:
- Originally, we push everything to B. On each step, we will slowly replace the cost values with
more efficient ones (*). Starting state: Nothing is in C, so DP[0][0] = sum.
- For the current string a[i], we get all possible intersections and choose the most optimal out of them
(**).
- We see (**) only happens in the case of j = i - 1, and since C ends at j, the DP states with
i - 1 values are updated.
*/
int len(int X,int Y) {bw (i,-1,m) if (i==-1||last[X][i]==beg[Y][i]) return m-(i+1);}
signed main() {
	//freopen("83E.inp","r",stdin);
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n;
	fw (i,0,n) { char s[21]; cin>>s; if (!m) m=strlen(s); fw (j,0,m+1)
	{beg[i][j]=(j?(beg[i][j-1]<<1):0)+s[j]-'0'; last[i][j]=(1<<j)*(s[m-j-1]-'0')+(j?last[i][j-1]:0);}}
	fw (i,0,n) {cost[i]=i?len(i-1,i):m; ans+=cost[i];}
	memset(dp,1,sizeof(dp));
	dp[0][0]=ans;
	fw (i,1,n) {
		int mini=INF;
		fw (j,0,m+1) min(mini,dp[j][(j?beg[i][j-1]:0)]+m-j);
		mini-=cost[i]; min(ans,mini);
		fw (j,0,m+1) min(dp[j][(j?last[i-1][j-1]:0)],mini);
	}
	cout<<ans;
}
