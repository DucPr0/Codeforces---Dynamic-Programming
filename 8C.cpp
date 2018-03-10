#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
int n,x[26],y[26];
int dist[26][26];
typedef pair<int,int> ii;
int distance(int i,int j) {
	return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}
int get_time(int obj1,int obj2) {
	return dist[n][obj1]+dist[obj1][obj2]+dist[obj2][n];
}
int setBit(int num,int i) {
	return num|(1<<i);
}
int unsetBit(int num,int i) {
	num^=1<<i;
	return num;
}
bool checkBit(int num,int i) {
	if (num&1<<i) return true;
	else return false;
}
int countOnes(int num) {
	return __builtin_popcount(num);
}
string binary(int num) {
	string ans;
	for (int i=0;i<n;i++) {
		if (checkBit(num,i)) ans="1"+ans;
		else ans="0"+ans;
	}
	return ans;
}
int dp[1<<24+1];
ii recur[1<<24+1];
void printSteps(int mask) {
	if (countOnes(mask)==0) return;
	ii temp=recur[mask];
	int firsty=temp.first; int secondy=temp.second;
	if (firsty!=-1) {
		int tempmask=unsetBit(mask,firsty);
		tempmask=unsetBit(tempmask,secondy);
		printSteps(tempmask);
		cout<<"0 "<<firsty+1<<" "<<secondy+1<<" ";
	} else {
		int tempmask=unsetBit(mask,secondy);
		printSteps(tempmask);
		cout<<"0 "<<secondy+1<<" ";
	}
	if (countOnes(mask)==n) cout<<"0";
}
int main() {
	int tempx,tempy;
	//freopen("8Cin.txt","r",stdin);
	//freopen("8Cout.txt","w",stdout);
	cin>>tempx>>tempy>>n;
	x[n]=tempx; y[n]=tempy;
	for (int i=0;i<n;i++) cin>>x[i]>>y[i];
	//dp[i]: Minimum time to pick up all objects in mask i. Check for all unset bits, set them for
	//new masks. Pick 'em up :D.
	for (int i=0;i<=n;i++) {
		for (int j=0;j<=n;j++) {
			dist[i][j]=distance(i,j);
		}
	}
	for (int mask=0;mask<(1<<n);mask++) {
		dp[mask]=INF;
	}
	dp[0]=0;
	for (int mask=0;mask<(1<<n);mask++) {
		//We never check point 0, 'cause it's the point we will be visiting alot.
		if (dp[mask]!=INF) {
			//cout<<"mask="<<binary(mask)<<" dp="<<dp[mask]<<"\n";
			if (countOnes(mask)<=n-2) {
				int next1=-1;
				for (int i=0;i<n;i++) {
					if (!checkBit(mask,i)) {
						next1=i;
						break;
					}
				}
				int tempmask=setBit(mask,next1);
				if (dp[tempmask]>dp[mask]+dist[n][next1]*2) {
					dp[tempmask]=dp[mask]+dist[n][next1]*2;
					recur[tempmask]=ii(-1,next1);
				}
				for (int i=0;i<n;i++) {
					if (!checkBit(mask,i)&&next1!=i) {
						int next2=i;
						if (dp[mask]+get_time(next1,next2)<dp[setBit(tempmask,next2)]) {
							dp[setBit(tempmask,next2)]=dp[mask]+get_time(next1,next2);
							recur[setBit(tempmask,next2)]=ii(next1,next2);
						}
					}
				}
			} else if (countOnes(mask)==n-1) {
				for (int i=0;i<n;i++) {
					if (!checkBit(mask,i)) {
						int next=i;
						if (dp[mask]+dist[n][next]*2<dp[setBit(mask,next)]) {
							dp[setBit(mask,next)]=dp[mask]+dist[n][next]*2;
							ii tempo=ii(-1,next);
							recur[setBit(mask,next)]=tempo;
						}
						break;
					}
				}
			}
		}
	}
	cout<<dp[(1<<n)-1]<<"\n";
	printSteps((1<<n)-1);
}
