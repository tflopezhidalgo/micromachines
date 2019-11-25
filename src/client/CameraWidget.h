#ifndef MICROMACHINES_CAMERAWIDGET_H
#define MICROMACHINES_CAMERAWIDGET_H

class Car;

class CameraWidget {
public:
    virtual void onRender() = 0;
    virtual void onAdded(Car* target) = 0;
};

#endif
