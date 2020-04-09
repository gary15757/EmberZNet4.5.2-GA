Smart Mirror Meter Sample Application

<app name> = SeMeterMirror

About the Application:

    The SeMeterMirror application is intended to be used with the Smart Gas Meter, SeMeterGas located in se-meter-gas. SeMeterMirror is a device with multiple endpoints:

    (1) ESP
    (3) Mirror Meter

    This application is intended to show how an ESP can be configured to include a mirrored endpoint for other (sleepy) meters in its network. In this type of network, the ESP serves as the coordinator for a network that includes one or more other meters, which spend most of their time sleeping. In order to provide constant access to the data in those meters, the ESP mirrors their attributes on one of its mirror endpoints. To a third device, like an in-home display, it looks like the sleepy meter, in this case SeMeterGas exists on one of the endpoints implemented by the ESP.

    To set up this test network and explore the mirroring functionality:

    1. build and compile both SeMeterGas and SeMeterMirror and load them onto two devices.

    2. Form a network with SeMeterMirror as coordinator. You can do this by opening the console windows for your devices in ISD. In the console use the following commands:

       SeMeterMirror> network form 22 2 0xabcd
       SeMeterMirror> network pjoin 0xff

       SeMeterGas> network join 22 2 0xabcd

       These commands form a network on channel 22 with power 2 and pan id 0xabcd

    3. Send a mirror request to SeMeterMirror from SeMeterGas using CLI command:
       
       SeMeterGas> zcl sm rm
       SeMeterGas> send 0 1 3

    4. SeMeterMirror should create a mirror on endpoint 03 and will enter the IEEE address for SeMeterGas into the smart meter attribute table on endpoint 3.

    5. At this point SeMeterGas (and only SeMeterGas) can start updating the simple meter cluster on the mirror endpoint with its attributes using the CLI's global report such as:

       SeMeterGas> zcl global report 1 0x0702 0x0306 1
       SeMeterGas> send 0 1 3

       This report causes the mirror to set its metering device type to that of the meter.

    6. The gas meter may remove its mirror at any time by sending a remove mirror command to the mirrored endpoint on the ESP.

       SeMeterGas> zcl sm dm
       SeMeterGas> send 0 1 3

       This command should cause the ESP to remove the mirror thereby freeing it for use by another device.


About the Code:

    All of the custom code required to implement the mirroring functionality is located in SeMeterMirror_callbacks.c. The code in this file is commented to explain what each of the callbacks does for the application.


To compile this application:

   1. Load the included application configuration file (<app name><chip>.isc) 
      file into InSight Desktop.

   2. Rename the Device Name in the pop-up window.

   3. Generate the application's header and project/workspace files into the 
      (root) directory by clicking on the "Generate" button in InSight Desktop. 
      The application header files will be put in <root>/app/builder/<device name>

   4. Load the generated project file into the appropriate compiler.

   5. Compile the app and load it onto your device.

