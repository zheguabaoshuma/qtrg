//
// Created by Tuuuu on 2023/4/26.
//

// You may need to build the project (run Qt uic code generator) to get "ui_select.h" resolved

#include "select.h"
#include "ui_select.h"
#include<fstream>

select::select(QWidget *parent) :
        QWidget(parent), ui(new Ui::select) {
    ui->setupUi(this);

    songlist_widget.setIconSize(QSize(64,64));
    ui->scrollArea->setWidget(&songlist_widget);
    ui->scrollArea->show();
    connect(&songlist_widget,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item){emit start_song(item->text());});
    connect(&songlist_widget,&QListWidget::itemClicked,[=](QListWidgetItem *item){ display(item);});

    add_songs("track");
    add_songs("Cyaegha");

    std::fstream file;
    file.open("../songs/songinfo.txt");
    while(true)
    {
        char name[50],artist[50];
        int bpm;
        file>>name>>artist>>bpm;
        if(strcmp(name,"eof")==0)break;
        else
        {
            artist_bpm ab;
            ab.artist=QString(artist);
            ab.bpm=bpm;
            songinfo_hashmap.insert(std::pair<QString,artist_bpm>(name,ab));
        }
    }
    file.close();
}

select::~select() {
    delete ui;
}

void select::add_songs(QString song) {
    QString base_path="../songs/";

    QPixmap bg;
    bg.load(base_path+song+QString("_bg.png"));
    //bg.scaled(64,64);

    QListWidgetItem* aitem;
    aitem=new QListWidgetItem;
    aitem->setIcon(QIcon(bg));
    aitem->setText(song);

    songlist_widget.addItem(aitem);

}

void select::display(QListWidgetItem *item) {
    QPixmap bg;
    QString name=item->text();
    bg.load("../songs/"+name+"_bg.png");
    bg=bg.scaled(QSize(255,255));
    ui->bglabel->setPixmap(bg);
    ui->songnamelabel->setText(name);

    artist_bpm ab=songinfo_hashmap.at(name);
    char buffer[3];itoa(ab.bpm,buffer,10);
    ui->songinfolabel->setText("ARTIST: "+ab.artist+"\tbpm: "+QString(buffer));
}


