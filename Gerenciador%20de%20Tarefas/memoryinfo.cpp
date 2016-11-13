#include "memoryinfo.h"

MemoryInfo::MemoryInfo() {
    info = "";
    value = 0.0;
    percentmem = 0.0;
    percentswap = 0.0;
}

bool MemoryInfo::fileRead() {

    std::string line;
    std::ifstream file;
    file.open("/proc/meminfo");

    if (!file)
    {
        exit(EXIT_FAILURE);
    }
    else {
        v.clear();
        for (int i = 0; i < 16; ++i)
        {
            getline(file,line);
            std::istringstream iss(line);
            getline(iss,info,':');
            iss >> value;
            v.push_back(value);
        }
        file.close();
        return true;
    }
    return false;
}

void MemoryInfo::calculatePercentage() {
    if(fileRead()){

        double memtotal = v[0], memfree = v[1], swaptotal = v[14],swapfree = v[15];

        percentmem = (memtotal - memfree)/memtotal;
        percentswap = (swaptotal - swapfree)/swaptotal;
    }
}

double MemoryInfo::getPercentMem() {
    return percentmem;
}

double MemoryInfo::getPercentSwap() {
    return percentswap;
}
