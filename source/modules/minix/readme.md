# Minix #

### What is this module for? ###

* Minix is a module that provides translations between influx and mqtt messages.
* It compiles as a library and provides interface to its translation functions.

### How do I get set up? ###

* This module doesn't need any special setup operation as it will be automatically generated and built by the workspace it is configured in.
* To build tests specifically to this module, use the cmake option `-DMINIX_BUILD_TESTS=ON`
- Or have the tests build alongwith all other modules if you use the option `-DBUILD_TESTS=ON`

### Dependencies ###

* It uses `mqtt::Message` data structure from [mqtt](..\mqtt\readme.md) module to store translated MQTT messages.
* It uses `influx::Message` data structure from [influx](..\influx\readme.md) module to store translated Influx messages.