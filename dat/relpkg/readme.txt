# README for MFlux v0.1b-21
# 
# Author: Felidae Systems
# Date:   29 June 2022, 14:43 IST


1. INTRODUCTION
--------------------------------------------------------------------------------
MFlux is a service tool that brigdes data flow between multiple devices on MQTT
to a single InfluxDB. This is helpful in running analytics for each device based
on its operation data.


2. INSTALLATION
--------------------------------------------------------------------------------
MFlux is a 'ready to run' application that doesn't require any installation
process. However, it does have few requirements to function properly.

- Active internet connection (To connect with remote broker and database, if any)
- MQTT broker (only if the broker in consideration is local)
- InfluxDB instance (only if the database in consideration is local)

3. USAGE
--------------------------------------------------------------------------------
The MFlux executable requires two command line arguments:
--config <file> : MFlux will use this file for boot-time configuration of app.
       --stdout : Optional flag to allow printing of runtime logs in terminal
             -v : Optional flag to increase the verbosity of output logs

So MFlux can be be executed by running the following command:
mflux-main --config <config_file> --stdout -v

To simplify the process, a start.sh file is also being shipped in this package
with pre-written commands. Just make sure theconfiguration file in /config folder
is edited as per your requirement and your system has access to MQTT broker and
Influx database localy or remotely. Then open the start.sh file.

Expect the generated reports in out/ folder.


4. CONFIGURATION
--------------------------------------------------------------------------------
MFlux is primarily focused on customization and thus relies heavily on its
.jsonc configuration file. The configuration file is present in config/ folder
with proper documentation on each config parameter. This config file is the tool
for you to tailor MFlux according to your requirements.