#include <bits/stdc++.h>
#define int long long
using namespace std;
struct event {
	int x,t;
};
struct point {
	int f,g;
};
int n,v;
event e[100001];
point fg[100001];
bool cmp(const event& a,const event& b) {
	return a.t<b.t;
}
bool cmp2(const point& a,const point& b) {
	if (a.f==b.f) return a.g<b.g;
	else return a.f<b.f;
}
signed main() {
	//freopen("76F.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for (int i=0;i<n;i++) cin>>e[i].x>>e[i].t;
	sort(e,e+n,cmp);
	cin>>v;
	/*
	The event j is reachable from event i if this condition apply:
	- t[j] >= t[i]
	- abs(x[j] - x[i]) <= (t[j] - t[i]) * v. There exist 2 cases:
	+ x[j] - x[i] <= t[j] * v - t[i] * v. => - x[i] + t[i] * v <= - x[j] + t[j] * v
	- Call F(u) = - x[u] + t[u] * v.
	+ x[i] - x[j] <= t[j] * v - t[i] * v. => x[i] + t[i] * v <= x[j] + t[j] * v
	- So G(u) = x[u] + t[u] * v.
	Firstly, we have to sort all of our points by time. Then, we create 2 arrays F and G to store
	these values. We see that:
	- If x[j] >= x[i], then x[j] + t[j] * v >= x[i] + t[i] * v.
	- If x[i] >= x[j], then x[i] - t[i] * v >= x[j] - t[j] * v. So basically, whenever an abs is applied,
	the reverse condition automatically become true. So we will know if point i is reachable from point
	j IF 
	+ F[i] <= F[j]
	+ G[i] <= G[j]
	So, we create the 2 functions, then sort F and G by F values firstly, G values secondly. Then, it
	just turned into the LIS problem, and we can do it in O(NlogN).
	*/
	for (int i=0;i<n;i++) {
		fg[i].f=-e[i].x+e[i].t*v;
		fg[i].g=e[i].x+e[i].t*v;
	}
	sort(fg,fg+n,cmp2);
	vector<int> v1;
	for (int i=0;i<n;i++) {
		//cout<<fg[i].f<<" "<<fg[i].g<<"\n";
		if (!v1.size()||fg[i].g>=v1[v1.size()-1]) {
			v1.push_back(fg[i].g);
		} else {
			int pos=upper_bound(v1.begin(),v1.end(),fg[i].g)-v1.begin();
			//We can repeat elements, so we don't replace the same one, we replace the BIGGER one.
			v1[pos]=fg[i].g;
		}
	}
	//This is the answer for the second case.
	/*
	For the first case, we can treat both of its x and t value as 0. We can force - start through this
	value by destroying all elements that is smaller than 0
	*/
	int secondans=v1.size();
	v1.clear();
	for (int i=0;i<n;i++) {
		if (fg[i].f<0||fg[i].g<0) continue;
		if (!v1.size()||fg[i].g>=v1[v1.size()-1]) {
			v1.push_back(fg[i].g);
		} else {
			int pos=upper_bound(v1.begin(),v1.end(),fg[i].g)-v1.begin();
			v1[pos]=fg[i].g;
		}
	}
	cout<<v1.size()<<" "<<secondans;
}
