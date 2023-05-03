//
// Created by Tuuuu on 2023/3/22.
//

#ifndef UNTITLED_RG_H
#define UNTITLED_RG_H

#include <QWidget>
#include<QPainter>
#include<qpixmap.h>
#include<qlogging.h>
#include<QFrame>
#include<QtGui>
#include<QImage>
#include<QThread>
#include<QtMultimedia/QMediaPlayer>
#include<QMovie>
#include <QAudioOutput>
#include "music.h"
#include"note_generator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class rg; }
QT_END_NAMESPACE

#include <QMovie>

class rg : public QWidget {
Q_OBJECT

public:
    explicit rg(QWidget *parent = nullptr);
    void begin();
    note_generator* gen;
    note_hitter* hit;
    note *v_note;
    ~rg() override;
    QLabel line;
    void kill(int);
    music_thread *mt;
    QAudioOutput out;
    QMovie *sprite1;
    QMovie *sprite2;
    QMovie *sprite3;
    QMovie *sprite4;
    QMovie *far1;
    QMovie *far2;
    QMovie *far3;
    QMovie *far4;
    void set_song(QString);
    void reset_lcdCombo();
private:
    Ui::rg *ui;
    void keyPressEvent(QKeyEvent *event) override{
        if(event->key()==Qt::Key_R)
            kill(1);
        else if(event->key()==Qt::Key_T)
            kill(2);
        else if(event->key()==Qt::Key_Y)
            kill(3);
        else if(event->key()==Qt::Key_U)
            kill(4);
    }


private slots:
    void set_volume(float);
    void pushbtn_slot();
};



#endif //UNTITLED_RG_H
