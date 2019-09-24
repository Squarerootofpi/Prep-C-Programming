#ifndef CR_H
#define CR_H

#include "Course.h"

//standard setters, getters, and toString

class CR :
	public Course
{
public:
	CR(string course = "none", string room = "none") : Course(course)
	{
		setRoom(room);
	}
	~CR(){}
	const string toString()
	{
		string returnString = "";
		ostringstream oS;
		oS << "cr(" << getCourse() << "," << getRoom() << ")";
		returnString = oS.str();
		return returnString;
	}
	const string getRoom()
	{
		return room;
	}
	friend ostream& operator<< (ostream& os, CR& thisCR)
	{
		os << thisCR.toString();
		return os;
	}

private:
	string room;

	void setRoom(string room)
	{
		this->room = room;
	}

};

#endif