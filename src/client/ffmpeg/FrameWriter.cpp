#include "FrameWriter.h"

#define ERROR_SEND_FRAME "Error sending a frame for encoding\n"
#define ERROR_ENCODING "Error during encoding\n"

FrameWriter::FrameWriter() {}


/* Codifica y escribe el archivo de salida en el frame actual */
void encode(CodecContext *codec, Frame *frame, Packet *packet, FILE *outFile) {
    /* send the frame to the encoder */
    int ret = avcodec_send_frame(codec->get(), frame->get());
    if (ret < 0) {
        throw RecorderException(ERROR_SEND_FRAME);
    }
    while (ret >= 0) {
        ret = avcodec_receive_packet(codec->get(), packet->get());
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            throw RecorderException(ERROR_ENCODING);
        }
    }
    packet->write(outFile);
}


void FrameWriter::close() {
    encode(&codec, NULL, &packet, this->outFile);
    /* add sequence end code to have a real MPEG file */
    uint8_t endcode[] = { 0, 0, 1, 0xb7 };
    fwrite(endcode, 1, sizeof(endcode), this->outFile);
}
