#include "../include/MemoBoxReader.h"

using namespace std;

MemoBoxReader::MemoBoxReader()
{
    //ctor
}

MemoBoxReader::~MemoBoxReader()
{
    //dtor
    iof->close();
    delete iof;
    iof = nullptr;

}

void MemoBoxReader::init() {
if(!iof->is_open())
    iof = new ifstream(filepath);

}

MemoBoxPart MemoBoxReader::readNextPart() {

MemoBoxPart part;
string line = "";

while(line=="" && ! iof->eof())
std::getline( iof, line);

while(line!="" && ! iof->eof()){

    if(line.at(0)=='#'){ //header
        part.setHeader(line.substr(1,line.size()));
    }else{
        part.addRow(line);
    }
  std::getline(iof,line);
}
if(part) counter++;

return part;

}
