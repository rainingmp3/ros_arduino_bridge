Changes
---

This fork:
- adds infra-red encoder logic (since there is no quadrature encoding,
  direction is derived from motor commands);
- modifies the Ping function (both pins are now used, and they are set
  to INPUT/OUTPUT at startup);
- changes pin numbers and baud rate (my board cannot handle speeds above
  31250 for some reason);
- removes the servo library, as it is not needed.

