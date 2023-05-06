//
// Created by Tuuuu on 2023/4/26.
//

#ifndef UNTITLED_SELECT_H
#define UNTITLED_SELECT_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include<unordered_map>
#include"rg.h"
QT_BEGIN_NAMESPACE
namespace Ui { class select; }
QT_END_NAMESPACE
struct artist_bpm{
    QString artist;
    int bpm;
};

class select : public QWidget {
Q_OBJECT

public:
    rg* bind_rg;
    explicit select(QWidget *parent = nullptr);
    QListWidget songlist_widget;
    void add_songs(QString name);
    void display(QListWidgetItem* item);
    QList<QString> nameinfo;
    QList<QString> artistinfo;
    QList<int> bpminfo;
    std::unordered_map<QString,artist_bpm> songinfo_hashmap;
    bool is_edit=false;
    void set_rg(rg*);
    ~select() override;

private:
    Ui::select *ui;

signals:
    void start_song(QString);
    void edit_song(QString);
};


#endif //UNTITLED_SELECT_H
