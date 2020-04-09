HA Combined Interface Sample Application

<app name> = HACombinedInterface

About the Application:

   The HACombinedInterface application is intended to be used in conjunction 
   with HALight located in ha-light.

To compile this application:

   1. Load the included application configuration file (<app name><chip>.isc) 
      file into InSight Desktop.

   2. Rename the Device Name in the pop-up window.

   3. Generate the application's header and project/workspace files into the 
      (root) directory by clicking on the "Generate" button in InSight Desktop. 
      The application header files will be put in <root>/app/builder/<device name>

   4. Load the generated project file into the appropriate compiler.

   5. Compile the app and load it onto your device.

To run the application:

   1. Form the network using HALight (or join it as a router if the network already exists).
      Then join HACombinedInterface to it.
      HALight> network form 22 2 0xabcd
      HALight> network pjoin 0xff

      HACombinedInterface> network join 22 2 0xabcd

      These commands form a network on channel 22 with power 2 and pan id 0xabcd 

   2. Discover HALight: Once the HACombinedInterface joins, it performs service 
      discovery to look for HALight by sending a broadcast match descriptor request
      for On/Off cluster (id: 0x0006).  It displays and stores the 
      light's information in RAM.
      Ex.
	found light: 0x0000
	  ept: 0x06

   3. Users can configure a report on the light by using the following command to 
      set up a report from the light on On/off cluster with a minimum interval of
      1 second and a maximum interval of 5 seconds.
      HACombinedInterface> zcl global send-me-a-report 0x0006 0x0000 0x10 0x0001 0x0005 {00}
	[send-me-a-report <cluster id:2> <attribute id:2> <attr type:1> ...
	... <min interval:2> <max interval:2> <reportable change:1-4>

	HACombinedInterface> send 0x0000 0x01 0x06
	[send <light node id> <switch/source ep> <light/dest ep>]

   4. If HASwitch (sample application) is used to manipulate the light, the
      report reflects the status of the light as it is being changed by the
      switch.

   5. Users can cancel the report by setting the maximum interval to 0xFFFF.
      HACombinedInterface> zcl global send-me-a-report 0x0006 0x0000 0x10 0x0001 0xffff {00}
	[send-me-a-report <cluster id:2> <attribute id:2> <attr type:1> ...
	... <min interval:2> <max interval:2> <reportable change:1-4>

	HACombinedInterface> send 0x0000 0x01 0x06
	[send <light node id> <switch/source ep> <light/dest ep>]

Note:
    1. The sample application uses HA security, in which a network key is picked
    randomly.  You must enter the key into InSight Desktop in order to
    decrypt the packets correctly. The command, "keys print", displays security keys.

    2. The sample application requires that an application or serial bootloader is 
    installed on the device in order to run.