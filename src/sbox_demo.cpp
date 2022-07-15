#include<iostream>
#include<iomanip>
#include<sstream>

#include "SubstitutionBox.h"

using namespace std;

int main (int argc, char* argv[])
{
    //  Create the Multiplicative Inverse object.
    SubstitutionBox sBox;

    //  Value that will be process. 
    unsigned short number = 0;

    //  Manipulator to set all output to hexidecimal.
    cout << std::hex;
    
    //  If no additional arguments are provided, display the inverse of
    //  all 256 values.
    if( argc == 1 )
    {
        //  Pad the left corner (0,0).
        cout << "-" << "\t";

        //  Axis maximums. Should be 15 but added 1 to account for
        //  row and column headers.
        int rowMax = 16;
        int colmax = 16;

        //  columnIdx header
        for( int columnIdx = 0; columnIdx < colmax; columnIdx++ )
            cout << columnIdx << "\t";
        cout << endl;

        for( int rowAxis = 0; rowAxis < rowMax; rowAxis++ )
        {
            for( int columnAxis = 0; columnAxis < colmax; columnAxis++ )
            {   
                //  rowIdx header
                if( columnAxis == 0 )
                    std::cout << rowAxis << "\t";

                //  Solve, get and print output.
                sBox.processSBoxInput( number );
                cout << setfill('0') << setw(2) << sBox.getSBoxValue() << "\t";
                number++;
            }
            cout << endl;
        }
    }

    else 
    {
        //  Before the argument that was accepted from the command line can be
        //  used as input into the multiInverse object it must first be 
        //  converted from a char* array -> unsigned short by implementing a
        //  stringstream object.

        //  Create the stringstream buffer object.
        stringstream numStream;

        //  Place the argument onto the buffer for conversion.
        numStream.str( argv[1] );

        //  Extract the data from off the buffer and store it as an unsigned short.
        numStream >> number;

        //  Clear the buffer from any unused data.
        numStream.str();

        //  Solve, get and print output.
        sBox.processSBoxInput( number );

        if( number >= 0 && number < 256 ) {
            cout << "0x" << number << " -> 0x";
            cout << setfill('0') << setw(2) << sBox.getSBoxValue() << endl;
        }

    }
    return 0;
}