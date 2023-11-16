#include <QApplication>
#include "expensetracker.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ExpenseTracker w;
    w.show();
    return a.exec();
}
