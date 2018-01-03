
#include <iostream>
#include <string>
using namespace std;

template <class type>
DEQ <type>::DEQ() {

	front = NULL;
	rear = NULL;
	size = 0;
}

//copy constructor
template <class type>
DEQ <type>::DEQ(const DEQ <type> & original) {

	nodepointer cursor = front;
	rear = NULL;
	size = 0;
	int i = 0;
	type v;

	while (i < original.size) {

		v = cursor->e;
		addRear(v);
		cursor = cursor->next;
		i++;
	}
}

template <class type>
DEQ <type>::~DEQ() {

	if (size > 0) {
		type v;

		while (!DEQempty()) 
			removeFront(v);
	}
}

//checks if deQueue is empty
template <class type>
bool DEQ <type>::DEQempty() const {

	return (size == 0);
}

//add an element at the front
template <class type>
void DEQ <type>::addFront(type v) {

	nodepointer newnode = new node;
	if (size == 0) {

		front = newnode;
		rear = newnode;
		newnode->e = v;
		newnode->next = NULL;
	}
	else {

		newnode->next = front;
		front = newnode;
		newnode->e = v;

	}
	size++;
}

//add an element at the rear
template <class type>
void DEQ <type>::addRear(type v) {
	
	nodepointer newnode = new node;
	if (size == 0) {
		front = newnode;
		rear = newnode;
		newnode->e = v;
		newnode->next = NULL;
	}
	else {
		rear->next = newnode;
		rear = newnode;
		newnode->e = v;
		newnode->next = NULL;
	}
	size++;
	//cout << "size= " << size << endl;
}

//remove the element at the front
template <class type>
void DEQ <type>::removeFront(type &v) {

	nodepointer cursor;
	if (size > 0) {
		cursor = front;
		v = front->e;
		front = front->next;
		delete cursor;
		size--;
		if (size == 0)
			rear = NULL;
	}
	else cout << "Error151: DEQ is empty. Failed to remove front." << endl;
}

//remove the element at the rear
template <class type>
void DEQ <type>::removeRear(type &v) {

	nodepointer cursor, current;
	if (size > 1) {

		//get the node before the rear
		current = front;
		while (current->next->next != nullptr)
			current = current->next;

		cursor = rear;
		v = rear->e;
		rear = current;
		current->next = NULL;
		delete cursor;
		size--;
	}
	else if (size == 1) {
		
		cursor = rear;
		v = rear->e;
		rear = NULL;
		front = NULL;
		delete cursor;
		size--;
	}
	else cout << "Error 152: DEQ is empty. Failed to remove rear." << endl;
}

//retrieve the front element without removal
template <class type>
void DEQ <type>::viewFront(type &v) const {

	if (size > 0)
		v = front->e;
	else cout << "Error 153: DEQ is empty. Failed to view front." << endl;
}

//retrieve the rear element without removal
template <class type>
void DEQ <type>::viewRear(type &v) const {

	if (size > 0)
		v = rear->e;
	else cout << "Error154: DEQ is empty. Failed to view rear." << endl;
}


//number of elements in the deq
template <class type>
int DEQ <type>::DEQLength() const {
	return size;
}
