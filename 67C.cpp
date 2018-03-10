#include <bits/stdc++.h>
using namespace std;
#define INSERT 0
#define REMOVE 1
#define REPLACE 2
#define SWAP 3
int t[4];
int dp[4001][4001];
int lastA[4001][27],lastB[4001][27];
//lastA[i][j] stores the last position character j appears in A, and we are at position i.
string a,b;
int main() {
	//freopen("67C.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	for (int i=0;i<4;i++) cin>>t[i];
	cin>>a>>b;
	int n=a.length(),m=b.length();
	/*
	http://scarcitycomputing.blogspot.com/2013/04/damerau-levenshtein-edit-distance.html
	*/
	for (int i=0;i<n;i++) {
		for (int j='a';j<='z';j++) {
			if (!i) {
				lastA[i][j-'a']=-1;
				continue;
			}
			if (j!=a[i]) lastA[i][j-'a']=lastA[i-1][j-'a'];
		}
		lastA[i][a[i]-'a']=i;
	}
	/*for (int i=0;i<n;i++) {
		for (int j='a';j<='z';j++) if (lastA[i][j-'a']!=-1) cout<<"lastA["<<i<<"]["<<char(j)<<"]="<<lastA[i][j-'a']<<"\n";
	}*/
	for (int i=0;i<m;i++) {
		for (int j='a';j<='z';j++) {
			if (!i) {
				lastB[i][j-'a']=-1;
				continue;
			}
			if (j!=b[i]) lastB[i][j-'a']=lastB[i-1][j-'a'];
		}
		lastB[i][b[i]-'a']=i;
	}
	/*for (int i=0;i<m;i++) {
		for (int j='a';j<='z';j++) if (lastB[i][j-'a']!=-1) cout<<"lastB["<<i<<"]["<<char(j)<<"]="<<lastB[i][j-'a']<<"\n";
	}*/
 	for (int i=0;i<=n;i++) {
		for (int j=0;j<=m;j++) {
			if (i==0) {
				dp[i][j]=j*t[INSERT];
				continue;
			}
			if (j==0) {
				dp[i][j]=i*t[REMOVE];
				continue;
			}
			if (a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1];
			else {
				dp[i][j]=min(dp[i][j-1]+t[INSERT],min(dp[i-1][j-1]+t[REPLACE],dp[i-1][j]+t[REMOVE]));
				/*
				We now find the last in a that is equal to b[j - 1], and the last in b that is equal
				to a[i - 1]
				*/
				int la=lastA[i-1][b[j-1]-'a'],lb=lastB[j-1][a[i-1]-'a'];
				if (la!=-1&&lb!=-1) {
					//cout<<"i="<<i<<" j="<<j<<" a[i-1]="<<a[i-1]<<" b="<<b[j-1]<<"\n";
					//cout<<"la="<<la<<" lb="<<lb<<"\n";
					//cout<<"dp="<<dp[i][j]<<" swap="<<dp[la][lb]+(i-la-2)*t[REMOVE]+(j-lb-2)*t[INSERT]+t[SWAP]<<"\n";
					//cout<<"dp[la][lb]="<<dp[la][lb]<<"\n";
					dp[i][j]=min(dp[i][j],dp[la][lb]+(i-la-2)*t[REMOVE]+(j-lb-2)*t[INSERT]+t[SWAP]);
				}
			}
		}
	} 
	cout<<dp[n][m];
}
