#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;
char ans[10][10];
int dp[10][513][513];
iii recur[10][513][513];
int insert[10][513][513];
/*
IDEA THAT WILL CERTAINLY WORK: Store a row with all the Ts that are placed BEGINNING FROM IT only.
Store 0, 1, 2, 3 for the status UP, DOWN, LEFT, RIGHT. So our number will reach a maximum of 2 ^ 18.
(We store each number in a form of 2 bits, 00, 01, 10, 11 and we store maximumlly 9 numbers)
*/
int curr,nexty,n,m;
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
string binary(int num,int m) {
	string ans;
	for (int i=0;i<m;i++) {
		if (checkBit(num,i)) ans="1"+ans;
		else ans="0"+ans;
	}
	return ans;
}
void backtrack(int j,int mask1,int mask2,int mask3,int newT,int ogmask1,int ogmask2,int ts) {
	//For every position i its status is stored on 2 * i and 2 * i + 1
	if (j==m) {
		//End of backtracking
		if (dp[curr][ogmask1][ogmask2]+newT>dp[nexty][mask2][mask3]) {
			dp[nexty][mask2][mask3]=dp[curr][ogmask1][ogmask2]+newT;
			recur[nexty][mask2][mask3]=iii(ii(ogmask1,ogmask2),mask1);
			insert[nexty][mask2][mask3]=ts;
			//Mask1's placing are all stored in ts.
		}
		return;
	}
	if (j>1) {
		if (!checkBit(mask1,j)&&!checkBit(mask1,j-1)&&!checkBit(mask1,j-2)&&!checkBit(mask2,j-1)&&!checkBit(mask3,j-1)) {
			int tempmask1=setBit(mask1,j);
			tempmask1=setBit(tempmask1,j-1);
			tempmask1=setBit(tempmask1,j-2);
			//Placing a normal one, and since it's 0, no setBit takes place.
			backtrack(j+1,tempmask1,setBit(mask2,j-1),setBit(mask3,j-1),newT+1,ogmask1,ogmask2,ts);
		}
	}
	if (j>1) {
		if (!checkBit(mask1,j-1)&&!checkBit(mask2,j-1)&&!checkBit(mask3,j-1)&&!checkBit(mask3,j)&&!checkBit(mask3,j-2)) {
			int newmask=setBit(mask3,j-1);
			newmask=setBit(newmask,j);
			newmask=setBit(newmask,j-2);
			//Placing a reverse one, 2 * j + 1 setBits take place.
			backtrack(j+1,setBit(mask1,j-1),setBit(mask2,j-1),newmask,newT+1,ogmask1,ogmask2,setBit(ts,2*(j-1)+1));
		}
	}
	if (j>1) {
		if (!checkBit(mask1,j-2)&&!checkBit(mask3,j-2)&&!checkBit(mask2,j)&&!checkBit(mask2,j-1)&&!checkBit(mask2,j-2)) {
			int newmask=setBit(mask2,j);
			newmask=setBit(newmask,j-1);
			newmask=setBit(newmask,j-2);
			//Placing a left one, 2 * j setBits take place
			backtrack(j+1,setBit(mask1,j-2),newmask,setBit(mask3,j-2),newT+1,ogmask1,ogmask2,setBit(ts,2*(j-2)));
		}
	}
	if (j>1) {
		if (!checkBit(mask1,j)&&!checkBit(mask3,j)&&!checkBit(mask2,j)&&!checkBit(mask2,j-1)&&!checkBit(mask2,j-2)) {
			int newmask=setBit(mask2,j);
			newmask=setBit(newmask,j-1);
			newmask=setBit(newmask,j-2);
			//Placing a right one, 2 * j and 2 * j + 1 setBits take place
			ts=setBit(ts,2*j);
			ts=setBit(ts,2*j+1);
			backtrack(j+1,setBit(mask1,j),newmask,setBit(mask3,j),newT+1,ogmask1,ogmask2,ts);
			ts=unsetBit(ts,2*j);
			ts=unsetBit(ts,2*j+1);
		}
	}
	//Not inserting anything at all
	backtrack(j+1,mask1,mask2,mask3,newT,ogmask1,ogmask2,ts);
}
char currchar='A';
void recursion(int i,int mask1,int mask2) {
	if (i==0) return;
	recursion(i-1,recur[i][mask1][mask2].first.first,recur[i][mask1][mask2].first.second);
	//cout<<binary(recur[i][mask1][mask2].second,m)<<" placings are: "<<binary(insert[i][mask1][mask2],2*m)<<"\n";
	int mask=insert[i][mask1][mask2];
	for (int j=0;j<m;j++) {
		if (!checkBit(recur[i][mask1][mask2].second,j)) {
			ans[i][j]='.';
			continue;
		}
		if (checkBit(mask,j*2)&&checkBit(mask,j*2+1)) {
			//We have placed a rightward T
			//cout<<"rightward T placed "<<i<<" "<<j<<"\n";
			ans[i][j]=ans[i+1][j]=ans[i+2][j]=ans[i+1][j-1]=ans[i+1][j-2]=currchar;
			currchar++;
		} else if (checkBit(mask,j*2)&&!checkBit(mask,j*2+1)) {
			//We have placed a leftward T
			//cout<<"leftward T placed "<<i<<" "<<j<<"\n";
			ans[i][j]=ans[i+1][j+2]=ans[i+2][j]=ans[i+1][j+1]=ans[i+1][j]=currchar;
			currchar++;
		} else if (!checkBit(mask,j*2)&&checkBit(mask,j*2+1)) {
			//We have placed an upside-down T
			//cout<<"upside-down T placed "<<i<<" "<<j<<"\n";
			ans[i][j]=ans[i+1][j]=ans[i+2][j+1]=ans[i+2][j-1]=ans[i+2][j]=currchar;
			currchar++;
		}
	}
}
signed main() {
	//freopen("142C.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	memset(dp,-1,sizeof(dp));
	memset(ans,0,sizeof(ans));
	dp[0][0][0]=0;
	for (int i=0;i<n;i++) {
		curr=i;
		nexty=i+1;
		for (int mask1=0;mask1<(1<<m);mask1++) {
			for (int mask2=0;mask2<(1<<m);mask2++) {
				if (dp[curr][mask1][mask2]!=-1) {
					backtrack(0,mask1,mask2,0,0,mask1,mask2,0);
				}
			}
		}
	}
	cout<<dp[n][0][0]<<"\n";
	recursion(n,0,0);
	for (int i=1;i<=n;i++) {
		for (int j=0;j<m;j++) {
			if (ans[i][j]==0&&ans[i][j-1]==0&&ans[i][j+1]==0&&ans[i+1][j]==0&&ans[i+2][j]==0) {
				ans[i][j]=ans[i][j-1]=ans[i][j+1]=ans[i+1][j]=ans[i+2][j]=currchar;
				currchar++;
			}
		}
	}
	for (int i=1;i<=n;i++) {
		for (int j=0;j<m;j++) cout<<ans[i][j];
		cout<<"\n";
	}
}
