//
// Created by Tuuuu on 2023/4/12.
//

#ifndef UNTITLED_MUSIC_H
#define UNTITLED_MUSIC_H
#include<QMediaPlayer>
#include<QThread>
#include <QList>
#include "note_generator.h"
extern int base_prepare_time;
extern int bias_time;
class music_player:public QMediaPlayer{
private:
    QString current_song;
public:
    void set_current(QString);
    music_player();
    QList<int> *note_rail_info;
    QList<int> *time_info;
    void read(QString s);
};

class music_thread:public QThread{
    Q_OBJECT
private:
    note_generator *gen;
    int prepare_ms;
    int bias_ms;
    QElapsedTimer *timer;
public:
    music_player *music;
    music_thread(note_generator* g,QWidget* parent,QAudioOutput *output);
    void stop();
    void reset();
    void run() override{
        prepare_ms=base_prepare_time;
        bias_ms=bias_time;
        int rail=0,time=0;
        music->read("");
        music->play();

        if(timer->isValid())
            timer->start();
        else
            timer->restart();

        while(!QThread::isInterruptionRequested()){
            double now=timer->elapsed();
            if(!rail&&!time&&!music->note_rail_info->isEmpty())
            {
                rail=music->note_rail_info->takeFirst();
                time=music->time_info->takeFirst()+bias_ms;
            }
            else if(music->note_rail_info->isEmpty()) break;
            if(time<=now+prepare_ms+3&&time>=now+prepare_ms-3){
                emit generate(rail);
                rail=0,time=0;
            }
        }
    };
    void set_bias(int);
    void set_speed(int);

    signals:
    void generate(int rail);
};
#endif //UNTITLED_MUSIC_H
