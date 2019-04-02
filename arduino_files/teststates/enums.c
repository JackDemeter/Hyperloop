enum state
{
  FAULT,
  SAFE,
  RTL,
  LAUNCH,
  COAST,
  BRAKE,
  CRAWL,
  MOUNT,
  STATES
};

enum faultType
{
  NONE,
  SETUP,
  COMM_NETWORK_LOSS,
  COMM_ARDUINO_LOSS,
  RTL_SKIP,
};

enum sensors
{
  GYRO_X,
  GYRO_Y,
  GYRO_Z,
  TEMP,
  ACCEL_X,
  ACCEL_Y

};
