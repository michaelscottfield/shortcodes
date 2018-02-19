#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define random(a,b) (rand()%(b-a+1)+a)
using namespace std;
int p,q;//p+q=100
int tracesize = 10000;
int maxnum = 60000;
int minnum = 1;

int main(){
	srand((unsigned)time(NULL));
	int i;
	p = 80;
	q = 20;
	for(i = 0; i < tracesize * p / 100; i ++){
		cout << random(minnum,maxnum*p/100) << endl;
	}
	for(i = 0; i < tracesize * q /100; i++){
		cout << random(maxnum * p /100+1, maxnum) << endl; 
	}
	return 0;
}
