#ifndef GERENCIADOR_TAREFAS_H
#define GERENCIADOR_TAREFAS_H

#include <QMainWindow>
#include <QTimer>
#include <thread>
#include <QObject>
#include "dischargetime.h"
#include "batterypercentage.h"
#include "memoryinfo.h"

namespace Ui {
class SystemMonitor;
}

class SystemMonitor : public QMainWindow {
    Q_OBJECT

 public:
    explicit SystemMonitor(QWidget *parent = 0);
    ~SystemMonitor();
    void initChartCPU();
    void initChartMemory();
    void initChartCharge();
    void initChartDischarge();

 private slots:
    void updateChartCPU();
    void updateChartMemory();
    void updateChartCharge();
    void updateChartDischarge();

 private:
    Ui::SystemMonitor *ui;
    QTimer timerCPU;
    QTimer timerMemory;
    QTimer timerCharge;
    QTimer timerDischarge;
    QVector<QColor> availableColors;

    DischargeTime d;
    BatteryPercentage b;
    MemoryInfo m;
};

#endif // GERENCIADOR_TAREFAS_H
