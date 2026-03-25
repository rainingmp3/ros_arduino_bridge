/*
  MPU6050 Raw

  A code for obtaining raw data from the MPU6050 module with the option to
  modify the data output format.

  Find the full MPU6050 library documentation here:
  https://github.com/ElectronicCats/mpu6050/wiki */

#ifdef USE_IMU

#include "I2Cdev.h"
#include "MPU6050.h"

/* MPU6050 default I2C address is 0x68*/
MPU6050 mpu;
// MPU6050 mpu(0x69);         //Use for AD0 high
// MPU6050 mpu(0x68, &Wire1); //Use for AD0 low, but 2nd Wire (TWI/I2C) object.

/* OUTPUT FORMAT
DEFINITION----------------------------------------------------------------------------------
- Use "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated list of the
accel X/Y/Z and gyro X/Y/Z values in decimal. Easy to read, but not so easy to
parse, and slower over UART.

- Use "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit binary, one
right after the other. As fast as possible without compression or data loss,
easy to parse, but impossible to read for a human. This output format is used as
an output.
--------------------------------------------------------------------------------------------------------------*/
#define OUTPUT_READABLE_ACCELGYRO
// #define OUTPUT_BINARY_ACCELGYRO

int16_t ax, ay, az;
int16_t gx, gy, gz;
bool blinkState;

void initIMU() {
/*--Sxtart I2C interface--*/
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    Serial.begin(BAUDRATE); // Initializate Serial wo work well at 8MHz/16MHz

    /*Initialize device and check connection*/
    Serial.println("Initializing MPU...");
    mpu.initialize();
    Serial.println("Testing MPU6050 connection...");
    if (mpu.testConnection() == false) {
        Serial.println("MPU6050 connection failed");
        while (true)
            ;
    } else {
        Serial.println("MPU6050 connection successful");
    }

    /* Use the code below to change accel/gyro offset values. Use MPU6050_Zero
     * to obtain the recommended offsets */
    Serial.println("Updating internal sensor offsets...\n");
    mpu.setXAccelOffset(-910); // Set your accelerometer offset for axis X
    mpu.setYAccelOffset(703);  // Set your accelerometer offset for axis Y
    mpu.setZAccelOffset(703);  // Set your accelerometer offset for axis Z
    mpu.setXGyroOffset(205);   // Set your gyro offset for axis X
    mpu.setYGyroOffset(53);    // Set your gyro offset for axis Y
    mpu.setZGyroOffset(66);    // Set your gyro offset for axis Z
    /*Print the defined offsets*/
    // Serial.print(" ");
    Serial.println("IMU OFFs:");
    Serial.print(mpu.getXAccelOffset());
    Serial.print(" ");
    Serial.print(mpu.getYAccelOffset());
    Serial.print(" ");
    Serial.print(mpu.getZAccelOffset());
    Serial.print(" ");
    Serial.print(mpu.getXGyroOffset());
    Serial.print(" ");
    Serial.print(mpu.getYGyroOffset());
    Serial.print(" ");
    Serial.print(mpu.getZGyroOffset());
    Serial.print("\n");

    /*Configure board LED pin for output*/
    pinMode(LED_BUILTIN, OUTPUT);
}

void runIMU() {
    /* Read raw accel/gyro data from the module. Other methods commented*/
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    // mpu.getAcceleration(&ax, &ay, &az);
    // mpu.getRotation(&gx, &gy, &gz);

    // Start of my changes
    // Translate to SI units. Couldn't find this functional in the docs,
    // needs to be adjusted depending on a sampling range (e.g. +- 2g, +-250
    // degrees, which are defaults, that are used below)
    float ax_f, ay_f, az_f, gx_f, gy_f, gz_f;
    ax_f = ax * 0.00059872253418; // value / 16384 * 9.80947: LSB -> g -> m/s^2
    ay_f = ay * 0.00059872253418; // value / 16384 * 9.80947: LSB -> g -> m/s^2
    az_f = az * 0.00059872253418; // value / 16384 * 9.80947: LSB -> g -> m/s^2
    gx_f = gx * 0.0001332312;     // value / 131 * 0.01745329: LSB/degree/s ->
                                  // degree/s -> radian/s
    gy_f = gy * 0.0001332312;     // value / 131 * 0.01745329: LSB/degree/s ->
                                  // degree/s -> radian/s
    gz_f = gz * 0.0001332312;     // value / 131 * 0.01745329: LSB/degree/s ->
                                  // degree/s -> radian/s
/*Print the obtained data on the defined format*/
#ifdef OUTPUT_READABLE_ACCELGYRO
    Serial.print(ax_f, 8);
    Serial.print(" ");
    Serial.print(ay_f, 8);
    Serial.print(" ");
    Serial.print(az_f, 8);
    Serial.print(" ");
    Serial.print(gx_f, 8);
    Serial.print(" ");
    Serial.print(gy_f, 8);
    Serial.print(" ");
    Serial.println(gz_f, 8);

#endif

#ifdef OUTPUT_BINARY_ACCELGYRO
    Serial.write((uint8_t)(ax >> 8));
    Serial.write((uint8_t)(ax & 0xFF));
    Serial.write((uint8_t)(ay >> 8));
    Serial.write((uint8_t)(ay & 0xFF));
    Serial.write((uint8_t)(az >> 8));
    Serial.write((uint8_t)(az & 0xFF));
    Serial.write((uint8_t)(gx >> 8));
    Serial.write((uint8_t)(gx & 0xFF));
    Serial.write((uint8_t)(gy >> 8));
    Serial.write((uint8_t)(gy & 0xFF));
    Serial.write((uint8_t)(gz >> 8));
    Serial.write((uint8_t)(gz & 0xFF));
#endif

    /*Blink LED to indicate activity*/
    blinkState = !blinkState;
    digitalWrite(LED_BUILTIN, blinkState);
}
#endif
