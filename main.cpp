#include <bits/stdc++.h>
using namespace std;

struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

pair<double, double> A;

void FCFS_scheduling(vector<process> &processes, const int &num_processes)
{
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         { return a.arrival_time < b.arrival_time; });

    int start[num_processes], end[num_processes], waiting[num_processes], turnaround[num_processes];

    cout << "\nFCFS Scheduling:\n\n";
    int current_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    for (const process &process : processes)
    {
        // Wait if the process hasn't arrived yet
        if (current_time < process.arrival_time)
        {
            current_time = process.arrival_time;
        }

        // Execute the process
        start[process.id - 1] = current_time;
        current_time += process.burst_time;
        start[process.id - 1] = current_time;
        turnaround[process.id - 1] = current_time - process.arrival_time;
        waiting[process.id - 1] = turnaround[process.id - 1] - process.burst_time;
        total_turnaround_time += turnaround[process.id - 1];
        total_waiting_time += waiting[process.id - 1];
    }

    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         { return a.id < b.id; });

    for (const process &process : processes)
    {
        cout << "process " << process.id << " executed during time " << start[process.id - 1];
        cout << " to " << end[process.id - 1] << " unit" << endl;
        cout << "Turn Around Time for process " << process.id << " is " << turnaround[process.id - 1] << " unit" << endl;
        cout << "Waiting Time for process " << process.id << " is " << waiting[process.id - 1] << " unit\n"
             << endl;
    }

    A.second = static_cast<double>(total_waiting_time) / num_processes;
    A.first = static_cast<double>(total_turnaround_time) / num_processes;
}

void SJF_scheduling(vector<process> &processes, const int &num_processes)
{
    // Considering this algo to be Preemptive
    int bursttime[num_processes];
    for (int i = 0; i < num_processes; i++)
    {
        bursttime[processes[i].id - 1] = processes[i].burst_time;
    }
    // Sort processes primarily by arrival time, secondarily by burst time
    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         {
        if (a.arrival_time == b.arrival_time) {
            return a.burst_time < b.burst_time;
        }
        return a.arrival_time < b.arrival_time; });

    vector<vector<int>> execution(num_processes);
    cout << "\nSJF Scheduling:\n"
         << endl;
    int current_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int processes_completed = 0;

    while (processes_completed < num_processes)
    {
        int index = -1;
        for (int i = 0; i < num_processes; ++i)
        {
            if (processes[i].arrival_time <= current_time && processes[i].burst_time > 0)
            {
                if (index == -1 || processes[i].burst_time < processes[index].burst_time)
                {
                    index = i;
                }
            }
        }

        if (index == -1)
        {
            // No process is ready to execute, move to the next available process's arrival time
            current_time++;
            continue;
        }

        process &process = processes[index];
        process.burst_time--;
        execution[process.id - 1].push_back(current_time);

        if (process.burst_time == 0)
        {
            processes_completed++;
        }

        current_time++;
    }

    // Sort processes back by their IDs for output consistency
    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         { return a.id < b.id; });

    // Print the execution times for each process
    for (const process &process : processes)
    {
        cout << "process " << process.id << " executed during time ";
        if (execution[process.id - 1].empty())
        {
            cout << "no time";
        }
        else
        {
            int start = execution[process.id - 1][0], end = execution[process.id - 1][0];
            for (size_t i = 1; i < execution[process.id - 1].size(); ++i)
            {
                if (execution[process.id - 1][i] == execution[process.id - 1][i - 1] + 1)
                {
                    end = execution[process.id - 1][i];
                }
                else
                {
                    if (start == end)
                    {
                        cout << start << " to " << start + 1;
                    }
                    else
                    {
                        cout << start << " to " << end + 1;
                    }
                    cout << ", ";
                    start = end = execution[process.id - 1][i];
                }
            }
            int completion_time = 0;
            if (start == end)
            {
                cout << start << " to " << start + 1 << " unit";
                completion_time = start + 1;
            }
            else
            {
                cout << start << " to " << end + 1 << " unit";
                completion_time = end + 1;
            }
            int turnaroundtime = completion_time - process.arrival_time;
            int waitingtime = turnaroundtime - bursttime[process.id - 1];
            cout << "\nTurn Around Time for process " << process.id << " is " << turnaroundtime << " unit" << endl;
            cout << "Waiting Time for process " << process.id << " is " << waitingtime << " unit"
                 << endl;
            total_waiting_time += waitingtime;
            total_turnaround_time += turnaroundtime;
        }
        cout << endl;
    }

    A.second = static_cast<double>(total_waiting_time) / num_processes;
    A.first = static_cast<double>(total_turnaround_time) / num_processes;
}

