# Influx #

### What is this module for? ###

* The Influx module provides all the necessary tools and services to Mflux for working with InfluxDB.
* It provides the following classes to work with :
    * **Client** : Provides a consistent interface for usage of the [cinflux]() library that communicates with InfluxDB. Also provides an additional functionality of `start_service()` and `stop_service()` functions that are tailor made for mflux handling the pushing and publising of incoming and outgoing influx messages into and from mflux buffer.
    * **Message** : A influx message data structure that contains all the info for single message transmission to InfluxDB.

### How do I get set up? ###

* This module doesn't need any special setup operation as it will be automatically generated and built by the workspace it is configured in.
* To build tests specifically to this module, use the cmake option `-DINFLUX_BUILD_TESTS=ON` 
* Or have the tests build alongwith all other modules if you use the option `-DBUILD_TESTS=ON`

### Dependencies ###

* To communicate with InfluxDB on a remote location, this module uses the [httplib]() library.