#ifndef __STATE_H__
#define __STATE_H__

typedef enum {
    IDLE,
    GO_FORWARD,
    GO_BACKWARD,
    OBSTACLE_DETECTED,
    DECIDE_DIRECTION,
    TURN_LEFT,
    TURN_RIGHT,
    SCAN_ALL,
} State_t;

#endif // __STATE_H__