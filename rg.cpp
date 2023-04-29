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
    line_skin.load("C:/Users/Tuuuu/CLionProjects/untitled/wip.png");
    line_skin=line_skin.scaled(QSize(line_skin.width()/3,line_skin.height()/3));
    line.setParent(this);
    line.setPixmap(line_skin);
    line.move(0,540);
    line.show();

    mt=new music_thread(gen,this,&out);

}


void rg::begin() {


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
    //QMutexLocker lock(&_list::lock);

    if(!gen->is_empty(r))
        n=gen->get_first(r);
    if(n!=nullptr&&n->ready_to_be_hit)
    {
        n->stop();
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
