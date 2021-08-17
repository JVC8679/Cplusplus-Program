//================================================
// Name        : CS 210 Project 3.cpp
// Author      : James Carver
// Version     :
// Copyright   : CS210-SNHU
// Description : The Corner Grocer
//================================================

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include<iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the int parameter you want to send
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
// Diplays main menu
void menu() {
	cout << "************************************** \n";
	cout << "1: List all items with totals. \n";
	cout << "2: Enter an item to display its total. \n";
	cout << "3: Display graph of all items. \n";
	cout << "4: Exit \n";
	cout << "Enter your selection 1, 2, 3, or 4 \n";
	cout << "************************************** \n";
}

void printHistogram() {
	// inFile object to read the file
	fstream inFile;
	// open the file
	inFile.open("frequency.dat");
	// if file did not open successfully
	if (inFile.fail())
	{
		cout << "Your file did not open successfully" << endl;
	}
	// if file opened successfully
	else {
		string item, freq;
		// read item and frequency line by line
		while (inFile >> item >> freq) {
			// align * in same column
			int spaces = 20 - item.length();
			// print the item name and leave the spaces
			cout << item << setw(spaces);
			// print the *  equal to frequency
			for (int i = 1; i <= stoi(freq); i++)
				cout << "*";
			
			cout << endl;
		}
	}
	// close the file
	inFile.close();
}

void main()
{
	int userSel;
	string userItem;
	menu();
	cin >> userSel;

	// Validates user input
	while (userSel != 4) {
		switch (userSel) {
			case 1:
				//Calls Python funtion
				CallProcedure("printlist");
				menu();
				cin >> userSel;
				break;
			case 2:
				cout << "Enter item." << endl;
				cin >> userItem;
				//Calls Python funtion
				cout << callIntFunc("printitem", userItem) << endl; 
				menu();
				cin >> userSel;
				break;
			case 3:
				//Calls Python funtion
				CallProcedure("itemprinter");
				printHistogram();
				menu();
				cin >> userSel;
				break;
			case 4:
				cout << "Good bye." << endl;
				break;
			default:
				//Error message for invalid input
				cout << "Invalid selection." << endl;
				cin.clear();
				cin.ignore();
				menu();
				cin >> userSel;
				break;
		}

	}
}