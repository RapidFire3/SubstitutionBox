/*******************************************************************************
 *                              Substitution Box
 * This class is responsible for finding the multiplicative inverse of the 
 * giving input byte by utilizing the Extended Euclidean Algorithm. This class 
 * only operates on values 0 - 255 resulting in the result being a byte. 
 * 
 * @author      Jeff Gardner
********************************************************************************/

#include "MultiplicativeInverse.h"

#ifndef SUBSTITUTION_BOX_H
#define SUBSTITUTION_BOX_H

class SubstitutionBox
{
public:
    SubstitutionBox();
    ~SubstitutionBox(){}
    void processSBoxInput( const unsigned short inputValue );
    unsigned short getSBoxValue();

private:
    void doInverseAffineTransformation();
    void doFowardAffineTransformation();
    unsigned short m_inputValue;
    unsigned short m_inverseValue;
    unsigned short m_sBoxValue;
    MultiplicativeInverse m_multiInverse;

};

#endif