#ifndef CDH_H
#define CDH_H

#include "Course.h"

//standard setters, getters, and toString

class CDH :
	public Course
{
public:
	CDH(string course = "none", string day = "none", string hour = "none") : Course(course)
	{
		setDay(day);
		setHour(hour);
	}
	~CDH(){}
	string const toString()
	{
		string returnString = "";
		ostringstream oS;
		oS << "cdh(" << getCourse() << "," << getDay() << ","
			<< getHour() << ")";
		returnString = oS.str();
		return returnString;
	}
	const string getDay()
	{
		return day;
	}
	const string getHour()
	{
		return hour;
	}
	friend ostream& operator<< (ostream& os, CDH& thisCDH)
	{
		os << thisCDH.toString();
		return os;
	}

private:
	string day;
	string hour;

	void setDay(string day)
	{
		this->day = day;
	}
	void setHour(string hour)
	{
		this->hour = hour;
	}
	


};

#endif