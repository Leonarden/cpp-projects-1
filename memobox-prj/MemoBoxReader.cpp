#include "MemoBoxReader.h"

using namespace std;


MemoBoxReader::~MemoBoxReader()
{
    //dtor
    iof->close();
    delete iof;
    iof = nullptr;

}

void MemoBoxReader::init() {
if(iof==nullptr)
    iof = new ifstream(filepath);

}

MemoBoxPart * MemoBoxReader::readNextPart() {

MemoBoxPart * part;
string line = "";
bool h_cont = false;
while(line=="" && ! iof->eof())
 getline( *iof, line);

while(line!="" && ! iof->eof()){

    if(line.at(0)=='#'){ //header
        h_cont = true;
        part = new MemoBoxPart();
        part->setHeader(line.substr(1,line.size()));
    }else{
        part->addRow(line);
    }
  getline(*iof,line);
}
if(h_cont) {
        counter++;
      return part;
}
return nullptr;
}
