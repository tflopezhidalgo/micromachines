#ifndef MICROMACHINES_PACKET_H
#define MICROMACHINES_PACKET_H


extern "C" {
#include <libavcodec/avcodec.h>
}

class Packet {
private:
    AVPacket* pkt;
public:
    Packet();

    AVPacket* get();

    void write(FILE* outFile);

    ~Packet();
};


#endif //MICROMACHINES_PACKET_H
