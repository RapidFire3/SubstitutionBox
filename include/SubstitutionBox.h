/*******************************************************************************
 *                              SubstitutionBox.h
 *  This class is responsible for finding the multiplicative inverse of the 
 *  giving input byte by utilizing the Extended Euclidean Algorithm. This class 
 *  only operates on values 0 - 255 resulting in the result being a byte. 
 * 
 * @author      Jeff Gardner
********************************************************************************/     

#include "MultiplicativeInverse.h"

#ifndef SUBSTITUTION_BOX_H
#define SUBSTITUTION_BOX_H

class SubstitutionBox
{
public:

    //  Default Constructor
    SubstitutionBox(){}

    //  Destructor
    ~SubstitutionBox(){}

    /*******************************************************************************
     *                          getForwardSBoxValue()
     *  This method is responsible for finding the forward substitution box value by
     *  first, finding the multiplicative inverse of the input value. Then, the
     *  result will then be passed off to the affine transformation which then 
     *  produce the S-Box value.
     * 
     *  @param  inputValue -> unsigned short that will be used for processing and
     *          manipulating.
     * 
     *  @return forwardSBoxValue
    *******************************************************************************/
    unsigned short getForwardSBoxValue( const unsigned short inputValue );

    /*******************************************************************************
     *                          getInverseSBoxValue()
     *  This method is responsible for finding the inverse substitution box value of
     *  an input number by conducting the inverse affine transformation and finding
     *  the multiplicative inverse of the input value.
     * 
     *  @param  inputValue -> unsigned short that will be used for processing and
     *          manipulating.
     * 
     *  @return inverseSBoxValue
    *******************************************************************************/
    unsigned short getInverseSBoxValue( const unsigned short inputValue );
};

#endif