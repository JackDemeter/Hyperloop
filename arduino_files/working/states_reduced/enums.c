#include <stdbool.h>

enum state
{
  FAULT,
  STA,
  RTL,
  LAUNCH,
  COAST,
  BRAKE,
  CRAWL,
  STATES
};

enum faultType
{
  NONE,
  SETUP,
  COMM_NETWORK_LOSS,
  COMM_ARDUINO_LOSS,
  RTL_SKIP,
  FAULTS
};

enum sensors
{
  GYRO_X1,
  GYRO_Y1,
  GYRO_Z1,
  GYRO_X2,
  GYRO_Y2,
  GYRO_Z2,
  TEMP1,
  TEMP2,
  ACCEL_X1,
  ACCEL_Y1,
  ACCEL_TOTAL1,
  ACCEL_X2,
  ACCEL_Y2,
  ACCEL_TOTAL2,
  SENSORS
};
