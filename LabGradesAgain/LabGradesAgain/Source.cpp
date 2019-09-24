/*
Joseph Steed, CS 235, 3pm MWF
Email me your advice upon reviewing it!!!!! 
josephsteed177@gmail.com
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include<iostream>	
#include<iomanip>
#include<string>
#include<limits>
#include<fstream>
#include<string>
#include<sstream>


char const doGrade(double theirScore, double averageScore);

int main(int arc, char* argv[])
{
	VS_MEM_CHECK               // enable memory leak check

	//Apply Input and Output files

	std::cout << "Iteration" << std::endl; //fixme

	std::ifstream in(argv[1]);
	if (!in) 
	{ 
		std::cout << "input opening error" << std::endl;
		return 1;
	}
	std::ofstream out(argv[2]);
	if (!out)
	{
		std::cout << "output opening error" << std::endl;
		return 1;
	}

	std::cout << "Iteration" << std::endl; //Command Line Output Test to make sure program: CLOT
										   //has come to this point. Done a couple times in program.
	//Input the number of students and exams
	int numStudents;
	int numExams;
	std::string tempString;
	in >> numStudents >> numExams;

	
	std::cout << "Students and Exams:" << numStudents << numExams << std::endl; //CLOT

	//Create the array of pointer to array pointers
	std::string **names = new std::string*[numStudents]; //numStudents is the array Rows
	int **exams = new int*[numStudents]; //numStudents is the array Rows
	
	//Create the arrays of students & exams
	for (int i = 0; i < numStudents; ++i)
	{
		names[i] = new std::string[2]; 
		in >> names[i][0] >> names[i][1];  //first and last name stored
		exams[i] = new int[numExams]; 
		
		for (int x = 0; x < numExams; ++x)
		{
			in >> exams[i][x];  //Exam scores stored in loop
		}
	}
	std::cout << "Iteration" << std::endl; //CLOT

	double *averages = new double[numExams];  //Averages scored in array

	//calculate and store averages:
	for (int x = 0; x < numExams; ++x)
	{
		double sumScores = 0.0;
		for (int i = 0; i < numStudents; ++i)
		{
			sumScores += exams[i][x];
		}
		averages[x] = (sumScores / numStudents);
	}


	//Writing to file:

	out << "Student Scores:" << std::endl;  //Student scores section
	
	for (int i = 0; i < numStudents; ++i)
	{

		std::string fullNameString = names[i][0] + " " + names[i][1];
		
		out << std::fixed << std::setw(20) << std::right
			<< fullNameString << " ";
		for (int x = 0; x < numExams; ++x)
		{
			out << std::fixed << std::setw(7) << std::right
				<< exams[i][x];
		}
		out << std::endl;
	}

	std::cout << "Iteration" << std::endl; //CLOT


	out << "Exam Averages: " << std::endl; //Exam Averages section
	
	for (int x = 0; x < numExams; ++x)
	{
		out << "    Exam " << (x + 1) << " Average =   " 
			<< std::setprecision(1) << averages[x] << std::endl;
	}
	
	std::cout << "Iteration" << std::endl; //Fixme

	out << "Student Exam Grades:" << std::endl;  //Student Exam Grades Section

	for (int i = 0; i < numStudents; ++i)
	{

		std::string fullNameString = names[i][0] + " " + names[i][1];

		out << std::fixed << std::setw(20) << std::right
			<< fullNameString;

		for (int x = 0; x < numExams; ++x)
		{
			//Each exam score and grade
			out << std::fixed << std::setw(6) << std::right
				<< exams[i][x] << "(" << doGrade(exams[i][x], averages[x])
				<< ")";

		}
		out << std::endl;
		
	}

	std::cout << "Iteration" << std::endl; //CLOT

	out << "Exam Grades:" << std::endl;  //Exam Grades section

	for (int x = 0; x < numExams; ++x)
	{
		out << "    Exam  " << (x + 1);

		//Find number of grades for A, B, C, etc.
		int A = 0, B = 0, C = 0, D = 0, E = 0;
		for (int i = 0; i < numStudents; ++i)
		{
			switch (doGrade(exams[i][x], averages[x]))
			{
				case 'A':
					A++;
					break;
				case 'B':
					B++;
					break;
				case 'C':
					C++;
					break;
				case 'D':
					D++;
					break;
				case 'E':
					E++;
					break;
			}
		}

		//Output amount of each grade for test
		out << std::fixed << std::setw(5) << std::right
			<< A << "(A)";
		out << std::fixed << std::setw(5) << std::right
			<< B << "(B)";
		out << std::fixed << std::setw(5) << std::right
			<< C << "(C)";
		out << std::fixed << std::setw(5) << std::right
			<< D << "(D)";
		out << std::fixed << std::setw(5) << std::right
			<< E << "(E)";
		out << std::endl;
	}

	std::cout << "Iteration" << std::endl; //CLOT

	out << "Student Final Grades:" << std::endl; //Final grades section

	//Calculate Class Average
	double aveSum = 0.0;
	for (int x = 0; x < numExams; ++x)
	{
		aveSum += averages[x];
	}
	double classAverage = (aveSum / numExams);


	for (int i = 0; i < numStudents; ++i)
	{
		//Names
		std::string fullNameString = names[i][0] + " " + names[i][1];
		
		out << std::fixed << std::setw(20) << std::right
			<< fullNameString << " ";

		//Calculate Student average in each iteration, for each loop output
		int thisStudentSum = 0;
		for (int x = 0; x < numExams; ++x)
		{
			thisStudentSum += exams[i][x];
		}
		//Needs to be floating point division.
		double thisStudentAverage = (thisStudentSum / static_cast<double>(numExams));

		out << std::fixed << std::setw(5) << std::right
			<< std::setprecision(1) << thisStudentAverage << "("
			<< doGrade(thisStudentAverage, classAverage) << ")";
		out << std::endl;
	}

	//Final Ave score
	out << "Class Average Score = " << std::setprecision(1) << classAverage; 

	std::cout << "Iteration" << std::endl;  //CLOT

	//Free the Allocated memory

	for (int i = 0; i < numStudents; ++i)
	{
		delete[] names[i];  //Each row etc
		delete[] exams[i];
	}
	delete[] exams;
	delete[] names;
	delete[] averages;

	//Close files
	in.close();
	out.close();

	return 0;
}

/** 
@param theirScore The score you are deciding to compare with average. 
@param averageScore The average score (which will be a C)
@return Grade The returned character of this instance's grade.
*/
char const doGrade(double theirScore, double averageScore) 
{
	char grade;
	double gradeScore = static_cast<double>(theirScore) - averageScore; //Static cast so you can pass in ints.
	if (gradeScore >= 15.0) { grade = 'A'; } 
	else if (gradeScore > 5.0) { grade = 'B'; }
	else if (gradeScore <= 5.0 && gradeScore >= -5.0) { grade = 'C'; }
	else if (gradeScore < -5.0 && gradeScore > -15.0) { grade = 'D'; }
	else { grade = 'E'; }
	return grade;
}


/*
This is the code to copy from one file to the other:

while (!in.eof())
	{
		std::string inputStream;
		getline(in, inputStream);
		out << inputStream << std::endl;
	}
*/