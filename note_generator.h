//
// Created by Tuuuu on 2023/3/23.
//
#ifndef UNTITLED_NOTE_GENERATOR_H
#define UNTITLED_NOTE_GENERATOR_H
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


class note_generator;
class move_thread;

class note:public QObject
{
    Q_OBJECT
private:
    static QPixmap* src_skin;
    QPropertyAnimation anim;
    note_generator* gen=nullptr;
    int rail=0;
    static int duration;
    QElapsedTimer timer;
public:
    QLabel *entity;
    bool ready_to_be_hit=false;
    bool is_hit=false;
    bool is_perfect=false;
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
    void setDuration(int d);
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
    void clear(){
        stack_.clear();
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
    void clear(){
        list_.clear();
    }

private:
    QList<QPointer<note>> list_;
};



class note_generator:public QObject
{
Q_OBJECT
private:
    QWidget *parent;
    _list note_pool[5];//0 is not used
    _stack note_stack;
    QTimer clock;
public:
    note_generator(){

    };
    void generate_note(int railSeq);
    void read();
    void set_Parent(QWidget* w){parent=w;};
    bool is_empty(int r) { return note_pool[r].isEmpty();};
    note* get_first(int r){return note_pool[r].getFirst();};
    friend note;
    void clear();
public slots:
    void expire_out_list(int r);
    void generate_by_music(int r);
signals:
    void combo_break();
};





#endif //UNTITLED_NOTE_GENERATOR_H
