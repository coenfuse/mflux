# MFlux #

### What is this repository for? ###

* Mflux v0.1.0 is a gateway application that performs bi-directional transfer of data between any MQTT network and InfluxDB.

### How do I get set up? ###

* Make sure to have [Visual Studio 2019](https://visualstudio.microsoft.com/vs/) and [CMake 3.22](https://cmake.org/download/) installed in your system if you are on Windows.
    - To build the Visual Studio project, go to the folder `out/build/` and in the terminal type `cmake ../../` to generate the project files for mflux. If you want to generate the unit tests as well, type this command instead `cmake ../../ -DBUILD_TESTS=ON`
    - Note that this doesn't build the mflux executable, it just generates a Visual Studio solution as `mflux.sln` that you can compile into `mflux.exe` as required. 
    - However, if you want to build the executable from the command line itself, after generating the project type in the following command `cmake --build .`
    - This will build the target executable along with all the other dependent libraries and link them together, if the unit tests were generated during the generation step, those target executables will be built here as well.
    
* Once the mflux executable is built, you can proceed on to start the application. For that go to where the mflux.exe has been build, open up the terminal and type a command in the following format :-
    -  `mflux.exe <config_file> [--stdout] [-v]`
    - Here `config_file` refers to the complete path of the file that contains necessary configuration for mflux. A pre-filled example config file is already present in folder `source/.config/` as `mflux.config.jsonc`
    - The `--stdout` is an optional flag to log the runtime details on the terminal, by default the logging level is set to INFO but it can be dialled up in its detail upto DEBUG level by using another `-v` flag that stands for verbosity. Note that, the flag `-v` won't work unless `--stdout` is already specified.

* Apart from having Visual Studio 19 and CMake installed. MFlux doesn't require installation of any extra dependencies as it comes will all its dependencies already being present in the source code. Specifically, in the `source/thirdparty` folder.

* In Mflux, we use the [doctest](https://github.com/doctest/doctest) to create our unit tests and [ctest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) to organize them in a proper hierarchy. This hierarchy ensures the tests are structured in a logical order which further enables us to perform complete sequence or a subset of unit tests conveniently as per the requirement.
    - To run the unit tests, first make sure to have the mflux project generated and built with this option `-DBUILD_TESTS=ON`
    - Then go to the directory where the target executables are present and simply type `ctest -C Debug` in the terminal. If the project is setup correctly, all the tests will be discovered, executed and reported.
    - Selective execution of subset of the unit tests is under development and will be implemented once the project reach a certain level of horizontal scale.  

* Deployment instructions, todo.

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact