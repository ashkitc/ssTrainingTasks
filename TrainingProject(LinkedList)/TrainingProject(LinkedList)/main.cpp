#include <iostream>
#include <conio.h>
#include "LinkedList.h"
using namespace std;
int main (int argc, char **argv)
{
	LinkedList<int> list;  //Crate new Linked list

	//try to add first and last object
	list.addLastObject(5);
	list.addLastObject(6);
	list.addFirstObject(4);
	list.addLastObject(7);
	list.addFirstObject(3);
	list.addLastObject(8);
	list.addFirstObject(2);
	list.addLastObject(9);
	list.addFirstObject(1);
	list.addLastObject(10);
	list.deleteLastObject();
	list.deleteFirstObject();
	//Adding last object using iterator
	LinkedList<int>::Iterator it1 = list.end();
    ++ it1;
	it1.insertObjectAtCurrentPosition(190);
	
	//Adding firstObject using iterator
	it1= list.begin();
	++ it1;
	it1.insertObjectAtCurrentPosition(30);
	
	//Adding a num of object for different positions using iterator
	int num = 134;
	for(LinkedList<int>::Iterator it = list.begin() ; it <= list.end(); ++ it , num += 14)
	{
		it.insertObjectAtCurrentPosition(num);
	}

	// display list to console using instance method
	list.displayToConsole();
	cout << "=============After deleting some objects================="<<endl;
	
	//delete a num of objects from different positions using iterator
	int i = 0;
	for (LinkedList<int>::Iterator it = list.begin() ; it <= list.end(); it++){
		if (i % 2 == 0)
		{
			it.removeObject();
	    }
		++i;
	}
	
	//display list to concole using iterator
	for(LinkedList<int>::Iterator it = list.begin(); it <=  list.end();  ++it)
	{
		 cout << *it << endl;
	}
	
	
	_getch();
	return 0;
}