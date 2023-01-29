#include <iostream>
using namespace std;

struct process {                // structure of each process
    int pid;                   
    int arrive_time;            
    int burst_time;
    int priority;
    bool completed;
    int start_time;
    int finishing_time;
    int turn_around_time;
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
    cout << "Enter the arrival time of process " << process << " : ";
    cin >> p[process-1].arrive_time;
    cout << "Enter the burst time of process " << process << " : ";
    cin >> p[process-1].burst_time;
    cout << "Enter the priority of process " << process << " : ";
    cin >> p[process-1].priority;
}
///////////////////////////////////////////////////////////////////
void priority_scheduling::show_details() {
    // represent all informations of processes
    for (int i=0; i<number_of_processes; i++) {
        cout << p[i].arrive_time << " " << p[i].burst_time << " " << p[i].priority << endl;
    }
}
//////////////////////////////////////////////////////////////////
int main() {
    int n;
    cout << "Enter the number of total processes: ";
    cin >> n;
    priority_scheduling obj(n);
    obj.get_input();
    obj.show_details();
}