#include "MemoBoxPart.h"

using namespace std;

MemoBoxPart::MemoBoxPart()
{
    //ctor
}

MemoBoxPart::~MemoBoxPart()
{
    //dtor
}

void MemoBoxPart::format() {
 _sep = ":";
if(_type_format)
    _sep = " ";

    formatBody();


}


void MemoBoxPart::formatBody() {
set<string>::iterator it;
string h_acronym = "";
string r_acronym = "";
string nrow = "";

int idx;
int cntrow;

it = _rows.begin();

while(it!= _rows.end()){
r_acronym = "";
nrow = "";
idx = 0;
cntrow = 0;
auto row = *it;
while(idx<row.size()){

    while(idx<row.size() && row.at(idx)==' ')
    idx++;

    char c = std::toupper(row.at(idx));
    nrow.push_back((char)c);
    r_acronym.push_back((char)c);
    if(!cntrow){
        //each first char from current row
        h_acronym.push_back((char)c);
        cntrow++;
    }
    idx++;
    while( idx<row.size() && row.at(idx)!= ' ' && row.at(idx)!='\n' ){
        nrow.push_back((char)row.at(idx));
    idx++;
    }


}
if(!_type_format)
    nrow.append(_sep).append(r_acronym);
    else
    nrow = r_acronym.append(_sep).append(nrow);
//cout << "Updating row " << nrow << endl;
*it = nrow;


it++;


}

//Update header
if(!_type_format)
  _header = "** " +  _header.append(_sep).append(h_acronym).append("\n");
else
  _header = "** " + h_acronym.append(_header).append("\n");


}

int MemoBoxPart::writeToFile(string outpath){
auto status =  ios::out | ios::app;
fstream ofs(outpath,status); //need open for append.
if(!ofs.fail()){

    ofs << _header << endl;
    for(auto &s : _rows)
        ofs << s << endl;
    ofs << endl; //line separator


}
ofs.close();
return 0;
}
