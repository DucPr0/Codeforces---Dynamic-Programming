#include <bits/stdc++.h>
#define int long long
#define MOD 1000000007
#define fw(i,l,r) for (int i=l;i<r;i++)
using namespace std;
typedef set<int>::iterator iter;
struct stop {int s,e;};
/*
Naive DP: DP[i]: Number of ways to go to the ith stop.
Check for all buses ending at i, and add up from s -> i - 1
Optimized DP: Since there are stops that won't be visited at all, we only store ones that are ended.
For each of these stops, store the starting positions. Use binary search and prefix sum in order to
update optimally. Binary search for the last number that is smaller than the start we are looking at.
Complexity: O(MlogM)
*/
bool cmp(const stop& a,const stop& b) {if (a.e==b.e) return a.s<b.s; else return a.e<b.e;};
int n,m,psum[100005],dp[100005];
set<int> temp;
stop bus[100005];
vector<int> endy;
vector<vector<int>> corr;
signed main() {
	//freopen("101B.inp","r",stdin);
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	fw (i,0,m) {cin>>bus[i].s>>bus[i].e; temp.insert(bus[i].e);};
	//Our algorithm doesn't work properly with multiple ends. Fix it by saving a set of registered
	//ends and saving a corresponding vector.
	sort(bus,bus+m,cmp);
	int currpos=0;
	corr.resize(temp.size());
	for (iter it=temp.begin();it!=temp.end();++it) {
		endy.push_back(*it);
		fw (i,currpos,m) if (bus[i].e==*it) corr[endy.size()-1].push_back(bus[i].s);
		else {currpos=i; break;}
	} 
	//fw (i,0,endy.size()) {cout<<"Station "<<endy[i]<<" have starts:"; fw (j,0,corr[i].size()) cout<<" "<<corr[i][j]; cout<<"\n";}
	int ans=0;
	fw (i,0,endy.size()) {
		//For each start get lower bound for erasing psum.
		psum[i]=i?psum[i-1]:0; dp[i]=0;
		fw (j,0,corr[i].size()) {
			if (!corr[i][j]) dp[i]++;
			int bes=lower_bound(endy.begin(),endy.end(),corr[i][j])-endy.begin()-1;
			dp[i]+=((i?psum[i-1]:0)-(bes>=0?psum[bes]:0)+MOD)%MOD;
			dp[i]%=MOD;
		}
		if (endy[i]==n) ans=dp[i];
		psum[i]+=dp[i];
		psum[i]%=MOD;
	}
	cout<<ans;
}
