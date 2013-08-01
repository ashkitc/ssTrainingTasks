//Definition of class for LinkedList
template <typename TYPE>
class LinkedList
{
	//Definition of class for LinkedList's node
	template <typename TYPE> 
	class Node
	{
	public:
		Node<TYPE> *nextNode; //Pointer to the next node
		Node<TYPE> *previousNode; //Pointer to the previous node
		TYPE *data; // Pointer to Node's data

		// we can insert  a new node into linked list using this constructor
		Node(Node<TYPE> *prev, Node<TYPE> *next, TYPE value)  
		{
			previousNode = prev;  
			nextNode = next;   
			data = new TYPE;  
			*data = value; 
		}

		// default constructor
		Node(){
			nextNode = NULL;
			previousNode = NULL;
			data = NULL;
		}

		//We can delete node from linked list using destructor
		~Node()
		{
			if(previousNode == NULL){
				nextNode->previousNode = previousNode;
			} else 
			if(nextNode == NULL){
				previousNode->nextNode = nextNode;
			} else 
			{
				nextNode->previousNode = previousNode;
				previousNode->nextNode = nextNode;
			}
			delete data;
		}
	};
	Node<TYPE> *firstNode; 	// A pointer to the begin of lincked list
	Node<TYPE> *lastNode;  //  A pointer to the end of lincked list
public:



	LinkedList();
	void addLastObject(TYPE object); //add object to the end of linked list 
	void addFirstObject(TYPE object); //add object to the begin of linked list

	void displayToConsole(); // output all objects in linked list to console
	void deleteLastObject(); // delete the last object from linked list
	void deleteFirstObject(); // delete the first object frome linked list
	bool isEmpty();

	//Class for linked list iterator
	class Iterator;
	Iterator& begin();
	Iterator& end();
};
template <typename TYPE>
LinkedList<TYPE>::LinkedList()
{
	firstNode = NULL;
	lastNode = NULL;
};

template <typename TYPE> 
bool LinkedList<TYPE>::isEmpty()
{
	return (firstNode == NULL && lastNode == NULL); // list is empty whet it hasn't first and last node
}

template <typename TYPE>
void LinkedList<TYPE>::addLastObject(TYPE object)
{
	if( isEmpty() ) // if list is empty we only add a new node, and setup first and last node pointers on it
	{
		firstNode = new Node<TYPE>(NULL,NULL,object);
		lastNode = firstNode;
	} else { // else add new node to the end of linked list and setup last node pointer on it
		lastNode->nextNode = new Node<TYPE> (lastNode,NULL,object);
		lastNode = lastNode ->nextNode;
	}
}


template <typename TYPE> 
void LinkedList<TYPE>::addFirstObject(TYPE object)
{
	if( isEmpty() ) // if list is empty do the same steps as in addLastObject method
	{
		firstNode = new Node<TYPE>(NULL,NULL,object);
		lastNode = firstNode;
	} else { // else add new node to the begin of linked list and setup first node pointer on it
		firstNode->previousNode = new Node<TYPE>(NULL,firstNode,object);
		firstNode = firstNode->previousNode;
	}
}

template <typename TYPE>
void LinkedList<TYPE>::displayToConsole()
{
	Node<TYPE> *current = firstNode; //set up temoporary nede pointer on the first node
	while (current != NULL){ // walk over the lincked list and display each node's data to console
		cout << *current->data << endl;
		current = current->nextNode;
	}
}

//  delete the last object from the linked list
template <class TYPE>
void LinkedList<TYPE>::deleteLastObject()
{
	lastNode = lastNode->previousNode;
	delete lastNode->nextNode;
}

// delete the first object from the linked list
template <class TYPE>
void LinkedList<TYPE>::deleteFirstObject()
{
	if(firstNode->nextNode != NULL)
	{
		firstNode = firstNode->nextNode;
	}
	delete firstNode ->previousNode;
}

template <typename TYPE>
typename LinkedList<TYPE>::Iterator& LinkedList<TYPE>::begin() //returns the iterator, pointed on first list's element
{
	Iterator *newIterator = new Iterator( this );
	newIterator->setCurrent( firstNode );
	//newIterator->setCurrent
	return *( newIterator );
}


template <typename TYPE>
typename LinkedList<TYPE>::Iterator& LinkedList<TYPE>::end() 
{
	Iterator *newIterator = new Iterator( this );
	newIterator->setCurrent( lastNode );
	return *( newIterator );
}

//********************************************
//* 
//*          Class for iterator
//*
//********************************************

template<typename TYPE>
class LinkedList<TYPE>::Iterator{
private:
	Node<TYPE> * current;
	LinkedList<TYPE> *list;
	int countNodesAfter();
	bool needsIncrement;
	bool needsDecrement;
public:
	Iterator(LinkedList<TYPE> *listPtr);
	//Operator overloading for LinkedList's iterator
	inline Iterator& operator++();
	inline Iterator& operator--();
	inline Iterator& operator++(int);
	inline Iterator& operator--(int);
	inline TYPE& operator*(); //Returns the curent node's data

