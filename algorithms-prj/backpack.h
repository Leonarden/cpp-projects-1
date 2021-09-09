#ifndef BACKPACK_H_INCLUDED
#define BACKPACK_H_INCLUDED

#include<vector>
#include <cmath>
#include <chrono>
#include <exception>
using namespace std;
//A backpack Item
class Item {
public:
    Item(double w, double b):_weight(w),_benefit(b){
    if(_weight==0) throw -100;
    }
    virtual ~Item() {}
    void setWeight(double w) { _weight = w; }
    void setBenefit(double b) { _benefit = b;}
    double getRatio(){ return _benefit/_weight; }

    double _weight;
    double _benefit;
    double _ratio;

};

class Backpack {
public:
    Backpack(double mw) {
        _maxWeight = mw;
        _items = new vector<Item*>;
        _totBenefit = 0;
        _currentWeight = 0;
    }
   virtual ~Backpack() {}
    virtual void computeAddItems(vector<Item*> &items) {
    //In this case we use raw algorithm
        double delta;
        vector<Item*>::iterator it;
        for(it=items.begin();it!=items.end();it++){
           Item * i = *it;
            delta = _maxWeight - (_currentWeight + i->_weight);
            if(delta <=0)
                break;
            _currentWeight = _currentWeight + i->_weight;
            _totBenefit = _totBenefit + i->_benefit;
            _items->push_back(i);
        }


    }


    vector<Item*> * getItems() { return _items; }

    virtual void displayResults();
    virtual double getTotalBenefit();


    double _maxWeight = -1;
    double _currentWeight=0;
    double _totBenefit=0;
    vector<Item*> * _items;
    vector<bool> * _sol;

};

void Backpack::displayResults(){

cout<< "Items added to Backpack" << endl;
vector<Item*>::iterator it;
int i = 1;
for(it=_items->begin();it!= _items->end();it++){
    Item * item = *it;
    cout << "Item n:" << i << " Weight:" << item->_weight << " Benefit:" << item->_benefit << " Ratio: " << item->getRatio() << endl;
    i++;
}

cout << " Total sum of benefit : " << this->getTotalBenefit() << endl;
}

double Backpack::getTotalBenefit(){

    _totBenefit = 0;
    for(int i=0;i<_items->size();i++)
        _totBenefit = _totBenefit + _items->at(i)->_benefit;



return _totBenefit;

}

class BackpackGreedy: public Backpack {
public:
    BackpackGreedy(double mw):Backpack(mw){}
    virtual ~BackpackGreedy() {}
    virtual void computeAddItems(vector<Item*> & items);

    vector<Item*> sortItems(vector<Item*>& items);



};

vector<Item*> BackpackGreedy::sortItems(vector<Item*> & items){

for(int i=0;i<(items.size() -1);i++){

Item* i1 = items.at(i);

     for(int j=(i+1);j<items.size();j++){
        Item* i2 = items.at(j);
        if(i2->_ratio>i1->_ratio){
           std::swap(items.at(i),items.at(j));

        }

    }

}

return items;


}

void BackpackGreedy::computeAddItems(vector<Item*> & items) {

    vector<Item*>  sortedItems = sortItems(items);

    Backpack::computeAddItems(sortedItems);

}

class BackpackDynamic: public Backpack {
public:
    BackpackDynamic(double mw):Backpack(mw) {}
    virtual void computeAddItems(vector<Item*>& items);



};

void BackpackDynamic::computeAddItems(vector<Item*> &items){
this->_sol = new vector<bool>(items.size());
for(int i=0;i<items.size();i++){
    this->_sol->at(i) = (this->_currentWeight + items.at(i)->_weight<=this->_maxWeight)? true : false;
    if(_sol->at(i)){
        this->_currentWeight = this->_currentWeight + items.at(i)->_weight;
        this->_items->push_back(items.at(i));
    }

}


}




class BackpackRunner {
public:

    virtual int run();

protected:

    vector<Item*> generateItems(int num);
    double sum;
    double generateBackpackCapacity(int max);


};

vector<Item*> BackpackRunner::generateItems(int n) {
Item * item = nullptr;
double w,b;
vector<Item*> items;
  if(n>100){
    cout<< "Generating Max items = 100" << endl;
    n = 100;
    }
    else
        cout << "Generating " << n << " items " << endl;
int i = 0;
while(i<n){
    w = 1.5*(rand()%10) +1;
    b = (5.5 * (rand()%5) )+ 1.3;
    item = new Item(w,b);
    items.push_back(item);
   i++;
}

return items;

}

double BackpackRunner::generateBackpackCapacity(int max){
double capacity = 0.0;
if(max <= 0)
    max = 10;

capacity = (rand()%(max/2)) + (max/2);

return capacity;
}


int BackpackRunner::run() {

Backpack *bp1;
string mesg = " Backpack ";
vector<Item*> items = generateItems(10);
double capacity = generateBackpackCapacity(50);
cout << " Items number: " << items.size() << endl;
cout << " Backpack capacity : " << capacity << endl;
try
{


for(int i=0;i<3;i++){
if(i==0){
bp1  = new Backpack(capacity);
}else if(i==1){
    mesg = "Backpack Greedy Technique";
    bp1  = new BackpackGreedy(capacity);
}else{
    mesg = "Backpack Dynamic Programming Technique";
    bp1  = new BackpackDynamic(capacity);
}
cout << "---------" << mesg << "---------"<<endl;
bp1->computeAddItems(items);

bp1->displayResults();
cout << "-------------------------------" << endl;

}

}catch(exception e){
    cout << " BackpackRunner an exception occurred : " << e.what() << endl;
}

return 0;
}




#endif // BACKPACK_H_INCLUDED
