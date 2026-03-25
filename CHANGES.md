Changes
---

This fork:
- adds digitial encoder logic (since there is no quadrature encoding,
  direction is derived from motor forward/backward movement commands);
- modifies the Ping function (both pins are now used, and they are set
  to INPUT/OUTPUT at startup);
- removes the servo library, as it is not needed.
- adds MPU6050 as an IMU;

