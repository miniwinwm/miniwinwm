Building into the default build folder ('build' subdirectory under this folder) may
give errors as the path and filename can exceed the Windows maximum length limit of 260
characters. To prevent this specify a build folder on the build command line with a 
shorter path, for example C:\build, like this...

	idf.py -B c:\MiniWinCamera_build build

You will also need to specify the same folder when flashing, like this...

	idf.py -B c:\MiniWinCamera_build -p COM4 flash

The connection from the digitial camera D5 to the DevKitC RXD/G3 pin must be
removed before flashing.