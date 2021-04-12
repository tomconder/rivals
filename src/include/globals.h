#ifndef INCLUDE_GLOBALS_H
#define INCLUDE_GLOBALS_H

namespace globals {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    enum retcode {
        FAIL = 0,
        OK = 1
    };
}

namespace direction {
    enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
}

namespace move {
    enum Move {
        LEFT,
        RIGHT,
        FORWARD,
        BACK,
        NONE
    };
}


#endif //INCLUDE_GLOBALS_H
