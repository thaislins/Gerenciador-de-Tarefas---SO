#include "batterypercentage.h"

BatteryPercentage::BatteryPercentage()
{
    percentage = 0.0;
}

bool BatteryPercentage::fileRead()
{
    std::ifstream file;
    file.open("/sys/class/power_supply/BAT1/capacity");

    if (!file)
    {
        exit(EXIT_FAILURE);
    }
    else {
        file >> percentage;
        file.close();
        return true;
    }
    return false;
}

double BatteryPercentage::getBatteryPercentage()
{
    if(fileRead()){
        return percentage;
    }
    return percentage;
}
