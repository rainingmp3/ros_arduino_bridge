/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
#define RIGHT_MOTOR_BACKWARD 5
#define LEFT_MOTOR_BACKWARD 6
#define RIGHT_MOTOR_FORWARD 9
#define LEFT_MOTOR_FORWARD 10
#define RIGHT_MOTOR_ENABLE 12
#define LEFT_MOTOR_ENABLE 13
// NOTE: extern
extern volatile bool left_reverse;
extern volatile bool right_reverse;
#endif

void initMotorController();
void setMotorSpeed(float i, float spd);
void setMotorSpeeds(float leftSpeed, float rightSpeed);
