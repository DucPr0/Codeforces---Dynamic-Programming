#include <bits/stdc++.h>
using namespace std;
int dp[22][22][5];
int main() {
	//freopen("14E.inp","r",stdin);
	//freopen("14E.out","w",stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n,t;
	cin>>n>>t;
	/*
	We can see the total number of breaks and cavities are supposed to be 2T - 1.
	dp[i][j][k]: We are at the ith x coordinate, there are j breaks (breaks mean a cavity or a hump),
	and our current y coordinate is k.
	DP means the number of ways to end the camel drawing with the information above.
	Because there are T humps and T - 1 cavities, humps go first. So, if the breaks are odd, then we
	are going to have a cavity. Else, we are going to have a hump.
	*/
	memset(dp,0,sizeof(dp));
	dp[n][2*t-1][1]=dp[n][2*t-1][2]=dp[n][2*t-1][3]=dp[n][2*t-1][4]=1;
	for (int i=n-1;i>=2;i--) {
		for (int j=0;j<=2*t-1;j++) {
			if (j%2==0) {
				//We are going up. If we do go back down there will be a new break.
				for (int curr=1;curr<=4;curr++) {
					for (int next=1;next<=4;next++) {
						if (next>curr) dp[i][j][curr]+=dp[i+1][j][next];
						else if (next<curr&&j<2*t-1) dp[i][j][curr]+=dp[i+1][j+1][next];
					}
				}
			} else {
				for (int curr=1;curr<=4;curr++) {
					for (int next=1;next<=4;next++) {
						if (next<curr) dp[i][j][curr]+=dp[i+1][j][next];
						else if (next>curr&&j<2*t-1) dp[i][j][curr]+=dp[i+1][j+1][next];
					}
				}
			}
		}
	}
	int ans=0;
	//There are curr - 1 ways to get to this point tho (We can only go from 1 to curr - 1, because 
	//humps start before cavities)
	for (int curr=1;curr<=4;curr++) ans+=(curr-1)*dp[2][0][curr];
	//Because there's no way we can get a new hump on the first line, we will add on the second one.
	cout<<ans;
}

