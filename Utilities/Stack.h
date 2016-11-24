//Stack.h
//Class used to demonstrate template usage with a class, also nested classes.
//Represents the Stack data structure.

//Include this for runtime_error
#include <stdexcept>
#include <iostream>


#ifndef STACK_H 
#define STACK_H

using namespace std;

//Note this syntax. We indicate that this class is a template and that we can give it any type, such as int, double, or string, 
//and that we refer to that type by the name T. T can be anything, e.g. <typename MyAwesomeItem> within c++ naming rules. 
//You might also see template <class T> instead of typename, that was the older way to do it. The word class was misleading, as the 
//type parameter doesn't have to be a class.
template <typename T>
class Stack
{
	private:
		//Here we nest a class. This Node class, being in the private section of Stack, can only be seen and used
		//by the Stack class. If it was public, others could use it. They would have to do, Stack::Node. E.g. Stack::Node node;
		class Node
		{
			private:
				//We can use the outer class' type parameter in the nested class. It's helpful to think of this Stack class
				//not as a class, but as a description of a class, a "template", as the compiler will actually generate
				//different classes depending on the type parameter, e.g. Stack<int> or Stack<string>. T will 
				//be essentially replaced with int or double.
				//Item is private so that the Stack class can't change it once set. We don't want nodes to change items.
				T item;

			public:
				Node(T item, Node* previous = nullptr, Node* next = nullptr);

				//We make these public as only the Stack class can use the Node class, and there is no logic 	
				//in getting/setting the node that the Stack shouldn't be able to do.
				Node* next;
				Node* previous;
				
				//Getter for the item, again, we don't allow to change the item once it's set.
				const T& getItem() const { return this->item; }
		};

		//Stack private variables here
		Node* tail;
		int count;

	public:
		Stack();
		~Stack();
		void push(T item);

		//TODO reference here maybe?
		T pop();
		int size() const { return this->count; }
		bool isEmpty() const { return this->count == 0; }

		//We delete the move/copy methods as we don't want to provide those to make this class simple.
		Stack(const Stack& that) = delete;
		Stack(Stack&& that) = delete;
		Stack operator=(const Stack& that) = delete;
		Stack operator=(Stack&& that) = delete;

		//Here we make a template function for the << operator. 
		//This allows us to define a function that will work with any type of Stack
		template <typename U>
		friend ostream& operator<<(ostream& output, const Stack<U>& stack);
};

//TODO copy, move, delete those?
template <typename T>
Stack<T>::Stack()
{
	this->tail = nullptr;
}

template <typename T>
Stack<T>::~Stack()
{
	Node* current = this->tail;
	Node* previous = current;

	while(current != nullptr)
	{
		previous = current->previous;
		delete current;
		current = previous;
	}
}

template <typename T>
void Stack<T>::push(T item)
{
	if(this->tail == nullptr)
	{
		this->tail = new Node(item);
	}
	else 
	{
		this->tail->next = new Node(item, this->tail);
		this->tail = this->tail->next;
	}

	this->count++;
}

template <typename T>
T Stack<T>::pop()
{
	if(this->tail == nullptr)
	{
		throw runtime_error("Stack is empty");
	}

	Node* currentNode = this->tail;
	T result = currentNode->getItem();

	this->tail = this->tail->previous;

	delete currentNode;
	
	if(this->tail != nullptr)
	{
		this->tail->next = nullptr;
	}

	this->count--;
	return result;
}

template <typename T>
Stack<T>::Node::Node(T item, Node* previous, Node* next)
{
	this->item = item;
	this->previous = previous;
	this->next = next;
}

//Definition of operator<< function. Notice we don't use the Stack template's typename T, as the 
//template function was defined as its own template
template <typename U>
ostream& operator<<(ostream& output, const Stack<U>& stack)
{
	//This is a little tricky. Without the keyword typename, the compiler doesn't understand that 
	//Stack<U>::Node* is a type, using the keyword typename makes it realize it is a type.
	//Alternatively, you could use auto tail = stack.tail. The compiler will automatically figure out the type then.
	//The auto approach is probably better as it is less error prone to type out and simpler to read too.
	//But unfortunately it's not clear what the type is, or that it's a pointer. Take your pick.
	typename Stack<U>::Node* tail = stack.tail;
	//auto tail = stack.tail; 

	//Here we print out the stack in order the items were pushed in.
	while(tail != nullptr && tail->previous != nullptr)
	{
		tail = tail->previous;
	}

	while(tail != nullptr)
	{
		cout << tail->getItem() << " ";
		tail = tail->next;
	}

	return output;
}


#endif
