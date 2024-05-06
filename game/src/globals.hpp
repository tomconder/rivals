#pragma once

namespace globals {
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum retcode { FAIL = 0, OK = 1 };
}  // namespace globals

namespace direction {
enum Direction { LEFT, RIGHT, UP, DOWN };
}

namespace move {
enum Move { LEFT, RIGHT, FORWARD, BACK, ROTATE_LEFT, ROTATE_RIGHT, NONE };
}
