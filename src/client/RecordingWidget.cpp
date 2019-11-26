#include "RecordingWidget.h"

#define RECORD_ICON "../media/sprites/recording_icon.png"

RecordingWidget::RecordingWidget(Window& main, RecorderHandle& recorder) :
texture(std::move(main.createTextureFrom(RECORD_ICON))),
main(main),
recorder(recorder) { }

RecordingWidget::RecordingWidget(RecordingWidget&& other) :
texture(std::move(other.texture)),
main(other.main),
recorder(other.recorder) { }


void RecordingWidget::onRender() {
    if (recorder.isRecording()) {
        SDL_Rect r = { 10, 10, 100, 100};
        texture.render(r, 0);
    }
}

void RecordingWidget::onAdded(Car *target) {
    return;
}
