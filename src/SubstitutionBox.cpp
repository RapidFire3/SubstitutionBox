
#include<bitset>
#include<cmath>         //  To implement Exponents.
#include<algorithm>     //  To implement the swap function.
#include<climits>

#include "SubstitutionBox.h"

using namespace std;

SubstitutionBox::SubstitutionBox() : 
    m_inverseValue{ 0 },
    m_sBoxValue{ 0 },
    m_multiInverse{ MultiplicativeInverse() }
{}

unsigned short SubstitutionBox::getSBoxValue()
{
    return m_sBoxValue;
}

void SubstitutionBox::processSBoxInput( const unsigned short inputValue )
{
    if(( inputValue >= 0 ) && ( inputValue < 256 )) { 
        m_multiInverse.solveForInverse( inputValue );
        m_inverseValue = m_multiInverse.getInverseValue();
        doFowardAffineTransformation();
    }

    else {
        m_sBoxValue = USHRT_MAX;
    }
}

void SubstitutionBox::doFowardAffineTransformation()
{
    //  Inbound multiplicative inverse object
    bitset<8> inverse = m_inverseValue;

    bitset<8> irreduciablePolynomial = 0x63;

    //  Result Byte
    bitset<8> sBoxByte; 
    
    sBoxByte[0] = inverse[0] ^ inverse[4] ^ inverse[5] ^ inverse[6] ^ inverse[7] ^ irreduciablePolynomial[0];
    sBoxByte[1] = inverse[0] ^ inverse[1] ^ inverse[5] ^ inverse[6] ^ inverse[7] ^ irreduciablePolynomial[1];
    sBoxByte[2] = inverse[0] ^ inverse[1] ^ inverse[2] ^ inverse[6] ^ inverse[7] ^ irreduciablePolynomial[2];
    sBoxByte[3] = inverse[0] ^ inverse[1] ^ inverse[2] ^ inverse[3] ^ inverse[7] ^ irreduciablePolynomial[3];
    sBoxByte[4] = inverse[0] ^ inverse[1] ^ inverse[2] ^ inverse[3] ^ inverse[4] ^ irreduciablePolynomial[4];
    sBoxByte[5] = inverse[1] ^ inverse[2] ^ inverse[3] ^ inverse[4] ^ inverse[5] ^ irreduciablePolynomial[5];
    sBoxByte[6] = inverse[2] ^ inverse[3] ^ inverse[4] ^ inverse[5] ^ inverse[6] ^ irreduciablePolynomial[6];
    sBoxByte[7] = inverse[3] ^ inverse[4] ^ inverse[5] ^ inverse[6] ^ inverse[7] ^ irreduciablePolynomial[7];

    //  Convert the Bitset object into an unsigned short
    m_sBoxValue = sBoxByte.to_ulong();
}



//	The Affine Transformation.
void SubstitutionBox::doInverseAffineTransformation()
{
    bitset<8> inverse = m_inverseValue;
    bitset<8> irreduciablePolynomial = 0x05;
    bitset<8> sBoxByte;
    
    sBoxByte[0] = inverse[2] ^ inverse[5] ^ inverse[7] ^ irreduciablePolynomial[0];
    sBoxByte[1] = inverse[0] ^ inverse[3] ^ inverse[6] ^ irreduciablePolynomial[1];
    sBoxByte[2] = inverse[1] ^ inverse[4] ^ inverse[7] ^ irreduciablePolynomial[2];
    sBoxByte[3] = inverse[0] ^ inverse[2] ^ inverse[5] ^ irreduciablePolynomial[3];
    sBoxByte[4] = inverse[1] ^ inverse[3] ^ inverse[6] ^ irreduciablePolynomial[4];
    sBoxByte[5] = inverse[2] ^ inverse[4] ^ inverse[7] ^ irreduciablePolynomial[5];
    sBoxByte[6] = inverse[0] ^ inverse[3] ^ inverse[5] ^ irreduciablePolynomial[6];
    sBoxByte[7] = inverse[1] ^ inverse[4] ^ inverse[6] ^ irreduciablePolynomial[7];
    
    //  Convert the Bitset object into an unsigned short
    m_sBoxValue = sBoxByte.to_ulong();
}


