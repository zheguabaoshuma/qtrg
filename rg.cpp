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
    gen->setParent(this),gen->set_Parent(this);

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

    connect(gen,&note_generator::combo_break,[=](){ui->lcdCombo->display(0);});

    far1=new QMovie("../hit_far.gif");
    far2=new QMovie("../hit_far.gif");
    far3=new QMovie("../hit_far.gif");
    far4=new QMovie("../hit_far.gif");
    far1->setScaledSize(QSize(57,54));
    far2->setScaledSize(QSize(57,54));
    far3->setScaledSize(QSize(57,54));
    far4->setScaledSize(QSize(57,54));

    ui->far_gif1->setMovie(far1);
    ui->far_gif2->setMovie(far2);
    ui->far_gif3->setMovie(far3);
    ui->far_gif4->setMovie(far4);
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
        n->entity->hide();
        switch (r) {
            case 1: sprite1->start();break;
            case 2: sprite2->start();break;
            case 3: sprite3->start();break;
            case 4: sprite4->start();break;
            default:break;
        }
        n->is_hit=true;
        ui->lcdCombo->display(ui->lcdCombo->value()+1);

        if(n->is_perfect==false)
        {
            switch(r){
                case 1: far1->start();break;
                case 2: far2->start();break;
                case 3: far3->start();break;
                case 4: far4->start();break;
                default:break;
            }
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

void rg::reset_lcdCombo() {
    ui->lcdCombo->display(0);
}

