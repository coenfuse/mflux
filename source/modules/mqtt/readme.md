# MQTT #

### What is this module for? ###

* The MQTT module provides all the necessary tools and services to Mflux for working with MQTT network.
* It provides the following classes to work with :
    * **Client** : Provides a consistent interface for usage of the [mosquitto]() library that communicates with MQTT network. It also provides an additional functionality of `start_service()` and `stop_service()` functions that are tailor made for mflux handling the pushing and publising of incoming and outgoing mqtt messages into and from mflux buffer.
    * **Message** : A mqtt message data structure that contains all the info for single message transmission to MQTT.

### How do I get set up? ###

* This module doesn't need any special setup operation as it will be automatically generated and built by the workspace it is configured in.
* To build tests specifically to this module, use the cmake option `-DMQTT_BUILD_TESTS=ON`
- Or have the tests build alongwith all other modules if you use the option `-DBUILD_TESTS=ON`

### Dependencies ###

* To communicate with InfluxDB on a remote location, this module uses the [mosquitto]() library.