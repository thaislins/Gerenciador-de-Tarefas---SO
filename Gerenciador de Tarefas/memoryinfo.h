#include <QVector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

#ifndef MEMORYINFO_H
#define MEMORYINFO_H

class MemoryInfo
{
    private:
        std::string info;
        double value;
        double percentmem;
        double percentswap;
        QVector<double> v;
    public:
        MemoryInfo();

        bool fileRead();
        void calculatePercentage();
        double getPercentMem();
        double getPercentSwap();
};

#endif // MEMORYINFO_H
