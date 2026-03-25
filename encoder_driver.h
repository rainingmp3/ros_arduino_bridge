/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
// Modified by Ivane Kotanov
// Changes: added definition for IR wheel encoders

#ifdef ARDUINO_ENC_COUNTER
// below can be changed, but should be PORTD pins;
// otherwise additional changes in the code are required
#define LEFT_ENC_PIN_A PD2 // pin 2
#define LEFT_ENC_PIN_B PD3 // pin 3

// below can be changed, but should be PORTC pins
//  #define RIGHT_ENC_PIN_A PC4  //pin A4
//  #define RIGHT_ENC_PIN_B PC5   //pin A5

// I assume previous encoder to be the Hall effect one,  hence the analog ports.
// But for an infra-red wheel encoders digital ports are used.
//
#elif defined(ARDUINO_ENC_COUNTER_IR)
#define LEFT_ENC 3
#define RIGHT_ENC 2

#endif

void initIrEncoders();
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();
