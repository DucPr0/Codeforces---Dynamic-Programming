#include <stdio.h>
#include <string.h>
#include <iostream>
#define INSERT 2
#define REMOVE 3
#define REPLACE 5
#define BLANK 6
using namespace std;
int process[1001][1001];
int steps[1001][1001];
char s[1001],t[1001];
int currspot=1;
void printSteps(int i,int j) {
	if (process[i][j]==REPLACE) {
		printSteps(i-1,j-1);
		cout<<"REPLACE "<<currspot<<" "<<t[j-1]<<"\n";
		currspot++;
	} else if (process[i][j]==INSERT) {
		printSteps(i,j-1);
		cout<<"INSERT "<<currspot<<" "<<t[j-1]<<"\n";
		currspot++;
	} else if (process[i][j]==REMOVE) {
		printSteps(i-1,j);
		cout<<"DELETE "<<currspot<<"\n";
		//currspot--;
	} else if (process[i][j]==BLANK) {
		printSteps(i-1,j-1);
		currspot++;
	}
}
int main() {
	//This program have been turned into a multi-test program from its original form, used when submitting
	while (cin>>s>>t) {
		currspot=1;
		//memset(steps,0,sizeof(steps));
		for (int i=1;i<=strlen(t);i++) {
			steps[0][i]=i;
			process[0][i]=INSERT;
		}
		for (int i=1;i<=strlen(s);i++) {
			steps[i][0]=i;
			process[i][0]=REMOVE;
		}
		for (int i=1;i<=strlen(s);i++) {
			for (int j=1;j<=strlen(t);j++) {
				//cout<<"s["<<i<<"-1]="<<s[i-1]<<" t["<<j<<"-1]="<<t[j-1]<<"\n";
				if (s[i-1]==t[j-1]) {
					steps[i][j]=steps[i-1][j-1];
					process[i][j]=BLANK;
				}
				else {
					int remove=steps[i-1][j];
					int insert=steps[i][j-1];
					int replace=steps[i-1][j-1];
					steps[i][j]=min(remove,min(insert,replace))+1;
					if (steps[i][j]==insert+1) {
						process[i][j]=INSERT;
					}
					else if (steps[i][j]==remove+1) {
						process[i][j]=REMOVE;
					}
					else if (steps[i][j]==replace+1) process[i][j]=REPLACE;
					//cout<<"process["<<i<<"]["<<j<<"]="<<process[i][j]<<"\n";
				}
			}
		}
		cout<<steps[strlen(s)][strlen(t)]<<"\n";
		//cout<<"PRINT STEPS:\n";
		printSteps(strlen(s),strlen(t));
	}
}

