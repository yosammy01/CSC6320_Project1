// CSC6320_Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int Check_Format(int argc, char* argv[])
{
    // do check for proper argument format
    if (argc != 3)
    {
        cout << "WRONG INPUT FORMAT! \n" << endl;
        cout << "Proper input format:" << endl;
        cout << "[executable name] [path to file] [filename]\n" << endl;
        cout << "Example:" << endl;
        cout << "CSC6320_project1 " << "C:\\temp " << "process.txt" << endl;
        return 1;
    }
    cout << "Argument count is correct." << endl;
    cout << "Arguments = " << argc << endl;

    // loop through arguments
    int i = 0;
    for (int i = 0; i < argc; i++)
    {
        cout << "Argument " << i << " = " << argv[i] << endl;
    }
    return 0;
}



int main(int argc, char* argv[])
{
    // check for argument format errors
    if (Check_Format(argc, argv))
    {
        return 0;
    }

    // read data file and assume proper data format.
    string filePath = argv[1];
    filePath.append("\\");
    filePath.append(argv[2]);
    cout << "File path = " + filePath << endl;
    ifstream dataFile(filePath);

    if (!dataFile.is_open())
    {
        cout << "ERROR OPENING FILE!" << endl;
        return 0;
    }
    cout << "Data file contents:" << endl;

    //read data line-by-line and store in a vector of integer vectors that will store the data.
    vector<int> dataVector = {0,0,0,0};
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

    // display the data stored in dataVectorList memory.
    for (int i=0; i<(int)dataVectorList.size(); i++)
    {
        cout << "dataVectorList[" << i << "] = ";
        for (int j=0; j<(int)dataVector.size(); j++)
        {
            cout << dataVectorList[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}