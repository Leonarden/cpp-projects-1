#ifndef FIBONACCI-NUMBER_H_INCLUDED
#define FIBONACCI-NUMBER_H_INCLUDED
#include<chrono>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//Fibonnacci recursive
int fiboRec(int n){
if(n==0)
    return 0;
if(n<=1)
    return 1;
else
    return (fiboRec(n-1)+ fiboRec(n-2));

}
int launcherFiboRec( int k) {

int n = k;
//////
auto start = chrono::steady_clock::now();

int r = fiboRec(n);

auto end = chrono::steady_clock::now();
//////

cout << "Fibonnacci value for n=" << n << " is: " << r << endl;
cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<< " ms" << endl;

return r;

}


//Fibonacci dinamic programming

int dp[30]={-6};

int fiboDP(int n)
{
	if (0<=n && n <= 1)
		return n;
	// temporary variables to store
	// values of fib(n-1) & fib(n-2)
	int first=-6, second=-6;
	if (dp[n - 2] >= 0){

		second = dp[n - 2];
	}
	if (dp[n-1] >= 0) {
		first = dp[n - 1];
	}

    if(second<0)
        second = fiboDP(n-2);
    if(first<0)
        first = fiboDP(n-1);
	if(first>=0 && second>=0)
	 return dp[n] = first + second;
	 else
     return -6;



}

int launcherFiboDP(int k) {

//dp = (int *) calloc( k+1, sizeof(*dp));
memset(dp, -6, sizeof(dp));



int n = k;
//////
auto start = chrono::steady_clock::now();

int r = fiboDP(n);

auto end = chrono::steady_clock::now();
//////

cout << "Fibonacci value for n=" << n << " is: " << r << endl;
cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<< " ms" << endl;

return r;

}



int runFibo()
{
    int n = 0;

    cout << "Fibonnacci number comparation (Recursive vs DP)" << endl;
    cout << " Find fibo number: " << endl;
    cin>> n;
    cout << "Recursive" << endl;
 int r1=  launcherFiboRec(n);
    getchar();
    cout << "Dynamic programming" << endl;
 int r2 =launcherFiboDP(n);
    if(r1==r2)
    return 0;

    return -1;
}



#endif // FIBONACCI-NUMBER_H_INCLUDED