void P_scheduling(vector<process> &processes, const int &num_processes)
{
    // Considering this algo to be Preemptive
    int bursttime[num_processes];
    for (int i = 0; i < num_processes; i++)
    {
        bursttime[processes[i].id - 1] = processes[i].burst_time;
    }
    // Sort processes primarily by arrival time, secondarily by burst time
    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         {
        if (a.arrival_time == b.arrival_time) {
            return a.priority > b.priority;
        }
        return a.arrival_time < b.arrival_time; });

    vector<vector<int>> execution(num_processes);
    cout << "\nPriority Scheduling:\n"
         << endl;
    int current_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int processes_completed = 0;

    while (processes_completed < num_processes)
    {
        int index = -1;
        for (int i = 0; i < num_processes; ++i)
        {
            if (processes[i].arrival_time <= current_time && processes[i].burst_time > 0)
            {
                if (index == -1 || processes[i].priority > processes[index].priority)
                {
                    index = i;
                }
            }
        }

        if (index == -1)
        {
            // No process is ready to execute, move to the next available process's arrival time
            current_time++;
            continue;
        }

        process &process = processes[index];
        process.burst_time--;
        execution[process.id - 1].push_back(current_time);

        if (process.burst_time == 0)
        {
            processes_completed++;
        }

        current_time++;
    }

    // Sort processes back by their IDs for output consistency
    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         { return a.id < b.id; });

    // Print the execution times for each process
    for (const process &process : processes)
    {
        cout << "process " << process.id << " executed during time ";
        if (execution[process.id - 1].empty())
        {
            cout << "no time";
        }
        else
        {
            int start = execution[process.id - 1][0], end = execution[process.id - 1][0];
            for (size_t i = 1; i < execution[process.id - 1].size(); ++i)
            {
                if (execution[process.id - 1][i] == execution[process.id - 1][i - 1] + 1)
                {
                    end = execution[process.id - 1][i];
                }
                else
                {
                    if (start == end)
                    {
                        cout << start << " to " << start + 1;
                    }
                    else
                    {
                        cout << start << " to " << end + 1;
                    }
                    cout << ", ";
                    start = end = execution[process.id - 1][i];
                }
            }
            int completion_time = 0;
            if (start == end)
            {
                cout << start << " to " << start + 1 << " unit";
                completion_time = start + 1;
            }
            else
            {
                cout << start << " to " << end + 1 << " unit";
                completion_time = end + 1;
            }
            int turnaroundtime = completion_time - process.arrival_time;
            int waitingtime = turnaroundtime - bursttime[process.id - 1];
            cout << "\nTurn Around Time for process " << process.id << " is " << turnaroundtime << " unit" << endl;
            cout << "Waiting Time for process " << process.id << " is " << waitingtime << " unit"
                 << endl;
            total_waiting_time += waitingtime;
            total_turnaround_time += turnaroundtime;
        }
        cout << endl;
    }

    A.second = static_cast<double>(total_waiting_time) / num_processes;
    A.first = static_cast<double>(total_turnaround_time) / num_processes;
}

void RR_scheduling(vector<process> &processes, const int &num_processes, const int &time_quantum)
{
    queue<process *> process_queue;
    int current_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int processes_completed = 0;
    cout << "\nRound Robin Scheduling:\n"
         << endl;

    vector<pair<int, int>> execution[num_processes];

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         { return a.arrival_time < b.arrival_time; });

    // Add initial processes to the queue
    auto process_it = processes.begin();
    while (process_it != processes.end() && process_it->arrival_time <= current_time)
    {
        process_queue.push(&(*process_it));
        process_it++;
    }

    while (processes_completed < num_processes)
    {
        if (!process_queue.empty())
        {
            process *process = process_queue.front();
            process_queue.pop();

            int exec_time = min(time_quantum, process->remaining_time);

            execution[process->id - 1].emplace_back(current_time, current_time + exec_time);
            process->remaining_time -= exec_time;
            current_time += exec_time;

            // Add new processes to the queue that have arrived
            while (process_it != processes.end() && process_it->arrival_time <= current_time)
            {
                process_queue.push(&(*process_it));
                process_it++;
            }

            if (process->remaining_time > 0)
            {
                process_queue.push(process);
            }
            else
            {
                int turnaround_time = current_time - process->arrival_time;
                int waiting_time = turnaround_time - process->burst_time;

                total_turnaround_time += turnaround_time;
                total_waiting_time += waiting_time;
                processes_completed++;
            }
        }
        else
        {
            current_time++;
        }
    }
    sort(processes.begin(), processes.end(), [](const process &a, const process &b)
         { return a.id < b.id; });

    for (const process &process : processes)
    {
        cout << "process " << process.id << " executed during time ";
        for (const auto &period : execution[process.id - 1])
        {
            cout << period.first << " to " << period.second << (period == execution[process.id - 1].back() ? " unit" : ", ");
        }
        cout << endl;
        int turnaround_time = execution[process.id - 1].back().second - process.arrival_time;
        int waiting_time = turnaround_time - process.burst_time;
        cout << "Turn Around Time for process " << process.id << " is " << turnaround_time << " unit" << endl;
        cout << "Waiting Time for process " << process.id << " is " << waiting_time << " unit\n"
             << endl;
    }

    A.second = static_cast<double>(total_waiting_time) / num_processes;
    A.first = static_cast<double>(total_turnaround_time) / num_processes;
}

int main()
{
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<process> processes(num_processes);
    cout << "Enter process details (arrival time, burst time, priority):\n";
    for (int i = 0; i < num_processes; ++i)
    {
        processes[i].id = i + 1;
        cout << "process " << processes[i].id << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].remaining_time = processes[i].burst_time;
    }

    cout << "Select the scheduling algorithm:\n"
         << "1. First Come First Served Scheduling Algorithm\n"
         << "2. Shortest Job First Preemptive Scheduling Algorithm\n"
         << "3. Priority Preemptive Scheduling Algorithm\n"
         << "4. Round Robin Scheduling Algorithm\n\n";

    bool a = true;

    int algo_want;
    cin >> algo_want;
    if (algo_want == 1)
    {
        FCFS_scheduling(processes, num_processes);
    }
    else if (algo_want == 2)
    {
        SJF_scheduling(processes, num_processes);
    }
    else if (algo_want == 3)
    {
        P_scheduling(processes, num_processes);
    }
    else if (algo_want == 4)
    {
        int time_quantum;
        cout << "\nEnter the time quantum for Round Robin scheduling: ";
        cin >> time_quantum;
        RR_scheduling(processes, num_processes, time_quantum);
    }
    else
    {
        a = false;
        cout << "Enter Valid Inputs\n";
    }
    if (a)
    {
        cout << "Average Turn Around Time: " << A.first << " unit" << endl;
        cout << "Average Waiting Time: " << A.second << " unit" << endl;
    }

    return 0;
}
