/*
 * visitor.h
 *
 *  Created on: Jul 27, 2021
 *      Author: david
 */

#ifndef VISITOR_H_
#define VISITOR_H_
#include <iostream>
#include <string>
#include <vector>
#include "Runnable.h"

using namespace std;
class Visitor;
//Question
class Question {
public:
	Question(vector<string> &words):_words(words){
		   _end = " ? ";
			vector<string>::iterator it;
			for(it=_words.begin(); it<_words.end(); it++)
				_o.append(*it);
		  _o.append(_end);
	}
	virtual ~Question(){}
	virtual void accept(Visitor * v);
	virtual string ask();
protected:
	vector<string>& _words;
	string _o;
	string _end;
};


class WHAT:public Question {
public:
	WHAT(vector<string>& wds):Question(wds){}
	virtual ~WHAT(){}
	virtual string askWhat();
	virtual void accept(Visitor *v);
protected:
};


class HOW:public Question {
public:
	HOW(vector<string>& wds):Question(wds){}
	virtual ~HOW(){}
	virtual string askHow();
	virtual void accept(Visitor *v);
protected:

};

//Visitor
class Visitor {
public:
   virtual void visit(Question* q){
	   cout <<  q->ask() << " " << endl;
   }
   virtual void visit(WHAT* what){}
   virtual void visit(HOW* how){}


};

class MentalProcess : public Visitor {
public:

	virtual ~MentalProcess() {}

};


class JOYFUL: public MentalProcess {
public:
	virtual ~JOYFUL() {}
	 virtual void visit(WHAT* what);
	  virtual void visit(HOW* how);


};

class SAD: public MentalProcess {
public:
	virtual ~SAD() {}
	virtual void visit(WHAT* what);
	 virtual void visit(HOW* how);
};


//Implementation

string Question::ask(){
	string s = "Question:" + _o ;
	return s;
}

void Question::accept(Visitor * v){
	v->visit(this);
}


string WHAT::askWhat(){
	string s = "WHAT ";
	s = s + this->_o;
	return s;
}

void WHAT::accept(Visitor * v){
	v->visit(this);
}


string HOW::askHow(){
	string * s = new string("HOW ");
	s->append( this->_o);
	return *s;
}

void HOW::accept(Visitor * v){
	v->visit(this);
}

void JOYFUL::visit(WHAT* w){

	string *s = new string;
	s->append(" JOY, JOY...I wonder..." + w->askWhat());

	cout << *s << endl;
}

void JOYFUL::visit(HOW* w){

	string *s = new string;
	s->append(" JOY, JOY...I wonder..." + w->askHow());

	cout << *s << endl;
}

void SAD::visit(WHAT* w){
	string *s = new string;
	s->append(" Sad, sad...I wonder..." + w->askWhat());

	cout << *s << endl;
}

void SAD::visit(HOW* w){

	string *s = new string;
	s->append(" Sad, sad...I wonder..." + w->askHow());

	cout << *s << endl;
}

class VisitorRun : public Runnable {
public:
    VisitorRun(const char* n,const char* t,const char* d):Runnable(n,t,d){}
	virtual ~VisitorRun(){}
    virtual int run();




};

int VisitorRun::run(){
	int st = 0;

	vector<string> words;
	words.push_back("the secret");
	words.push_back("of existence");
	//visitors
	Visitor * joyful = new JOYFUL;
	Visitor * sad = new SAD;

	//
	WHAT what(words);
	HOW how(words);

	try{

		cout << "Visiting questions with JOYFUL Mental process" << endl;
		what.accept(joyful); how.accept(joyful);


		string a = "N";
		while(1){
		cout << "Continue (Y/N)?";
		cin >> a;
		if(a == "Y"){
			cout << "Visiting questions with SAD Mental process" << endl;
					what.accept(sad); how.accept(sad);

					break;
		  }else if(a == "N")
			     break;


		}


	}catch(int e){
		st = e;
	}


	return st;
}





#endif /* VISITOR_H_ */
