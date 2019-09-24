//vector class for outputs of cars

#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class Vector
{
private:
	Deque<T> container;
public:
	Vector()
	{}
	~Vector()
	{}
	const string toString() // iterates through train.
	{
		return container.toString();
	}
	T& at(size_t index) //returns reference to index pointed at
	{
		return container.at(index);
	}
	size_t size() //size of vector
	{
		return container.size();
	}
	size_t arrayCapacity()
	{
		return container.maxCapacity();
	}
	T& back() //returns reference to back
	{
		return container.back();
	}
	void pop_back() //popback shouldn't be a problem in this, because don't remove from vector.
	{
		container.pop_back();
		return;
	}
	void push_back(const T& toPush) //pushes to end of vector
	{
		container.push_back(toPush);
		return;
	}
};


#endif // !VECTOR_H

