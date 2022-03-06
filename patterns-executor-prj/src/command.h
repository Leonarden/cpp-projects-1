/*
 * command.h
 *
 *  Created on: Jul 30, 2021
 *      Author: david
 */

#ifndef COMMAND_H_
#define COMMAND_H_
#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<map>
#include"Runnable.h"

enum typeState {
	SOLID=0,LIQUID=1,GAZ=2

};

typedef typeState STATE;
/*
class PhysChangeable {
public:
	virtual void toSolid();
	virtual void toLquid();
	virtual void toGaz();
private:

};
*/
class Product{
public:
Product();
Product(string n, double w, double sh, STATE cs, double ct, double cp){
	_name = n; _weight = w; _specificHeat = sh; _currentState = cs;
	_currentTemperature = ct; _currentPreasure = cp;
}
virtual ~Product(){}

protected:
	string _name;
	//physical properties
	double _weight; //in Kg
	double _specificHeat;
	STATE _currentState;
	double _currentTemperature;
    double _currentPreasure;

};

//,public PhysChangeable

class ProcessedProduct : public Product {
public:
ProcessedProduct();
ProcessedProduct(string n, double w, double sh, STATE cs, double ct, double cp):
		Product(n,w,sh,cs,ct,cp){

	_energyPhases = new vector<double>;
	_phases = new vector<STATE>;
	_currentIndex = -1;
	_energyRequired = 0.0;


}
virtual ~ProcessedProduct(){}

virtual double getEnergyRequired() { return _energyRequired; }
virtual double getTotalEnergyRequired();
virtual void toSolid();
virtual void toLiquid();
virtual void toGaz();

void setTransitionParams(map<STATE,double*> * trp){
	_transitionParams = trp;
}
int insTransitionParams (STATE s, double *ps);

//getters and setters
protected:
virtual void toState(STATE taget);

private:
	 double _deltaTemp; //variation from last temperature to current one
    double _deltaPreasure; //variation from last preasure to current one

    double _energyRequired; //in last transition
    vector<double> * _energyPhases;
    vector<STATE> * _phases;
    int _currentIndex;
    //ie:water= SOLID,{0,-50}
    //This means from 0 to margin err. -50, toSolid()= computenewtemperature: ( -50-0 ), setDelta
   //

    map<STATE,double*> *_transitionParams;

};

double ProcessedProduct::getTotalEnergyRequired(){
	double v = 0.0;
	vector<double>::iterator it;
	for(it=_energyPhases->begin();it<_energyPhases->end();it++)
		v =+ (*it);
	return v;
}
int  ProcessedProduct::insTransitionParams(STATE s, double * ps){

	int r = 0;

	_transitionParams->insert(pair<STATE,double*>(s,ps));

	return r;
}

void ProcessedProduct::toState(STATE target){
	double rt1=0,t1=0,t2=0,merror=0;
	try{
		t1 = _transitionParams->at(target)[0];
		merror = _transitionParams->at(target)[1];
		rt1 = t1 + merror;
		if(rt1<0){

			t2 =-1* (rand()% -1*(rt1));

		}else if(rt1>0){
			t2 = (rand()% 1*(rt1));
		}
		t2 = t2 + t1;
		_deltaTemp = _currentTemperature - t2;
		//if(_deltaTemp<0) _deltaTemp = -1*_deltaTemp;
		_currentTemperature = t2;

		_energyRequired = _deltaTemp * _specificHeat * _weight;

		_energyPhases->push_back(_energyRequired);
	    _phases->push_back(_currentState);
	    _currentState = target;

	    _currentIndex++;

	}catch(int e){
		cout<< "Something went wrong : #->" << e << endl;
	}

}


void ProcessedProduct::toSolid() {

	toState(SOLID);
}
void ProcessedProduct::toLiquid() {
	toState(LIQUID);
}
void ProcessedProduct::toGaz() {

	toState(GAZ);
}
//specific products
class Water : public ProcessedProduct {};
class Iron : public ProcessedProduct {};
//Oxygen?


/*
class Command {
public:
	virtual void execute();
	virtual void undo();
};
*/

//:public Command
class ProcProductCommand {
public:
	ProcProductCommand(ProcessedProduct * s=0,  void(ProcessedProduct::* trFunc)()=0){
		_product= s;
		_trFunc = trFunc;

	}
	virtual ~ProcProductCommand(){}
	virtual void execute();
	virtual void undo(){}
    //returns changed state product
	ProcessedProduct * getProduct(){ return _product; }

protected:
	ProcessedProduct * _product;
  void (ProcessedProduct::*_trFunc)();

};


 void ProcProductCommand::execute() {
     try{
    	  (_product->*_trFunc)();

     }catch(int e){
    	 cout << "Error executing command err: "<< e << " " << endl;
     }


}

//We use the composite pattern now for implementing MacroCommand

class MacroProcProductCommand: public ProcProductCommand {
public:
    MacroProcProductCommand(ProcessedProduct * s=0,  void(ProcessedProduct::* trFunc)()=0):ProcProductCommand(s,trFunc){


        initialize();
    }

