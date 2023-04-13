//
// Created by Tuuuu on 2023/3/23.
//
#include"note_generator.h"
#include<QObject>
#include<QLabel>
QPixmap* note::src_skin=nullptr;
QMutex _list::lock;
QMutex _stack::lock;
note::note(note_generator* g,QWidget* fa_pt,QObject* parent):QObject(parent)
{
    //src_skin.load("C:/Users/Tuuuu/CLionProjects/untitled/note.png");
    //src_skin=src_skin.scaled(QSize(src_skin.width()/4,src_skin.height()/4));
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
    entity->move(0,-20);
    QMutexLocker lock(&_stack::lock);
    gen->note_stack.push(this);
}

void note::setSkin() {
    QPixmap *p=new QPixmap;
    p->load("C:/Users/Tuuuu/CLionProjects/untitled/note.png");
    src_skin=p;
    *src_skin=src_skin->scaled(QSize(src_skin->width()/4,src_skin->height()/4));

}

void note::setAnim() {
    if(anim.state()==QAbstractAnimation::Running)
        anim.stop();
    anim.setPropertyName("pos");
    anim.setTargetObject(entity);
    anim.setStartValue(entity->pos());
    anim.setEndValue(QPoint(posx,posy+600));
    anim.setDuration(1500);
}

void note::start_anim() {
    setAnim();
    qDebug()<<anim.state();
    QTimer::singleShot(1450,[=](){emit me(rail);});
    QTimer::singleShot(1300,[=](){ready_to_be_hit=!ready_to_be_hit;});

    if(timer.isValid())
        timer.start();
    else timer.restart();
    anim.start();
}

void note::setRail(int r) {
    rail=r;
}

void note::stop() {
    anim.stop();
    //setpos(posx,posy-10000);
}


void note_generator::generate_note(int railSeq) {
    note* n=nullptr;
    QMutexLocker lock(&_list::lock);
    QMutexLocker Lock(&_stack::lock);
    qDebug()<<"lock";

    if(note_stack.isEmpty())
        n=new note(this,parent);
    else
        n=note_stack.pop();
    note_pool[railSeq].push_back(n);
    n->setRail(railSeq);
    n->setpos(63*(railSeq-1),0);
    n->show();
    n->start_anim();
    qDebug()<<"unlock";

    //note* current_note=note_pool.pop();
}

void note_generator::expire_out_list(int r) {
    note* n=note_pool[r].out_list();
    n->recycle();
}

void note_generator::generate_by_music(int r) {
    generate_note(r);
    qDebug()<<"copy!";
}

void move_thread::hit(move_thread *who) {
    if(who==this)
    {
        stop=true;
        railSeq=0;
    }
}




