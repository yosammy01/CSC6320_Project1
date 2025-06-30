// CSC6320_Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Debugging output - display the data stored in dataVectorList memory.
// ---------------------------------------------------------------------------
void PrintdataVectorList(vector<vector<int>> &dataVectorList)
{
    cout << endl;
    for (int i = 0; i < (int)dataVectorList.size(); i++)
    {
        cout << "dataVectorList[" << i << "] = ";
        for (int j = 0; j < (int)dataVectorList[i].size(); j++)
        {
            cout << dataVectorList[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

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
        cout << "Supported sheduling algorithm codes:" << endl;
        cout << "First-Come, First-Served - FCFS" << endl;
        cout << "Shortest Job First - SJF" << endl;
        //cout << "Round Robin - RR" << endl;
        //cout << "Priority Scheduling - PS" << endl;
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
    cout << endl;
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
// 
// Data Format:
// PID  Arrival_Time  Burst_Time  Priority 
// 1    0            5           2
// 2    2            3           1
// 3    4            2           3
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
    PrintdataVectorList(dataVectorList);
    // ---------------------------------------------------------------------

    return dataVectorList;
}


// ----------------------------------------------------------------------------
// First-Come, First-Served (FCFS) - The first process that arrives runs first.
// 1. Sort the dataVectorList by Arrival Time (dataVectorList[i][1])
// ----------------------------------------------------------------------------
void SortFCFS(vector<vector<int>> &dataVectorList)
{
    // no sorting necessary if 0 or 1 process only
    if (dataVectorList.size() == 0 || dataVectorList.size() == 1)
    {
        return;
    }

    int earliest;
    vector<int> temp;

    // loop though the dataVectors one-by-one
    for (int i = 0; i < (int)dataVectorList.size() - 1; i++)
    {
        // assume current process in process list arrived earlier than remaining processes in the list.
        earliest = i;

        // loop though the remaining dataVectors one-by-one
        for (int j = i+1; j < (int)dataVectorList.size(); j++)
        {
            // if current earliest process arrived later than the next process,
            // then set earliest to the next process.
            if (dataVectorList[i][1] > dataVectorList[j][1])
            {
                earliest = j;
            }

            // now swap the new earliest process with the current process.
            temp = dataVectorList[earliest];
            dataVectorList[earliest] = dataVectorList[i];
            dataVectorList[i] = temp;
        }
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    PrintdataVectorList(dataVectorList);
    // ---------------------------------------------------------------------

    return;
}

// -------------------------------------------------------------------------
// Calculate turnaround time for each process and add new "Turnaround" data
// column to the dataVectors in the dataVectorList.
// NOTE: Turnaround time is measured from submission to completion.
// NOTE: Turnaround time = Burst time, for the FCFS algorithm.
// -------------------------------------------------------------------------
void CalculateTurnaroundTimeFCFS(vector<vector<int>> &dataVectorList)
{
    // loop through the data vectors and add the new column of data.
    for (int i=0; i<(int)dataVectorList.size(); i++)
    {
        dataVectorList[i].push_back(dataVectorList[i][2]);
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    PrintdataVectorList(dataVectorList);
    // ---------------------------------------------------------------------

    return;
}

// -------------------------------------------------------------------------
// Calculate wait time for each process and add new "WaitTime" data column
// to the dataVectors in the dataVectorList.
// NOTE: Wait time = Sum(Burst time all previous processes) with accounting
// for arrival time, for the FCFS algorithm.
// -------------------------------------------------------------------------
// Test cases:
// 1. [DONE] need case where previous process ends at the exact time the 
// next process begins.
// 2. [DONE] need case where previous process ends seconds before the next 
// process begins.
// 3. [DONE] need case where next process is waiting for the previous 
// process to end.
// 4. [DONE] need case where next process is waiting for mutliple previous 
// processes to end.
void CalculateWaitTimeFCFS(vector<vector<int>>& dataVectorList)
{
    // state variables
    int currentTimeStamp = 0;
    int currentProcessArrivalTime = dataVectorList[0][1];
    int processCurrentlyRunning = 0;
    int waitTime = 0;
    int currentProcessIndex = 0;
    bool inBetween = true;
    bool skipping = false;
    bool executing = false;
    int executingProcess = 0;

    // simulate time passing
    while (currentProcessIndex < dataVectorList.size())
    {
        // ---------------------------------------------------------------------
        // Debugging output - display the data stored in dataVectorList memory.
        // ---------------------------------------------------------------------
        cout << "current time = " << currentTimeStamp << endl;
        // ---------------------------------------------------------------------
        
        // if currentProcesssArrivalTime == current time, the next process
        // is beginning.
        if (currentProcessArrivalTime == currentTimeStamp)
        {
            // in between last process ending and new process beginning
            if (inBetween)
            {
                // assign burst time.
                processCurrentlyRunning = dataVectorList[currentProcessIndex][2];

                // set state variables.
                inBetween = false;
                executing = true;
                executingProcess = currentProcessIndex;
            }
            // skipping time cycles while waiting for the next process to arrive.
            else if (skipping)
            {
                // assign burst time.
                processCurrentlyRunning = dataVectorList[currentProcessIndex][2];

                // set state variables.
                skipping = false;
            }
        }
        // the next process has not arrived yet. 
        else if (currentProcessArrivalTime > currentTimeStamp)
        {
            // not skipping time cycles while waiting for the next process. This
            // is where we begin the logic to wait for the next process.
            if (!skipping)
            {
                // assign burst time.
                processCurrentlyRunning = dataVectorList[currentProcessIndex][2];

                // set state variables.
                skipping = true;
                waitTime = 0;
                inBetween = false;
                executing = true;
            }
        }
        // the next process arrived while a previous process was running.
        else if (currentProcessArrivalTime < currentTimeStamp)
        {
            // no process is currently executing - currenTimeStamp will exceed the 
            // currentProcessArrivalTime during normal execution of a process.
            if (!executing)
            {
                // set the wait time for the next process
                waitTime = currentTimeStamp - currentProcessArrivalTime;
                processCurrentlyRunning = 0;

                // ---------------------------------------------------------------------
                // Debugging output - display the data stored in dataVectorList memory.
                // ---------------------------------------------------------------------
                cout << "process " << dataVectorList[currentProcessIndex][0] << " waited " << waitTime << endl;
                // ---------------------------------------------------------------------

                currentTimeStamp = currentTimeStamp + dataVectorList[currentProcessIndex][2];
            }


        }

        // skipping time cycles while waiting for the next process to arrive.
        if (skipping)
        {
            // ---------------------------------------------------------------------
            // Debugging output - display the data stored in dataVectorList memory.
            // ---------------------------------------------------------------------
            cout << "Awaiting next process arrival..." << endl;
            // ---------------------------------------------------------------------
        }
        // if process is running, decrement its count by 1 time unit each loop
        else if (processCurrentlyRunning)
        {

            // ---------------------------------------------------------------------
            // Debugging output - display the data stored in dataVectorList memory.
            // ---------------------------------------------------------------------
            cout << "Process " << dataVectorList[currentProcessIndex][0] << " running !!!" << endl;
            // ---------------------------------------------------------------------

            processCurrentlyRunning--;

        }
        // current process has completed execution
        else
        {
            // set state variables
            executing = false;

            // save the wait time for each process in the dataVector.
            dataVectorList[currentProcessIndex].push_back(waitTime);

            // start the next process and indicate we are wating for the next
            // process to begin.
            currentProcessIndex++;

            // not at the end of the vectorDataList
            if (currentProcessIndex < dataVectorList.size())
            {
                // set state variables.
                waitTime = 0;
                inBetween = true;

                // get the next process's arrival time
                currentProcessArrivalTime = dataVectorList[currentProcessIndex][1];
            }
            // there are no more processes to execute.
            else
            {
                break;
            }

        }

        // in between the previous and next process and the next process starts at 
        // the same time the previous process ends. So, do not increment the time.
        if (!inBetween)
        {
            currentTimeStamp++;
        }
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    PrintdataVectorList(dataVectorList);
    // ---------------------------------------------------------------------

    return;
}


// -------------------------------------------------------------------------
// NOTE: Turnaround time is time for process to complete from arrival to 
// done.
// NOTE: Burst time time is time for process to complete it's cpu and i/o 
// cycle.

// -------------------------------------------------------------------------
void SimulateFCFS(vector<vector<int>> &dataVectorList)
{
    int timeStamp = 0;
    int waitTime = 0;
    int turnaroundTime = 0;
    vector<vector<int>> newDataVector;

    // 1. Calculate turnaround time for each process and add new "Turnaround"
    // data column to the dataVectors in the dataVectorList.
    CalculateTurnaroundTimeFCFS(dataVectorList);

    // 2. calculate wait time for each process and add new "WaitTime" data
    // column to the datavectors in the dataVectorList.
    CalculateWaitTimeFCFS(dataVectorList);

    // 3. display a Gantt Chart(Execution Order)
    DisplayGanttChart(dataVectorList);
}

// ---------------------------------------------------------------------------
// 1. checks the requested scheduling algotithm and calls specific functions 
// to handle the specific algorithms.
// ---------------------------------------------------------------------------
void SchedulingAlgortihm(vector<vector<int>> &dataVectorList, string algorithm)
{

    // First Come, First Served - The first process that arrives runs first.
    if (algorithm == "FCFS")
    {
        // 1. sort the processes based on arrival time (dataVector[1]).
        SortFCFS(dataVectorList);

        // 2. simulate the FCFS process scheduling.
        SimulateFCFS(dataVectorList);

    }
    // Shortest Job First - The process with the smallest burst time runs first.
    else if (algorithm == "SJF")
    {
        cout << "Shortest Job First (SJF) algorithm requested." << endl;
    }
    // Round Robin - Each process gets a fixed time (time quantum), then the 
    // next process runs.
    //else if (algorithm == "RR")
    //{
    //    cout << "Round Robin (RR) algorithm requested." << endl;
    //}
    // Priority Scheduling - Processes with a higher priority run first.
    //else if (algorithm == "PS")
    //{
    //    cout << "Priority Scheduling (PS) algorithm requested." << endl;
    //}
    else
    {
        cout << algorithm << " algorithm not supported." << endl;
    }
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

    //read data line-by-line from the data file and store data in a vector of
    // integer vectors.
    vector<vector<int>> dataVectorList = GetVectorListOfDataVectors(dataFile);

    // ----------------------------------------------
    // Step 2: Implement Two Scheduling Algorithms
    // ----------------------------------------------
    // process data using requested scheduling algorithm.
    SchedulingAlgortihm(dataVectorList, argv[3]);


    return 0;
}