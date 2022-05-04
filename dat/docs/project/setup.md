# Setup Mflux

- Mflux is cross-platform and can be developed on both, Windows & Linux. 
- To support cross-platform setup, Mflux uses [CMake](https://cmake.org/).
- [Visual Studio](https://visualstudio.microsoft.com/downloads/) & 
MSVC are the recommended IDE & compiler on Windows.
- [VSCode](https://code.visualstudio.com/) & GCC are the recommended 
editor & compiler on Linux.

<br />
<br />

## Setup on Linux Ubuntu

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

<br />
<br />

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

<br/>
<br/>
<br/>

## 

### L01 - Install updates
Update the existing libraries and packages in your linux system by typing the
following command in the terminal,
```
sudo apt-get update
```
<br/>


### L02 - Install essential libraries
Install the essential build libraries and packages by typing the following command in the terminal,
```
sudo apt-get install build-essential libssl-dev
```
- [What is libssl-dev?](https://www.openssl.org/)
- [What is build-essential?](https://linuxhint.com/install-build-essential-ubuntu/)

<br/>


### L03 - Install CMake
<br/>


### L04 - Install and Setup InfluxDB
<br/>


### L05 - Install and Setup Mosquitto
<br/>


### L06 - Install and Setup VSCode
<br/>


### L07 - Clone repository
<br/>


### L08 - Understand config
<br/>


### L09 - Build project
<br/>


### L10 - Build tests
<br/>


### L11 - Use debugger
<br/>


### L12 - Send first payload
<br/>

<br />
<br />
<br />

## 

### W01 - Install CMake
<br/>


### W02 - Install and Setup Mosquitto
<br/>


### W03 - Install and Setup InfluxDB
<br/>


### W04 - Install and Setup Visual Studio
<br/>


### W05 - Clone repository
<br/>


### W06 - Understand config
<br/>


### W07 - Build project
<br/>


### W08 - Build tests
<br/>


### W09 - Use debugger
<br/>


### W10 - Send first payload
<br/>


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