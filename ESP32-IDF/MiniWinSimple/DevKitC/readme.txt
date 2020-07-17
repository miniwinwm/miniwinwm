Building into the default build folder ('build' subdirectory under this folder) may
give errors as the path and filename can exceed the Windows maximum length limit of 260
characters. To prevent this specify a build folder on the build command line with a 
shorter path, for example C:\build, like this...

	idf.py -B c:\build build

You will also need to specify the same folder when flashing, like this...

	idf.py -B c:\build -p COM7 flash