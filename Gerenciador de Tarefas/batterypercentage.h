#include <iostream>
#include <fstream>
#include <cstdlib>

#ifndef BATTERYPERCENTAGE_H
#define BATTERYPERCENTAGE_H

class BatteryPercentage
{
    private:
        double percentage;
    public:
        BatteryPercentage();

        bool fileRead();
        double getBatteryPercentage();
};


#endif // BATTERYPERCENTAGE_H
