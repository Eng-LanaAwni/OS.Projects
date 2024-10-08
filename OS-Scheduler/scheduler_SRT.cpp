//Lana Alotoom 144806
//Eman Edries  152531
//Saba Mustafa 140454
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <climits>
#include <vector>
#include <cstdio>

using namespace std;

class Process {
public:
    string name;
    long at; // arrivaltime
    long pt; // proccessingtime
    long rt; // remainingtime
    long end_t; // endtime
    long rst; // responsetime
    long first_strt;
    long TAT; // turnaround time
    long delay; // waiting time
    long pid; // process id
};

void SRT(Process processes[], long Numofprocesses, ofstream &output) {
    vector<string> exec_order(Numofprocesses);
    long clock = 0; // current time
    long completed = 0; // number of processes that are done

    while (completed != Numofprocesses) {
        long min_idx = -1; // minimum index (process with the least remaining time)
        long min_remt = LONG_MAX; // minimum remaining time

        for (long i = 0; i < Numofprocesses; i++) {
            if (processes[i].at <= clock && processes[i].rt != 0) {
                if (processes[i].rt < min_remt) {
                	
                    min_remt = processes[i].rt;
                    min_idx = i;
                   
                }
                if(processes[i].rt==min_remt){
                	if(processes[i].at==processes[min_idx].at)
                	{
                		min_idx=min(processes[i].pid, processes[min_idx].pid);
                	}else{
                	
                		if(processes[i].at>processes[min_idx].at)
                		{
                			min_idx=processes[i].pid;
                		}else
                		{
                			min_idx=processes[min_idx].pid;
                		}
                	}
                
                }
            }
            
        }

        if (min_idx == -1) {
            clock++;
        } else {
            if (processes[min_idx].rt == processes[min_idx].pt) {
                processes[min_idx].first_strt = clock;
                	
                
            }
            processes[min_idx].rt -= 1;
            clock++;
            if (processes[min_idx].rt == 0) {
                processes[min_idx].end_t = clock;
                processes[min_idx].TAT = processes[min_idx].end_t - processes[min_idx].at;
                processes[min_idx].delay = processes[min_idx].TAT - processes[min_idx].pt;
                processes[min_idx].rst = processes[min_idx].first_strt - processes[min_idx].at;

                output << processes[min_idx].name << ": (end = " << processes[min_idx].end_t << ", turnaround = "
                       << processes[min_idx].TAT << ", delay = " << processes[min_idx].delay << ", Response = "
                       << processes[min_idx].rst << ")" << endl;
                completed++;
                exec_order[completed-1]=processes[min_idx].name;
            }
        }
    }
    	for(long i=0 ; i<Numofprocesses ; i++){
    		output<<exec_order[i];
    	}
}

int main() {
    ifstream input;
    ofstream output;
    input.open("in.txt");
    output.open("out.txt");

    if (!input.is_open()) {
        cerr << "Error opening input file" << endl;
        return 1;
    }
    if (!output.is_open()) {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    long Numofprocesses;
    input >> Numofprocesses;
    Process *processes = new Process[Numofprocesses];

    for (long i = 0; i < Numofprocesses; i++) {
        input >> processes[i].name >> processes[i].at >> processes[i].pt;
        processes[i].rt = processes[i].pt;
        processes[i].pid = i;
    }

    SRT(processes, Numofprocesses, output);

    delete[] processes;
    input.close();
    output.close();

    return 0;
}

