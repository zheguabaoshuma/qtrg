//
// Created by Tuuuu on 2023/3/23.
//
#include<QApplication>
#include<qobject.h>
#include<QTimer>
#include<QStack>
#include<QThread>
#include <QPixmap>
#include<QLabel>
#include<QThreadPool>
#include<QRunnable>
#include<QPointer>
#include <QPropertyAnimation>
#include<QMutex>

#ifndef UNTITLED_NOTE_GENERATOR_H
#define UNTITLED_NOTE_GENERATOR_H
class note_generator;
class move_thread;
class note_hitter;

class note:public QObject
{
    Q_OBJECT
private:
    static QPixmap* src_skin;
    QPropertyAnimation anim;
    note_generator* gen=nullptr;
    int rail=0;
    QElapsedTimer timer;
public:
    QLabel *entity;
    bool ready_to_be_hit=false;
    double posx=0,posy=0,velocity=5;
    bool recycled=false;
    void setSkin();
    void setAnim();
    void start_anim();
    note(note_generator*,QWidget*,QObject* parent=nullptr);
    void show();
    void setRail(int);
    void setpos(double x,double y);
    void recycle();
    void stop();
public slots:

signals:
    void me(int r);
};

class _stack//a simple stack to store QObject
{
public:
    _stack() {}
    static QMutex lock;
    void push(note *obj) {
        stack_.append(QPointer<note>(obj));
    }

    note *pop() {
        if (stack_.isEmpty()) {
            return nullptr;
        }
        note *obj = stack_.last().data();
        stack_.removeLast();
        return obj;
    }

    bool isEmpty() const {
        return stack_.isEmpty();
    }

    int size() const {
        return stack_.size();
    }

    note* at(int seq) const{
        return stack_[seq];
    }
private:
    QList<QPointer<note>> stack_;
};

class _list//a simple list to store note
{
public:
    _list() {}
    static QMutex lock;
    void push_back(note *obj) {
        list_.append(QPointer<note>(obj));
    }

    note *out_list() {
        if (list_.isEmpty()) {
            return nullptr;
        }
        note *obj = list_.first().data();
        list_.removeFirst();
        return obj;
    }
    note* getFirst(){
        return list_.first();
    }

    bool isEmpty() const {
        return list_.isEmpty();
    }

    int size() const {
        return list_.size();
    }
    note* at(int seq) const{
        if(seq<list_.size())
            return list_.at(seq);
        else return nullptr;
    }
    void copy(_list *n){

    }

private:
    QList<QPointer<note>> list_;
};

class move_thread:public QThread
{
Q_OBJECT
private:
    _list* bind_list[5]= {nullptr,nullptr,nullptr,nullptr,nullptr};
    _list* bind_list_copy[5]={nullptr, nullptr, nullptr, nullptr, nullptr};
    note_hitter* h=nullptr;
    int railSeq=0;
    bool stop=false;
    int line_pospx=560;//distance from top, 7/8 window height
    int velocity=1;
    int halfwinpx=30;

public:
    bool readyToSuicide=false;
    move_thread(note_hitter* h,QObject* parent=nullptr){

        //QObject::connect(h,SIGNAL(&note_hitter::suicide()),this,SLOT(&move_thread::hit()));
    };
    void bind(_list* n,_list* m){
        for(int k=1;k<5;k++)
            bind_list[k]=(n+k),bind_list_copy[k]=(m+k);
    }
    void run() override
    {

        while(!stop){

            for(int i=1;i<5;i++){
                int n=bind_list[i]->size();
                if(n>0) {
                    qDebug()<<"run";
                    QLabel* e=bind_list[i]->getFirst()->entity;
                    QPropertyAnimation anim(e, "pos");
                    anim.setDuration(200);
                    anim.setStartValue(e->pos());
                    anim.setEndValue(QPoint(bind_list[i]->getFirst()->posx, bind_list[i]->getFirst()->posy+600));
                    anim.start();
                }

            }
            QThread::msleep(1000);
        }
    }

signals:

private slots:
    void hit(move_thread* who);// hitter will broadcast who will be hit, and each thread decide whether to suicide, from hitter
};

class note_generator:public QObject
{
Q_OBJECT
private:
    QWidget *parent;
    _list note_pool[5];//0 is not used
    _stack note_stack;
    double bpm=0;
    QTimer clock;
    int default_v=5;
    note_hitter* h=nullptr;
    move_thread *m=nullptr;
public:
    note_generator(){

    };
    void generate_note(int railSeq);
    void read();
    void setHitter(note_hitter* h){this->h=h;}
    void set_Parent(QWidget* w){parent=w;};
    bool is_empty(int r) { return note_pool[r].isEmpty();};
    note* get_first(int r){return note_pool[r].getFirst();};
    friend note;
    friend note_hitter;
public slots:
    void expire_out_list(int r);
    void generate_by_music(int r);
};

class move_thread;
class note_hitter:public QObject
{
Q_OBJECT
private:
    note_generator* g=nullptr;
public:
    note_hitter(QObject* parent=nullptr): QObject(parent){};
    void setGenerator(note_generator* g){this->g=g;}
private slots:

signals:
    void suicide(move_thread* who);//decide which note to be hit, to move_thread
};



#endif //UNTITLED_NOTE_GENERATOR_H
