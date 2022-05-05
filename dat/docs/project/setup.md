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

01. [Install updates](#l01---install-updates)
02. [Install essential libs](#l02---install-essential-libraries)
03. [Install CMake](#l03---install-cmake)
04. [Install and Setup InfluxDB](#l04---install-and-setup-influxdb)
05. [Install and Setup Mosquitto](#l05---install-and-setup-mosquitto)
06. [Install and Setup VSCode](#l06---install-and-setup-vscode)
07. [Clone repository](#l07---clone-repository)
08. [Understand config](#l08---understand-config)
09. [Build project](#l09---build-project)
10. [Build tests](#l10---build-tests)
11. [Use debugger](#l11---use-debugger)
12. [Send first payload](#l12---send-first-payload)

<br />
<br />

## Setup on Windows

01. [Install CMake](#w01---install-cmake)
02. [Install and Setup Mosquitto](#w02---install-and-setup-mosquitto)
03. [Install and Setup InfluxDB](#w03---install-and-setup-influxdb)
04. [Install Visual Studio](#w04---install-and-setup-visual-studio)
05. [Clone repository](#w05---clone-repository)
06. [Understand config](#w06---understand-config)
07. [Build project](#w07---build-project)
08. [Build test](#w08---build-tests)
09. [Use debugger](#w09---use-debugger)
10. [Send sample messages](#w10---send-first-payload)

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
In this CMake installation method, we are going to build and install the latest version of CMake from its source code. Firstly, open the terminal and go to the `tmp` directory,
```
cd /tmp
```

Dowload the latest source code from Kitware's github by typing the following in terminal,
```
wget https://github.com/Kitware/CMake/releases/download/v3.23.0-rc4/cmake-3.23.0-rc4.tar.gz
```
_At the time of writing this documentation, the latest version of CMake was v3.23.0-rc4. It is very likely that at the time of your setup CMake has progressed in its development and released new versions. To download them, first check the latest release version number [here](https://github.com/Kitware/CMake/releases) and then update the version info in the above `wget` command accordingly._

Extract the downloaded archive into a folder by using the following command,
```
tar -zxvf cmake-3.23.0-rc4.tar.gz
```

Go into the extracted folder,
```
cd cmake-3.23.0-rc4 
```

Now compile and install CMake by typing running the bootstrap script as follows,
```
./bootstrap
```

This will be long process, do not interrupt it. If succeeded, it will print
```
CMake has bootstrapped. Now run make.
```

Start the make file by typing just `make` in the terminal.
And then finish the installation by typing `sudo make install`

Verify the installd CMake by checking its install version from terminal. Type,
```
cmake --version
```
If successful, this should print `cmake version 3.23.0-rc4` or the number of latest version you've installed.

<br/>


### L04 - Install and Setup InfluxDB
<br/>


### L05 - Install and Setup Mosquitto
<br/>


### L06 - Install and Setup VSCode
<br/>


### L07 - Clone repository
Clone the repository to your system using the git command in terminal,
```
git clone https://github.com/coenfuse/mflux
```
Alternatively, you can download the [released source archive](https://github.com/coenfuse/mflux/releases) and extract it in a folder of choice.
Now open the repository in VSCode by using the following commands,
```
cd <path/to/repo>
code .
```

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