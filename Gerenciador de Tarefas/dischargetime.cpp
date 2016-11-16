#include "dischargetime.h"

DischargeTime::DischargeTime()
{
    value = 0.0;
    info = "";
    dischargetime = 0.0;
}

bool DischargeTime::fileRead()
{
    std::string line;
    std::ifstream file;
    file.open("/sys/class/power_supply/BAT1/uevent");

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
            getline(iss,info,'=');
            iss >> value;
            v.push_back(value);
        }
        file.close();
        return true;
    }
    return false;
}


void DischargeTime::calculateDischargeTime()
{
    if (fileRead())
    {
        double value1 = v[9],value2 = v[10],value3 = v[7];

        //dischargetime = (value1 - value2)/value3;
        dischargetime = value2/value3;
    }
}

double DischargeTime::getDischargeTime()
{
    return dischargetime * 60;
}
