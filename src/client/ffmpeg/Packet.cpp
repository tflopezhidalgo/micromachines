#include "Packet.h"

Packet::Packet() : pkt(av_packet_alloc())
    {}

AVPacket *Packet::get() {
    return this->pkt;
}

void Packet::write(FILE *outFile) {
    fwrite(pkt->data, 1, pkt->size, outFile);
    av_packet_unref(pkt);
}

Packet::~Packet() {
    av_packet_free(&pkt);
}
