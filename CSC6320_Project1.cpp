// CSC6320_Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using std::cout;

// ---------------------------------------------------------------------------
// Debugging output - display the data stored in dataVectorList memory.
// ---------------------------------------------------------------------------
void PrintdataVectorList(vector<vector<int>> &dataVectorList)
{
    cout << endl;
    cout << "+PrintdataVectorList" << endl;

    for (int i = 0; i < (int)dataVectorList.size(); i++)
    {
        cout << "dataVectorList[" << i << "] = ";
        for (int j = 0; j < (int)dataVectorList[i].size(); j++)
        {
            cout << dataVectorList[i][j] << " ";
        }
        cout << endl;
    }

    cout << "-PrintdataVectorList" << endl;
    cout << endl;
    return;
}

// ---------------------------------------------------------------------------
// 1. do check for proper argument format
// 2. if not correct, retrun 1 and end the program.
// 3. if correct, return 0 and continue the program.
// ---------------------------------------------------------------------------
int Check_Format(int argc, char* argv[])
{
    cout << "+Check_Format" << endl;

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
        cout << "+Check_Format" << endl;
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

    cout << "-Check_Format" << endl;
    cout << endl;
    return 0;
}

// ---------------------------------------------------------------------------
// 1. read data file and assume proper data format.
// 2. if cannot open the file for some reason, display error.
// 3. return the ifstream to check if it is true (open) or false(not open).
// ---------------------------------------------------------------------------
ifstream ReadFile(char* argv[])
{
    cout << "+ReadFile" << endl;

    string filePath = argv[1];
    filePath.append("\\");
    filePath.append(argv[2]);
    cout << "File path = " + filePath << endl;
    ifstream dataFile(filePath);

    if (!dataFile.is_open())
    {
        cout << "ERROR OPENING FILE!" << endl;
        cout << "-ReadFile" << endl;
        return dataFile;
    }

    cout << "-ReadFile" << endl;
    cout << endl;
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
    cout << "+GetVectorListOfDataVectors" << endl;

    vector<int> dataVector = { 0,0,0,0 };
    vector<vector<int>> dataVectorList;
    string line;
    string word;

    cout << "File Contents:" << endl;
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
    if (!(dataVectorList.size() == 0 || dataVectorList.size() == 1))
    {
        PrintdataVectorList(dataVectorList);
    }
    // ---------------------------------------------------------------------

    cout << "-GetVectorListOfDataVectors" << endl;
    return dataVectorList;
}

