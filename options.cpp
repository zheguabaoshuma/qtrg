//
// Created by Tuuuu on 2023/4/20.
//

// You may need to build the project (run Qt uic code generator) to get "ui_options.h" resolved

#include "options.h"
#include "ui_options.h"


options::options(QWidget *parent) :
        QWidget(parent), ui(new Ui::options) {
    ui->setupUi(this);

    connect(ui->horizontalSlider,&QSlider::sliderMoved,this,[=](int a){ float vol=static_cast<float>(a)/102;set_volume(vol);});
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
