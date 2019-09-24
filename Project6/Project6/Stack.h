#ifndef STACK_H
#define STACK_H

template<typename T>
class Stack
{
private:
	Deque<T> container;
public:
	Stack()
	{}
	~Stack()
	{}

	void pop() //removes top of stack off
	{
		if (container.empty())
		{
			throw string("Stack empty!");
		}
		else container.pop_back();
		return;
	}
	void push(const T& toPush) //adds toPush to stack
	{
		container.push_back(toPush);
		return;
	}
	T& top() //returns what is on top
	{
		if (container.empty())
		{
			throw string ("Stack empty!");
		}
		return container.back(); //back is the top of stack
	}
	size_t size() // returns stack's size
	{
		return container.size();
	}
	T& at(size_t index) //returns the value of stack at index
	{
		if (container.empty())
		{
			throw string("Stack empty!");
		}
		return container.at(index);
	}
	const string toString() //returns iteration of items within stack
	{
		return container.toString();
	}
};



#endif // !STACK_H

