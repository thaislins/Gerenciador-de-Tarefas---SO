#include <QVector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

#ifndef DISCHARGETIME_H
#define DISCHARGETIME_H

class DischargeTime
{
    private:
        std::string info;
        double value;
        QVector<double> v;
        double dischargetime;
    public:
        DischargeTime();

        bool fileRead();
        void calculateDischargeTime();
        double getDischargeTime();
};

#endif // DISCHARGETIME_H
