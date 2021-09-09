#ifndef MEMOBOX_H
#define MEMOBOX_H
#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
#include <exception>
#include "MemoBoxPart.h"
#include "MemoBoxReader.h"

class MemoBox
{
    public:
        MemoBox();
        virtual ~MemoBox();
        int generate();
        void setInParams(string infpath) {
           _infpath = infpath;
        }
        void setOutParams(string oprefix, string fextension, bool is_sequ) {
         _oprefix = oprefix;
         _fext = fextension;
         _issequence = is_sequ;
        }
    protected:
    private:
        string _infpath;
        string _oprefix;
        string _fext;
        bool _issequence;

};

#endif // MEMOBOX_H