	virtual void execute(vector<STATE> *ps);
	virtual void execute();
    void setPhases(vector<STATE> *phs){
    	_phases = phs;
    }
protected:
    void initialize();
private:


	vector<ProcProductCommand*> * _commands;
	vector<STATE> * _phases;


};
//
void MacroProcProductCommand::initialize() {

	_commands = new vector<ProcProductCommand*>;

	//State a = SOLID;
	ProcProductCommand * _command = new ProcProductCommand(_product , &ProcessedProduct::toSolid);

	_commands->push_back(_command);
    //LIQUID
	 _command = new ProcProductCommand(_product , &ProcessedProduct::toLiquid);
     _commands->push_back(_command);

    //GAZ
     _command = new ProcProductCommand(_product , &ProcessedProduct::toGaz);
     _commands->push_back(_command);



}

void MacroProcProductCommand::execute(vector<STATE> *ps){

	ProcProductCommand * _physCCommand;
	vector<STATE>::iterator it;
	int sol1=0, liq1 = 0, gaz1=0; //we will check non repeated transitions SOLID-SOLID, LIQUID-LIQUID
	bool repeated = false;
	try{


	for(it=ps->begin();it<ps->end();it++){

		switch(*it){
		case SOLID:
			if(sol1<1){
				_physCCommand = _commands->at(0);
				sol1++; liq1=0; gaz1=0;
				}else repeated = true;
			break;
		case LIQUID:
			if(liq1<1){
		     	_physCCommand = _commands->at(1);
							liq1++; sol1=0; gaz1=0;
			}else repeated = true;
			break;

		case GAZ:

			if(gaz1<1){
		     	_physCCommand = _commands->at(2);
							gaz1++; sol1=0; liq1=0;
			}else repeated = true;
			break;
		default:
			break;
		}

      if(!repeated){

    	  _physCCommand->execute();

		//this->_prod = _physCCommand->getProduct();
      }else
       repeated = false;
      }


	}catch(int e){

		cout << " Macrocommand: something went worng # " << e <<endl;
	}

}

void MacroProcProductCommand::execute(){
//
	if(_phases->size()>0){
		execute(_phases);
	}

	if(_trFunc){ //macro command was set with a function to execute

		ProcProductCommand::execute();
	}

}
//Invoker
class ProductProcessingUnit {
public:

	virtual void doProcess();
	void setProcProductCommand(ProcProductCommand * pProcCommand){ _procProdCommand = pProcCommand;}
private:
	ProcProductCommand * _procProdCommand;
};

class MetalProcessingUnit:public ProductProcessingUnit {

};



//

class ProcessedProductGenerator {


protected:

};

class CommandRun:public Runnable {
public:
	CommandRun(const char* n, const char* t, const char* d):Runnable(n,t,d){}
    virtual ~CommandRun(){}
	virtual int run();
};

int CommandRun::run() {
	int r = -1;

	map<STATE,double*> * transitions = new map<STATE,double*>();

	double trv[3][2]  = {{0,-5.0},{15,10},{100,5.0}};
	STATE arr[3] = {SOLID,LIQUID,GAZ};

	for(int i=0;i<3;i++){
		//pair<STATE,double[2]>(
		transitions->emplace(arr[i],trv[i]);
	}



    // Water, 1kg, 4.2KJ / KgC, Liquid, 20C, 0preasure
    ProcessedProduct * water = new ProcessedProduct("Water",1,4.2,LIQUID,15,0);

    water->setTransitionParams(transitions);





	try{

	    ProcProductCommand * wcommand = new ProcProductCommand(water,&ProcessedProduct::toGaz);


	    wcommand->execute();


	    ProcessedProduct * vapour =((ProcProductCommand*)wcommand)->getProduct();



		//assert true
		if(vapour == water)
		  cout << "water to vapour " << endl;

		cout << "1- Energy spent in KJoule " << vapour->getEnergyRequired() << endl;


		wcommand = new ProcProductCommand(vapour,&ProcessedProduct::toLiquid);


		wcommand->execute();

		if(vapour == water)
				  cout << " vapour to water " << endl;

		cout << "2- Energy spent in KJoule " << water->getEnergyRequired() << endl;



	    ProcessedProduct * ice =((ProcProductCommand*)wcommand)->getProduct();

    	wcommand = new ProcProductCommand(ice,&ProcessedProduct::toSolid);

		wcommand->execute();

		if(water == ice)
					  cout << " water to ice " << endl;

			cout << "3- Energy spent in KJoule " << ice->getEnergyRequired() << endl;



       //Test macro command

		wcommand = new MacroProcProductCommand(ice,0);

		((MacroProcProductCommand*)wcommand)->setPhases(new vector<STATE>({LIQUID,GAZ}));

		wcommand->execute();

	//	cout << " current STATE :" << ice->_currentState << " energyRequired:" << ice->_energyRequired << endl;
		cout << " total energy spent: " << ice->getTotalEnergyRequired() << endl;






		r=0;
	}catch(int ex){

		r=ex;
	}

	return r;
}




#endif /* COMMAND_H_ */
