#include <QVector>
#include <sstream>
#include <fstream>
#include <cstdlib>

#ifndef CPUINFO_H
#define CPUINFO_H


class CpuInfo
{
    private:
        std::string info;
        long double value;
        double cpu;
        QVector<long double> storeinfo;
        QVector<long double> prevUsage;
        QVector<long double> prevTotal;
        QVector<long double> currentUsage;
        QVector<long double> currentTotal;
    public:
        CpuInfo();

        bool fileRead();
        void print();
        void currentToprev();
        void calculateCPU();
        double getCpuValue(int i);
};

#endif // CPUINFO_H

