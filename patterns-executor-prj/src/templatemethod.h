/*
 * templatemethod.h
 *
 *  Created on: Jul 27, 2021
 *      Author: david
 */

#ifndef TEMPLATEMETHOD_H_
#define TEMPLATEMETHOD_H_
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "stdlib.h"
#include "Person.h"
#include "Runnable.h"

using namespace std;


class TypeVaccine {
public:
	string _name = "unkn";
	double _amount = 0.0;
	double _cost = 0.0;
    TypeVaccine(){}
	TypeVaccine(string n, double a, double c){
		_name = n; _amount = a; _cost = c;
	}
virtual ~TypeVaccine() {}
};

class TypeVaccA: public TypeVaccine {
public:
	string _name = "Pfiz";
	double _amount = 6.1; //mliters
	double _cost = 30; //$30
};
class TypeVaccB: public TypeVaccine {
public:
	string _name = "Ast";
	double _amount = 5.1; //mliters
	double _cost = 20; //$20

};



//template<class TypeVaccine>
class Vaccines {
public:
virtual ~Vaccines() {}
	vector<TypeVaccine*> * getVaccines(){return _vaccines; }
	void setVaccines(vector<TypeVaccine*> * vaccines) { _vaccines = vaccines;}
private:
	vector<TypeVaccine*> * _vaccines;
};


class Vaccination {
public:
	enum ShotOrder {
		FIRST=0, SECOND=1
	};
	Vaccination( vector<Person*> *persons[2],Vaccines * vacc);

	Vaccination(vector<Person*> *firstShot, vector<Person*> *secondShot,Vaccines * vacc){

		_patients[FIRST] = firstShot;
		_patients[SECOND] = secondShot;
		_vaccines = vacc;
		_restRoom = new vector<Person*>;
		_infected = new vector<Person*>;
	}
	virtual ~Vaccination();
    void vaccinate(int order);
	virtual bool checkIfInfection(Person *p,int order){ return false;}
	virtual void inject(Person *p,int order){}
	virtual void patientRest(Person *p,int order){}

protected:
	vector<Person*> * *_patients;
	vector<Person*> * _restRoom;
	vector<Person*> * _infected;
    Vaccines *_vaccines;
};
Vaccination::Vaccination( vector<Person*> **persons,Vaccines * vacc){
		_patients = persons;
		this->_vaccines = vacc;
		_restRoom = new vector<Person*>;
		_infected = new vector<Person*>;
	}
Vaccination::~Vaccination() {
	delete this;
}
//Temmplte method
void Vaccination::vaccinate(int order){
int ninfected = 0; int nshots = 0;

	vector<Person*>::iterator it;

	for(it=_patients[order]->begin();it<_patients[order]->end();it++){
		if(! checkIfInfection( *it,order )){
			inject(*it,order);
			patientRest(*it,order);
			nshots++;
		}else{
		 Person * p = *it;
		 string ord =	(p->_shotNum>0)?" Second": " First";
			cout << " Person:" << p->_id << " Name: " << p->_name << " Age:"<<p->_age << endl;
			cout << " Is infected!" << " in his/her " << ord <<  " shot" << endl;
			cout << " Preparing for hospital " << endl;
			this->_infected->push_back(*it);
			ninfected++;
		}

	}

	cout << " Total: " << (ninfected+nshots) << endl;
	cout << " Vaccinated: " << nshots << endl;
	cout << " Infected: " << ninfected << endl;

}

// 0-18 years old

class UnderAgeVaccination : public Vaccination {
public:
	UnderAgeVaccination( vector<Person*> *persons[],Vaccines* vacc):Vaccination(persons,vacc) {}
	UnderAgeVaccination(vector<Person*> *firstShot, vector<Person*> *secondShot,Vaccines* vacc):Vaccination(firstShot,secondShot,vacc){}
	virtual ~UnderAgeVaccination() {}
	virtual bool checkIfInfection(Person*p, int order);
	virtual void inject(Person *p,int order);
	virtual void patientRest(Person *p,int order);

};

