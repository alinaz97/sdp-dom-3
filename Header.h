#pragma once
#ifndef HEADER_H
#define HEADER_H
#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<string>

using namespace std;
const int NAME_LENGHT = 256;
const long long FN_SIZE = 1125899906842624;
const int ARRAY_SIZE = 1000000;
class Student
{
private:
	long long fn;
	char* first_name;
	char* last_name;
	int grade;

public:
	Student() :fn(0), grade(0) {}
	Student(const long long fnum, const char* fname, const char* lname, int grd)
	{
		fn = fnum;
		grade = grd;
		first_name = new char[(strlen(fname)) + 1];
		last_name = new char[(strlen(lname)) + 1];
		strcpy(first_name, fname);
		strcpy(last_name, lname);
	}
	Student(const Student& other)
	{
		fn = other.fn;
		grade = other.grade;
		strcpy(first_name, other.first_name);
		strcpy(last_name, other.last_name);
	}
	Student& operator=(const Student& other)
	{
		if (this != &other)
		{
			fn = other.fn;
			grade = other.grade;
			delete[] first_name;
			delete[] last_name;
			first_name = new char[(strlen(other.first_name)) + 1];
			last_name = new char[(strlen(other.last_name)) + 1];
			strcpy(first_name, other.first_name);
			strcpy(last_name, other.last_name);
		}
		return *this;
	}
	~Student()
	{
		delete[] first_name;
		delete[] last_name;
	}
	long long get_fn() const {
		return fn;
	}
	char* get_firstname() const
	{
		return first_name;
	}
	char* get_lastname() const
	{
		return last_name;
	}
	int get_grade() const
	{
		return grade;
	}
};


template <typename T>
void heapify(T arr[], T index[], int n, int i)
{
	int largest = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	
	if (l < n && arr[l] > arr[largest])largest = l;

	if (r < n && arr[r] > arr[largest])largest = r;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		swap(index[i], index[largest]);
		
		heapify(arr, index, n, largest);
	}
}

template <typename T>
void heapSort(T arr[], T index[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, index, n, i);
	}
	
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		swap(index[0], index[i]);
		heapify(arr,index, i, 0);
	}
}

void create()
{

	long long fnum;
	char fname[NAME_LENGHT];
	char lname[NAME_LENGHT];
	int grade;
	cin >> fnum;
	cin >> fname;
	cin >> lname;
	cin >> grade;

	if (fnum < FN_SIZE)
	{
		if (grade >= 2 && grade <= 6)
		{
			Student s(fnum, fname, lname, grade);
			ofstream file("StudentsGrades.db", ios::app);
			if (!file)
			{
				cout << "File couldn’t be opened!" << endl;
			}
			else
			{
				file << s.get_fn() << " " << s.get_firstname() << " " << s.get_lastname() << " " << s.get_grade() << endl;
				file.close();
				cout << "Record saved!" << endl;
			}
		}
		else cout << "Invalid grade! Please insert a grade between 2 and 6." << endl;
	}

	else cout << "Invalid faculty number!" << endl;
}

void buildIndex()
{
	fstream facultyfile("new.ids", ios::app);
	fstream gradesfile("StudentsGrades.db", ios::app);
	if (facultyfile && gradesfile)
	{
		long long arr[ARRAY_SIZE];
		long long index[ARRAY_SIZE];
		int arrayindex = 0;
		int currentline = 0;
		char c;
		string line;
		while (getline(gradesfile, line))
		{
			while (gradesfile.get(c))
			{
				if(c != ' ') arr[currentline] = arr[currentline] * 10 + (c - '0');
				else break;
			}
			index[arrayindex++] = currentline;
			gradesfile.seekp(line.length() + 1);
			currentline++;
		}
		gradesfile.seekp(0, ios::beg);
		gradesfile.close();

		heapSort(arr, index, currentline);

		for (int i = 0; i < currentline; i++)
		{
			facultyfile << arr[i] << " " << index[i] << endl;
		}

		facultyfile.seekp(0, ios::beg);
		facultyfile.close();

		remove("FacultyNumber.txt");
		rename("new.txt", "FacultyNumber.txt");
		cout << "Index is built!" << endl;
	}
}

void search()
{
	fstream facultyfile("FacultyNumber.ids", ios::app);
	fstream gradesfile("StudentsGrades.db", ios::app);
	string search;
	cin >> search;
	bool found = false;
	int currentline = 0;
	string line1;
	string line2;
	while (getline(facultyfile, line1))
	{
		if (search == line1.substr(0, search.length()))
		{
			found = true;
			int index = 0;
			int foundindex = search.length() + 1;
			facultyfile.seekp(foundindex);
			char c;
			while (facultyfile.get(c) && c != '\n')
			{
				index = index * 10 + (c - '0');
			}
			int i = 0;
			while (getline(gradesfile, line2))
			{
				if (i == index) break;
				else i++;
			}
			cout << line2 << endl;
			
			break;
		}
		facultyfile.seekp(line1.length() + 1);
		currentline++;
	}
	if (found == false)
	{
		cout << "Record not found!" << endl;
		create();
		buildIndex();
	}

	facultyfile.seekp(0, ios::beg);
	gradesfile.seekp(0, ios::beg);

	facultyfile.close();
	gradesfile.close();
}

void sequentialSearch()
{
	ifstream file("StudentsGrades.db");
	string search;
	cin >> search;
	bool found = false;
	int currentline = 0;
	string line;
	while (getline(file, line))
	{
		if (search == line.substr(0, search.length()))
		{
			cout << line << endl;
			found = true;
			break;
		}

		currentline++;
	}
	if (found == false) cout << "Record not found!" << endl;
	file.seekg(0, ios::beg);
	file.close();
}



#endif