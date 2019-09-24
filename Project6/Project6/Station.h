#ifndef STATION_H
#define STATION_H
#include "Deque.h"
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"

template<typename T>
class Station 
{
private:
	bool empty;
	T turnTableCar;
	Queue<T> queue;
	Vector<T> vector;
	Stack<T> stack;
public:
	Station() 
	{
		empty = true;
	}
	~Station() 
	{
		
	}

	string addCar(const T& toAdd) //adds car to station
	{
		if (empty) 
		{
			turnTableCar = toAdd;
			empty = false;
			return "OK";
		}
		else
		{
			return "Turntable occupied!";
		}
		
	}
	string removeCar() //removes car from station
	{
		if (empty)
		{
			return "Turntable empty!";
		}
		else
		{
			vector.push_back(turnTableCar);//Put into vector!
			empty = true;
			return "OK"; 
		}
	}
	string topCar() //returns train on station
	{
		if (empty)
		{
			//turnTableCar = toAdd;
			return "Turntable empty!";
		}
		else
		{
			string str;
			stringstream ss;
			ss << turnTableCar;
			str = ss.str();
			return str; 
		}
	}
	string addStack() //puts train car into stack
	{
		if (empty)
		{
			throw string("Turntable empty!");
		}
		stack.push(turnTableCar);
		empty = true;
		return "OK";
	}
	string removeStack() //puts top of stack on turntable
	{
		if (!empty) //something already on turntable
		{
			throw string("Turntable occupied!");
		}
		turnTableCar = stack.top();
		stack.pop();
		empty = false;
		return "OK";
	}
	string topStack() //returns top of stack
	{
		string str;
		stringstream ss;
		ss << stack.top(); //throws error if empty
		str = ss.str();
		return str;
	}
	string sizeStack() //returns the size of stack
	{
		string str;
		stringstream ss;
		ss << stack.size();
		str = ss.str();
		return str;
	}
	string addQueue() //adds turntablecar to queue
	{
		if (empty)
		{
			throw string("Turntable empty!");
		}
		queue.push(turnTableCar);
		empty = true;
		return "OK";
	}
	string removeQueue() //removes queue front to turntable
	{
		if (!empty) //something already on turntable
		{
			throw string("Turntable occupied!");
		}
		turnTableCar = queue.top(); //will throw if empty
		queue.pop();
		empty = false;
		return "OK";
	}
	string topQueue() //adds turntable car to queue
	{
		string str;
		stringstream ss;
		ss << queue.top(); //throws error if empty
		str = ss.str();
		return str;
	}
	string sizeQueue() //returns queue's size
	{
		string str;
		stringstream ss;
		ss << queue.size();
		str = ss.str();
		return str;
	}
	string find(T toFind) //finds if train car exists within system
	{
		for (int i = 0; i < vector.size(); ++i)			//vector search
		{
			if (vector.at(i) == toFind) 
			{ 
				stringstream ss;
				ss << "Train[" << i << "]";
				string str = ss.str();
				return str;
			}
		}
		for (int i = 0; i < queue.size(); ++i)			//queue search
		{
			if (queue.at(i) == toFind)
			{
				stringstream ss;
				ss << "Queue[" << i << "]";
				string str = ss.str();
				return str;
			}
		}
		for (int i = 0; i < stack.size(); ++i)			//stack search
		{
			if (stack.at(i) == toFind)
			{
				stringstream ss;
				ss << "Stack[" << i << "]";
				string str = ss.str();
				return str;
			}
		}
		//turntable
		if (turnTableCar == toFind)
		{
			return "Turntable";
		}

		return "Not Found!";
	}
	const string toString()  //outputs train, vector
	{
		return vector.toString();
	}
};


#endif // !STATION_H



