//
// Created by Tuuuu on 2023/4/19.
//

#ifndef UNTITLED_RG_MAINMENU_H
#define UNTITLED_RG_MAINMENU_H

#include <QWidget>
#include<QStackedWidget>
#include"rg.h"
#include"options.h"
#include"select.h"

QT_BEGIN_NAMESPACE
namespace Ui { class rg_mainmenu; }
QT_END_NAMESPACE


class rg_mainmenu : public QWidget {
Q_OBJECT

public:
    explicit rg_mainmenu(QWidget *parent = nullptr);
    void hide_everything();
    void show_everything();
    void setup_myui();
    void anim_fadein();
    void anim_fadeout();
    ~rg_mainmenu() override;

private:
    Ui::rg_mainmenu *ui;
    rg *core_rg;
    options *core_opt;
    class select *select_menu;
    QPalette palette;
    QLabel *trans_anim;
    QPropertyAnimation *fadein;
    QPropertyAnimation *fadeout;
    QSequentialAnimationGroup *anim_group;
private slots:
    void pushbtn_slot();
    void pushbtn_slot2();
    void pushbtn_slot3();
    void play_songs(QString);
signals:
    void reset_rg();
};


#endif //UNTITLED_RG_MAINMENU_H
