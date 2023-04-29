#include <QApplication>
#include"rg.h"
#include"rg_mainmenu.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    rg w;
//    w.show();
    rg_mainmenu main_menu;
    main_menu.show();
    QApplication::exec();

    return 0;
}
