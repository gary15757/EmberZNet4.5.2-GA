  	Sleepy Smart Gas Meter Sample Application

<app name> = SeMeterGasSleepy

About the Application:

   The SeMeterGasSleepy application is intended to be used in conjunction with the Smart Meter Mirror (SeMeterMirror) located in se-meter-mirror.

   Please see the README.txt file located in the se-meter-mirror directory for more information on how SeMeterGas is intended to be used with SeMeterMirror.

   This device is different from SeMeterGas in that the device is a Sleepy End Device so that it spends much of the time hibernating. This device relies on the sleep wake cycle of the Application Framework to govern how long it stays out of hibernation during the processing and sending of messages on the network.

   By default, the sleepy gas meter will stay awake when not connected to a network. This behavior is caused by the #define EMBER_AF_STAY_AWAKE_WHEN_NOT_JOINED which is included in the .isc file and can be modified through the "includes" tab in the application configuration. If this #define is removed, the sleepy gas meter will begin to sleep as soon as it is loaded or reset. 

	When the gas meter is sleeping it is almost impossible to interact with it using the Command Line Interface (CLI). The sample application is written so that a button press of Button 0 will toggle the device in and out of its sleep cycle so that the user can interact with the CLI.

   The SeMeterGasSleepy device does nothing until it is connected to the network. Once connected to the network, the SeMeterGasSleepy device scans for an appropriate mirror to host its data by using the service discovery module within the ApplicationFramework, located at: app/framework/util/service-discovery.h.

   Once the SeMeterGasSleepy device connects to the network, if you are using real ECC the sleepy device initiates key establishment with its parent. The SeMeterGasSleepy device is programmed to stay out of hibernation during smart energy registration (key establishment). Once key establishment is completed, the SeMeterGasSleepy device sends out a service discovery broadcast looking for any device on the network that implements a simple meter cluster. It then sends a mirror request to each simple meter endpoint on each responding device. The first device to respond with a mirror becomes this SeMeterGasSleepy device's mirror.


About the Code:

   All of the custom code for SeMeterGasSleepy is located in the SeMeterGasSleepy_callbacks.c file. Please read the comments in SeMeterGasSleepy_callbacks.c for more information.

To compile this application:


   1. Load the included application configuration file (<app name><chip>.isc) 
      file into InSight Desktop.

   2. Rename the Device Name in the pop-up window.

   3. Generate the application's header and project/workspace files into the 
      (root) directory by clicking on the "Generate" button in InSight Desktop. 
      The application header files will be put in <root>/app/builder/<device name>

   4. Load the generated project file into the appropriate compiler.

   5. Compile the app and load it onto your device.
   

