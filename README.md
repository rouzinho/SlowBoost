# Slow Boost in Cedar

This Cedar plugin induce an iterative boost. At each time step, an increasing boost is produced until a certain threshold.
The widget takes a node as input. So basically, a boost rises until it receives an activation from a node.
It's pratical if you want to slowly rise the resting level of a Neural field and see the higher activation peaks. The input node stops the rise of the resting level, so easy to integrate in any architecture.

Everything you want to know about DFT -> https://dynamicfieldtheory.org/

Cedar is the C++ Framework implementing the concepts of DFT -> https://cedar.ini.rub.de/


## Getting Started

The plugin is a widget reading an input node (trigger) and producing a rising boost.

The code work for the 6.x version of Cedar.


### Prerequisites

You first need to install cedar by following the instructions here : https://cedar.ini.rub.de/tutorials/installing_and_running_cedar/

You can't use a precompiled version of Cedar to compile and run the plugin.

I suggest reading about how to create a plugin in Cedar first, it will greatly help to understand how it works : https://cedar.ini.rub.de/tutorials/writing_custom_code_for_cedar/

**INSTALL YARP**

This last version of the plugin requires yarp (cedar built with yarp support - you don't have to do it if you didn't include YARP when building Cedar)

https://www.yarp.it/install.html

If you don't need it, remove the find_package(YARP REQUIRED) in the cedarProject.cmake


### Installing

First clone the repository :

`https://github.com/rouzinho/SlowBoost.git`

In the project.conf, change the CEDAR_HOME directory to your own :

`set(CEDAR_HOME "your_own_cedar_repository")`

Then create a build repository and prepare the environment for the compilation :

`mkdir build`

`cd build`

`cmake ..`

Finally start the compilation :

`make`

You should see the plugin under the name libSlowBoost.so in the build/ repository

## Run the plugin

Execute cedar and load it into cedar 

*Tools -> Manage plugins*

In the plugin Manager window, click on *add* and choose the plugin libSlowBoost.so (located in build/). This one should appear in the window.

You can close the window. The plugin is loaded inside cedar.

You can now go back to the cedar main interface and click on the Utilities tab.


## Authors

Quentin Houbre - Tampere University.

## License

This project is licensed under the BSD licence


# SlowBoost
