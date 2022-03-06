/*
 * state.h
 *
 *  Created on: Jul 26, 2021
 *      Author: david
 */

#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include "Runnable.h"

using namespace std;
class State;
class RESET;
class Machine
{ static int LIMIT;
  int errorCount = 0;
  State *current;
  public:
    Machine();
    virtual ~Machine(){ }
    void setErrorCount(int v){
    	errorCount = v;
    }
    int getErrorCount() {return errorCount;}
    State * getCurrent();
    virtual void setCurrent(State *s);
    void on();
    void off();
    void reset();
};
int Machine::LIMIT = 10;

class State
{
	enum PenaltyType
	    {
	       ONPe = 10, OFFPe= 5, RESPe = 20
	    };
  public:
	State(){}
	virtual ~State(){}

	virtual int on(Machine *m)
    {
        cout << "   already ON\n";
        return ONPe;
    }
    virtual int off(Machine *m)
    {
        cout << "   already OFF\n";
        return OFFPe;
    }

    virtual int reset(Machine *m)
        {
            cout << "   already on RESET\n";
            return RESPe;
        }

};
State * Machine::getCurrent() {
	return current;
}
void Machine::on()
{
 errorCount = errorCount + current->on(this);
}

void Machine::off()
{
	errorCount = errorCount + current->off(this);
}
void Machine::reset(){
	errorCount = errorCount +	current->reset(this);
}



class ON: public State
{
  public:
    ON()
    {
        cout << "   ON-ctor ";
    }
    ~ON()
    {
        cout << "   dtor-ON\n";
    }
   virtual int off(Machine *m);
};

class OFF: public State
{
  public:
    OFF()
    {
        cout << "   OFF-ctor ";
    }
    ~OFF()
    {
        cout << "   dtor-OFF\n";
    }
    virtual int on(Machine *m)
    {
        cout << "   going from OFF to ON";
        m->setCurrent(new ON());
       // delete this;
       return 0;
    }
};

int ON::off(Machine*m){
	  cout << "   going from ON to OFF";
	  m->setCurrent((State*)new OFF());
	  //delete this;
	  return 0;
}

class RESET: public State
{
  public:
    RESET()
    {
        cout << "   RESET-ctor "<<endl;
    }
    ~RESET()
    {
        cout << "   dtor-RESET\n";
    }
    virtual int reset(Machine *m)
    {
        cout << "   Reseting Machine ......" << endl;
        m->setErrorCount(-1);
        m->setCurrent(new OFF());
       // delete this;

        return 0;
    }
};


Machine::Machine()
{
  current = new OFF();
  cout << '\n';
}

void Machine::setCurrent(State* s) {

	    	if(errorCount>Machine::LIMIT){

	    		current = (State*) new RESET();
	    		this->reset();
	    	}
	    	else

	        	current = s;

}




class StateRun : public Runnable {
public:
	StateRun(const char* n,const char* t, const char* d):Runnable(n,t,d){}
   ~StateRun(){}
	int run();
private:
};

int StateRun::run(){
	int status = 0;

	Machine fsm;

	int nreset=0,num;
	try{

		  while (1)
		  {

			cout << "Enter 0/1: (2 to exit) :";

		    cin >> num;
		    if(num==2)
		    	break;
		    if(num>1 || num<0)
		    	continue;
		    if(num){
		    	cout << "Turning machine on:" << endl;
		    	fsm.on();
		    }else{
		    	cout << "Turning machine off:" << endl;
		    	fsm.off();
		    }
		  }

		  cout << " Testing reset..." << endl;

           int j = 0;

           while(1){
        	  num = rand()% 2;

        	  if(num==0)
        		  fsm.off();
        	  if(num==1)
        		  fsm.on();


              if(fsm.getErrorCount()<0)
           	   cout << " Machine executed a reset-> " << nreset++ << " " << endl;

             if(j>99)
            	 break;
        	  j++;
           }






	}catch(int e){
		status = e;
	}

	return status;
}




#endif /* STATE_H_ */
