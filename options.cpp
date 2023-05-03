//
// Created by Tuuuu on 2023/4/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_options.h" resolved

#include "options.h"
#include "ui_options.h"
#include "note_generator.h"


options::options(QWidget *parent) :
        QWidget(parent), ui(new Ui::options) {
    ui->setupUi(this);
    note *virtual_note=new note(nullptr,nullptr);

    connect(ui->horizontalSlider,&QSlider::sliderMoved,this,[=](int a){ float vol=static_cast<float>(a)/102;set_volume(vol);});
    connect(ui->speedbox,&QDoubleSpinBox::valueChanged,[=](double a){ set_speed(a);});
    connect(ui->biasbox,&QSpinBox::valueChanged,[=](int a){ set_bias(a);});
    connect(ui->speedbox,&QDoubleSpinBox::valueChanged,[=](double a){virtual_note->setDuration(1500/a);});

}

options::~options() {
    delete ui;
}

void options::set_volume(float h) {
    emit mvolume(h);
}

void options::bind(rg *bind) {
    bind_rg=bind;
    connect(this,SIGNAL(mvolume(float)),bind_rg,SLOT(set_volume(float)));
}

void options::set_speed(float t) {
    speed=t;
    base_prepare_time=1375/speed;
}

void options::set_bias(int t) {
    bias=t;
    bias_time=bias;
}