	inline void setCurrent(Node<TYPE> *nodePtr);
	//compare operators overloadong
	bool operator == (const Iterator& rightOperand);
	bool operator != (const Iterator& rightOperand);
	bool operator <= ( Iterator& rightOperand);
	void removeObject();
	void insertObjectAtCurrentPosition(TYPE newObjectValue);
};

template <typename TYPE>
LinkedList<TYPE>::Iterator::Iterator(LinkedList<TYPE> *listPtr)
{
	list = listPtr;
	current = list->firstNode;
	needsIncrement = true;
	needsDecrement = true;
}

template <typename TYPE>
void LinkedList<TYPE>::Iterator::setCurrent(Node<TYPE> *nodePtr)
{
	current = nodePtr;
}

//******************************************************************
//*
//*     Overload increment and decrement and comaparation operators
//*              (for using Iterator in the cicles)
//*
//******************************************************************
template <typename TYPE>
typename LinkedList<TYPE>::Iterator& LinkedList<TYPE>::Iterator::operator++() // prefix form of increment operator
{
	if(needsIncrement)
	{
		current = current->nextNode;
	}
	needsIncrement = true; //Now we need increment
	return *this;
}

template <typename TYPE>
typename LinkedList<TYPE>::Iterator& LinkedList<TYPE>::Iterator::operator--() // prefix form of decrement operator
{
		current = current->previousNode;
	return *this;
}

template <typename TYPE>
typename LinkedList<TYPE>::Iterator& LinkedList<TYPE>::Iterator::operator++(int) //postfix form of increment operator
{
	if(needsIncrement)
	{
		current = current->nextNode;
	}
	needsIncrement = true;
	return *this;
}

template <typename TYPE>
typename LinkedList<TYPE>::Iterator& LinkedList<TYPE>::Iterator::operator--(int) //postfix form of decrement operator
{
		current = current->previousNode;
	return *this;
}
 //Overload comparation operators
template <typename TYPE>
bool LinkedList<TYPE>::Iterator::operator==(typename const LinkedList<TYPE>::Iterator &rightOperand){
	bool res = (current == rightOperand.current);
	return (current == rightOperand.current);
}

template <typename TYPE>
bool LinkedList<TYPE>::Iterator::operator!=(typename const LinkedList<TYPE>::Iterator &rightOperand){
	return !(current == rightOperand.current);
}

template <typename TYPE> 
bool LinkedList<TYPE>::Iterator::operator<=(typename  LinkedList<TYPE>::Iterator &rightOperand)
{
	if(countNodesAfter() == -1)
	{
		return false;
	}
	else 
	{
		return  (this->countNodesAfter() >= rightOperand.countNodesAfter());
	}
}
//overload unary * operator for returning curent node's value
template <typename TYPE>
TYPE& LinkedList<TYPE>::Iterator::operator*() 
{
		return *current->data;
}


template <typename TYPE>
void LinkedList<TYPE>::Iterator::removeObject() // remove object from current position
{
	if(current == list->firstNode)
	{
		list->deleteFirstObject();
     	current = list->firstNode;
		needsIncrement = false; //wee need no increment because we did it with previous row

	}
	else if (current == list->lastNode)
	{
		list->deleteLastObject();
	    current = list->lastNode;
	}
	else
	{
	    current = current->nextNode;
		delete current->previousNode;
		needsIncrement = false;
	}
}

template <typename TYPE>
void LinkedList<TYPE>::Iterator::insertObjectAtCurrentPosition(TYPE newObjectValue) //insert object on current position
{
	//chek if we must change list's first node and last node pointers
	if(current == list->firstNode)
	{
		list->addFirstObject(newObjectValue);
	} else if(current == NULL)
	{
		list->addLastObject(newObjectValue);
		current = list->lastNode;
	} else //if we must not change it insert object att current posititon
		{
		Node<TYPE> *objectForInsrting = new Node<TYPE>(current->previousNode,current,newObjectValue);
		if(current->previousNode != NULL)
		{
			current->previousNode->nextNode = objectForInsrting;
		}
			current->previousNode = objectForInsrting; // new object will be next node for current 
			current = objectForInsrting;
			current = current->nextNode;
	}
}

//returns a count of objects after this node (uses for comparation operator)
template <typename TYPE>
int  LinkedList<TYPE>::Iterator::countNodesAfter()
{
	Node<TYPE> *nodePtr = current;
	if(nodePtr == NULL)
	{
		return -1; //return -1 when current position is out of bounds
	}
	else // else calculate count of objects after current position
	{
		int count = 0;
		while(nodePtr->nextNode != NULL)
		{
			++count;
			nodePtr = nodePtr->nextNode;
		}
		return count;
	}
}