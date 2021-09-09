#include <iostream>
#include "MemoBox.h"

using namespace std;
/*
int main()
{
int s;
MemoBox mbx;
string inpath = "/user/dev/workspaces/worksc++/code-patterns/cb-practice-15/source-2.txt";

try{

mbx.setInParams(inpath);
mbx.setOutParams("/user/dev/workspaces/worksc++/code-patterns/cb-practice-15/output-2","txt",false);

s = mbx.generate();

}catch(exception e){
 s = -1;
 cout << " Exception in Main: " << e.what() << endl;

}


    return s;
}
