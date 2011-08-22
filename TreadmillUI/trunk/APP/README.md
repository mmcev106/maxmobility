Treadmill-UI Qt Application
=======
The application running on the premium (computer & touchscreen based) version of the 
Max Mobility PushOn Accessible Treadmill.

System Requirements
-------------------
To build this code, Qt Creator 2010 (v 2.0.1) must be installed on the computer.

To use the SubVersion respority (SVN) which maintains this code, you must have an SVN
client installed on your computer.  An example (and good) SVN client is TortoiseSVN,
which can be downloaded from the [TortoiseSVN download page][tSVN-dl].

[tSVN-dl]: http://tortoisesvn.net/downloads.html

Getting the APP code
---------------------
You can download & update the application code (duplicated in the SVN) 
by right clicking in a folder and choosing the TortoiseSVN command *SVN Checkout...*
and using:

	https://pl3.projectlocker.com/MaxMobility/project1/svn/TreadmillUI/trunk/APP/

as the URL of the repository.
        
To copy your changes into the SVN or to update your local copy to the latest SVN copy, simply
right click the folder (or specific file) and use the TortoiseSVN commands *SVN Update* or 
*SVN Commit*.

Building the Code
---------------------
To build the code into a runnable application, open the .pro file in the APP directory 
using Qt Creator.  Press the build button in the bottom left of the window.  Make sure that 
Qt Creator is set to *Release* instead of *Debug*.

Running the Code on the Treadmill
---------------------------------
After the code is built, a folder *TreadmillUI-build-desktop* is created in the same
directory as the APP directory.  Inside the *TreadmillUI-build-desktop* directory is 
a *release* directory.  Copy this directory to the Treadmill, and run the *TreadmillUI.exe*
executable located in it.  

Requirements for Running the App on the Treadmill (and having everything work)
------------------------------------------------------------------------------
 *  You must have SSL installed on the computer.  You can install OpenSSL from
	[OpenSSL download][sll-dl].
	After it is installed, copy *libeay32.dll* and *ssleay32.dll* to the *TreadmillUI-build-desktop/release* 
	folder.  This will enable you to login to gmail, etc. through the webkit browser.

 *  To use flash (and other plugins) through the webkit browser in the application,
	first firefox must be installed on the computer.  Then the flash and other plugins
	must be installed through flash.  The webkit browser uses the plugins from firefox.

[ssl-dl]: http://www.slproweb.com/download/Win32OpenSSL-1_0_0d.exe