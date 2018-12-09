#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#ifndef BUTTON_DEBRIEF_THRESHOLD
#define BUTTON_DEBRIEF_THRESHOLD 100UL
#endif

#ifndef BUTTON_HOLD_THRESHOLD
#define BUTTON_HOLD_THRESHOLD 100000UL
#endif

enum ButtonMode {
    BUTTON_MODE_PULL_DOWN,
    BUTTON_MODE_PULL_UP,
};

enum ButtonState {
    BUTTON_STATE_RELEASED = -1,
    BUTTON_STATE_UNKNOWN  =  0,
    BUTTON_STATE_PRESSED  =  1,
};

class Button;

typedef bool (*ButtonEventHandler_t)(Button &);

class Button {
private:
    volatile uint8_t *_port;
    uint8_t _pin;
    ButtonMode _mode;
    uint8_t _state;
    uint32_t _counter = 0;

    ButtonEventHandler_t _onPressHandler;
    ButtonEventHandler_t _onReleaseHandler;
    ButtonEventHandler_t _onHoldHandler;
public:
    /**
     * @param port
     * @param pin
     * @param mode
     */
    Button(volatile uint8_t *port, uint8_t pin, ButtonMode mode);

    /**
     * Get state of button, must be called in loop
     *
     * @return
     */
    ButtonState getState();

    /**
     * Dispatch callbacks, must be called in loop
     */
    void dispatch();

    /**
     * @param value
     */
    void setCounter(uint32_t value);

    /**
     * @param handler
     */
    void setOnPressHandler(ButtonEventHandler_t handler);

    /**
     * @param handler
     */
    void setOnReleaseHandler(ButtonEventHandler_t handler);

    /**
     * @param handler
     */
    void setOnHoldHandler(ButtonEventHandler_t handler);
};

#endif //BUTTON_H