// ----------------------------------------------------------------------------
// Shortest Job First (SJF) - The process with the smallest burst time runs first. 
// 1. Sort the dataVectorList by Burst Time (dataVectorList[i][2])
// ----------------------------------------------------------------------------
void SortSJF(vector<vector<int>>& dataVectorList)
{
    cout << "+SortSJF" << endl;

    // no sorting necessary if 0 or 1 process only
    if (dataVectorList.size() == 0 || dataVectorList.size() == 1)
    {
        cout << "-SortSJF" << endl;
        return;
    }

    int shortest;
    vector<int> temp;

    // loop though the dataVectors one-by-one
    for (int i = 0; i < (int)dataVectorList.size() - 1; i++)
    {
        // assume current process in process list has shorter burst time than 
        // remaining processes in the list.
        shortest = i;

        // loop though the remaining dataVectors one-by-one
        for (int j = i + 1; j < (int)dataVectorList.size(); j++)
        {
            // if current earliest process's burst time is larger than the next process,
            // then set earliest to the next process.
            if (dataVectorList[i][2] > dataVectorList[j][2])
            {
                shortest = j;

                // now swap the new earliest process with the current process.
                temp = dataVectorList[shortest];
                dataVectorList[shortest] = dataVectorList[i];
                dataVectorList[i] = temp;
            }
            // if current earliest process's burst time is same as the next process, 
            // then skip to the next process because this one will run before the next 
            // process because this one was first in the process list.
            // Note: I asked the professor how to deal with two processes that had same 
            // burst time, she advised that the first in the process.txt would be run 
            // first.
            else if (dataVectorList[i][2] == dataVectorList[j][2])
            {
                // order by processid.
                // 1. processid should never match.
                // 2. if previous processid is less than next, no need to swap.
                if (dataVectorList[i][0] <= dataVectorList[j][0])
                {

                }
                // if previous processid is greater than next, swap.
                else if (dataVectorList[i][0] > dataVectorList[j][0])
                {
                    shortest = j;

                    // now swap the new earliest process with the current process.
                    temp = dataVectorList[shortest];
                    dataVectorList[shortest] = dataVectorList[i];
                    dataVectorList[i] = temp;
                }

            }
        }
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    PrintdataVectorList(dataVectorList);
    // ---------------------------------------------------------------------

    cout << "-SortSJF" << endl;
    return;
}


// ----------------------------------------------------------------------------
// First-Come, First-Served (FCFS) - The first process that arrives runs first.
// 1. Sort the dataVectorList by Arrival Time (dataVectorList[i][1])
// ----------------------------------------------------------------------------
void SortFCFS(vector<vector<int>> &dataVectorList)
{
    cout << "+SortFCFS" << endl;

    // no sorting necessary if 0 or 1 process only
    if (dataVectorList.size() == 0 || dataVectorList.size() == 1)
    {
        cout << "-SortFCFS" << endl;
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

    cout << "-SortFCFS" << endl;
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
// -------------------------------------------------------------------------
void CalculateWaitTimeFCFS(vector<vector<int>>& dataVectorList)
{
    cout << "+CalculateWaitTimeFCFS" << endl;

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

    cout << "-CalculateWaitTimeFCFS" << endl;
    return;
}


// -------------------------------------------------------------------------
// Calculate turnaround time for each process and add new "Turnaround" data
// column to the dataVectors in the dataVectorList.
// NOTE: Turnaround time is measured from submission to completion.
// NOTE: Turnaround time = Wait time + Burst time, for the FCFS algorithm.
// -------------------------------------------------------------------------
void CalculateTurnaroundTimeFCFS(vector<vector<int>>& dataVectorList)
{
    cout << "+CalculateTurnaroundTimeFCFS" << endl;

    // loop through the data vectors and add the new column of data.
    for (int i = 0; i < (int)dataVectorList.size(); i++)
    {
        dataVectorList[i].push_back(dataVectorList[i][4] + dataVectorList[i][2]);
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    PrintdataVectorList(dataVectorList);
    // ---------------------------------------------------------------------

    cout << "-CalculateTurnaroundTimeFCFS" << endl;
    return;
}

// -------------------------------------------------------------------------
// Calculate wait time for each process and add new "WaitTime" data column
// to the dataVectors in the dataVectorList.
// NOTE: Wait time = sum(Turnaround time of previous processes) - Arrival
// time.
// -------------------------------------------------------------------------
// Calculate turnaround time for each process and add new "Turnaround" data
// column to the dataVectors in the dataVectorList.
// NOTE: Turnaround time is measured from submission to completion.
// NOTE: Turnaround time = Wait time + Burst time, for the SJF algorithm.
// -------------------------------------------------------------------------
// Test cases:
// 1. [DONE] need case where arrival time order is opposite direction to the 
// Burst order.
// 2. [DONE] need case where arrival time exactly matches the previous process
// completion time.
// 3. [DONE] need case where arrival times are over a second after the previous 
// process completes - there is wait time.
// -------------------------------------------------------------------------
void CalculateWaitTimeAndTurnaroundSJF(vector<vector<int>>& dataVectorList)
{
    cout << "+CalculateWaitTimeAndTurnaroundSJF" << endl;

    int waitTime = 0;
    int turnaroundTime = 0;
    int burstTime = 0;
    int arrivalTime = 0;

    // loop through dataVectorList
    for (int i = 0; i < dataVectorList.size(); i++)
    {
        waitTime = 0;
        burstTime = dataVectorList[i][2];

        // first process has no wait time and turnaroundTime = Burst time.
        if (i == 0)
        {
            turnaroundTime = burstTime;
            dataVectorList[i].push_back(waitTime);
            dataVectorList[i].push_back(turnaroundTime);
            continue;
        }

        // calculate waitTime
        // waitTime = sum(all previous turnaroundTime) - Arrival time.
        for (int j=i-1; j>=0; j--)
        {
            // the first process has turnaroundTime = Burst time.
            // we need to add the arrival time to the wait time for the
            // first process, to calculate the proceeding wait process 
            // waitTimes.
            if (j==0)
            {
                waitTime = waitTime + dataVectorList[j][5] + dataVectorList[j][1];
            }
            // other processes have turnaroundTime = waitTime + burstTime
            else
            {
                waitTime = waitTime + dataVectorList[j][2];
            }
        }
        arrivalTime = dataVectorList[i][1];
        waitTime = waitTime - arrivalTime;

        if (waitTime < 0)
        {
            waitTime = 0;
        }
        dataVectorList[i].push_back(waitTime);

        // calculate turnaroundTime
        turnaroundTime = waitTime + burstTime;
        dataVectorList[i].push_back(turnaroundTime);
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    PrintdataVectorList(dataVectorList);
    // ---------------------------------------------------------------------

    cout << "-CalculateWaitTimeAndTurnaroundSJF" << endl;
    return;
}

void PrintOutGanttChart(vector<vector<int>> &startAndEndTimes)
{
    int currentTimeStamp = 0;

    cout << "GANTT CHART (Execution Order):" << endl;
    cout << "|     Process     | |     Process     |..." << endl;
    cout << "|StartTime EndTime| |StartTime EndTime|..." << endl;
    cout << endl;

    // loop through and print processes out in order from first to last.
    for (int i = 0; i < (int)startAndEndTimes.size(); i++)
    {
        // first print out pipe "|".
        cout << "|";
        cout << "P" << startAndEndTimes[i][0];
        cout << " | ";
    }
    cout << endl;

    // loop though and print start and end times of each process.
    for (int i = 0; i < (int)startAndEndTimes.size(); i++)
    {
        // first print out pipe "|".
        cout << "|";

        // print out the start time
        cout << startAndEndTimes[i][1];

        // print out spaces and end time of process.
        cout << " ";
        cout << startAndEndTimes[i][2];
        cout << "| ";
    }

    cout << endl;
    cout << endl;
    return;
}

// diplay output in Gantt Chart
void DisplayGanttChart(vector<vector<int>>& dataVectorList)
{
    cout << "+DisplayGanttChart" << endl;

    vector<vector<int>> startAndEndTimes;
    int startTime = 0;
    int endTime = 0;
    int processId = 0;

    // loop through each dataVector and save the start and end times of each 
    // process in a new data structure, to use when displaying the Gantt Chart.
    // Start Time = Arrival Time + Wait Time.
    // End Time = Arrival Time + Turnaround Time;
    for (int i=0; i<(int)dataVectorList.size(); i++)
    {
        processId = dataVectorList[i][0];
        startTime = dataVectorList[i][1] + dataVectorList[i][4];
        endTime = dataVectorList[i][1] + dataVectorList[i][5];
        startAndEndTimes.push_back({processId, startTime, endTime });
    }

    // ---------------------------------------------------------------------
    // Debugging output - display the data stored in dataVectorList memory.
    // ---------------------------------------------------------------------
    cout << "ProcessId, Start Time, End Time" << endl;
    PrintdataVectorList(startAndEndTimes);
    // ---------------------------------------------------------------------

    // display the gantt chart
    PrintOutGanttChart(startAndEndTimes);

    cout << "-DisplayGanttChart" << endl;
    return;
}

// display the statistics for the process scheduling.
// 1. Waiting Time(WT) for each process
// 2. Turnaround Time(TAT) for each process
// 3. Average WT and TAT
void DisplayStatistics(vector<vector<int>> dataVectorList)
{
    cout << "+DisplayStatistics" << endl;
    
    float averageWaitTime = 0;
    float averageTurnaroundTime = 0;
    

    // Waiting Time(WT) for each process
    cout << endl;
    cout << "Wait Times:" << endl;
    for (int i=0; i<(int)dataVectorList.size(); i++)
    {
        averageWaitTime = averageWaitTime + dataVectorList[i][4];
        cout << "WT(P" << dataVectorList[i][0] << ") = " << dataVectorList[i][4] << endl;
    }
    averageWaitTime = averageWaitTime / dataVectorList.size();
    cout << endl;

    // Turnaround Time(TAT) for each process
    cout << "Turnaround Times:" << endl;
    for (int i = 0; i < (int)dataVectorList.size(); i++)
    {
        averageTurnaroundTime = averageTurnaroundTime + dataVectorList[i][5];
        cout << "TAT(P" << dataVectorList[i][0] << ") = " << dataVectorList[i][5] << endl;
    }
    averageTurnaroundTime = averageTurnaroundTime / dataVectorList.size();
    cout << endl;

    // Average WT and TAT
    cout << "Average Wait Time (WT) = " << averageWaitTime << endl;
    cout << "Average Turnaround Time (TAT) = " << averageTurnaroundTime << endl;
    cout << endl;

    cout << "-DisplayStatistics" << endl;
    return;
}

// -------------------------------------------------------------------------
// Simulate the SJF algorithm on the process list
// 
// NOTE: Burst time is time for process to complete it's cpu cycle.
// -------------------------------------------------------------------------
void SimulateSJF(vector<vector<int>>& dataVectorList)
{
    cout << "+SimulateSJF" << endl;

    // 1. calculate wait time for each process and add new "WaitTime" data
// column to the dataVectors in the dataVectorList.
    CalculateWaitTimeAndTurnaroundSJF(dataVectorList);

    // 3. display a Gantt Chart(Execution Order)
    DisplayGanttChart(dataVectorList);

    // 4. print out statistics
    DisplayStatistics(dataVectorList);

    cout << "-SimulateSJF" << endl;
    return;
}

// -------------------------------------------------------------------------
// Simulate the FCFS algorithm on the process list
// 
// NOTE: Arrival time is time process arrived in the waiting queue.
// -------------------------------------------------------------------------
void SimulateFCFS(vector<vector<int>> &dataVectorList)
{
    cout << "+SimulateFCFS" << endl;
    // 1. calculate wait time for each process and add new "WaitTime" data
    // column to the dataVectors in the dataVectorList.
    CalculateWaitTimeFCFS(dataVectorList);

    // 2. Calculate turnaround time for each process and add new "Turnaround"
    // data column to the dataVectors in the dataVectorList.
    CalculateTurnaroundTimeFCFS(dataVectorList);

    // 3. display a Gantt Chart(Execution Order)
    DisplayGanttChart(dataVectorList);

    // 4. print out statistics
    DisplayStatistics(dataVectorList);
    
    cout << "-SimulateFCFS" << endl;
    return;
}

// ---------------------------------------------------------------------------
// 1. checks the requested scheduling algorithm and calls specific functions 
// to handle the specific algorithms.
// ---------------------------------------------------------------------------
void SchedulingAlgortihm(vector<vector<int>> &dataVectorList, string algorithm)
{
    cout << "+SchedulingAlgortihm" << endl;
    // First Come, First Served - The first process that arrives runs first.
    if (algorithm == "FCFS" || algorithm == "fcfs")
    {
        cout << "First Come, First Served (FCFS) algorithm requested." << endl;
        // 1. sort the processes based on arrival time (dataVector[1]).
        SortFCFS(dataVectorList);

        // 2. simulate the FCFS process scheduling.
        SimulateFCFS(dataVectorList);

    }
    // Shortest Job First - The process with the smallest burst time runs first.
    else if (algorithm == "SJF" || algorithm == "sjf")
    {
        cout << "Shortest Job First (SJF) algorithm requested." << endl;
        // 1. sort the processes based on arrival time (dataVector[1]).
        SortSJF(dataVectorList);

        // 2. simulate the FCFS process scheduling.
        SimulateSJF(dataVectorList);
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

    cout << "-SchedulingAlgortihm" << endl;
    return;
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

    if (dataVectorList.size() == 1 || dataVectorList.size() == 0)
    {
        cout << "There are no processes to be scheduled." << endl;
        return 0;
    }

    // ----------------------------------------------
    // Step 2: Implement Two Scheduling Algorithms
    // ----------------------------------------------
    // process data using requested scheduling algorithm.
    SchedulingAlgortihm(dataVectorList, argv[3]);


    return 0;
}