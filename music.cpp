//
// Created by Tuuuu on 2023/4/13.
//
#include "music.h"
#include<fstream>
int base_prepare_time;
int bias_time;
music_player::music_player() {
    note_rail_info=new QList<int>;
    time_info=new QList<int>;
}

void music_player::read(QString s) {//TODO: change s to a specific file
    std::fstream read_stream;
    read_stream.open("../songs/track.txt",std::ios_base::in);
    int line_buf;
    while(true)
    {
        read_stream>>line_buf;
        if(line_buf==-1)break;
        note_rail_info->append(line_buf);
        read_stream>>line_buf;
        time_info->append(line_buf);
    }
    read_stream.close();
}

void music_player::set_current(QString s) {
    current_song=s;
    setSource(QUrl("../songs/"+s+".mp3"));
}


music_thread::music_thread(note_generator *g,QWidget* parent,QAudioOutput* output) {
    music=new music_player;
    music->setAudioOutput(output);
    music->set_current("track");
    timer=new QElapsedTimer;
    connect(this,SIGNAL(generate(int)),g,SLOT(generate_by_music(int)));
    base_prepare_time=1375;

}

void music_thread::reset() {
    music->note_rail_info->clear();
    music->time_info->clear();
    timer->invalidate();
    prepare_ms=base_prepare_time;
}

void music_thread::stop() {
    music->stop();
    requestInterruption();
//    if (!wait(1000)) {
//        terminate();
//    }
    wait();
    reset();
}


