# Configurator #

### What is this module for? ###

* The Configurator module deals with the configuration details in the Mflux workspace.
* It has a responsibility of :
    * Parsing the `.json` formatted configuration file 
    * Providing convenient access to configuration values to any module that requires it.

### How do I get set up? ###

* This module doesn't need any special setup operation as it will be automatically generated and built by the workspace it is configured in.

### Dependencies ###

* To parse the `.json` files, it uses the [nlohmann::json](https://github.com/nlohmann/json) library.
* To provide list of subscription topics, it relies on `mqtt::Subscription` data structure from the [mqtt](../mqtt/readme.md) module.