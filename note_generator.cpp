//
// Created by Tuuuu on 2023/3/23.
//
#include"note_generator.h"
#include<QObject>
#include<QLabel>
extern int base_prepare_time;
QPixmap* note::src_skin=nullptr;
int note::duration=1500;
QMutex _list::lock;
QMutex _stack::lock;
note::note(note_generator* g,QWidget* fa_pt,QObject* parent):QObject(parent)
{
    connect(this, &note::me,g, &note_generator::expire_out_list);
    entity=new QLabel(fa_pt);
    setAnim();
    entity->move(0,0);
    gen=g;
}

void note::setpos(double x, double y) {
    posx=x;
    posy=y;
    entity->move(x,y);

}

void note::show()
{
    entity->setPixmap(*src_skin);
    entity->show();
}


void note::recycle() {
    anim.stop();
    timer.invalidate();
    gen->note_pool->out_list();
    ready_to_be_hit=false;
    is_hit=false;
    //entity->move(0,-20);
    entity->hide();
    //QMutexLocker lock(&_stack::lock);
    gen->note_stack.push(this);
}

void note::setSkin() {
    QPixmap *p=new QPixmap;
    p->load("../note.png");
    src_skin=p;
    *src_skin=src_skin->scaled(62,16);

}

void note::setAnim() {
    if(anim.state()==QAbstractAnimation::Running)
        anim.stop();
    anim.setPropertyName("pos");
    anim.setTargetObject(entity);
    anim.setStartValue(entity->pos());
    anim.setEndValue(QPoint(posx,posy+600));
    anim.setDuration(duration);//base duration is 1500, speed is 0.4px/ms
}

void note::start_anim() {
    int base=base_prepare_time;
    if(!recycled){
        setAnim();
        recycled=true;
    }
    else{
        anim.setStartValue(entity->pos());
        anim.setEndValue(QPoint(posx,posy+600));

    }
    if(timer.isValid())
        timer.start();
    else timer.restart();//base prepare time is 1375ms
    QTimer::singleShot(base-75,[=](){ready_to_be_hit=true;});
    QTimer::singleShot(base-50,[=](){is_perfect=true;});
    QTimer::singleShot(base+50,[=](){is_perfect=false;});
    QTimer::singleShot(base+75,[=](){emit me(rail);});
    anim.start();
}

void note::setRail(int r) {
    rail=r;
}

void note::stop() {
    anim.stop();
}

void note::setDuration(int d) {
    duration=d;
    qDebug()<<duration;
}


void note_generator::generate_note(int railSeq) {
    note* n=nullptr;
    QMutexLocker lock(&_list::lock);
    QMutexLocker Lock(&_stack::lock);
    //qDebug()<<railSeq;

    if(note_stack.isEmpty())
        n=new note(this,parent);
    else
        n=note_stack.pop();
    note_pool[railSeq].push_back(n);
    n->setRail(railSeq);
    n->setpos(480+19+100*(railSeq-1),0);
    n->show();
    n->start_anim();
    //qDebug()<<"unlock";

    //note* current_note=note_pool.pop();
}

void note_generator::expire_out_list(int r) {
    note* n=note_pool[r].out_list();
    if(n->is_hit==false)
        emit combo_break();
    n->recycle();
}

void note_generator::generate_by_music(int r) {
    generate_note(r);
    //qDebug()<<"copy!";
}

void note_generator::clear() {
    note_stack.clear();
    for(int k=0;k<5;k++)
        note_pool[k].clear();
}






