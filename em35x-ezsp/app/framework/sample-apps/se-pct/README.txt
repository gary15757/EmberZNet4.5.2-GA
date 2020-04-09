Programmable Communicating Thermostat Sample Application

<app name> = SePct

About the Application:
   This application creates a ZigBee Programmable Communicating Thermostat 
   (PCT) device which is intended to be used in conjunction with the SeMeterMirror.



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

   You may interact with this application using the command line interface 
   either through a Telnet session to port 4901 on your ISA 
   or through the Console window for your ISA in InSight Desktop (ISD).

   Generally I like to do a capture "with options" on my device's PAN ID, 
   (in this case 0xabcd) while at the same time interacting
   with it through the ISD console.

   The following are instructions on how to perform some typical interactions
   betwen the MeterMirror's ESP and the PCT.

   For more information on DRLC CLI-related commands please see the 
   CLI section of the AFV2 Developer's Guide. 

   1. Form the network using the MeterMirror as the coordinator.

   2. Join the PCT to the network.
   
	SeMeterMirror> network form 22 2 0xabcd
      	SeMeterMirror> network pjoin 0xff

      	SePct> network join 22 2 0xabcd

     These commands form a network on channel 22 with power 2 and pan id 0xabcd

	
   3. Set the device class value on the PCT's DRLC client to whatever you want. In this
      case I am setting bit 0 by writing 0x0001, indicating that my PCT controls a furnace.
        
	SePct> write 0x01 0x0701 0x0003 0x00 0x21 {00 01}

   4. Set the UTC time on the MeterMirror's time cluster server. The value 0x13bcca43 is the
      number of seconds since the year 2000, representing UTC time: 6/29/2010 15:15:0. I
      retrieved this time value from the Internet by searching for "seconds since year 2000."

        SeMeterMirror> zcl time 0x13bcca43

   5. Sync time with the MeterMirror, from the PCT.

        SePct> timesync 0 1 1

   6. Print the time out on the PCT to check that it has sync'd properly.

        SePct>print time

   7. Send a default Load Control Event (LCE) from the Meter Mirror (ESP) to the PCT. You'll have
      to look at the PCT's short ID <SID> for sending this message.

        SeMeterMirror> zcl drlc lce 0 0 1 0
        SeMeterMirror> send <sid> 1 1

      This will send a load control event to the PCT. You should see the PCT responding
      to the load control event by sending back event status messages indicating rx, 
      start and stop of the LCE.


   8. Schedule an LCE with Event ID 0x000000BA, starting at time 0 (now) on the ESP's DRLC server. 
      The ESP is expected to be a pass-through for LCEs, however it is useful 
      to be able to schedule LCEs on the ESP for testing. We have provided an LCE table 
      on the DRLC server plugin for this purpose.

        SeMeterMirror> zcl drlc slce 0 23 { ba 00 00 00 ff 0f 00 00 00 00 00 01 00 01 00 00 09 1a 09 1a 0a 00 }
        
   9. Retrieve the scheduled event from the MeterMirror by sending a Get Scheduled Events command from the PCT.
        
 	SePct> zcl drlc gse 1
	SePct> send 0 1 1

      This causes the ESP to send back the scheduled LCE to the PCT. You should see
      the same type of DRLC traffic as in (7) above.

  10. Schedule another event with Event Id 0x000000BB starting at time 0 (now) on the MeterMirror and 
      send it directly from the MeterMirror to the PCT. Again you will need to use the PCT's short 
      ID <SID> for addressing the message.

        SeMeterMirror> zcl drlc slce 0 23 { bb 00 00 00 ff 0f 00 00 00 00 00 01 00 01 00 00 09 1a 09 1a 0a 00 }
	SeMeterMirror> zcl drlc sslce 0
        SeMeterMirror> send <sid>  1 1


  11. Schedule another event with Event Id 0x000000BC starting in 15 minutes 
      (0x13bcca43 + (15 * 60) = 0x13BCCDC7) on the MeterMirror and send it directly from the 
      MeterMirror to the PCT. Again you will need to use the PCT's short ID <SID> for addressing the message.

        SeMeterMirror> zcl drlc slce 0 23 { bc 00 00 00 ff 0f 00 c7 cd bc 13 01 00 01 00 00 09 1a 09 1a 0a 00 }
	SeMeterMirror> zcl drlc sslce 0
        SeMeterMirror> send <sid>  1 1

  12. Opt out of the event with event id 0x000000bc on the PCT.

        SePct> zcl drlc opt out 0x000000bc

      You should see drlc traffic from the PCT to the MeterMirror indicating that the user has chosen
      to opt out of the event.