bool UnderAgeVaccination::checkIfInfection(Person *p,int order){
	double TEMP = 37.6;
	bool infected = false;
	if(order==this->FIRST){
		infected = (p->_temperature>TEMP);
		cout << "Under age, first shot: id= "<< p->_id <<" name="<< p->_name << " temperature= " << p->_temperature << " so: infected=" << infected << endl;
	}else{
		TEMP = 36.7;

		infected = p->_temperature>TEMP;
		cout << "Under age, second shot: id= "<< p->_id <<" name="<< p->_name << " temperature= " << p->_temperature << " so: infected=" << infected << endl;

	}
	return infected;
}
void UnderAgeVaccination::inject(Person* p,int order){
	//we are going to consume vaccines

	string ordstr;
	ordstr.append((order==this->FIRST? " first " : " second "));
    if(_vaccines->getVaccines()->size()>0){
	TypeVaccine * tva = _vaccines->getVaccines()->front();
	cout<< " Injecting Under age patient: " << p->_id << " Name:" << p->_name << " Age:"<<p->_age << " in his " << ordstr << "  shot"<< endl;
	cout << " Vaccine used: " << tva->_name << endl;
	p->_shotNum++;
	_vaccines->getVaccines()->erase(_vaccines->getVaccines()->begin());
    }else{
    	cout<< " Could not inject!: Under age patient: " << p->_id << " Name:" << p->_name << " Age:"<<p->_age << " in his " << ordstr << "  shot"<< endl;
    	cout << " No more vaccine " << endl;
    }
}

void UnderAgeVaccination::patientRest(Person* p,int order){
	string ordstr;
	ordstr = order==this->FIRST? " first " : " second ";
	cout<< "  Under age patient: " << p->_id << " Name:" << p->_name << " in his " << ordstr << " shot"<< endl;
	cout << " Passes to the rest room " << endl;
	this->_restRoom->push_back(p);

	Person * po = this->_restRoom->front();

    cout<< "  Under age patient: " << po->_id << " Name:" << po->_name << " in his " << po->_shotNum << " shot"<< " exits the rest room "<<endl;

    if(this->_restRoom->size()>0)
        	this->_restRoom->erase(this->_restRoom->begin());

}


// 18<= years old

class AdultVaccination : public Vaccination {
public:
	AdultVaccination( vector<Person*> *persons[],Vaccines* vacc):Vaccination(persons,vacc) {}
	AdultVaccination(vector<Person*> *firstShot, vector<Person*> *secondShot,Vaccines* vacc):Vaccination(firstShot,secondShot,vacc){}
	virtual ~AdultVaccination() {}
	virtual bool checkIfInfection(Person*p, int order);
	virtual void inject(Person *p,int order);
	virtual void patientRest(Person *p,int order);

};

bool AdultVaccination::checkIfInfection(Person *p,int order){
	int TEMP = 37.0;
	bool infected = false;
	if(order==this->FIRST){
		infected = p->_temperature>TEMP;
		cout <<" Adult , first shot: id= "<< p->_id <<" name="<< p->_name << " temperature= " << p->_temperature << " so: infected=" << infected << endl;

	}else{
		TEMP = 36.5;

		infected = p->_temperature>TEMP;
		cout << "Adult, second shot: id= "<< p->_id <<" name="<< p->_name << " temperature= " << p->_temperature << " so: infected=" << infected << endl;

	}
	return infected;
}
void AdultVaccination::inject(Person* p,int order){
	//we are going to consume vaccines

	string ordstr = order==this->FIRST? " first " : " second ";
	if(_vaccines->getVaccines()->size()>0){
		TypeVaccine * tva = _vaccines->getVaccines()->front();
		cout<< " Injecting Adult patient: " << p->_id << " Name:" << p->_name << " Age:"<<p->_age <<" in his " << ordstr << "  shot"<< endl;
		cout << " Vaccine used: " << tva->_name << endl;
		p->_shotNum++;
		_vaccines->getVaccines()->erase(_vaccines->getVaccines()->begin());
	    }else{
	    	cout<< " Could not inject!: Adult patient: " << p->_id << " Name:" << p->_name << " Age:"<<p->_age << " in his " << ordstr << "  shot"<< endl;
	    	cout << " No more vaccine " << endl;
	    }
}

void AdultVaccination::patientRest(Person* p,int order){
	string ordstr = order==this->FIRST? " first " : " second ";
	cout<< "  Adult patient: " << p->_id << " Name:" << p->_name << " in his " << ordstr << " shot"<< endl;
	cout << " Passes to the rest room " << endl;
	this->_restRoom->push_back(p);
	Person * po = this->_restRoom->front();


    cout<< " Adult patient: " << po->_id << " Name:" << po->_name << " in his " << po->_shotNum << " shot"<< " exits the rest room "<<endl;

    if(this->_restRoom->size()>0)
    	this->_restRoom->erase(this->_restRoom->begin());

}


class PersonGenerator {
protected:
virtual	Person * generate(int minage,int maxage);
public:
virtual	vector<Person *> * generateAdults(int n,int maxage);
virtual vector<Person*> *  generateUnderAge(int n,int minage);
};

Person* PersonGenerator::generate(int minage, int maxage){
	string names [] = {"John","Mike","Sara","Tom","Alice","Bertha","Sony","Martha","Julie","Mary","Sam"};
	int i1 = (int)rand()%names->length();
	int i2 = rand()% maxage;
	double i3 = (double) (rand()% 42);
	int i4 = (int) rand() % 2;
	if(i2<minage) i2 = minage;
	if(i3<36.2) i3 = 36.4;

	Person * p = new Person;
	p->_name = names[i1];
	p->_age = i2; p->_temperature = i3; p->_shotNum = i4;
	return p;
}

