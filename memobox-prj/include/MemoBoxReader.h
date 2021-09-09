#ifndef MEMOBOXREADER_H
#define MEMOBOXREADER_H
#include "MemoBoxPart.h"
#include <fstream>

class MemoBoxReader
{
    public:
        MemoBoxReader() = default;
        virtual ~MemoBoxReader();
        void setFilepath(string fpath){
            filepath = fpath;
        }
        void init();
        MemoBoxPart readNextPart();
        int counter =0;
    protected:
    private:
        string filepath;
        ifstream *iof;

};

#endif // MEMOBOXREADER_H
