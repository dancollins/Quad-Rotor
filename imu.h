#ifndef IMU_h
#define IMU_h

#include <math.h>

#include "accel.h"
#include "gyro.h"

#include "FreeRTOS.h"
#include "task.h"

struct imuEstimate {
    /* Accelerometer Data (This is a normalised vector) */
    float ax;
    float ay;
    float az;

    /* These are obtained from the previous estimate and the measured gyroscope value */
    float gx;
    float gy;
    float gz;

    /* Estimated values */
    float ex;
    float ey;
    float ez;
};

void imu_update(struct imuEstimate *imu);
float square(float x);

#endif