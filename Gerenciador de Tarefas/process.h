#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
#include <csignal>

#ifndef PROCESS_H
#define PROCESS_H

class Process {
    private:
        int pid;
        int ppid;
        double cpu;
        double memory;
        int threads;
        std::string name;
        std::map<int, std::vector<Process> > info;
    public:
        Process();

        void filemanipulation();
        void createjsonfile(int filter);
        void killProc(int pid);
        //void funcaoSignalHandler(int sig);
};

#endif // PROCESS_H
