#include "gerenciador_tarefas.h"
#include "ui_gerenciador_tarefas.h"

SystemMonitor::SystemMonitor(QWidget *parent) : QMainWindow(parent), ui(new Ui::SystemMonitor) {
    ui->setupUi(this);

    // Define available colors
    availableColors.append(Qt::blue);
    availableColors.append(Qt::red);
    availableColors.append(Qt::green);
    availableColors.append(Qt::yellow);
    availableColors.append(Qt::cyan);
    availableColors.append(Qt::magenta);

    // Init Charts
    initChartCPU();
    initChartMemory();
    initChartCharge();
    initChartDischarge();

    up = true;
    qRegisterMetaType<QVector<double> >("QVector<double>");
    connect(this,SIGNAL(updateCpu(QVector<double>)),SLOT(updateChartCPU(QVector<double>)));
    connect(this,SIGNAL(updateMemory(double,double)),SLOT(updateChartMemory(double,double)));
    connect(this,SIGNAL(updateBatteryPercentage(double)),SLOT(updateChartCharge(double)));
    connect(this,SIGNAL(updateDischargeTime(double)),SLOT(updateChartDischarge(double)));

    update();
}

SystemMonitor::~SystemMonitor() {
    delete ui;
}

void SystemMonitor::update()
{
    if (up)
    {
        threadDischargeTime = std::thread(&SystemMonitor::runChartDischargeTime,this);
        threadBatteryPercentage = std::thread(&SystemMonitor::runChartBatteryPercentage,this);
        threadMemory = std::thread(&SystemMonitor::runChartMemory,this);
        threadCpu = std::thread(&SystemMonitor::runChartCpu,this);
        up = false;
    }
}

void SystemMonitor::runChartCpu()
{
    while(true)
    {
       c.calculateCPU();
       QVector<double> results;
       for(int i = 0;i < 4;i++)
            results.push_back(c.getCpuValue(i));
       emit (updateCpu(results));
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void SystemMonitor::runChartMemory()
{
    while(true)
    {
       m.calculatePercentage();
       emit updateMemory(m.getPercentMem(),m.getPercentSwap());
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void SystemMonitor::runChartBatteryPercentage()
{
    while(true)
    {
       emit updateBatteryPercentage(b.getBatteryPercentage());
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void SystemMonitor::runChartDischargeTime()
{
    while(true)
    {
       d.calculateDischargeTime();
       emit updateDischargeTime(d.getDischargeTime());
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

//
// Init Charts
//

void SystemMonitor::initChartCPU() {
    unsigned nCPUs = 4;

    // Create pens for each CPU and set his name
    for (auto i = 0u; i < nCPUs; i++) {
        ui->chartCPU->addGraph();
        ui->chartCPU->graph(i)->setPen(QPen(availableColors.at(i)));
        ui->chartCPU->graph(i)->setName("CPU " + QString::number(i + 1));
    }

    // Set X axis
    ui->chartCPU->xAxis->setTickLabels(true);
    ui->chartCPU->axisRect()->setupFullAxesBox();

    // Set y axis
    ui->chartCPU->yAxis->setRange(0, 100);

    // Legend Settings
    ui->chartCPU->legend->setVisible(true);
    ui->chartCPU->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartCPU->legend->setRowSpacing(0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartCPU->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartCPU->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartCPU->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartCPU->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls SystemMonitor::updateChartCPU
    //connect(&timerCPU, SIGNAL(timeout()), this, SLOT(updateChartCPU()));
    //timerCPU.start(0); // Interval 0 means to refresh as fast as possible
}

void SystemMonitor::initChartMemory() {
    // Create pens for RAM
    ui->chartMemory->addGraph();
    ui->chartMemory->graph(0)->setPen(QPen(availableColors.at(0)));
    ui->chartMemory->graph(0)->setName("RAM");

    // Create pens for Swap
    ui->chartMemory->addGraph();
    ui->chartMemory->graph(1)->setPen(QPen(availableColors.at(1)));
    ui->chartMemory->graph(1)->setName("Swap");

    // Set X axis
    ui->chartMemory->xAxis->setTickLabels(true);
    ui->chartMemory->axisRect()->setupFullAxesBox();

    // Set y axis
    ui->chartMemory->yAxis->setRange(-0.5, 100);

    // Legend Settings
    ui->chartMemory->legend->setVisible(true);
    ui->chartMemory->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartMemory->legend->setRowSpacing(0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartMemory->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartMemory->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartMemory->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartMemory->yAxis2, SLOT(setRange(QCPRange)));
}

void SystemMonitor::initChartCharge() {
    // Create pen for Charge
    ui->chartCharge->addGraph();
    ui->chartCharge->graph(0)->setPen(QPen(availableColors.at(0)));
    ui->chartCharge->graph(0)->setName("Carga (%)");

    // Set X axis
    ui->chartCharge->xAxis->setTickLabels(true);
    ui->chartCharge->axisRect()->setupFullAxesBox();

    // Set y axis
    ui->chartCharge->yAxis->setRange(-0.5, 100.5);

    // Legend Settings
    ui->chartCharge->legend->setVisible(true);
    ui->chartCharge->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartCharge->legend->setRowSpacing(0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartCharge->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartCharge->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartCharge->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartCharge->yAxis2, SLOT(setRange(QCPRange)));
}

void SystemMonitor::initChartDischarge() {
    // Create pen for Charge
    ui->chartDischarge->addGraph();
    ui->chartDischarge->graph(0)->setPen(QPen(availableColors.at(1)));
    ui->chartDischarge->graph(0)->setName("Tempo de Descarga (minutos)");

    // Set X axis
    ui->chartDischarge->xAxis->setTickLabels(true);
    ui->chartDischarge->axisRect()->setupFullAxesBox();

    // Set y axis
    ui->chartDischarge->yAxis->setRange(-0.5, 240);

    // Legend Settings
    ui->chartDischarge->legend->setVisible(true);
    ui->chartDischarge->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chartDischarge->legend->setRowSpacing(0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->chartDischarge->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartDischarge->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chartDischarge->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chartDischarge->yAxis2, SLOT(setRange(QCPRange)));
}

//
// Update Charts
//

void SystemMonitor::updateChartCPU(QVector<double> results) {
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    
    // add data to lines:
    for(int i = 0;i < results.size();i++)
        ui->chartCPU->graph(i)->addData(key,results[i]);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartCPU->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartCPU->replot();
}

void SystemMonitor::updateChartMemory(double memory,double swap) {

    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    double value0 = memory;
    double value1 = swap;

    // add data to lines:
    ui->chartMemory->graph(0)->addData(key, value0);
    ui->chartMemory->graph(1)->addData(key, value1);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartMemory->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartMemory->replot();
}

void SystemMonitor::updateChartCharge(double batterypercentage) {

    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    double value = batterypercentage;

    // add data to lines:
    ui->chartCharge->graph(0)->addData(key,value);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartCharge->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartCharge->replot();
}

void SystemMonitor::updateChartDischarge(double dischargetime)
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    double value = dischargetime;

    // add data to lines:
    ui->chartDischarge->graph(0)->addData(key,value);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chartDischarge->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->chartDischarge->replot();
}
