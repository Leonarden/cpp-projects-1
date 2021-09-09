#include "../include/MemoBox.h"


MemoBox::MemoBox()
{
    //ctor
}

MemoBox::~MemoBox()
{
    //dtor
}

int MemoBox::generate() {
int status = 0;
MemoBoxReader mreader;
MemoBoxPart & mpart;
string outfname = "";
try {
mreader.setFilepath(_infpath);
mreader.init();
while((mpart=mreader.readNextPart())){

 outfname = getfname(mreader.counter);

 mpart.writeToFile(outfname);

}
//generated parts.
 status = mreader.counter;

}catch(exception e) {

  cout << " Something went wrong generating parts. " << e.what() << endl;
  status = -1;

}

return status;


}

string MemoBox::getfname(int nseq) {
string fname = _oprefix;

if(_issequence){
 fname.append(new string(nseq));
}
fname.append(".").append(_fext);

return fname;

}
