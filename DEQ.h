#pragma once

#ifndef DEQ_H
#define DEQ_H


template <class type>


class DEQ {


	private:

		int size;

		class node {

		public:
			node* next;
			type e;
		};

		typedef node* nodepointer;
		nodepointer front, rear;


	public:

		//constructor
		DEQ();
		//copy constructor
		DEQ(const DEQ <type> &);
		//destructor
		~DEQ();

		//checks if deQueue is empty
		bool DEQempty() const;

		//add an element at the front
		void addFront(type v);

		//add an element at the rear
		void addRear(type v);

		//remove the element at the front
		void removeFront(type &v);

		//remove the element at the rear
		void removeRear(type &v);

		//retrieve the front element without removal
		void viewFront(type &v) const;

		//retrieve the rear element without removal
		void viewRear(type &v) const;

		//number of elements in the deq
		int DEQLength() const;


};

#include "deq.cpp"
#endif