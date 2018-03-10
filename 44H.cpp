#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[51][10];
string s;
bool get_own_number(int i,int j) {
	if (i==s.length()-1) return true;
	int next=j+s[i+1]-'0';
	int next1,next2;
	if (next%2==0) {
		next=next/2;
		if (s[i+1]-'0'==next) return get_own_number(i+1,next);
	} else {
		next1=(next-1)/2;
		next2=(next+1)/2;
		if (s[i+1]-'0'==next1) return get_own_number(i+1,next1);
		else if (s[i+1]-'0'==next2) return get_own_number(i+1,next2);
	}
	return false;
}
signed main() {
	//freopen("11.inp","r",stdin);
	//freopen("11.out","w",stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>s;
	memset(dp,0,sizeof(dp));
	for (int i=0;i<10;i++) dp[0][i]=1;
	for (int i=0;i<s.length()-1;i++) {
		for (int j=0;j<10;j++) {
			int num=s[i+1]-'0';
			int next=j+num;
			if (next%2==0) {
				if (next/2<10) dp[i+1][next/2]+=dp[i][j];
			}
			else {
				if (next<19) dp[i+1][(next+1)/2]+=dp[i][j];
				if (next<21&&next>0) dp[i+1][(next-1)/2]+=dp[i][j];
			}
		}
	}
	int ans=0;
	for (int j=0;j<10;j++) {
		ans+=dp[s.length()-1][j];
	}
	//We will detect if it's possible to get your own number.
	cout<<ans-get_own_number(0,s[0]-'0');
}

