# Setup Mflux

- Mflux is a cross-platform app that can be built and debugged on both, Windows 
and Linux Ubuntu systems. 
- To simplify cross-platform setup processes, Mflux uses [CMake](https://cmake.org/).
- Microsoft [Visual Studio](https://visualstudio.microsoft.com/downloads/) & 
MSVC are the recommended IDE & compiler on Windows.
- Microsoft [VSCode](https://code.visualstudio.com/) & GCC are the recommended 
editor & compiler on Linux.

## Setup on Linux

- [Install updates](#l01---install-updates)
- [Install essential libs](#l02---install-essential-libraries)
- [Install CMake](#l03---install-cmake)
- [Install and Setup InfluxDB](#l04---install-and-setup-influxdb)
- [Install and Setup Mosquitto](#l05---install-and-setup-mosquitto)
- [Install and Setup VSCode](#l06---install-and-setup-vscode)
- [Clone repository](#l07---clone-repository)
- [Understand config](#l08---understand-config)
- [Build project](#l09---build-project)
- [Build tests](#l10---build-tests)
- [Use debugger](#l11---use-debugger)
- [Send first payload](#l12---send-first-payload)

## Setup on Windows

- [Install CMake](#w01---install-cmake)
- [Install and Setup Mosquitto](#w02---install-and-setup-mosquitto)
- [Install and Setup InfluxDB](#w03---install-and-setup-influxdb)
- [Install Visual Studio](#w04---install-and-setup-visual-studio)
- [Clone repository](#w05---clone-repository)
- [Understand config](#w06---understand-config)
- [Build project](#w07---build-project)
- [Build test](#w08---build-tests)
- [Use debugger](#w09---use-debugger)
- [Send sample messages](#w10---send-first-payload)

---

#### L01 - Install updates
Update the existing libraries and packages in your linux system by typing the
following command in the terminal,
```
sudo apt-get update
```


#### L02 - Install essential libraries
Install the essential build libraries and packages by typing the following command in the terminal,
```
sudo apt-get install build-essential libssl-dev
```
- [What is libssl-dev?](https://www.openssl.org/)
- [What is build-essential?](https://linuxhint.com/install-build-essential-ubuntu/)


#### L03 - Install CMake

#### L04 - Install and Setup InfluxDB
#### L05 - Install and Setup Mosquitto
#### L06 - Install and Setup VSCode
#### L07 - Clone repository
#### L08 - Understand config
#### L09 - Build project
#### L10 - Build tests
#### L11 - Use debugger
#### L12 - Send first payload

---

#### W01 - Install CMake
#### W02 - Install and Setup Mosquitto
#### W03 - Install and Setup InfluxDB
#### W04 - Install and Setup Visual Studio
#### W05 - Clone repository
#### W06 - Understand config
#### W07 - Build project
#### W08 - Build tests
#### W09 - Use debugger
#### W10 - Send first payload

- [Install CMake](https://vitux.com/how-to-install-cmake-on-ubuntu/)
- [Install Mosquitto](https://mosquitto.org/download/) by typing the following,
```
sudo apt-get install mosquitto
sudo apt-get install libmosquitto-dev
```
- [Install and setup InfluxDB](https://docs.influxdata.com/influxdb/v2.2/install/)
- Install essential libs and updates,
 ```
 sudo apt-get install build-essential libssl-dev
 sudo apt-get update
 ```
- [Install VSCode](https://code.visualstudio.com/) and install the following VSCode extensions 
```
- ms-vscode.cpptools
- jeff-hykin.better-cpp-syntax
- coolchyni.beyond-debug
```
- Clone the repository
- [Understand the codebase]()
- [Setup configuration]()
- [Build the project]()
- [Build tests]()
- [Setup mosquitto broker]()
- [Setup InfluxDB core]()
- [Use the debugger]()

## Setup on Windows

- [Install CMake]()
- [Install Mosquitto]()
- [Install InfluxDB]()
- [Install Visual Studio]()
- Clone the repository
- Build the project.
- Build tests.
- Understand the codebase.
- Understand and use the configuration
- Setup debugger configuration.
- Setup and run mosquitto broker
- Setup and run InfluxDB
- Launch the debugger.
- Step through the code.
- Send sample messages.