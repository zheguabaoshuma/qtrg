//
// Created by Tuuuu on 2023/3/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_rg.h" resolved
#include<QThread>
#include<QDebug>
#include "rg.h"
#include "ui_rg.h"
#include"note_generator.h"



rg::rg(QWidget *parent) :
        QWidget(parent), ui(new Ui::rg) {
    gen=new note_generator();
    hit=new note_hitter();
    gen->setParent(this),gen->set_Parent(this);
    hit->setParent(this);
    hit->setGenerator(gen);
    gen->setHitter(hit);

    ui->setupUi(this);
    setFixedSize(1359,640);

    v_note=new note(gen,this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(pushbtn_slot()));
    ui->pushButton->setStyleSheet("QPushButton {""border: none;""padding: 0;""}");

    QPixmap line_skin;

    mt=new music_thread(gen,this,&out);

    line_skin.load("../line.png");
    line_skin=line_skin.scaled(500,8);
    ui->line->setPixmap(line_skin);

    sprite1=new QMovie("../sprite.gif");
    sprite2=new QMovie("../sprite.gif");
    sprite3=new QMovie("../sprite.gif");
    sprite4=new QMovie("../sprite.gif");
    sprite1->setScaledSize(QSize(128,128));
    sprite2->setScaledSize(QSize(128,128));
    sprite3->setScaledSize(QSize(128,128));
    sprite4->setScaledSize(QSize(128,128));

    ui->sprite1->setMovie(sprite1);
    ui->sprite2->setMovie(sprite2);
    ui->sprite3->setMovie(sprite3);
    ui->sprite4->setMovie(sprite4);
    ui->sprite1->raise();
    ui->sprite2->raise();
    ui->sprite3->raise();
    ui->sprite4->raise();
}


rg::~rg() {
    delete ui;
}

void rg::pushbtn_slot() {
    v_note->setSkin();
    mt->start();
}

void rg::kill(int r) {
    note* n=nullptr;
    if(!gen->is_empty(r))
        n=gen->get_first(r);
    if(n!=nullptr&&n->ready_to_be_hit)
    {
        n->stop();
        switch (r) {
            case 1: sprite1->start();break;
            case 2: sprite2->start();break;
            case 3: sprite3->start();break;
            case 4: sprite4->start();break;
            default:break;
        }
    }

}

void rg::set_volume(float h) {
    out.setVolume(h);
    qDebug()<<out.volume();
}

void rg::set_song(QString s) {
    mt->music->set_current(s);
    mt->music->read(s);
}

