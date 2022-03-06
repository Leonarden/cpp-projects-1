/*
 * observer.h
 *
 *  Created on: Jul 28, 2021
 *      Author: david
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <iostream>
#include <deque>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include "Runnable.h"
#include "Person.h"

using namespace std;

class Observer;
//template <class T>
class Subject {

public:
	Subject(){
		_observers = new deque<Observer*>;
	}
	virtual ~Subject() {}
	virtual int attach(Observer * o);
	virtual int detach(Observer * o);
	virtual int notify();

protected:
	deque<Observer*> * _observers;

};


class Observer {
public:
	Observer(){}
	Observer(Subject* s);
	virtual ~Observer(){
	 cout<< "Deleting observer " << endl;
	_subject->detach(this);
	}
	virtual int update(Subject * s);
	virtual void setSubject(Subject * s);
protected:
	int _nupdate;
	Subject * _subject;

};
//implementation
Observer::Observer(Subject * s){
	_subject = s;
	if(_subject!=NULL)
		_subject->attach(this);
}
void Observer::setSubject(Subject * s){
	_subject = s;
		if(_subject!=NULL)
			_subject->attach(this);

}

int Observer::update(Subject * s){
	int r =0;
	if(s==_subject){
		//_subject->getData()
		_nupdate++;
		r = _nupdate;
	}
	return r;
}
//Subject implementation
int Subject::attach(Observer * o){
	_observers->push_back(o);
}

int Subject::detach(Observer * o){
	int r=0;
	deque<Observer*>::iterator it;
	for(it=_observers->begin();it<_observers->end();it++)
		if((*it) == o){
		 _observers->erase(it);
		 	 r = 1;
		 	 break;
          }

	return r;
}
int Subject::notify(){
	int r=0,s=0;
	deque<Observer*>::iterator it;
	vector<Observer*> * toremove = new vector<Observer*>;
	for(it=_observers->begin();it<_observers->end();it++){
		s = ((Observer*)(*it))->update(this);

		r =+s;
		if(s>0) {//has received
			toremove->push_back(*it);
		}
	}

	vector<Observer*>::iterator rit;
	Observer * obs;
	while(toremove->size()>0){
		rit = toremove->begin();
		obs = *rit;
		toremove->erase(rit);
		delete obs;
	}


	return r;
}



class Appointment {
public:
	Appointment(){}
	virtual ~Appointment(){}
	string _code;
	time_t _date;
	virtual int compare(Appointment* a1);
};
int Appointment::compare(Appointment* a1){
	int c = -1;
	if(_code==a1->_code)
		c++;
	if(_date== a1->_date)
		c++;
	return c;
}

class AppointmentSubject:public Subject {
public:
	AppointmentSubject():Subject(){

	}
	AppointmentSubject(deque<Appointment*>* apms,int mode){

		_appointments = apms;
		_mode = mode;
		if(_appointments->size()>0)
				_currentAppointment = getNextAppointment();

	}
	virtual ~AppointmentSubject(){}
	void setAppointments(deque<Appointment*>* apms){
		_appointments = apms;
	}
	void setMode(int m){ _mode = m; }
	virtual int appointmentNotification();
	virtual Appointment * getNextAppointment();
	Appointment * _currentAppointment;
protected:
  int removeAppointment(Appointment * toremove);

  deque<Appointment*>* _appointments;
  int _appointmentReceived =0;
  int _mode = 1;
};

//mode=0 (sequential), mode=1 (random)
Appointment * AppointmentSubject::getNextAppointment(){
	Appointment * a;
	if(_mode){
		int idx = rand() % _appointments->size();
		a = _appointments->at(idx);

	}else{

		a = _appointments->at(0);

	}

	return a;

}

int AppointmentSubject::removeAppointment(Appointment* ap){
	deque<Appointment*>::iterator it;
	for(it=_appointments->begin();it<_appointments->end();it++)
		if((*it) == ap ){
			_appointments->erase(it);
			return 1;
		}
  return 0;
}
//
int AppointmentSubject::appointmentNotification() {
int totalReceived = 0;
int failedReception = 0;

	try{
		while(_observers->size()>0 && failedReception<100){
			_currentAppointment = getNextAppointment();

			_appointmentReceived = this->notify();

			if(_appointmentReceived>0){
				//check if received by >1
				removeAppointment(_currentAppointment);
				totalReceived =+ _appointmentReceived;
			}else{
				failedReception++;
			}

		}
	}catch(int e){
		cout << " Exception # " << e << endl;
	}

	return totalReceived;
}


class Appointee:public Person, public Observer {
public:
	Appointee(int id, string name,int age,AppointmentSubject* as){
		_id = id; _name = name; _age = age;
	   _subject = as;
	   _waited = std::time(nullptr);
	    _appointment = NULL;
	}
	Appointee(int id, string name, int age,AppointmentSubject* as, Appointment * a){
		Appointee(id,name,age,as);
		_appointment = a;

	}
	void setAppointment(Appointment * ap){
		_appointment = ap;
	}

   virtual ~Appointee(){ _subject->detach(this);}
   virtual int update(Subject* s);

protected:
	time_t _waited;
    Appointment * _appointment;

};

int Appointee::update(Subject * s){
	int r = 0;
	if(_subject==s &&
		(_appointment->compare(((AppointmentSubject*)_subject)->_currentAppointment) > 0)){
			r = 1;
			cout << " Observer Appointee name: " << this->_name << " Receive appointment confirm " << endl;
			cout << " For appointment:(code) " << _appointment->_code << endl;


	}
	return r;
}

template<class T>
class Generator {
public:
	virtual T * generate() = 0;
	virtual deque<T*>* generate(int num){}
};

class AppointmentGenerator : public Generator<Appointment> {
public:

	virtual ~AppointmentGenerator(){

	}
	virtual Appointment* generate();
	virtual deque<Appointment*>* generate(int num);

	void initParams(vector<string>* prefixes,int offset){
		_prefixes = prefixes; _offset = offset;
		_noMoreCodes = false;
		_indexpref=0;
		_indexoff=1;

	}
	static AppointmentGenerator * getInstance(){
		if(!_instance){
			_instance = new AppointmentGenerator;
		}
		return _instance;
	}

protected:
	static AppointmentGenerator * _instance;
	AppointmentGenerator(){
		 _indexpref=0;
		  _indexoff=1;
		  _offset=10;
		_noMoreCodes=false;
		_prefixes = NULL;
	}
	virtual string generateCode();
	vector<string> * _prefixes;
	int _offset;
	int _indexpref;
	int _indexoff;
    bool _noMoreCodes;

};
 AppointmentGenerator * AppointmentGenerator::_instance=0;




string AppointmentGenerator::generateCode(){
	string code;
	string sidx;
	if(_indexpref>= _prefixes->size()){
		_noMoreCodes = true;
		return NULL;
	}else{
		if(_indexoff>_offset && _indexpref<_prefixes->size()-1){
			_indexoff = 1;
			_indexpref++;
		}else{

			 _indexoff++;
		 }


	  code = _prefixes->at(_indexpref);
	  code.append("-");
      sidx = "" + to_string(_indexoff);
	  code = code +sidx;
	  return code; //pass to upper-case
	}
}

Appointment * AppointmentGenerator::generate(){
	Appointment * apt = new Appointment();

	string c = generateCode();
	if( _noMoreCodes)
		return NULL;
	else{
		apt->_code = c;
		apt->_date = std::time(nullptr);

	}

	return apt;
}

deque<Appointment*> * AppointmentGenerator::generate(int num){
	deque<Appointment*> *appointments = new deque<Appointment*>;
	Appointment * apt;
	for(int i=0;i<num;i++){
		apt = generate();
		appointments->push_back(apt);
	}


	return appointments;
}

class AppointeeGenerator: public Generator<Appointee> {
public:
	static AppointeeGenerator * getInstance();
	virtual ~AppointeeGenerator(){}
	virtual Appointee* generate();
	virtual deque<Appointee*>* generate( int num);

protected:
	static AppointeeGenerator * _instance;
	AppointeeGenerator(){
		_names = new vector<string>({"Mark","Sarah","Alice","John","Sharon","Paul"});
		_number = 0;

	}
	static vector<string> * _names;
    static int _number;
};

AppointeeGenerator* AppointeeGenerator::_instance=0;
vector<string>* AppointeeGenerator::_names;
int  AppointeeGenerator::_number=0;

AppointeeGenerator* AppointeeGenerator::getInstance() {
	if(_instance==NULL){
		_instance = new AppointeeGenerator;

	}
	return _instance;
}

Appointee* AppointeeGenerator::generate() {
	Appointee* apt = NULL;
	if(_names->size()>0){
		string name = _names->at(0);
		int age = rand()%75;
		if(age<5) age = 11;
		_number++;
		apt = new Appointee(_number,name,age,NULL); //Initially created with subject NULL

		vector<string>::iterator it = _names->begin();
		_names->erase(it);

	}

	return apt;
}

deque<Appointee*>* AppointeeGenerator::generate(int num) {
	deque<Appointee*>* apts = new deque<Appointee*>;
	Appointee* apt;
	for(int i=0;i<num;i++){
		apt = generate();
		if(apt==NULL)
			break;
		apts->push_back(apt);
	}

	return apts;
}

class ObserverRun:public Runnable {
public:
	ObserverRun(const char* n, const char* t, const char* d):Runnable(n,t,d){}
	virtual ~ObserverRun() {}
	virtual int run();

};

int ObserverRun::run(){

	vector<string>* prefixes= new vector<string>({"AA","BB","CC","DD"});
	AppointmentGenerator * apmGen;
    AppointeeGenerator * apteGen;
	deque<Appointment*> * appointments;
	deque<Appointee*> * appointees;
	Subject * subject;
    int ret = 0;
	try{
        apmGen = AppointmentGenerator::getInstance();
		apmGen->initParams(prefixes,4);
		apteGen = AppointeeGenerator::getInstance();

		appointments = apmGen->generate(10);

		subject = new AppointmentSubject(appointments,1);
		//Generating appointees
		appointees = apteGen->generate(5);
		deque<Appointee*>::iterator ait;
		Appointment * a;
		Appointee * apt;
		for(ait=appointees->begin();ait< appointees->end();ait++){
			apt = *ait;
			a = ((AppointmentSubject*) subject)->getNextAppointment();
			apt->setAppointment(a);
			apt->setSubject(subject);
		}


		//ret = subject->notify();

		ret = ((AppointmentSubject*) subject)->appointmentNotification();

        cout << " Subject status:" << ret << endl;

	}catch(int e){
		cout << " Exception in run # " << e << endl;
		ret = e;
	}

	return ret;

}





#endif /* OBSERVER_H_ */
