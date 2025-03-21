
// #include <Arduino.h>

// // MACROS
// // PIN ASSIGNMENTS
// // USER SPECIFICATIONS
// #define HEARTBEAT_FREQ_HZ 1
// #define HEARTBEAT_DUTY_CYCLE 25
// #define HEARTBEAT_LED 13

// // GLOBAL VARIABLES
// unsigned long heartbeat_period_ms;
// unsigned long heartbeat_ontime_interval_ms;
// unsigned long heartbeat_offtime_interval_ms;
// unsigned long heartbeat_time_last_toggle_ms = 0;

// // structures create a bundle of common variables that can be applied 
// struct heartbeat_led
// {
//     unsigned long period_ms;
//     unsigned long ontime_interval_ms;
//     unsigned long offtime_interval_ms;
//     unsigned long time_last_toggle_ms;
//     bool state;
// };

// /*
// // create instance of the structure
// struct heartbeat_led heartbeat_led = {
//     .period_ms = 0,
//     .ontime_interval_ms = 0,
//     .offtime_interval_ms = 0,
//     .time_last_toggle_ms = 0,
//     .state = HIGH
// };

// heartbeat_led0.state = HIGH
// */

// unsigned long current_time_ms = 0;

// bool heartbeat_led_state = HIGH; // default ON

// // FUNCTION DECLARATIONS
// int toggle_heartbeat_led();
//  /*
// enum states = {IDLE, READ_ADC, TOGGLE_LED};
// int state = IDLE;
// */

// void setup() {
    
//     pinMode(HEARTBEAT_LED, OUTPUT);
//     Serial.begin(9600);
//     Serial.println("INF: Device initialized.");

//     heartbeat_period_ms = (float)(1/HEARTBEAT_FREQ_HZ) * 1000; // TECHDEBT: div int problem
//     // (float) - typecast operation, temp. makes operation floating point #

//     // TECHDEBT: lazy
//     heartbeat_ontime_interval_ms = (float)heartbeat_period_ms * (float)HEARTBEAT_DUTY_CYCLE / 100;
//     heartbeat_offtime_interval_ms = heartbeat_period_ms - heartbeat_ontime_interval_ms;

//     digitalWrite(HEARTBEAT_LED, HIGH);
// }



// void loop() {

//     // Is my current time - when I last changed the heartbeat LED > change interval
//     current_time_ms = millis();

//     int ret = toggle_heartbeat_led();
//     if (ret != 0) {
//         Serial.println("ERR: Failed to toggle heartbeat LED.");
//     }
//  /*
//     switch(state) {
//         case IDLE:
//             //ret = take_a_nap();
//             break;
//         case READ_ADC:
//             //ret = read_analog_input_pin();
//             break;
//         case TOGGLE_LED:
//             //ret = toggle_read_pin_led();
//             break;
//         default:
//         Serial.println("ERR: Invalid state.");
//         break;
//     }
//         */
// }

// int toggle_heartbeat_led() {
//     switch (heartbeat_led_state) {
//         case HIGH:
//             if ((current_time_ms - heartbeat_time_last_toggle_ms) > heartbeat_ontime_interval_ms) {
//                 digitalWrite(HEARTBEAT_LED, LOW);
//                 heartbeat_led_state = LOW;
//                 heartbeat_time_last_toggle_ms = current_time_ms;
//             }
//             break;
//         case LOW:
//             if ((current_time_ms - heartbeat_time_last_toggle_ms) > heartbeat_offtime_interval_ms) {
//                 digitalWrite(HEARTBEAT_LED, HIGH);
//                 heartbeat_led_state = HIGH;
//                 heartbeat_time_last_toggle_ms = current_time_ms;
//             }
//             break;
//         default:
//             Serial.println("ERR: Invalid state.");
//             return -1;
//             break;
//     }

//     return 0;
// }
