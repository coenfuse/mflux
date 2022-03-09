# MemDB #

### What is this module for? ###

* In-memory key-value database featuring basic push-pop operations. 
* In Mflux it is used as a buffer for load balancing asynchronous operation of MQTT and Influx.

### How do I get set up? ###

* This module doesn't need any special setup operation as it will be automatically generated and built by the workspace it is configured in.
* To build tests specifically to this module, use the cmake option `-DMEMDB_BUILD_TESTS=ON` 
* Or have the tests build alongwith all other modules if you use the option `-DBUILD_TESTS=ON`