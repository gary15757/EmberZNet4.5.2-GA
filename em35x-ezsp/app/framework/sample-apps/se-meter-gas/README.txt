Smart Gas Meter Sample Application

<app name> = SeMeterGas

About the Application:

   The SeMeterGas application is intended to be used in conjunction with the Smart Meter Mirror (SeMeterMirror) located in se-meter-mirror.

   Please see the README.txt file located in the se-meter-mirror directory for more information on how SeMeterGas is intended to be used with SeMeterMirror.

About the Code:

   All of the custom code for SeMeterGas is located in the SeMeterGas_callbacks.c file. Please read the comments in SeMeterGas_callbacks.c for more information.

To compile this application:

1. Load the included application configuration file (<app name><chip>.isc) 
   file into InSight Desktop.

2. Rename the Device Name in the pop-up window.

3. Generate the application's header and project/workspace files into the 
   (root) directory by clicking on the "Generate" button in InSight Desktop. 
   The application header files will be put in <root>/app/builder/<device name>

4. Load the generated project file into the appropriate compiler.

5. Compile the app and load it onto your device.


