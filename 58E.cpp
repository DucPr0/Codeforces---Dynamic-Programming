#include <bits/stdc++.h>
#define int long long
#define INF 1e18
using namespace std;
int dp[21][21][21][2];
string sa[21][21][21][2];
string sb[21][21][21][2];
string a,b,c;
void top_down(int i,int j,int k,bool l) {
	if (!i&&!j&&!k&&!l) return;
	int imin1=i-1,jmin1=j-1,kmin1=k-1;
	if (imin1<0) imin1=0; if (jmin1<0) jmin1=0; if (kmin1<0) kmin1=0;
	bool addi;
	if (!k) addi=true;
	else addi=false;
	if (a[i]-'0'+b[j]-'0'+l==c[k]-'0') {
		if (dp[i][j][k][l]+addi<dp[imin1][jmin1][kmin1][0]) {
			dp[imin1][jmin1][kmin1][0]=dp[i][j][k][l]+addi;
			sa[imin1][jmin1][kmin1][0]=a[i]+sa[i][j][k][l];
			sb[imin1][jmin1][kmin1][0]=b[j]+sb[i][j][k][l];
			top_down(imin1,jmin1,kmin1,0);
		}
	} else if (a[i]-'0'+b[j]-'0'+l==c[k]-'0'+10) {
		if (dp[i][j][k][l]+addi<dp[imin1][jmin1][kmin1][1]) {
			dp[imin1][jmin1][kmin1][1]=dp[i][j][k][l]+addi;
			sa[imin1][jmin1][kmin1][1]=a[i]+sa[i][j][k][l];
			sb[imin1][jmin1][kmin1][1]=b[j]+sb[i][j][k][l];
			top_down(imin1,jmin1,kmin1,1);
		}
	} else {
		int d=(c[k]-b[j]-l+10)%10;
		if (d+b[j]-'0'+l==c[k]-'0') {
			if (dp[i][j][k][l]+1+addi<dp[i][jmin1][kmin1][0]) {
				dp[i][jmin1][kmin1][0]=dp[i][j][k][l]+1+addi;
				sa[i][jmin1][kmin1][0]=char(d+'0')+sa[i][j][k][l];
				sb[i][jmin1][kmin1][0]=b[j]+sb[i][j][k][l];
				top_down(i,jmin1,kmin1,0);
			}
		} else if (d+b[j]-'0'+l==c[k]-'0'+10) {
			if (dp[i][j][k][l]+1+addi<dp[i][jmin1][kmin1][1]) {
				dp[i][jmin1][kmin1][1]=dp[i][j][k][l]+1+addi;
				sa[i][jmin1][kmin1][1]=char(d+'0')+sa[i][j][k][l];
				sb[i][jmin1][kmin1][1]=b[j]+sb[i][j][k][l];
				top_down(i,jmin1,kmin1,1);
			}
		}
		d=(c[k]-a[i]-l+10)%10;
		if (a[i]-'0'+d+l==c[k]-'0') {
			if (dp[i][j][k][l]+1+addi<dp[imin1][j][kmin1][0]) {
				dp[imin1][j][kmin1][0]=dp[i][j][k][l]+1+addi;
				sa[imin1][j][kmin1][0]=a[i]+sa[i][j][k][l];
				sb[imin1][j][kmin1][0]=char(d+'0')+sb[i][j][k][l];
				top_down(imin1,j,kmin1,0);
			}
		} else if (a[i]-'0'+d+l==c[k]-'0'+10) {
			if (dp[i][j][k][l]+1+addi<dp[imin1][j][kmin1][1]) {
				dp[imin1][j][kmin1][1]=dp[i][j][k][l]+1+addi;
				sa[imin1][j][kmin1][1]=a[i]+sa[i][j][k][l];
				sb[imin1][j][kmin1][1]=char(d+'0')+sb[i][j][k][l];
				top_down(imin1,j,kmin1,1);
			}
		}
		d=(a[i]-'0'+b[j]-'0'+l+10)%10;
		if (a[i]-'0'+b[j]-'0'+l==d) {
			if (dp[i][j][k][l]+1<dp[imin1][jmin1][k][0]) {
				dp[imin1][jmin1][k][0]=dp[i][j][k][l]+1;
				sa[imin1][jmin1][k][0]=a[i]+sa[i][j][k][l];
				sb[imin1][jmin1][k][0]=b[j]+sb[i][j][k][l];
				top_down(imin1,jmin1,k,0);
			}
		} else if (a[i]-'0'+b[j]-'0'+l==d+10) {
			if (dp[i][j][k][l]+1<dp[imin1][jmin1][k][1]) {
				dp[imin1][jmin1][k][1]=dp[i][j][k][l]+1;
				sa[imin1][jmin1][k][1]=a[i]+sa[i][j][k][l];
				sb[imin1][jmin1][k][1]=b[j]+sb[i][j][k][l];
				top_down(imin1,jmin1,k,1);
			}
		}
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	string s;
	int tempa,tempb,tempc;
	char temp;
	getline(cin,s);
	stringstream ss;
	ss<<s;
	ss>>tempa>>temp>>tempb>>temp>>tempc;
	a=to_string(tempa); b=to_string(tempb); c=to_string(tempc);
	a="0"+a; b="0"+b; c="0"+c;
	for (int i=0;i<21;i++) for (int j=0;j<21;j++)
	for (int k=0;k<21;k++) dp[i][j][k][0]=dp[i][j][k][1]=INF;
	dp[a.length()-1][b.length()-1][c.length()-1][0]=0;
	top_down(a.length()-1,b.length()-1,c.length()-1,0);
	int ansa=stoll(sa[0][0][0][0]);
	int ansb=stoll(sb[0][0][0][0]);
	cout<<ansa<<"+"<<ansb<<"="<<ansa+ansb;
}
