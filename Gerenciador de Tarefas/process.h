#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <csignal>
#include <map>

#ifndef PROCESS_H
#define PROCESS_H

class Process
{
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
};

#endif // PROCESS_H
