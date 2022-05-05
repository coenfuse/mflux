# Build Mflux

- Mflux is a cross-platform app that can be deployed on both, Windows and Linux
Ubuntu systems. 
- To simplify cross-platform build processes, Mflux uses [CMake](https://cmake.org/).
- It is recommended to build MFlux for Linux systems as the Windows app is unstable.

## Build on Linux

- Clone the repository.
- [Install CMake](https://vitux.com/how-to-install-cmake-on-ubuntu/)
- [Install InfluxDB & Influx CLI](https://docs.influxdata.com/influxdb/v2.2/install/) (Optional) 
- [Install Mosquitto](https://mosquitto.org/download/) typing the following,
```
sudo apt-get install mosquitto
sudo apt-get install libmosquitto-dev
```
- Install essential libs and updates by typing the following,
 ```
 sudo apt-get install build-essential libssl-dev
 sudo apt-get update
 ```
- Navigate to your repository root using `cd` command as `cd path/to/repo`
- Once in the root, now go to the `out/build` folder by typing `cd out/build`
- Use CMake to build the project files by typing `cmake -DCMAKE_BUILD_TYPE=Debug ../../`
- Now build the executable by typing `cmake --build .`
- If the build process completes successfully, expect the built binaries in folder
`out/build/source/apps/mflux` as `mflux-main`

**NOTE** : InfluxDB is only required to run Mflux, not to build it. That is why
installation of InfluxDB was marked as OPTIONAL above.



## Build on Windows

- Clone the repository
- [Install CMake](https://cmake.org/download/)
- [Install InfluxDB](https://portal.influxdata.com/downloads/) (Optional)
- [Install Visual Studio](https://visualstudio.microsoft.com/downloads/) for MSVC
- [Install Mosquitto](https://mosquitto.org/download/) and verify system PATH
- Navigate to your repository root using `cd` command as `cd path/to/repo`
- Once in the root, now go to the `out/build` folder by typing `cd out/build`
- Use CMake to build the project files by typing `cmake -DCMAKE_BUILD_TYPE=Debug ../../`
- Now build the executable by typing `cmake --build .`
- If the build process completes successfully, expect the build binaries in folder
`out/build/source/apps/mflux` as `mflux-main.exe`

**NOTE** : InfluxDB is only required to run Mflux, not to build it. That is why
installation of InfluxDB was marked as OPTIONAL above.





[//]: # (cd /tmp)
[//]: # (wget https://github.com/Kitware/CMake/releases/download/v3.23.0-rc4/cmake-3.23.0-rc4.tar.gz)
[//]: # (tar -zxvf cmake-3.23.0-rc4.tar.gz)
[//]: # (cd cmake-3.23.0.rc4)
[//]: # (./bootstrap)
[//]: # (make)
[//]: # (sudo make install)
[//]: # (cmake --version)

[//]: # (sudo apt-get update                       [Update the installed libraries])
[//]: # (sudo apt-get install mosquitto            [Install the mosquitto broker])
[//]: # (sudo apt-get install libmosquitto-dev     [Install the dev API])