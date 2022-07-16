
/*******************************************************************************
 *                            SubstitutionBox.cpp
 *  @author     Jeff Gardner
*******************************************************************************/

#include <bitset>

#include "SubstitutionBox.h"

const std::bitset<8> FWD_SBOX_CONST { 0x63 };
const std::bitset<8> INV_SBOX_CONST { 0x05 };

unsigned short SubstitutionBox::getForwardSBoxValue( const unsigned short inputValue )
{
    //  Forward Substitution Box result
    unsigned short forwardSBoxValue = 0;

    //  Only process 256 ( 0 - 255 ) values
    if(( inputValue >= 0 ) && ( inputValue < 256 )) {
        
        MultiplicativeInverse multiInverseObj;

        //  Find the multiplicative inverse of the input value and assign the
        //  result to an 8 bit bitset object to manipulate each bit
        multiInverseObj.solveForInverse( inputValue );
        std::bitset<8> inputByte = multiInverseObj.getInverseValue();

        //  The resulting byte after the affine transformation
        std::bitset<8> affineTransResult; 
        
        //  The Forward Affine transformation Matrix and rotations
        affineTransResult[0] = inputByte[0] ^ inputByte[4] ^ inputByte[5] ^ inputByte[6] ^ inputByte[7] ^ FWD_SBOX_CONST[0];
        affineTransResult[1] = inputByte[0] ^ inputByte[1] ^ inputByte[5] ^ inputByte[6] ^ inputByte[7] ^ FWD_SBOX_CONST[1];
        affineTransResult[2] = inputByte[0] ^ inputByte[1] ^ inputByte[2] ^ inputByte[6] ^ inputByte[7] ^ FWD_SBOX_CONST[2];
        affineTransResult[3] = inputByte[0] ^ inputByte[1] ^ inputByte[2] ^ inputByte[3] ^ inputByte[7] ^ FWD_SBOX_CONST[3];
        affineTransResult[4] = inputByte[0] ^ inputByte[1] ^ inputByte[2] ^ inputByte[3] ^ inputByte[4] ^ FWD_SBOX_CONST[4];
        affineTransResult[5] = inputByte[1] ^ inputByte[2] ^ inputByte[3] ^ inputByte[4] ^ inputByte[5] ^ FWD_SBOX_CONST[5];
        affineTransResult[6] = inputByte[2] ^ inputByte[3] ^ inputByte[4] ^ inputByte[5] ^ inputByte[6] ^ FWD_SBOX_CONST[6];
        affineTransResult[7] = inputByte[3] ^ inputByte[4] ^ inputByte[5] ^ inputByte[6] ^ inputByte[7] ^ FWD_SBOX_CONST[7];

        //  Convert the Bitset object into an unsigned short
        forwardSBoxValue = affineTransResult.to_ulong();
    }

    return forwardSBoxValue;
}


unsigned short SubstitutionBox::getInverseSBoxValue( const unsigned short inputValue )
{
    //  Inverse Substitution Box result
    unsigned short inverseSBoxValue = 0;

    //  Only process 256 ( 0 - 255 ) values
    if(( inputValue >= 0 ) && ( inputValue < 256 )) { 

        MultiplicativeInverse multiInverseObj;

        //  Assign the input value that will XOR and rotated as an 8 bit bitset
        //  object to manipulate each bit
        std::bitset<8> inputByte = inputValue ;

        //  Will contain the resulting byte after the affine transformation
        std::bitset<8> affineTransResult;
        
        //  The Inverse Affine transformation Matrix and rotations
        affineTransResult[0] = inputByte[2] ^ inputByte[5] ^ inputByte[7] ^ INV_SBOX_CONST[0];
        affineTransResult[1] = inputByte[0] ^ inputByte[3] ^ inputByte[6] ^ INV_SBOX_CONST[1];
        affineTransResult[2] = inputByte[1] ^ inputByte[4] ^ inputByte[7] ^ INV_SBOX_CONST[2];
        affineTransResult[3] = inputByte[0] ^ inputByte[2] ^ inputByte[5] ^ INV_SBOX_CONST[3];
        affineTransResult[4] = inputByte[1] ^ inputByte[3] ^ inputByte[6] ^ INV_SBOX_CONST[4];
        affineTransResult[5] = inputByte[2] ^ inputByte[4] ^ inputByte[7] ^ INV_SBOX_CONST[5];
        affineTransResult[6] = inputByte[0] ^ inputByte[3] ^ inputByte[5] ^ INV_SBOX_CONST[6];
        affineTransResult[7] = inputByte[1] ^ inputByte[4] ^ inputByte[6] ^ INV_SBOX_CONST[7];
        
        //  Find the multiplicative inverse of the inverse affine transformation 
        //  result which will then be the resulting inverse substitution box value
        multiInverseObj.solveForInverse( affineTransResult.to_ulong() );
        inverseSBoxValue = multiInverseObj.getInverseValue();
    }

    return inverseSBoxValue;
}