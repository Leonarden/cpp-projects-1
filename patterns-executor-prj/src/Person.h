/*
 * Person.h
 *
 *  Created on: Jul 29, 2021
 *      Author: david
 */

#ifndef PERSON_H_
#define PERSON_H_
#include<string>

class Person {

public:
Person() {}
Person(int id,string n, int a){
	 _id = id;	_name = n; _age = a;
}
Person(int id,string n, int a, int shot, double temp){
  _id = id;	_name = n; _age = a; _shotNum = shot; _temperature = temp;
}
virtual ~Person();
virtual string tostring();

int _id;
string _name;
int _age;
int _shotNum;
double _temperature;


};

 Person::~Person() {  }
 string Person::tostring(){
    string s1( "Patient: "+_id );
    s1.append(" name: ");
    s1.append(_name);
    s1.append(" age: " +_age );
    s1.append(" shotNum:" + _shotNum);//.append(_name) );//.append( " age:").append(_age ).append(" shotNum:").append( _shotNum));

   // s1.append( "Patient: ").append(""+_id ).append( " name: ").append( _name ).append( " age:").append(_age ).append(" shotNum:").append( _shotNum);


	return s1;
 }




#endif /* PERSON_H_ */
