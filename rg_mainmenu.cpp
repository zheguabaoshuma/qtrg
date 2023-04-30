//
// Created by Tuuuu on 2023/4/19.
//

// You may need to build the project (run Qt uic code generator) to get "ui_rg_mainmenu.h" resolved

#include "rg_mainmenu.h"
#include "ui_rg_mainmenu.h"
#include<QStyle>


rg_mainmenu::rg_mainmenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::rg_mainmenu) {
    ui->setupUi(this);
    setup_myui();
    ui->pushButton_3->hide();

    core_rg=new rg(ui->stackedWidget);
    core_opt=new options(ui->stackedWidget);
    select_menu=new class select(ui->stackedWidget);

    core_opt->bind(core_rg);
    ui->stackedWidget->addWidget(select_menu);
    ui->stackedWidget->addWidget(core_opt);
    ui->stackedWidget->addWidget(core_rg);
    ui->stackedWidget->hide();
    setFixedSize(1359,640);
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(pushbtn_slot()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(pushbtn_slot2()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(pushbtn_slot3()));
    connect(select_menu,&select::start_song,this,&rg_mainmenu::play_songs);

    QPixmap pixmap;
    pixmap.load("../blur.jpg");
    palette.setBrush(QPalette::Window,pixmap);
    this->setPalette(palette);
    QPixmap apophenia;
    apophenia.load("../blur.jpg");

    trans_anim=new QLabel(this);
    trans_anim->setPixmap(apophenia);
    trans_anim->move(QPoint(-1000,-1000));
    //trans_anim->hide();

    fadein=new QPropertyAnimation(trans_anim,"size");
    fadein->setStartValue(QSize(1,640));
    //fadein->setKeyValueAt(0.5,QSize(780,640));
    fadein->setEndValue(QSize(1360,640));
    fadein->setDuration(300);

    fadeout=new QPropertyAnimation(trans_anim,"size");
    fadeout->setStartValue(QSize(1360,640));
    fadeout->setEndValue(QSize(1,640));
    fadeout->setDuration(300);

    anim_group=new QSequentialAnimationGroup(this);
    anim_group->addAnimation(fadein);
    anim_group->addAnimation(fadeout);
}

rg_mainmenu::~rg_mainmenu() {
    delete ui;
}

void rg_mainmenu::pushbtn_slot() {
    anim_fadein();
    connect(anim_group,&QSequentialAnimationGroup::currentAnimationChanged,[=]{
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget->show();
        ui->pushButton_3->show();
        hide_everything();});


}

void rg_mainmenu::pushbtn_slot2() {
    anim_fadein();
    connect(anim_group,&QSequentialAnimationGroup::currentAnimationChanged,[=]{
        ui->stackedWidget->setCurrentIndex(1);
        ui->stackedWidget->show();
        ui->pushButton_3->show();
        hide_everything();});

}

void rg_mainmenu::pushbtn_slot3() {
    if(core_rg->mt->isRunning()){
        core_rg->mt->stop();
        core_rg->mt->music->stop();
        QThread::msleep(500);
    }

    anim_fadein();
    connect(anim_group,&QSequentialAnimationGroup::currentAnimationChanged,[=]{
        ui->stackedWidget->setCurrentIndex(-1);
        ui->stackedWidget->hide();
        ui->pushButton_3->hide();
        show_everything();});

}

void rg_mainmenu::hide_everything() {
    ui->pushButton->hide();
    ui->pushButton_2->hide();
}

void rg_mainmenu::show_everything() {
    ui->pushButton->show();
    ui->pushButton_2->show();
}

void rg_mainmenu::setup_myui() {
    ui->pushButton->setStyleSheet("QPushButton {""border: none;""padding: 0;""border-radius: 5px""}");
    ui->pushButton_2->setStyleSheet("QPushButton {""border: none;""padding: 0;""border-radius: 5px""}");
    ui->pushButton_3->setStyleSheet("QPushButton {""border: none;""padding: 0;""}");

}

void rg_mainmenu::play_songs(QString s) {
    core_rg->set_song(s);
    qDebug()<<s;
    ui->stackedWidget->setCurrentIndex(2);
}

void rg_mainmenu::anim_fadein() {
    anim_group->start();
    trans_anim->move(0,0);
}






