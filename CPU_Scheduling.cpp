#include <iostream>
using namespace std;

struct process {                // structure of each process
    int pid;                   
    int arrive_time;            
    int burst_time;
    int remaining_burst_time;
    int priority;
    bool completed;
    int finishing_time;
    int turnaround_time;
    int waiting_time;
    int respond_time;
};
////////////////////////////////////////////////////////////////////
class priority_scheduling {         
    private:
        int clock;                 // stores current time
        int finished_processes;    // number of processes that their execution is finished by current time
        int number_of_processes;   // number of all existing processes
        struct process p[1000];    // stores all processes
    
    public:
        priority_scheduling(int);
        void get_input();
        void set_input(int);
        void show_details();
        void scheduling();
        void run(int);
        double calculate_turnaround();
        double calculate_waiting();
        double calculate_respond();
        double calculate_utilization();
        double calculate_throughput();
};
////////////////////////////////////////////////////////////////////
priority_scheduling::priority_scheduling(int n) {    // initializer 
    clock = 0;                         // set the time to 0
    finished_processes = 0;
    number_of_processes = n;
}
////////////////////////////////////////////////////////////////////
void priority_scheduling::get_input() {
    for (int i=1; i<=number_of_processes; i++) {
        set_input(i);             // set the properties of each process
    }
}
////////////////////////////////////////////////////////////////////
void priority_scheduling::set_input(int process) {
    p[process-1].pid = process;      // set the pid of the process to its number
    p[process-1].completed = false;      
    // cout << "Enter the arrival time of process " << process << " : ";
    cin >> p[process-1].arrive_time;
    // cout << "Enter the burst time of process " << process << " : ";
    cin >> p[process-1].burst_time;
    p[process-1].remaining_burst_time = p[process-1].burst_time;
    // cout << "Enter the priority of process " << process << " : ";
    cin >> p[process-1].priority;
}
///////////////////////////////////////////////////////////////////
void priority_scheduling::show_details() {
    // represent all informations of processes
    for (int i=0; i<number_of_processes; i++) {
        cout << p[i].arrive_time << " " << p[i].remaining_burst_time << " " << p[i].priority << endl;
    }
}
//////////////////////////////////////////////////////////////////
void priority_scheduling::scheduling() {
    // this is the main function that specifies the process that should be run in current time clock
    while (finished_processes != number_of_processes) {  // until the time that every processes are finished
        int selected_process = 0;
        int max_priority = 10000;
        for (int i=0; i<number_of_processes; i++) {      // check all processes and find the process with maximum
                                                         // priority by the current time 
            if (p[i].arrive_time<=clock && !p[i].completed && p[i].priority<max_priority) {
                max_priority = p[i].priority;
                selected_process = p[i].pid;
            }
        }
        run(selected_process);                  // execute the selected process
        clock += 1;                             // go for next time clock
    }
    
}
//////////////////////////////////////////////////////////////////
void priority_scheduling::run(int process) {    // execute the process for current time clock and update properties
    cout << "Process " << process << " is executing..." << endl;
    int index = process - 1;             // location of the process in the array of processes
    if (p[index].remaining_burst_time == p[index].burst_time) {
        p[index].respond_time = clock - p[index].arrive_time;
    }
    p[index].remaining_burst_time -= 1;
    if (p[index].remaining_burst_time == 0) {
        p[index].completed = true;
        finished_processes += 1;
        p[index].finishing_time = clock + 1;
        p[index].turnaround_time = p[index].finishing_time - p[index].arrive_time;
        p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
    }
    cout << "Finished. " << p[index].remaining_burst_time << " " << p[index].completed << endl;
}
//////////////////////////////////////////////////////////////////
double priority_scheduling::calculate_turnaround() {
    double sum = 0.0;
    for (int i=0; i<number_of_processes; i++) {
        sum += p[i].turnaround_time;
    }
    return sum / number_of_processes;
}
//////////////////////////////////////////////////////////////////
double priority_scheduling::calculate_waiting() {
    double sum = 0.0;
    for (int i=0; i<number_of_processes; i++) {
        sum += p[i].waiting_time;
    }
    return sum / number_of_processes;
}
//////////////////////////////////////////////////////////////////
double priority_scheduling::calculate_respond() {
    double sum = 0.0;
    for (int i=0; i<number_of_processes; i++) {
        sum += p[i].respond_time;
    }
    return sum / number_of_processes;
}
//////////////////////////////////////////////////////////////////
double priority_scheduling::calculate_utilization() {
    int total_burst_times = 0;
    double sum = 0.0;
    for (int i=0; i<number_of_processes; i++) {
        total_burst_times += p[i].burst_time;
    }
  
    return (total_burst_times / clock) * 100;
}
//////////////////////////////////////////////////////////////////
double priority_scheduling::calculate_throughput() {
    int latest_finished = 0, earliest_arrive = 10000;
    for (int i=0; i<number_of_processes; i++) {
        if (p[i].finishing_time > latest_finished) {
            latest_finished = p[i].finishing_time;
        }
        if (p[i].arrive_time < earliest_arrive) {
            earliest_arrive = p[i].arrive_time;
        }
    }
    double throughput = double(number_of_processes) / (latest_finished - earliest_arrive);
    return throughput;
}
//////////////////////////////////////////////////////////////////
int main() {
    int n;
    // cout << "Enter the number of total processes: ";
    cin >> n;
    priority_scheduling obj(n);
    obj.get_input();
    obj.show_details();
    obj.scheduling();
    cout << "Average TurnAround time: " << obj.calculate_turnaround() << endl;
    cout << "Average Waiting time: " << obj.calculate_waiting() << endl;
    cout << "Average Respond time: " << obj.calculate_respond() << endl;
    cout << "CPU utilization: " << obj.calculate_utilization() << "%" << endl;
    cout << "Throughput: " << obj.calculate_throughput() << endl;
}