vector<Person *> * PersonGenerator::generateAdults(int n,int maxage){
	vector<Person*> * adults = new vector<Person*>;
	Person* p;
	for(int i=0;i<n;i++){
	 p = this->generate(18,maxage);
	 p->_id = i;
		adults->push_back(p);
	}
	return adults;
}

vector<Person *> * PersonGenerator::generateUnderAge(int n,int minage){
	vector<Person*> * uage = new vector<Person*>;
		Person* p;
		for(int i=0;i<n;i++){
		 p = this->generate(minage,17);
		 p->_id = i+100;
			uage->push_back(p);
		}
		return uage;
}

class FirstSecondShotPersonGenerator{
public:
	FirstSecondShotPersonGenerator(){
		_pgenerator = new PersonGenerator;
	}
virtual	vector<Person *> * * generateFirstSecondShotAdults(int n,int maxage){
	return generateFirstSecondShot(n,maxage,true);
}
virtual	vector<Person *> * * generateFirstSecondShotUnderAge(int n,int minage){
	return generateFirstSecondShot(n,minage,false);
}

protected:
virtual	vector<Person *> * * generateFirstSecondShot(int n, int age, bool isAdults);
	PersonGenerator * _pgenerator;
};
vector<Person *> * * FirstSecondShotPersonGenerator::generateFirstSecondShot(int n,int age, bool isAdults){
	vector<Person *> * * fsShot = new vector<Person*> *;
	vector<Person *> * firstShot = new vector<Person *>;
	vector<Person *> * secondShot = new vector<Person *>;

	vector<Person *> * persons;

	//delete persons;

	if(isAdults)
	 persons = _pgenerator->generateAdults(n,age);
	else{

		persons = _pgenerator->generateUnderAge(n,age);
	}

	vector<Person *>::iterator it;
	for(it=persons->begin();it<persons->end();it++){
		if((*it)->_shotNum>0){
			secondShot->push_back((*it));
		}else{
			firstShot->push_back((*it));
		}
	}
	fsShot[0] = firstShot;

	fsShot[1] = secondShot;

	return fsShot;
}


class VaccineGenerator {
public:
	virtual ~VaccineGenerator(){}
 virtual	Vaccines* generateVaccines(int number,TypeVaccine *vname);

};

Vaccines* VaccineGenerator::generateVaccines(int number,TypeVaccine *vname){
	vector<TypeVaccine*>* tvaccines = new vector<TypeVaccine*>;
	TypeVaccine* tva;
	int i = 0;
	if(vname->_name.compare("Pfiz")>0){
		while(i++<number){
			tva = new TypeVaccA;
			tvaccines->push_back(tva);

		}
	}else
		while(i++<number){
			tva = new TypeVaccB;
			tvaccines->push_back(tva);


		}
	Vaccines *vaccines = new Vaccines;
	vaccines->setVaccines(tvaccines);

	return vaccines;

}



class TemplateMethodRun:public Runnable {
public:
	TemplateMethodRun(const char* n, const char* t, const char* d):Runnable(n,t,d){}
	virtual ~TemplateMethodRun() {}
	int run();

};

int TemplateMethodRun::run() {

	FirstSecondShotPersonGenerator *  firstSecondPGenerator = new FirstSecondShotPersonGenerator;
	VaccineGenerator * vaccGenerator = new VaccineGenerator;

	//
	Vaccination * adultVaccination;
	Vaccination * underAgeVaccination;
	int st = 0;

	try{

       TypeVaccine* tva;
       TypeVaccine* tvb;
       tva = new TypeVaccA;
       tvb = new TypeVaccB;
		adultVaccination = new AdultVaccination(
						firstSecondPGenerator->generateFirstSecondShotAdults(5,75),
						vaccGenerator->generateVaccines(5,tva));



		underAgeVaccination = new UnderAgeVaccination(
				firstSecondPGenerator->generateFirstSecondShotUnderAge(5,2),
				vaccGenerator->generateVaccines(5,tvb));


		//template method invocation
		adultVaccination->vaccinate(adultVaccination->FIRST);


		//
		underAgeVaccination->vaccinate(underAgeVaccination->FIRST);


		//template method invocation
		adultVaccination->vaccinate(adultVaccination->SECOND);

		//
		underAgeVaccination->vaccinate(underAgeVaccination->SECOND);





	}catch(int e){
		st = e;
		cout << "Exception : " << e << endl;
	}

	return st;

}



#endif /* TEMPLATEMETHOD_H_ */
