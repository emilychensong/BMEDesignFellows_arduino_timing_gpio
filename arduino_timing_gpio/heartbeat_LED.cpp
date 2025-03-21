// // LIBRARIES
// #include <Arduino.h>
// #include <avr/sleep.h> 

// // MACROS
// // PIN ASSIGNMENTS
// // USER SPECIFICATIONS
// #define HEARTBEAT_FREQ_HZ 1  // frequency of heartbeat LED at 1 Hz
// #define HEARTBEAT_DUTY_CYCLE 25  // duty cycle of heartbeat LED blinking at 25%
// #define HEARTBEAT_LED 13  // on board LED blinks heartbeat

// #define LED_PIN 9 // PWM-capable pin
// #define ANALOG_READ_RANGE 1023 // 10-bit ((2**10)-1); 10-bit is specific to your microcontroller (see datasheet)
// #define ADC_READ_INTERVAL_MS 5000  // reads analog voltage every 5 sec


// // GLOBAL VARIABLES
// unsigned long heartbeat_period_ms;
// unsigned long heartbeat_ontime_interval_ms;
// unsigned long heartbeat_offtime_interval_ms;
// unsigned long heartbeat_time_last_toggle_ms = 0;

// unsigned long current_time_ms = 0;  // current absolute time

// bool heartbeat_led_state = HIGH; // default ON

// // FUNCTION DECLARATIONS
// int toggle_heartbeat_led();

// /*
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
 
//     /*
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
// */

// }

// int toggle_heartbeat_led() {
//     switch (heartbeat_led_state) {
//         case HIGH:
//             if ((current_time_ms - heartbeat_time_last_toggle_ms) > heartbeat_ontime_interval_ms) {
//                 digitalWrite(HEARTBEAT_LED, LOW);
//                 heartbeat_led_state = LOW;
            
//                 // Serial monitor displays terminal message of current absolute time
//                 Serial.print("Current absolute time (ms): ");
//                 Serial.println(current_time_ms);
//                 // Serial monitor displays terminal message of relative time since last heartbeat LED state toogle
//                 Serial.print("Last LED state toggle (ms): ");
//                 Serial.println(heartbeat_time_last_toggle_ms);

//                 heartbeat_time_last_toggle_ms = current_time_ms;
//             }
//             break;
//         case LOW:
//             if ((current_time_ms - heartbeat_time_last_toggle_ms) > heartbeat_offtime_interval_ms) {
//                 digitalWrite(HEARTBEAT_LED, HIGH);
//                 heartbeat_led_state = HIGH;
                
//                 // Serial monitor displays terminal message of current absolute time
//                 Serial.print("Current absolute time (ms): ");
//                 Serial.println(current_time_ms);
//                 // Serial monitor displays terminal message of relative time since last heartbeat LED state toogle
//                 Serial.print("Last LED state toggle (ms): ");
//                 Serial.println(heartbeat_time_last_toggle_ms);

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
