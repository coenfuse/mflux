# Mflux #

### What is this app for? ###

* This is the main application in mflux workspace that uses other modules and third-party libraries to operate. 
* This compiles as a library and an executable simultaneouly. 
* The generated library then serves as a dependency for `mflux-main.exe` and `mflux-utest.exe`

### Why it is setup the way it is? ###

* This application compiles in two parts of .lib and .exe because it needs to support unit testing.
* The unit testing application requires the source files (not only the header interface) to compile. 
* Compiled just `mflux.exe` and linking `mflux-utest.exe` to it results in series of linker errors.
* To resolve this issue, we compiled mflux as a library first. Then linked it as a dependency to mflux-main.exe and mflux-utest.exe
* Since mflux is a library, it provides both the interface and a functionality to the targets that are dependent on it.
* Additonally, it also seperated two previously intertwined problem into different scopes :
    * The `mflux.lib` now handles all the application related issues like initializing modules, starting services, etc.
    * The `mflux-main.exe` handles all the external issues for application like OS' signal handling, etc.

### How do I get set up? ###

* This application project doesn't need any special setup operation as it will be automatically generated and built by its workspace solution's configuration.