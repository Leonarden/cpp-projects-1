#ifndef MEMOBOXPART_H
#define MEMOBOXPART_H
#include <set>
#include<string>
#include <sstream>
#include <fstream>

using namespace std;

class MemoBoxPart
{
    public:
        MemoBoxPart();
        virtual ~MemoBoxPart();
        void setTypeFormat(int type) {
            _type_format = type;
        }
        void format();
        int writeToFile(string outpath);
        void setHeader(string header) {
            _header = header;
        }
        void addRow(string row){
            _rows.insert(row);
        }
    protected:
        void formatBody();
    private:
    string _header;
    set<string> _rows;
    string _sep;
    int _type_format=0;

};

#endif // MEMOBOXPART_H
