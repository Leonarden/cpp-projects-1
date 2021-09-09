#include "../include/MemoBoxPart.h"

using namespace std;

MemoBoxPart::MemoBoxPart()
{
    //ctor
}

MemoBoxPart::~MemoBoxPart()
{
    //dtor
}

void MemoPart::format() {
 _sep = ":";
if(_type_format)
    _sep = " ";

    formatBody();


}


void MemoPart::formatBody() {
set<string>::iterator it;
string h_acronym = "";
string r_acronym = "";
string nrow = "";
string &row;
int idx;
int cntrow;

it = _rows.begin();

while(it!= _rows.end()){
r_acronym = "";
nrow = "";
idx = 0;
row = *it;
cntrow = 0;

while(idx<row.size()){

    while(idx<row.size() && row.at(idx)==' ')
    idx++;

    char c = std::toupper(row.at(idx));
    nrow.append(c);
    r_acronym.append(c)
    if(!cntrow){
        //each first char from current row
        h_acronym.append(c);
        cntrow++;
    }
    idx++;
    while(row.at(idx)!= ' ' && idx<row.size()){
        nrow.append(row.at(idx));
    idx++;
    }
    nrow.append(' ');

}
if(!_type_format)
    nrow.append(_sep).append(r_acronym);
    else
    nrow = r_acronym.append(_sep).append(nrow);
//cout << "Updating row " << nrow << endl;
row = nrow;


it++;


}

//Update header
if(!_type_format)
    _header.append(_sep).append(h_acronym);
else
  _header =  h_acronym.append(_header);


}

int MemoBoxPart::writeToFile(string outpath){
ofstream ofs(outpath); //need open for append.
if(!ofs.fail()){

    ofs << _header << endl;
    for(auto &s : _rows)
        ofs << s << endl;
    ofs << endl; //line separator


}
ofs.close();
return 0;
}
