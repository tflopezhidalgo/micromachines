#ifndef MICROMACHINES_RECORDINGWIDGET_H
#define MICROMACHINES_RECORDINGWIDGET_H

#include <ffmpeg/RecorderHandle.h>
#include "CameraWidget.h"
#include "Texture.h"

class RecordingWidget : public CameraWidget {
private:
    Texture texture;
    Window& main;
    RecorderHandle& recorder;

public:
    RecordingWidget(Window& main, RecorderHandle& recorder);
    RecordingWidget(RecordingWidget&& other);
    void onRender() override;
    void onAdded(Car* target) override;
};


#endif
