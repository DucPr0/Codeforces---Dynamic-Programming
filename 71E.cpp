#include <bits/stdc++.h>
using namespace std;
map<string,int> atoms;
bool dp[19][1<<17];
int n,k,a[18],b[18];
int recur[19][1<<17];
string chemicala[19],chemicalb[19];
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
string binary(int num,int n) {
	string ans;
	for (int i=0;i<n;i++) {
		if (checkBit(num,i)) ans="1"+ans;
		else ans="0"+ans;
	}
	return ans;
}
void recursion(int i,int mask) {
	if (i==0) return;
	int usedpart=recur[i][mask];
	recursion(i-1,(mask^usedpart));
	int county=0;
	for (int i=0;i<n;i++) {
		if (checkBit(usedpart,i)) {
			if (county) cout<<"+"<<chemicala[i];
			else cout<<chemicala[i];
			county++;
		}
	}
	cout<<"->"<<chemicalb[i]<<"\n";
}
int main() {
	freopen("71E.inp","r",stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	/*
	DP[i][j][mask]: We are at the ith element, j atoms allocated, with the mask of used atoms as mask. It stores if this
	status is reachable
	*/
	atoms["H"]=1; atoms["He"]=2; atoms["Li"]=3; atoms["Be"]=4; atoms["B"]=5; atoms["C"]=6; atoms["N"]=7;
	atoms["O"]=8; atoms["F"]=9; atoms["Ne"]=10; atoms["Na"]=11; atoms["Mg"]=12; atoms["Al"]=13; atoms["Si"]=14;
	atoms["P"]=15; atoms["S"]=16; atoms["Cl"]=17; atoms["Ar"]=18; atoms["K"]=19; atoms["Ca"]=20;
	atoms["Sc"]=21; atoms["Ti"]=22; atoms["V"]=23; atoms["Cr"]=24; atoms["Mn"]=25; atoms["Fe"]=26; atoms["Co"]=27;
	atoms["Ni"]=28; atoms["Cu"]=29; atoms["Zn"]=30; atoms["Ga"]=31; atoms["Ge"]=32; atoms["As"]=33; 
	atoms["Se"]=34; atoms["Br"]=35; atoms["Kr"]=36; atoms["Rb"]=37; atoms["Sr"]=38; atoms["Y"]=39;
	atoms["Zr"]=40; atoms["Nb"]=41; atoms["Mo"]=42; atoms["Tc"]=43; atoms["Ru"]=44; atoms["Rh"]=45;
	atoms["Pd"]=46; atoms["Ag"]=47; atoms["Cd"]=48; atoms["In"]=49; atoms["Sn"]=50; atoms["Sb"]=51;
	atoms["Te"]=52; atoms["I"]=53; atoms["Xe"]=54; atoms["Cs"]=55; atoms["Ba"]=56; atoms["La"]=57;
	atoms["Ce"]=58; atoms["Pr"]=59; atoms["Nd"]=60; atoms["Pm"]=61; atoms["Sm"]=62; atoms["Eu"]=63;
	atoms["Gd"]=64; atoms["Tb"]=65; atoms["Dy"]=66; atoms["Ho"]=67; atoms["Er"]=68; atoms["Tm"]=69;
	atoms["Yb"]=70; atoms["Lu"]=71; atoms["Hf"]=72; atoms["Ta"]=73; atoms["W"]=74; atoms["Re"]=75;
	atoms["Os"]=76; atoms["Ir"]=77; atoms["Pt"]=78; atoms["Au"]=79; atoms["Hg"]=80; atoms["Tl"]=81;
	atoms["Pb"]=82; atoms["Bi"]=83; atoms["Po"]=84; atoms["At"]=85; atoms["Rn"]=86; atoms["Fr"]=87;
	atoms["Fr"]=87; atoms["Ra"]=88; atoms["Ac"]=89; atoms["Th"]=90; atoms["Pa"]=91; atoms["U"]=92;
	atoms["Np"]=93; atoms["Pu"]=94; atoms["Am"]=95; atoms["Cm"]=96; atoms["Bk"]=97; atoms["Cf"]=98;
	atoms["Es"]=99; atoms["Fm"]=100;
	cin>>n>>k;
	for (int i=0;i<n;i++) {
		string temp;
		cin>>temp;
		chemicala[i]=temp;
		a[i]=atoms[temp];
	}
	for (int i=1;i<=k;i++) {
		string temp;
		cin>>temp;
		chemicalb[i]=temp;
		b[i]=atoms[temp];
	}
	vector<vector<int>> masks;
	masks.resize(k+1);
	for (int mask=1;mask<(1<<n);mask++) {
		int getsum=0;
		for (int i=0;i<n;i++) if (checkBit(mask,i)) getsum+=a[i];
		for (int i=1;i<=k;i++) if (getsum==b[i]) masks[i].push_back(mask);
	}
	memset(dp,false,sizeof(dp));
	memset(recur,0,sizeof(recur));
	dp[0][0]=true;
	for (int i=0;i<k;i++) {
		for (int mask=0;mask<(1<<n);mask++) {
			if (dp[i][mask]) {
				for (int curr=0;curr<masks[i+1].size();curr++) {
					if ((mask&masks[i+1][curr])==0) {
						//AND operation return 0, which means there are no overlapping 1s.
						//The mask we use for next will be created from an OR operation
						dp[i+1][(mask|masks[i+1][curr])]=true;
						recur[i+1][(mask|masks[i+1][curr])]=masks[i+1][curr];
						//When we recursion back, we XOR our mask with the recursion part.
						//cout<<"Next is "<<(mask|masks[i+1][curr])<<"\n";
					}
				}
			}
		}
	}
	if (!dp[k][(1<<n)-1]) cout<<"NO";
	else {
		cout<<"YES\n";
		recursion(k,(1<<n)-1);
	}
}
