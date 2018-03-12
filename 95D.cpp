#include <bits/stdc++.h>
#define INF 1e9
#define MOD 1000000007
#define int long long
using namespace std;
int q,k;
int dp[1001][1001][2];
/*
DP[i][j][0 / 1]: The number of lucky numbers with the distance from the last 4 or 7 as j, we are at the ith digit
Use a top - down algorithm again, and only save unrestricted values in order to save time. 0 means it
is not beautiful yet, 1 means that it is already beautiful.
If it's not beatiful, then the next state is forced to be beautiful
Else, the next state can be any one of the two.
*/
string endy;
int calc_ans(int i,bool strict,int j,bool beauty) {
	//cout<<"i="<<i<<" strict="<<strict<<" j="<<j<<" beauty="<<beauty<<"\n";
	if (i==0) return beauty;
	if (!strict&&dp[i][j][beauty]!=-1) return dp[i][j][beauty];
	int ans=0,n=(strict)?endy[i-1]-'0':9;
	for (int run=0;run<=n;run++) {
		if (run!=4&&run!=7) {
			int nextj=(j==-1)?-1:j+1;
			ans+=calc_ans(i-1,strict&&run==n,nextj,beauty);
			ans%=MOD;
		}
		else {
			if (j>=0&&j<=k-1) {
				ans+=calc_ans(i-1,strict&&run==n,0,1);
				ans%=MOD;
			}
			else {
				ans+=calc_ans(i-1,strict&&run==n,0,beauty);
				ans%=MOD;
			}
		}
	}
	if (!strict) dp[i][j][beauty]=ans;
	return ans;
}
int get_ans(string lim) {
	reverse(lim.begin(),lim.end());
	endy=lim;
	return calc_ans(lim.length(),1,-1,0);
}
signed main() {
	//freopen("95D.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	memset(dp,-1,sizeof(dp));
	cin>>q>>k;
	while (q--) {
		string l,r;
		cin>>l>>r;
		//Remember to reverse the strings.
		//We find the answer for r and l, then check if l is also a number satisfying our constraints.
		//Check if l is a lucky number
		bool lucky=false;
		int last=-1;
		for (int i=0;i<l.length();i++) {
			if (l[i]=='4'||l[i]=='7') {
				if (last>=0&&last<=k-1) {
					lucky=true;
					break;
				} else last=0;
			} else {
				if (last!=-1) last++;
			}
		}
		cout<<(get_ans(r)-get_ans(l)+lucky+MOD)%MOD<<"\n";
	}
}
