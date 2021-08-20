// Cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

void CallProcedure(string pName);
int callIntFunc(string proc, string param);
int callIntFunc(string proc, int param);
void first_display();
void histogram();

int main()
{
	system("Color F4"); // To change background and text color in terminal
	int choice; // User input to choose from the given options
	int check; // Checks if the specified item in case 2 exists or not
	string item; // To store the specific item name that user inputs
	first_display(); // Method to display the options

	cout << "Enter Choice from 1-4" << endl;
	cin >> choice;
	cout << endl;

	// Switch case block 
	switch (choice)
	{
	case 1:
		CallProcedure("display_all_items"); // Calling the python function to display all of the items with their frequency
		break;

	case 2:
		cout << "Enter the Item Name" << endl; // Taking user input 
		cin >> item;
		// Calling the python function to return the frequency of the specific item and storing it in the variable check
		check = (callIntFunc("display_specific_items", item));
		if (check > 0) // Will return - 1 if the specified item does not exist
			cout << "The Frequency of " << item << " is : " << check << endl;
		else
			cout << "The Specified Item Does not Exist" << endl;
		break;

	case 3:
		CallProcedure("write_data"); // Python Function to write the data to frequency.dat file
		histogram(); // Cpp Function to print out the Text Based Histogram
		break;

	case 4:
		break; // Exit the program

	default:
		cout << "You Entered Incorrect Option" << endl; // Notify the user if the select option is invalid
		return 0;
	}

}


/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
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
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
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
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
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




void first_display() // Method to display the first menu to the user
{
	cout << "******************************************************************************************************\n" << endl;
	cout << "						Main Menu\n\n" << endl;
	cout << "	1 - All items purchased in a given day along with the number of times each item was purchased. " << endl;
	cout << "	2 - How many times a specific item was purchased in a given day. " << endl;
	cout << "	3 - Text-Based histogram listing all items purchased in a given day" << endl;
	cout << "	4 - Exit Application\n\n" << endl;
	cout << "******************************************************************************************************" << endl;
}

void histogram() // Method to display the text-based histogram
{

	string input;
	ifstream obj ("frequency.dat");
	while (getline (obj,input))
	{
		
		int i = 0;
		do
		{
			cout << input.at(i);
			i++;
		} 
		while (input.at(i) != ' ');

		cout << " ";

		string str = input.substr(i + 1, input.length() - 1);
		int num = stoi(str);
		
		for (int j = 0 ;j < num;j++)
		{
			cout << "*";

		}

		cout << endl;

	
	}

	obj.close();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
