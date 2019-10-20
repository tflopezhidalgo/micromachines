//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_CRASHOBJECT_H
#define TESTING_CRASHOBJECT_H

enum CrashType {
    PLAYER,
    CAR,
    BORDER,
    BOX,
};

class CrashObject {
private:
    CrashType type;
    int health = 100;
public:
    virtual CrashType getType() = 0;

    virtual void getDamage(int damage) = 0;
};

#endif //TESTING_CRASHOBJECT_H
