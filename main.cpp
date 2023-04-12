#include <QApplication>
#include"rg.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    rg w;
    w.show();
    QApplication::exec();

    return 0;
}
