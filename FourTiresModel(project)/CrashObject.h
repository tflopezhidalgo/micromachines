//
// Created by eliana on 19/10/19.
//

#ifndef TESTING_CRASHOBJECT_H
#define TESTING_CRASHOBJECT_H

enum CrashType {
    CAR,
    BORDER,
    BOX,
};

class CrashObject {
private:
    CrashType type;
public:
    CrashType getType();
};


#endif //TESTING_CRASHOBJECT_H
