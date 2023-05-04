//
// Created by Tuuuu on 2023/5/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_edit.h" resolved
#include<QtGlobal>
#include "edit.h"
#include "ui_edit.h"


edit::edit(QWidget *parent) :
        QWidget(parent), ui(new Ui::edit) {
    ui->setupUi(this);


    player=new QMediaPlayer;
    Timer=new QTimer(this);
    player->setAudioOutput(&out);
    player->setSource(QUrl("../songs/track.mp3"));
    out.setVolume(1);

    ui->horizontalSlider->setRange(0,player->duration());
    connect(ui->horizontalSlider,&QSlider::sliderPressed,[=](){Timer->stop();});
    connect(ui->horizontalSlider,&QSlider::sliderReleased,[=](){emit slider_update(ui->horizontalSlider->value());Timer->start();});
    connect(this,&edit::slider_update,[=](int value){player->setPosition(value);});

    connect(ui->play,&QPushButton::clicked,[=](){if(!player->isPlaying())player->play();if(!Timer->isActive())Timer->start();ui->jump->setEnabled(false);});
    connect(ui->pause,&QPushButton::clicked,[=](){if(player->isPlaying())player->pause();ui->spinBox->setValue(player->position());ui->jump->setEnabled(true);});
    connect(ui->stop,&QPushButton::clicked,[=](){player->stop();ui->horizontalSlider->setValue(0);ui->lcdNumber->display(0);ui->spinBox->setValue(0);ui->jump->setEnabled(true);});

    connect(Timer, &QTimer::timeout, [=]() { ui->horizontalSlider->setValue(player->position()); ui->lcdNumber->display(int(player->position()));});
    connect(ui->jump,&QPushButton::clicked,this,&edit::spin_update);
    Timer->start(1);

    file=new QFile("../songs/track.txt");
    file->open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream in(file);
    in.setAutoDetectUnicode(true);
    ui->textEdit->setText(in.readAll().removeLast().removeLast().removeLast());
    file->close();
    connect(ui->write,&QPushButton::clicked,this,&edit::write_txt);
    connect(this,&edit::rail,this,&edit::write_rail);
    connect(ui->rail1,&QPushButton::clicked,[=](){emit rail(1);});
    connect(ui->rail2,&QPushButton::clicked,[=](){emit rail(2);});
    connect(ui->rail3,&QPushButton::clicked,[=](){emit rail(3);});
    connect(ui->rail4,&QPushButton::clicked,[=](){emit rail(4);});
}

edit::~edit() {
    delete ui;
}

void edit::spin_update() {
    if(player->isPlaying())
        return;
    if(ui->spinBox->value()<player->duration()){
        player->setPosition(ui->spinBox->value());
    }
    else
        player->setPosition(player->duration());
}

void edit::write_txt() {
    file->open(QIODevice::Truncate|QIODevice::Text|QIODevice::WriteOnly);
    QString data=ui->textEdit->toPlainText();
    data+="\n-1";
    QTextStream output(file);
    output<<data;
    file->close();
}

void edit::write_rail(int r) {
    int timestamp=ui->lcdNumber->value();
    switch (r) {
        case 1:    ui->textEdit->append("1 "+QString::number(timestamp));break;
        case 2:    ui->textEdit->append("2 "+QString::number(timestamp));break;
        case 3:    ui->textEdit->append("3 "+QString::number(timestamp));break;
        case 4:    ui->textEdit->append("4 "+QString::number(timestamp));break;
    }

}

void edit::keyPressEvent(QKeyEvent *event) {
    QWidget::keyPressEvent(event);
    if(event->key()==Qt::Key_F1)
        if(player->isPlaying())
            ui->pause->click();
        else if(!player->isPlaying())
            ui->play->click();

}
