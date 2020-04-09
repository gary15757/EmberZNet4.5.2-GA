HA Light Sample Application

<app name> = HALight

About the Application:

   The HALight application is intended to be used in conjunction with HASwitch 
   located in ha-switch and HACombinedInterface located in ha-combined-interface.

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
      Then join HASwitch and/or HACombinedInterface to it.
      HALight> network form 22 2 0xabcd
      HALight> network pjoin 0xff

      HASwitch> network join 22 2 0xabcd

      These commands form a network on channel 22 with power 2 and pan id 0xabcd 

   2. Discover HALight: Once the HASwitch joins, it performs a service 
      discovery to look for HALight by sending a broadcast match descriptor request
      for On/Off cluster (id: 0x0006).  It displays and stores the 
      light's information in the token.
      Ex.
	found light: 0x0000
	  ept: 0x06

   3. To manipulate the light (on/off attribute), use the following command
      Turn the light on:
	HASwitch> zcl on-off on
	HASwitch> send 0x0000 0x01 0x06
		 [send <light node id> <switch/source ep> <light/dest ep>]

      Turn the light off:
	HASwitch> zcl on-off off
	HASwitch> send 0x0000 0x01 0x06
		 [send <light node id> <switch/source ep> <light/dest ep>]

      Toggle the light:
	HASwitch> zcl on-off toggle
	HASwitch> send 0x0000 0x01 0x06
		 [send <light node id> <switch/source ep> <light/dest ep>]

   4. To validate the on/off commands, the user can either:
      4.1) Send a read attribute command to read the on/off attribute.
      HASwitch> zcl global read 0x0006 0x0000
               [zcl global read <cluster id> <attribute id>
      HASwitch> send 0x0000 0x01 0x06
	       [send <light node id> <switch/source ep> <light/dest ep>]

      4.2) Print the attribute table on the light.
      HALight> print attribute

   5. If HACombinedInterface (sample application) is used, it discovers
      and configures reporting on the light.

Note:
    1. The sample application uses HA security, in which a network key is picked
    randomly.  You must enter the key into InSight Desktop in order to
    decrypt the packets correctly.  The command, "keys print", displays security keys.

    2. The sample application requires that an application or serial bootloader is  
    installed on the device in order to run.