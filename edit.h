//
// Created by Tuuuu on 2023/5/4.
//

#ifndef UNTITLED_EDIT_H
#define UNTITLED_EDIT_H

#include <QWidget>
#include<QtMultimedia>
#include<fstream>
#include<QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class edit; }
QT_END_NAMESPACE

class edit : public QWidget {
Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    QMediaPlayer *player;
    QAudioOutput out;
    QTimer *Timer;
    QFile *file;
    QString current_song;
    bool en_slider=false;
    void set_song(QString);
    ~edit() override;

private:
    Ui::edit *ui;
    void keyPressEvent(QKeyEvent* event) override;
signals:
    void slider_update(int value);
    void rail(int);
public slots:
    void spin_update();
    void write_txt();
    void write_rail(int);
};


#endif //UNTITLED_EDIT_H
