// You can override default thresholds
#define BUTTON_DEBRIEF_THRESHOLD 100UL
#define BUTTON_HOLD_THRESHOLD 16000000UL

#include <Button.h>

#include <avr/io.h>

bool onPressHandler(Button &button) {
    // Do some stuff
    return true;//<-- Return true for execute handler only once after button state changed
}

bool onReleaseHandler(Button &button) {
    // Do some stuff
    return true;
}

bool onHoldHandler(Button &button) {
    // You can set threshold for repeat call handler
    button.setCounter(8000000UL);

    // Do some stuff
    return true;//<-- Return true for execute handler only once after button state changed
}

int main() {
    // Initialize buttons
    Button button1 = Button(&PORTA, PIN0, BUTTON_MODE_PULL_UP);   //<-- Button connected to GND
    Button button2 = Button(&PORTA, PIN1, BUTTON_MODE_PULL_DOWN); //<-- Button connected to VCC

    // You can set handler callbacks for dispatch later
    button2.setOnPressHandler(onPressHandler);
    button2.setOnReleaseHandler(onReleaseHandler);
    button2.setOnHoldHandler(onHoldHandler);

    while (true) {
        // Now You can check button state and execute some code depends on state
        if (BUTTON_STATE_PRESSED == button1.getState()) {
            // Do some stuff
        }

        // Or You can dispatch callbacks for get your code more clear
        button2.dispatch();
    }
}