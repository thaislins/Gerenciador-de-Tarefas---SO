#ifndef GERENCIADOR_TAREFAS_H
#define GERENCIADOR_TAREFAS_H

#include <QMainWindow>
#include <QTimer>
#include <thread>
#include <QObject>
#include "dischargetime.h"
#include "batterypercentage.h"
#include "memoryinfo.h"
#include "cpuinfo.h"
#include "process.h"

namespace Ui
{
class SystemMonitor;
}

class SystemMonitor : public QMainWindow
{
    Q_OBJECT

 public:
    explicit SystemMonitor(QWidget *parent = 0);
    ~SystemMonitor();
    void initChartCPU();
    void initChartMemory();
    void initChartCharge();
    void initChartDischarge();
    void update();

signals:
    void updateCpu(QVector<double>);
    void updateMemory(double,double);
    void updateBatteryPercentage(double);
    void updateDischargeTime(double);
    void updateProcess(int);

 private slots:
    void updateChartCPU(QVector<double>);
    void updateChartMemory(double,double);
    void updateChartCharge(double);
    void updateChartDischarge(double);
    void updateChartProc(int);

    void on_pbKill_clicked();

    void on_pbUpdate_clicked();

private:
    Ui::SystemMonitor *ui;
    QTimer timerCPU;
    QTimer timerMemory;
    QTimer timerCharge;
    QTimer timerDischarge;
    QVector<QColor> availableColors;

    void runChartCpu();
    void runChartMemory();
    void runChartBatteryPercentage();
    void runChartDischargeTime();

    bool up;
    std::thread threadCpu;
    std::thread threadMemory;
    std::thread threadBatteryPercentage;
    std::thread threadDischargeTime;

    DischargeTime d;
    BatteryPercentage b;
    MemoryInfo m;
    CpuInfo c;
    Process p;
};

#endif // GERENCIADOR_TAREFAS_H
