#include "MemoBox.h"


MemoBox::MemoBox()
{
    //ctor
}

MemoBox::~MemoBox()
{
    //dtor
}

string MemoBox::getfname(int nseq) {
string fname = _oprefix;
ostringstream oss;
oss << fname;
if(_issequence){
 oss << nseq;
}
oss << "."<< _fext;

return oss.str();

}


int MemoBox::generate() {
int status = 0;
MemoBoxReader mreader;

string outfname = "";
try {
mreader.setFilepath(_infpath);
mreader.init();
MemoBoxPart * mpart = mreader.readNextPart();
while(mpart!=nullptr){

 mpart->setTypeFormat(0);
 mpart->format();
 outfname = getfname(mreader.counter);
 mpart->writeToFile(outfname);

 delete mpart;

 mpart = mreader.readNextPart();

}
//generated parts.
 status = mreader.counter;

}catch(exception e) {

  cout << " Something went wrong generating parts. " << e.what() << endl;
  status = -1;

}

return status;


}
