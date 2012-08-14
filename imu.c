#include "imu.h"

//void imu_update(struct imuEstimate *imu) {
//    static char firstSample = 1;
//    static portTickType oldCount = 0;
//    portTickType newCount, interval;
//    struct accelData accel;
//    struct gyroData gyro;
//    float tmpf, tmpf2;
//    float Awx, Awy;
//    char gyroSign, i;
//
//    newCount = xTaskGetTickCount(); // Save the time the samples were taken
//
//    /* Get the input data values */
//    accel_read(&accel);
//    gyro_read(&gyro);
//
//    /* Find the interval between this and previous samples */
//    interval = newCount - oldCount; // TODO: Make sure this actually works after an overflow...
//    oldCount = newCount;
//
//    /* Normalise the accelerometer vector */
//    tmpf = sqrt(square(accel.x)+square(accel.y)+square(accel.z));
//    imu->ax = accel.x / tmpf;
//    imu->ay = accel.y / tmpf;
//    imu->az = accel.z / tmpf;
//
//    if (firstSample) {
//        /* We don't have any prior estimate values, so use the accelerometer directly. */
//        imu->gx = imu->ax;
//        imu->gy = imu->ay;
//        imu->gz = imu->az;
//        firstSample = 0;
//    } else {
//        /* If this value is too small, then we can't use it as it is used during the esitmate */
//        if (abs(imu->ez) < 0.1) {
//            imu->gx = imu->ex;
//            imu->gy = imu->ey;
//            imu->gz = imu->ez;
//        } else {
//            /* Convert gyro mesaurements into deg/ms */
//            tmpf = gyro.x * 1000;
//            tmpf2 = gyro.y * 1000;
//
//            /* Convert into degrees */
//            tmpf *= (interval / 1000.0f);
//            tmpf2 *= (interval / 1000.0f);
//
//            /* Find the angle, and then convert into degrees */
//            Awx = atan2(imu->ex, imu->ez) * 180 / M_PI;
//            Awy = atan2(imu->ey, imu->ez) * 180 / M_PI;
//
//            /* Get updated angle according to gyro movement */
//            Awx += tmpf;
//            Awy += tmpf2;
//
//            gyroSign = (cos(Awx * 180/M_PI) >= 0) ? 1 : -1; // Find which quadrant
//
//            /* Calculate gyro values from the angles */
//            for (i=0; i<=1; i++) {
//                imu->gx = sin(Awx * M_PI / 180);
//                imu->gx /= sqrt( 1 + square(cos(Awx * M_PI / 180)) * square(tan(Awy * M_PI / 180)));
//                imu->gy = sin(Awy * M_PI / 180);
//                imu->gy /= sqrt( 1 + square(cos(Awy * M_PI / 180)) * square(tan(Awx * M_PI / 180)));
//            }
//            imu->gz = gyroSign * sqrt(1 - square(imu->gx) - square(imu->gy));
//        }
//
//        /* Combine accelerometer and gyroscope data */
//        imu->ex = (imu->ax + 10 * imu->gx) / 11;
//        imu->ey = (imu->ay + 10 * imu->gy) / 11;
//        imu->ez = (imu->az + 10 * imu->gz) / 11;
//
//        /* Normalise the estimate */
//        tmpf = sqrt(square(imu->ex)+square(imu->ey)+square(imu->ez));
//        imu->ex /= tmpf;
//        imu->ey /= tmpf;
//        imu->ez /= tmpf;
//    }
//}

void imu_update(struct imuEstimate *imu) {
    
}

float square(float x) {
    return x*x;
}
