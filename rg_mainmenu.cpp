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
}

rg_mainmenu::~rg_mainmenu() {
    delete ui;
}

void rg_mainmenu::pushbtn_slot() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->show();
    ui->pushButton_3->show();
    hide_everything();
}

void rg_mainmenu::pushbtn_slot2() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->show();
    ui->pushButton_3->show();
    hide_everything();
}

void rg_mainmenu::pushbtn_slot3() {
    core_rg->mt->stop();
    core_rg->mt->music->stop();
    ui->stackedWidget->setCurrentIndex(-1);
    ui->stackedWidget->hide();
    ui->pushButton_3->hide();
    show_everything();
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
    ui->pushButton->setStyleSheet("QPushButton {""border: none;""padding: 0;""}");
    ui->pushButton_2->setStyleSheet("QPushButton {""border: none;""padding: 0;""}");
    ui->pushButton_3->setStyleSheet("QPushButton {""border: none;""padding: 0;""}");

}

void rg_mainmenu::play_songs(QString s) {
    core_rg->set_song(s);
    qDebug()<<s;
    ui->stackedWidget->setCurrentIndex(2);
}





