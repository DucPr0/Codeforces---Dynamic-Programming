#include <bits/stdc++.h>
using namespace std;
int k,a,b;
bool dp[201][201];
int recur[201][201];
string s;
//dp[i][j]: Every letter up to the (i-1)th one have been distributed and j lines have been created.
void recursion(int i,int j) {
	if (j==0) return;
	int words=recur[i][j];
	recursion(i-words,j-1);
	for (int run=i-words+1;run<=i;run++) {
		cout<<s[run-1];
	}
	cout<<"\n";
}
int main() {
	//freopen("44E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>k>>a>>b;
	cin>>s;
	memset(dp,false,sizeof(dp));
	dp[0][0]=true;
	for (int i=0;i<=s.length();i++) {
		for (int j=0;j<=k;j++) {
			if (dp[i][j]) {
				for (int run=a;run<=b;run++) {
					if (i+run<=s.length()&&j+1<=k) {
						dp[i+run][j+1]=true;
						recur[i+run][j+1]=run;
					}
				}
				//cout<<"dp["<<i<<"]["<<j<<"]="<<dp[i][j]<<"\n";
			}
		}
	}
	if (!dp[s.length()][k]) cout<<"No solution";
	else {
		recursion(s.length(),k);
	}
}

