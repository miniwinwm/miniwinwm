/*

MIT License

Copyright (c) John Blaiklock 2018 miniwin Embedded Window Manager

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "EasyBMP.h"
using namespace std;

void usage(char* appname)
{
	cout << "Usage: " << appname << " -i <input filename> -o <output filename>" << endl;
}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main( int argc, char* argv[] )
{
 cout << endl
      << "Using EasyBMP Version " << _EasyBMP_Version_ << endl << endl
      << "Copyright (c) by the EasyBMP Project 2005-6" << endl
      << "WWW: http://easybmp.sourceforge.net" << endl << endl;

 char * iFilename = getCmdOption(argv, argv + argc, "-i");
 if (!iFilename)
 {
	 usage(argv[0]);
	 return 1;
 }

 char * oFilename = getCmdOption(argv, argv + argc, "-o");
 if (!oFilename)
 {
	 usage(argv[0]);
	 return 1;
 }

 BMP sourceImage;
 if (!sourceImage.ReadFromFile(iFilename))
 {
	 cout << "Opening " << iFilename << " failed." << endl;
	 return 1;
 }

 std::fstream fs;
 fs.open(oFilename, ios_base::out | ios_base::trunc);
 if (!fs.is_open())
 {
	 cout << "Could not open output file " << oFilename << endl;
 }

 if (sourceImage.TellBitDepth() != 1)
 {
	 cout << "Not a 1 bit depth bitmap" << endl;
	 return(1);
 }

 int width = sourceImage.TellWidth();
 int height = sourceImage.TellHeight();

 fs << "/***************" << endl;
 fs << "*** INCLUDES ***" << endl;
 fs << "***************/" << endl;
 fs << endl;
 fs << "#include <stdint.h>" << endl;
 fs << endl;
 fs << "/****************" << endl;
 fs << "*** CONSTANTS ***" << endl;
 fs << "****************/" << endl;
 fs << endl;
 fs << "/* Bitmap width: " << width << " */" << endl;
 fs << "/* Bitmap height: " << height << " */" << endl;
 fs << endl;
 fs << "const uint8_t array[] = {" << endl;

 for (int h=0; h < height; h++)
 {
	 int mask = 0x80;
	 int byte = 0;

	 fs << "  ";
	 for (int w = 0; w < width; w++)
	 {
		 RGBApixel pixel = sourceImage.GetPixel(w,h);
		 if (pixel.Blue > 0)
		 {
			 byte |= mask;
		 }
		 mask >>= 1;
		 if (mask == 0)
		 {
             if (h == height - 1 && w == width - 1)
             {
			    fs << "0x" << hex << setw(2) << setfill('0') << byte;
             }
             else
             {
			    fs << "0x" << hex << setw(2) << setfill('0') << byte << ", ";
             }
			 mask = 0x80;
			 byte = 0;
		 }
	 }

    if (width % 8 > 0)
    {
        if (h == height-1)
        {
	        fs << "0x" << hex << setw(2) << setfill('0') << byte;
        }
        else
        {
	        fs << "0x" << hex << setw(2) << setfill('0') << byte << ",";
        }
    }

	if (h == height - 1)
	{
		fs << "};";
	}

	fs << endl;
 }

 fs << endl;
 fs << "/************" << endl;
 fs << "*** TYPES ***" << endl;
 fs << "************/" << endl;
 fs << endl;
 fs << "/***********************" << endl;
 fs << "*** GLOBAL VARIABLES ***" << endl;
 fs << "***********************/" << endl;
 fs << endl;
 fs << "/***********************" << endl;
 fs << "*** GLOBAL VARIABLES ***" << endl;
 fs << "***********************/" << endl;
 fs << endl;
 fs << "/*************************" << endl;
 fs << "*** EXTERNAL VARIABLES ***" << endl;
 fs << "*************************/" << endl;
 fs << endl;
 fs << "/**********************" << endl;
 fs << "*** LOCAL VARIABLES ***" << endl;
 fs << "**********************/" << endl;
 fs << endl;
 fs << "/********************************" << endl;
 fs << "*** LOCAL FUNCTION PROTOTYPES ***" << endl;
 fs << "********************************/" << endl;
 fs << endl;
 fs << "/**********************" << endl;
 fs << "*** LOCAL FUNCTIONS ***" << endl;
 fs << "**********************/" << endl;
 fs << endl;
 fs << "/***********************" << endl;
 fs << "*** GLOBAL FUNCTIONS ***" << endl;
 fs << "***********************/" << endl;

 fs.close();

 return 0;
}
