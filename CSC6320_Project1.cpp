// CSC6320_Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// 1. do check for proper argument format
// 2. if not correct, retrun 1 and end the program.
// 3. if correct, return 0 and continue the program.
// ---------------------------------------------------------------------------
int Check_Format(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "WRONG INPUT FORMAT! \n" << endl;
        cout << "Proper input format:" << endl;
        cout << "[executable name] [path to file] [file name] [scheduling algorithm]\n" << endl;
        cout << "Example:" << endl;
        cout << "CSC6320_project1 " << "C:\\temp process.txt FCFS\n" << endl;
        cout << "Sheduling algorithm codes:" << endl;
        cout << "First-Come, First-Served - FCFS" << endl;
        cout << "Shortest Job First - SJF" << endl;
        cout << "Round Robin - RR" << endl;
        cout << "Priority Scheduling - PS" << endl;
        return 1;
    }

    // -------------------------------------------------------------
    // Debugging output - loop through arguments and print them out
    // -------------------------------------------------------------
    cout << "Argument count is correct." << endl;
    cout << "Arguments = " << argc << endl;
    int i = 0;
    for (int i = 0; i < argc; i++)
    {
        cout << "Argument " << i << " = " << argv[i] << endl;
    }
    // -------------------------------------------------------------

    return 0;
}

// ---------------------------------------------------------------------------
// 1. read data file and assume proper data format.
// 2. if cannot open the file for some reason, display error.
// 3. return the ifstream to check if it is true (open) or false(not open).
// ---------------------------------------------------------------------------
ifstream ReadFile(char* argv[])
{
    string filePath = argv[1];
    filePath.append("\\");
    filePath.append(argv[2]);
    cout << "File path = " + filePath << endl;
    ifstream dataFile(filePath);

    if (!dataFile.is_open())
    {
        cout << "ERROR OPENING FILE!" << endl;
        return dataFile;
    }

    // --------------------------------------
    // Debugging output
    // --------------------------------------
    cout << "Data file contents:" << endl;
    // --------------------------------------

    return dataFile;
}

// ---------------------------------------------------------------------------
// 1. read data line-by-line from the data file and store data in a vector of 
// integer vectors.
// 2. we are assuming the datafile is in proper format.
// 3. returns the dataVectorList.
// ---------------------------------------------------------------------------
vector<vector<int>> GetVectorListOfDataVectors(ifstream& dataFile)
{
    vector<int> dataVector = { 0,0,0,0 };
    vector<vector<int>> dataVectorList;
    string line;
    string word;

    int lineNumber = 0;
    while (getline(dataFile, line))
    {
        cout << line << endl;

        // Skip the first line containing the column names
        if (lineNumber == 0)
        {
            lineNumber++;
            continue;
        }

        // Extract words one by one until the end of each line and store in data vector
        istringstream iss(line);
        int wordCount = 0;
        while (iss >> word)
        {
            dataVector[wordCount] = stoi(word);
            wordCount++;
        }

        // store each data vector in the list of vectors
        dataVectorList.push_back(dataVector);
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    for (int i = 0; i < (int)dataVectorList.size(); i++)
    {
        cout << "dataVectorList[" << i << "] = ";
        for (int j = 0; j < (int)dataVector.size(); j++)
        {
            cout << dataVectorList[i][j] << " ";
        }
        cout << endl;
    }
    // ---------------------------------------------------------------------
    
    return dataVectorList;
}


int main(int argc, char* argv[])
{
    // check for argument format errors
    if (Check_Format(argc, argv))
    {
        return 0;
    }

    // ----------------------------------------------
    // Step 1: Read Process Data from a File
    // ----------------------------------------------
    
    // read data file and assume proper data format.
    ifstream dataFile = ReadFile(argv);

    // if data file not open or not in good state, end program.
    if (!dataFile)
    {
        return 0;
    }

    //read data line-by-line from the data file and store data in a vector of integer vectors.
    vector<vector<int>> dataVectorList = GetVectorListOfDataVectors(dataFile);

    // ----------------------------------------------
    // Step 2: Implement Two Scheduling Algorithms
    // ----------------------------------------------


    return 0;
}