//
// Created by Tuuuu on 2023/4/20.
//

#ifndef UNTITLED_OPTIONS_H
#define UNTITLED_OPTIONS_H

#include <QWidget>
#include "rg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class options; }
QT_END_NAMESPACE

class options : public QWidget {
Q_OBJECT

public:
    explicit options(QWidget *parent = nullptr);
    void bind(rg *bind);
    void set_volume(float);
    void set_bias(int);
    void set_speed(float);
    ~options() override;

private:
    rg* bind_rg;
    int volume;
    int bias;
    double speed=1;
    Ui::options *ui;

signals:
    void mvolume(float);
    void duration_changed(int);
};


#endif //UNTITLED_OPTIONS_H
