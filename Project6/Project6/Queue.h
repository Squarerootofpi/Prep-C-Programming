#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue
{
private:
	Deque<T> container;

public:
	Queue()
	{}
	~Queue()
	{}
	void pop() //pops the front of container.
	{
		if (container.empty())
		{
			throw string("Queue empty!");
		}
		container.pop_front();
		return;
	}
	void push(const T& toPush) //pushes to queue
	{
		container.push_back(toPush);
		return;
	}
	T& top() //returns the front of queue
	{
		if (container.empty())
		{
			throw string("Queue empty!");
		}
		return container.front();
	}
	size_t size() //returns size of queue
	{
		return container.size();
	}
	T& at(size_t index) //returns traincar at index
	{
		if (container.empty())
		{
			throw string("Queue empty!");
		}
		return container.at(index);
	}
	const string toString() //returns all values in queue
	{
		return container.toString();
	}
};

#endif // !QUEUE_H

