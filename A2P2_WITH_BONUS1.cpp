#include <iostream>
#include <string>
#include <time.h>
#include "DEQ.h"
#include "Runway.h"
using namespace std;

//avg wait time for planes that didnt land during the simulation period???

void logLanding(Runway &r, int t);


void logArrival(Runway &r, int Ta, int cnt);


void processArrival(int ta, Runway &r1, Runway &r2, Runway &r_case1, int &cnt1, int &cnt2, int &cntcase);


void simulationConditions(int &Tmax, int &Ta, int &Ts);


void RunwayReady(Runway &r, int t);


bool ifArrived(int ta, double prob);


double findAvgWaitTime(Runway &r1, Runway &r2);


double findSingleAVGWaitTime(Runway &r);


void printSimulationDetails(Runway &r1, Runway &r2, Runway &r3, int cnt1, int cnt2, int cntcase);


void simulate(int tmax, int ta, int ts, double &avg, double &avgsingle);




int main() {

	//note: Ta means delta t not Tarrival
	int Tmax, Ts, Ta;
	double avgwait, avgwaitsingle;


	//get the simulation conditions from the user
	simulationConditions(Tmax,Ta, Ts);

	//simulate the process
	simulate(Tmax, Ta, Ts, avgwait,avgwaitsingle);
		

		//print average wait time for 2 runways
		cout << "Average wait time with 2 runways is " << avgwait << " minutes." << endl;

		//print average wait time for single runway case
		cout << "Average wait time for a single runway is " << avgwaitsingle << " minutes." << endl;

		cout << endl;

	system("pause");
	return 0;
}


//logs the landing of a plane
void logLanding(Runway &r, int t) {
	cout << "Runway " << r.getNo() << ": Plane #" << r.getJOBCOUNT() << " Landed at time " << t << " minutes." << " Wait time= " << r.getWaitTime() << " minutes." << endl;
}


//logs the arrival of a plane
void logArrival(Runway &r, int Ta, int cnt) {
	cout << "Runway " << r.getNo() << ": Plane #" << cnt << " Arrived at time " << Ta << " minutes." << endl;
}


// process plane arrival
void processArrival(int ta, Runway &r1, Runway &r2, Runway &r_case1, int &cnt1, int &cnt2, int &cntcase) {

	//compares the size of both runways and lets the plane join the shorter queue
	if (r1.Length() <= r2.Length()) {
		//add plane to queue of runway1
		r1.addPlane(ta);
		//increment total number of planes in this queue
		cnt1++;
		//log the arrival
		logArrival(r1, ta, cnt1);

	}

	else {
		//add plane to runway2
		r2.addPlane(ta);
		cnt2++;
		logArrival(r2, ta, cnt2);
	}

	// in the single runway case, no comparisons are needed so you just add the plane
	r_case1.addPlane(ta);
	cntcase++;
	logArrival(r_case1, ta, cntcase);

}


//asks the user to input Tmax, delta T=Ta, and Tlanding=Ts and validates the input
void simulationConditions(int &Tmax, int &Ta, int &Ts) {
	
	cout << "Enter the time of the simulation period in minutes" << endl;
	
	do {
		while (!(cin >> Tmax)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "INVALID INPUT. Enter the time of the simulation period in minutes again." << endl;
		}
		if (Tmax < 1)
			cout << "INVALID INPUT. Make sure your number is more than 0" << endl;
	} while (Tmax < 1);

	cout << endl;

	cout << "Enter the time it takes for the plane to land in minutes" << endl;
	do {
		while (!(cin >> Ts)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "INVALID INPUT. Enter the time it takes for the plane to land in minutes again." << endl;
		}
		if (Ts < 1)
			cout << "INVALID INPUT. Make sure your number is more than 0" << endl;
	} while (Ts < 1);

	cout << endl;

	cout << "Enter the average inter-arrival time in minutes" << endl;
	do {
		while (!(cin >> Ta)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "INVALID INPUT. Enter the average inter-arrival time in minutes again." << endl;
		}
		if (Ta < 1)
			cout << "INVALID INPUT. Make sure your number is more than 0" << endl;
	} while (Ta < 1);
}


//checks if runway is ready and processes exits and landings
void RunwayReady(Runway &r, int t) {

	if (r.Ready()) {
		
		//exit line
		r.finishLanding(t);

		//log the landing
		logLanding(r, t);

		//start next landing
		r.startLanding();
	}

}



// checks if plane has arrived
bool ifArrived( int ta, double prob) {
	return prob <= (1 / (double)ta);
}


//finds the average wait time for the case with 2 runways
// returns -1 if no plane has landed
double findAvgWaitTime(Runway &r1, Runway &r2) {

	int job = r1.getJOBCOUNT() + r2.getJOBCOUNT();
	int waittotal = r1.getTotalWait() + r2.getTotalWait();
	if (job > 0)
		return  waittotal/ double(job);
	else return -1;
}


//finds the average wait time for a single runway
// returns -1 if no plane has landed
double findSingleAVGWaitTime(Runway &r) {
	if (r.getJOBCOUNT() > 0)
		return (r.getTotalWait() / r.getJOBCOUNT());
	else
		return -1;
}


//simulate the whole process
void simulate(int tmax, int ta, int ts, double &avg, double &avgsingle) {

	//variable initializations
	int t = 0;
	//note to self: add the cnts as public variables in runway class
	int cnt1 = 0;		//total number of planes that joined Runway1
	int cnt2 = 0;		//total number of planes that joined Runway2
	int cntcase = 0;	//total number of planes in the case of a single runway
	int waitTotal = 0;

	//construct 3 Runway objects
	Runway runway1(ts, "1");
	Runway runway2(ts, "2");
	Runway runway_case1(ts, "Single");


	srand((unsigned)time(NULL));
	

	while (t < tmax) {


		cout << "---------------" << endl;

		double probabilityArrival = rand() / float(RAND_MAX);

		//check if plane arrived
		if (ifArrived(ta, probabilityArrival))
			//process arrival
			processArrival(t, runway1, runway2, runway_case1, cnt1, cnt2, cntcase);


		//check if runway is ready to receive plane
		RunwayReady(runway1, t);
		RunwayReady(runway2, t);
		RunwayReady(runway_case1, t);

		//Tr--
		runway1.inLanding();
		runway2.inLanding();
		runway_case1.inLanding();
		

		//increment time
		t++;
	}
	cout << endl;
	cout << endl;
	

	//find the average wait time in the 2 cases and store them
	//in variables that will be returned by reference in the function
	avg = findAvgWaitTime(runway1, runway2);
	avgsingle = findSingleAVGWaitTime(runway_case1);
	
	printSimulationDetails(runway1, runway2, runway_case1, cnt1, cnt2, cntcase);
}


void printSimulationDetails(Runway &r1, Runway &r2, Runway &r3, int cnt1, int cnt2, int cntcase) {

	//print details about the number of planes that arrived during the simulation period
	//print details about the number of planes that landed during the simulation period in both cases
	cout << endl;
	cout << "Total number of planes that arrived during the simulation period = " << cntcase << endl;
	cout << "Total number of planes that landed in the 2 runways during the simulation period = " << r1.getJOBCOUNT() + r2.getJOBCOUNT() << endl;
	cout << "Total number of planes that landed in the single runway during the simulation period = " << r3.getJOBCOUNT() << endl;
	cout << endl;
}