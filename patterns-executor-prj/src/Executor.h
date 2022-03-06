/*
 * Executor.h
 *
 *  Created on: Jul 25, 2021
 *      Author: david
 */

#ifndef EXECUTOR_H_
#define EXECUTOR_H_
#include<vector>
#include<iostream>
#include<string>
#include "Runnable.h"
#include "Log.h"
using namespace std;


class Executor {
public:
	Executor();
	Executor(vector<Runnable*> * runs);
	virtual ~Executor();
	void setRunnables(vector<Runnable*> * runs) { _runnables = runs;}
	vector<Runnable*> * getRunnables(){ return _runnables; }
    virtual int executeAll();
    virtual int execute( vector<int> idx);

private:
    vector<Runnable*>* _runnables;
    LOG logger;
};

#endif /* EXECUTOR_H_ */
