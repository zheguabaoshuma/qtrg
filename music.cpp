//
// Created by Tuuuu on 2023/4/13.
//
#include "music.h"
#include<fstream>
music_player::music_player() {
    note_rail_info=new QList<int>;
    time_info=new QList<int>;
}

void music_player::read(QString s) {
    std::fstream read_stream;
    read_stream.open("../data.txt",std::ios_base::in);
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
//    for(int k=0;k<150;k++)
//    {
//        for(int r=1;r<4;r++){
//            note_rail_info->append(r);
//            time_info->append(500*(k+5));
//        }
//    }
}

void music_player::set_current(QString s) {
    current_song=s;
    setSource(QUrl("../"+s));
}


music_thread::music_thread(note_generator *g,QWidget* parent,QAudioOutput* output) {
    music=new music_player;
    music->setAudioOutput(output);
    music->set_current("track.mp3");
    timer=new QElapsedTimer;
    connect(this,SIGNAL(generate(int)),g,SLOT(generate_by_music(int)));
}
