/*
 * Meta.h
 *
 *  Created on: Jul 23, 2021
 *      Author: david
 */

#ifndef META_H_
#define META_H_
#include<string.h>
#include<stdlib.h>

class Meta {
public:
	Meta(const char* n, const char* t, const char* d) {
		_name = (char*) malloc(sizeof(n)*sizeof(char)); _type = (char*)malloc(sizeof(t)*sizeof(char)); _description= (char*) malloc(sizeof(d)*sizeof(char));
		strcpy(_name , n); strcpy(_type, t); strcpy(_description,d);
	}
     virtual char* getDescription() { return this->_description; }
     virtual void setDescription(const char* in){ strcpy(_description, in); }
     virtual char* getName() { return _name; }
     virtual void setName(const char* n){ strcpy(_name,n); }
     virtual char* getType() { return _type; }
     virtual void setType(const char* t){strcpy(_type, t);}
protected:
      char* _name;
      char* _type;
      char*  _description;
	//Meta information about code, in this case introduction to the example

};





#endif /* META_H_ */
