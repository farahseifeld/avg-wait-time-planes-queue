#pragma once

#ifndef RUNWAY_H
#define RUNWAY_H
#include "DEQ.h"


class Runway {

	private:
		DEQ <int> RunwayQueue;		//Queue to simulate waiting line
		int landingTime;			//Tlanding for this runway
		int Tr;						//Tremaining for this runway
		int jobcount;				//job count for this runway
		string code;				//code name for this runway
		int waittime;				//wait time for each plane that gets serviced
		int TotalWait;				//total wait time for planes in the runway
		

	public:
		Runway();						//default constructor
		Runway(int l, string c);		//constructor that initializes Tlanding and code to the parameters	
		~Runway();						//destructor


		void addPlane(int Ta);			//add plane to the runway queue
			//RunwayQueue.addRear(Ta);
			

		bool Ready();					//check if runway is ready to receive a landing plane
			//return Tr == 0;
		
		void startLanding();			//start landing plane 
			//Tr = landingTime;

		void inLanding();				//plane is landing so decrement Tremaining
			//Tr--;

		void finishLanding(int t);		//Exit Line, calculate wait time for plane and increments job count
			// int ta;
			//RunwayQueue.removeFront(ta);
			//jobcount++;
			//waittime= t-ta;

		int getJOBCOUNT() const;		//returns job count of runway
			//return jobcount;

		string getNo() const;			//returns runway code

		int getWaitTime() const;		//returns wait time of current landing plane

		int getTr() const;				// returns Tremaining for runway

		int Length() const;				//returns number of planes in runway queue
			//return RunwayQueue.DEQLength();

		int getTotalWait() const;		//returns the total wait time of the runway

};

#include "Runway.cpp"
#endif