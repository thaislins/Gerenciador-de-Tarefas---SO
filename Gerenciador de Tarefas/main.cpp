#include "gerenciador_tarefas.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SystemMonitor w;
    w.show();

    return a.exec();
}
