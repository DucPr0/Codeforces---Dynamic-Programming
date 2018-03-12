#include <bits/stdc++.h>
#define int long long
using namespace std;
int divi[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};
int divi2[2521];
int gcd(int a,int b) {
	if (a%b==0) return b;
	else return gcd(b,a%b);
}
int lcm(int a,int b) {
	if (!a) return b;
	return (a*b)/gcd(a,b);
}
int dp[19][48][2520];
/*
We have to DP in a top - down fashion in order to avoid a possible TLE.
The DP value stands for the number of ways to END with our current state.
DP[i][k][remain]: We are at the ith digit, the LCM of all digits as the kth number in divi[], and the
remainder for 2520 is remain.
Array size: 2 million. The smaller flag is handled inside the recursion function, so we don't have
to consider it inside our array.
*/
string endy;
int find_ans(int i,bool strict,int currlcm,int remain) {
	//cout<<"i="<<i<<" strict="<<strict<<" currlcm="<<currlcm<<" remain="<<remain<<"\n";
	if (i==0) {
		//Final digit, these are intial cases. It is only a good number if the remain is divisible
		//by the current lcm.
		return remain%currlcm==0;
	}
	if (!strict&&dp[i][divi2[currlcm]][remain]!=-1) return dp[i][divi2[currlcm]][remain];
	/*
	If the current number is unrestricted, we can place whatever integer next and it's still unrestricted
	If the current number is restricted, we are only able to place integers smaller than end[i] - '0', and
	in the explicit case of that number, the next state is also restricted.
	We don't really have to memset because if the current number is not strict, we can start choosing
	from 0 to 9, which because dp only stores non - strict values, we are fine.
	REASON DP ISN'T WORKING PROPERLY: It over-calculates the number of digits, so instead of running
	down to up, we will run up downto bottom in order to avoid overcalculating number of digits.
	*/
	if (!strict) {
		int ans=0;
		for (int j=0;j<10;j++) {
			ans+=find_ans(i-1,0,lcm(j,currlcm),(remain*10+j)%2520);
		}
		dp[i][divi2[currlcm]][remain]=ans;
		return ans;
	} else {
		int ans=0;
		for (int j=0;j<endy[i-1]-'0';j++) {
			ans+=find_ans(i-1,0,lcm(j,currlcm),(remain*10+j)%2520);
		}
		ans+=find_ans(i-1,1,lcm(endy[i-1]-'0',currlcm),(remain*10+endy[i-1]-'0')%2520);
		//Ans here is considered for the strict, so we can't store it.
		return ans;
	}
}
int calc_ans(string lim) {
	if (lim=="0") return 1;
	endy=lim;
	//Reverse the array in order to accomodate our new needs.
	reverse(endy.begin(),endy.end());
	return find_ans(endy.length(),1,1,0);
}
signed main() {
	//freopen("55D.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t;
	cin>>t;
	for (int i=0;i<48;i++) divi2[divi[i]]=i;
	memset(dp,-1,sizeof(dp));
	while (t--) {
		string r;
		int l;
		cin>>l>>r;
		l--;
		string temp=to_string(l);
		cout<<calc_ans(r)-calc_ans(temp)<<"\n";
		//cout<<calc_ans(temp)<<"\n";
	}
}
