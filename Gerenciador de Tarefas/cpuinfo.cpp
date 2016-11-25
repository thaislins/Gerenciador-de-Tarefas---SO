#include "cpuinfo.h"

CpuInfo::CpuInfo()
{
    info = " ";
    value = 0.0;
    cpu = 0.0;


    if (fileRead())
    {
        for (int i = 0; i < 4; ++i)
        {
            int n = i * 4;
            long double l1 = storeinfo[n],l2 = storeinfo[n+1],l3 = storeinfo[n+2],l4 = storeinfo[n+3];
            long double usage = (l1+l2+l3);
            long double total = (l1+l2+l3+l4);
            currentUsage.push_back(usage);
            currentTotal.push_back(total);
        }
    }
}

bool CpuInfo::fileRead()
{
    std::string line;
    std::ifstream file;

    file.open("/proc/stat");

    if(!file)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            getline(file,line);
            std::istringstream iss(line);
            getline(iss,info,' ');
            if(i >= 1)
            {
                for (int j = 0; j < 4; j++)
                {
                    iss >> value;
                    iss.ignore();

                    storeinfo.push_back(value);
                }
            }
            else
            {
                iss >> value;
                iss.ignore();
            }
        }
            file.close();
        return true;
    }
    return false;
}

void CpuInfo::currentToprev()
{
    prevUsage.clear();
    prevTotal.clear();

    for (int i = 0; i < currentTotal.size(); ++i)
    {
        prevUsage.push_back(currentUsage[i]);
        prevTotal.push_back(currentTotal[i]);
    }
}

void CpuInfo::calculateCPU()
{
    currentToprev();
    storeinfo.clear();
    if (fileRead())
    {
        currentTotal.clear();
        currentUsage.clear();

        for (int i = 0; i < 4; ++i)
        {
            int n = i * 4;
            long double l1 = storeinfo[n],l2 = storeinfo[n+1],l3 = storeinfo[n+2],l4 = storeinfo[n+3];
            long double usage = (l1+l2+l3);
            long double total = (l1+l2+l3+l4);
            currentUsage.push_back(usage);
            currentTotal.push_back(total);
        }
    }
}

double CpuInfo::getCpuValue(int i)
{
    return ((currentUsage[i] - prevUsage[i])/(currentTotal[i] - prevTotal[i]))*100.0;
}
