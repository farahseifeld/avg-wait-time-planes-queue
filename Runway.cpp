
#include <iostream>
#include <string>
#include "Runway.h"
using namespace std;

//runway default constructor
Runway:: Runway() {

	landingTime = 0;
	Tr = 0;
	code = "";
	TotalWait = 0;

}

//runway constructor
Runway::Runway(int l, string c) {
	landingTime = l;
	Tr = 0;
	code = c;
	TotalWait = 0;
}

//runway destructor
Runway::~Runway() {
	RunwayQueue.~DEQ();
}

//add plane to the rear of the queue
void Runway::addPlane(int Ta){

	RunwayQueue.addRear(Ta);
}

// check if runway is ready to start service
bool Runway::Ready(){
	return (Tr == 0 && RunwayQueue.DEQLength()!=0);
}

// start landing 
void Runway::startLanding() {
	Tr = landingTime;
}

//decrement Tremaining
void Runway::inLanding() {
	 if(Tr>0)
	Tr--; 
}

//EXIT LINE
void Runway::finishLanding(int t) {
	int ta;
	RunwayQueue.removeFront(ta);
	jobcount++;
	waittime = t - ta;
	TotalWait += waittime;
}


int Runway::getJOBCOUNT() const {
	return jobcount;
}

string Runway::getNo() const {
	return code;
}

int Runway::getWaitTime() const {
	return waittime;
}

int Runway::getTr() const {
	return Tr;
}

int Runway::Length() const {
	return RunwayQueue.DEQLength();
}


int Runway::getTotalWait() const{
	return TotalWait;
}

