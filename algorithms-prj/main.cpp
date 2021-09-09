#include <iostream>
#include <exception>
#include "fibonacci-number.h"
#include "coin-change.h"
#include "backpack.h"
#include "nqueens.h"

using namespace std;

int runCoinChange() {

cout << "Coin change problem " << endl;
cout << "Running recursive version:" << endl;
auto start = chrono::steady_clock::now();
int r1= lauchCoinChangeRecursive();
auto end = chrono::steady_clock::now();

cout << "Solutions found s=" << r1 << endl;
cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<< " ms" << endl;

cout << "Running DP version:" << endl;

start = chrono::steady_clock::now();
int r2 =launchCoinChangeDP();
end = chrono::steady_clock::now();
cout << "Solutions found s=" << r2 << endl;
cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<< " ms" << endl;


return r1 & r2;

}
//main
int mainFibo() {
    int s = -1;


try{


s = runFibo();

}catch(exception e){

    cout << "Exception while running main"<< e.what() << endl;

}

return s;

}


int mainRunCoin() {
    int s = -1;


try{

s = runCoinChange();

}catch(exception e){

    cout << "Exception while running main"<< e.what() << endl;

}

return s;

}
//backpack problem
int mainBackpack(){
int s = -1;
BackpackRunner * runner = new BackpackRunner();
try{

s = runner->run();

}catch(exception e){

    cout << "Exception while running main"<< e.what() << endl;

}

return s;

}


//main Backtracking
int main() {
bool s = false;

NBacktracking *nqueens;

try{

cout << "Running NQueens problem N=8 :" << endl;
nqueens = new NQueens(4,0); //8x8 board intialized at 0
auto start = chrono::steady_clock::now();
s = nqueens->solve();
auto end = chrono::steady_clock::now();

cout << "End NQueens with found=" << s << endl;
cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()<< " ms" << endl;

}catch(exception e){

    cout << "Exception while running main"<< e.what() << endl;

}

return (s*1);

}


