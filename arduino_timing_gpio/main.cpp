// LOAD ALL LIBRARIES FIRST
#include <Arduino.h>
#include <avr/sleep.h> 

// DEFINE ALL PREPROCESSOR MACROS
// see pinout in datasheet to know what pins are where / do what
// NOTE: macros are defined in ALL CAPS to help identify their usage in the code (in contrast to variables)
// All device specification-related values should be defined here, *not* in the downstream code!  You should
// not have to search the code for where values are defined / used.

#define LED_PIN 9 // PWM-capable pin
#define ANALOG_READ_RANGE 1023 // 10-bit ((2**10)-1); 10-bit is specific to your microcontroller (see datasheet)
#define ADC_READ_INTERVAL_MS 5000 

#define HEARTBEAT_FREQ_HZ 1  // frequency of heartbeat LED at 1 Hz
#define HEARTBEAT_DUTY_CYCLE 25  // duty cycle of heartbeat LED blinking at 25%
#define HEARTBEAT_LED 13 // built-in LED on Arduino Nano Every


// DEFINE ALL GLOBAL VARIABLES
// millis() returns an unsigned long int (32-bit) value 
// default int is 16-bit

//for heartbeat LED:
unsigned long heartbeat_period_ms;
unsigned long heartbeat_ontime_interval_ms;
unsigned long heartbeat_offtime_interval_ms;
unsigned long heartbeat_time_last_toggle_ms = 0;

bool heartbeat_led_state = HIGH; // default ON

unsigned long last_toggle_time_ms = 0; // long int is 32-bit (default int is 16-bit)
int pot_voltage_raw;
bool led_state = LOW;

unsigned long current_time_ms = 0;

// DECLARE ALL FUNCTIONS (excluding loop() and setup())

int toggle_heartbeat_led(); // for heartbeat LED
int read_adc(void);
int toggle_led(void);
int ADC_read(); // for ADC part

// setup state machine enum and variable
enum states {IDLE, READ_ADC, TOGGLE_LED};
int state = IDLE;

// setup is run once when the device is powered on
void setup() {
    // configure GPIO pin to be an output
    pinMode(HEARTBEAT_LED, OUTPUT);

    pinMode(LED_PIN, OUTPUT);
    
    // start the serial (communication) monitor
    // 9600 is the baud rate (rate of data communication, 9600 bits/s)
    // set increments; slower is more reliable
    Serial.begin(9600);
    Serial.println("INF: Device initialized.");

    heartbeat_period_ms = (float)(1/HEARTBEAT_FREQ_HZ) * 1000; // TECHDEBT: div int problem
    // (float) - typecast operation, temp. makes operation floating point #

    // TECHDEBT: lazy
    heartbeat_ontime_interval_ms = (float)heartbeat_period_ms * (float)HEARTBEAT_DUTY_CYCLE / 100;
    heartbeat_offtime_interval_ms = heartbeat_period_ms - heartbeat_ontime_interval_ms;

    digitalWrite(HEARTBEAT_LED, HIGH);
}

// loop continuously runs after setup until to break/stop it
// note that the loop reads like an "action script"
void loop() {

    // poll the system clock since the device was powered on
    // do this in every state
    current_time_ms = millis();

    // TODO: add a function call here that runs in every state that blinks the heartbeat LED (D13)
    // at the specified 25% duty cycle
    int ret = toggle_heartbeat_led();
        if (ret != 0) {
            Serial.println("ERR: Failed to toggle heartbeat LED.");
        }
    
    ret = ADC_read();
        if (ret != 0) {
            Serial.println("ERR: Failed to toggle ADC_read function.");
        }
    
}

// avoid using delay() in your code; it's a blocking function!!!!
int ADC_read() {
    int ret;
    switch (state) {
        case IDLE:
            /* to help get your started, you may want to calculate the time since the
            * last toggle to figure out when to next change the LED state; below is a
            * pseudo-code snippet 
            */
            // Serial.println("INF: Device is idle.");
            if ((current_time_ms - last_toggle_time_ms > ADC_READ_INTERVAL_MS))
            {
                // do something after a specified time interval has elapsed
                state = READ_ADC;
            }
            break;
        case READ_ADC:
            //Serial.println("INF: Reading ADC value.");
            ret = read_adc();  // the returned value is the exit code, not the read value
            if (ret == 0) {
                Serial.println("INF: ADC read successful.");
                Serial.println(pot_voltage_raw);
                // TODO: convert this to a percentage of max voltage that can be read on this pin

                // Converts ADC value (0-1023) into a fraction of the full 5V range, then converts to %
                // typecast pot_voltage_raw
                float percentage = ((float)pot_voltage_raw / 1023.0) * 100.0;

                // Print to Serial Monitor
                Serial.print("ADC Value: ");
                Serial.print(pot_voltage_raw);
                Serial.print("Percentage: ");
                Serial.print(percentage, 1);
                Serial.println("%");

            } else {
                Serial.println("ERR: ADC read failed.");
            }
            // print_next_on_off_times();
            state = TOGGLE_LED;
            break;
        case TOGGLE_LED:
            //Serial.println("INF: Toggling LED state.");
            ret = toggle_led();
            if (ret == 0) {
                Serial.println("INF: LED toggle successful.");
            } else {
                Serial.println("ERR: LED toggle failed.");
            }
            state = IDLE;
            break;
    }
    
    // how to print to the serial monitor
    // (annoyingly, the Arduino Serial.print commands are very limited)
    //Serial.print("DBG: Setting LEDs HIGH/LOW at time:");
    //Serial.println(current_time_ms);
}


int read_adc() {
    // read the voltage on the analog pin
    pot_voltage_raw = analogRead(A0);
    //Serial.print("ADC: ");
    //Serial.println(pot_voltage_raw);
    return 0;    
}

int toggle_led() {
    // toggle the LED state
    digitalWrite(LED_PIN, !led_state);
    led_state = !led_state;
    return 0;
}

int toggle_heartbeat_led() {
    switch (heartbeat_led_state) {
        case HIGH:
            if ((current_time_ms - heartbeat_time_last_toggle_ms) > heartbeat_ontime_interval_ms) {
                digitalWrite(HEARTBEAT_LED, LOW);
                heartbeat_led_state = LOW;
            
                // // Serial monitor displays terminal message of current absolute time
                // Serial.print("Current absolute time (ms): ");
                // Serial.println(current_time_ms);
                // // Serial monitor displays terminal message of relative time since last heartbeat LED state toogle
                // Serial.print("Last LED state toggle (ms): ");
                // Serial.println(heartbeat_time_last_toggle_ms);

                heartbeat_time_last_toggle_ms = current_time_ms;
            }
            break;
        case LOW:
            if ((current_time_ms - heartbeat_time_last_toggle_ms) > heartbeat_offtime_interval_ms) {
                digitalWrite(HEARTBEAT_LED, HIGH);
                heartbeat_led_state = HIGH;
                
                // // Serial monitor displays terminal message of current absolute time
                // Serial.print("Current absolute time (ms): ");
                // Serial.println(current_time_ms);
                // // Serial monitor displays terminal message of relative time since last heartbeat LED state toogle
                // Serial.print("Last LED state toggle (ms): ");
                // Serial.println(heartbeat_time_last_toggle_ms);

                heartbeat_time_last_toggle_ms = current_time_ms;
            }
            break;
        default:
            Serial.println("ERR: Invalid state.");
            return -1;
            break;
    }

    return 0;
}

