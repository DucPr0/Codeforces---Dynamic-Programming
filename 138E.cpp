#include <bits/stdc++.h>
#define for(i,l,r) for (int i=l;i<r;i++)
typedef long long LL;
using namespace std;
char c[501];
int l[501],r[501];
int k;
string s;
int county[26][100001];
int lpos[501],rpos[501];
int val[100001];
int range(int l,int r,int j) {
	return county[c[j]-'a'][r]-(l?county[c[j]-'a'][l-1]:0);
}
signed main() {
	//freopen("138E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int L,R;
	cin>>s>>k>>L>>R;
	for (i,0,k) cin>>c[i]>>l[i]>>r[i];
	LL ans=0,curr=0;
	memset(lpos,-1,sizeof(lpos)); 
	memset(rpos,-1,sizeof(rpos));
	for (i,0,s.length()) {
		for (j,0,26) county[j][i]+=(i?county[j][i-1]:0)+(s[i]-'a'==j);
		for (j,0,k) {
			//rpos will store the last member that creates a suffix starting at i with r[j] + 1 cs
			//Then rpos + 1 is the bound.
			//lpos will store the first member that creates a suffix starting at i with l[j] cs
			//We can see that the l and r values will never intersect eachother, so we can efficiently
			//store them inside an array.
			//So rpos + 1 to lpos will be the array that have constraint j satisfied, ending at suffix i.
			//We will need to find a way to update these values efficiently
			/*
			We see that if we update all the values while increasing lpos, we will have an extra
			range from up to rpos + 1, so if we also update all the values while increasing rpos,
			we can destroy this extra value.
			*/
			while (lpos[j]<i&&range(lpos[j]+1,i,j)>=l[j]) {
				//This will check if the next one still satisfies >= l[j] before moving up, so essentially
				//it will find our needed position
				lpos[j]++;
				val[lpos[j]]++;
				if (val[lpos[j]]==L) curr++;
				if (val[lpos[j]]==R+1) curr--;
			}
			while (rpos[j]<i&&range(rpos[j]+1,i,j)>r[j]) {
				rpos[j]++;
				val[rpos[j]]--;
				if (val[rpos[j]]==L-1) curr--;
				if (val[rpos[j]]==R) curr++;
			}
			//cout<<"lpos="<<lpos[j]<<" rpos="<<rpos[j]<<"\n";
		}
		if (!L) curr++;
		//cout<<"i="<<i<<" curr="<<curr<<"\n";
		ans+=curr;
	}
	cout<<ans;
}
