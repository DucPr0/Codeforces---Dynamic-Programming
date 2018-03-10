#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#define LEAVEI 10
#define LEAVEJ 20
#define LEAVEJPLUS1 30
#define ONLYTWO 40
int n;
int cnt[1001][1001];
int process[1001][1001];
void printProc(int i,int j) {
	if (j==n+1) {
		cout<<i<<"\n";
		return;
	}
	if (process[i][j]==LEAVEI) {
		cout<<j<<" "<<j+1<<"\n";
		printProc(i,j+2);
	} else if (process[i][j]==LEAVEJ) {
		cout<<i<<" "<<j+1<<"\n";
		printProc(j,j+2);
	} else if (process[i][j]==LEAVEJPLUS1) {
		cout<<i<<" "<<j<<"\n";
		printProc(j+1,j+2);
	} else if (process[i][j]==ONLYTWO) {
		cout<<i<<" "<<j<<"\n";
	}
} 
int main() {
	while (cin>>n) {
		int a[1001];
		memset(process,0,sizeof(process));
		memset(cnt,0,sizeof(cnt));
		for (int i=1;i<=n;i++) {
			cin>>a[i];
		}
		for (int i=1;i<=n;i++) {
			cnt[i][n]=max(a[i],a[n]);
			process[i][n]=ONLYTWO;
			cnt[i][n+1]=a[i];
		}
		cnt[n][n+1]=a[n];
		for (int i=n-2;i>0;i--) {
			for (int j=n-1;j>i;j--) {
				int leavei=cnt[i][j+2]+max(a[j],a[j+1]);
				int leavejplus1=cnt[j+1][j+2]+max(a[i],a[j]);
				int leavej=cnt[j][j+2]+max(a[j+1],a[i]);
				//cnt[i][j]=min(cnt[i][j+2]+max(a[j],a[j+1]),min(cnt[j+1][j+2]+max(a[i],a[j]),cnt[j][j+2]+
																					//max(a[j+1],a[i])));
				cnt[i][j]=min(leavei,min(leavej,leavejplus1));
				if (cnt[i][j]==leavei) process[i][j]=LEAVEI;
				else if (cnt[i][j]==leavej) process[i][j]=LEAVEJ;
				else if (cnt[i][j]==leavejplus1) process[i][j]=LEAVEJPLUS1;
				//cout<<"i="<<i<<" j="<<j<<" cnt[i][j]="<<cnt[i][j]<<"\n";
				//cout<<"cnt[i][j+2]="<<cnt[i][j+2]<<"\n";
				//cout<<"cnt[j+1][j+2]="<<cnt[j+1][j+2]<<"\n";
				//cout<<"cnt[j][j+2]="<<cnt[j][j+2]<<"\n";
			}
		}
		cout<<cnt[1][2]<<"\n";
		printProc(1,2);
	}
}

