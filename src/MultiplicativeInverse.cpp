#include<iostream>
#include<bitset>
#include<cmath>
#include<algorithm>

#include "MultiplicativeInverse.h"

//  Irreducible polynomial x8+x4+x3+x+1 with a degree of 8.
const unsigned short IRREDUCIBLE_POLYNOMIAL = 283;

//  Maxium value range.
const unsigned short MAX_VALUE = 256;

MultiplicativeInverse::MultiplicativeInverse(){
    initialize();
}

/*******************************************************************************
 *                              getInverseValue()
 * This method is responsible for returning the multiplicative inverse of the 
 * input/original value to the caller.
 * 
 * @return              the multiplicative inverse of the input value.
*******************************************************************************/
unsigned short MultiplicativeInverse::getInverseValue() 
{   return m_inverse;  }


/*******************************************************************************
 *                              solveForInverse()
 * This method is responsible for initiating the sequence of operations for 
 * computing to locate the multiplicative inverse of the original/input value.
 * 
 * @param inputByte     the number that the class is responsible for finding
 *                      the multiplicative inverse of.
*******************************************************************************/
void MultiplicativeInverse::solveForInverse(unsigned short inputValue)
{
    //  Initialize all class attributes to defaults.
    initialize();

    //  The multiplicative inverse of 0 and 1 is itself.
    if(inputValue == 0 || inputValue == 1)
        m_inverse = inputValue;

    else {
        //  Input value will be assigned as the first divisor.
        m_divisor = inputValue;

        //  Execute step one.
        doLongDivision();
    }
}


/*******************************************************************************
 *                              initialize()
 * This method is responsible for setting all member attributes to defaults.
*******************************************************************************/
void MultiplicativeInverse::initialize()
{
    m_divisor       = 0;
    m_dividend      = IRREDUCIBLE_POLYNOMIAL;
    m_quotient      = 0;
    m_inverse       = 0;
    m_auxilary      = 0;
    m_auxilaryPrev1 = 1;
    m_auxilaryPrev2 = 0;
}


/*******************************************************************************
 *                              doLongDivision()
 * This method is step one of the multiplicative inverse operation and it is 
 * responsible for conducting long division on two polynomials or binary numbers 
 * in order to find the inverse of the original value. 
*******************************************************************************/
void MultiplicativeInverse::doLongDivision()
{
    //  Determine how many shifts the divisor must conduct in order to have the
    //  same index of the most significant bit of the dividend. Division of 
    //  binary numbers.
    unsigned short shiftLength = 
        getMostSignificantBit(m_dividend) - getMostSignificantBit(m_divisor);

    //  Conduct a shift on the divisor. In regular division, this is where 
    //  quotient is multiplied by the divisor and the result is placed under the 
    //  dividend.
    unsigned short shiftResult = m_divisor << shiftLength;

    //  XOR the dividend and the result from the previous step. In regular 
    //  division, this is where the result from the previous step is subtracted 
    //  from the dividend.
    m_dividend ^= shiftResult;

    //  Builds the quotient in binary based off of what bit index is set or 
    //  equals 1.
    m_quotient += pow(2, shiftLength);

    //  If the MSB of the dividend is greater than or equal to the MSB of the 
    //  divisor repeat long division false, leaving a remainder.
    if (getMostSignificantBit(m_dividend) >= getMostSignificantBit(m_divisor))
        doLongDivision();
    
    else
    {
        //  The remainder which is the current dividend will be the new divisor
        //  and the current divisor will be the new dividend until. This cycle 
        //  will until the remainder is 1.
        std::swap(m_dividend, m_divisor);

        //  Continue to step two.
        calculateAuxilary();
    }
}


/*******************************************************************************
 *                              calculateAuxilary()
 * This method is step two of the multiplicative inverse operation and it is 
 * responsible for solving for the auxilary values. This method generates the 
 * inverse of the original number when the final remainder is 1.
*******************************************************************************/
void MultiplicativeInverse::calculateAuxilary()
{
    unsigned short temp1 = 0;

    //  Assist with determining how many shifts must conducted when utilizing 
    //  the distributive property.
    unsigned short msbIdx = getMostSignificantBit(m_quotient);

    std::bitset<8> quotientByte = m_quotient;

    //  Multiply the two binary polynomials. Used the distributive property 
    //  and XOR for binary.
    for(int bitIdx = msbIdx; bitIdx >= 0; bitIdx--) 
    {
        if(quotientByte.test(bitIdx)) 
        {
            temp1 = m_auxilaryPrev1 << bitIdx;
            m_auxilary ^= temp1;
        }
    }
    
    //  XOR the results from the previous step to the second previous auxilary.
    m_auxilary ^= m_auxilaryPrev2 ;

    //  PREPARE FOR NEXT ROUND. 
    //  The previous first auxilary will become the second previous auxilary and 
    //  the current auxilary will become the first previous auxilary.
    m_auxilaryPrev2 = m_auxilaryPrev1;
    m_auxilaryPrev1 = m_auxilary;

    if(m_divisor > 1 || m_dividend == 1)
    {
        //  Zeroize the quotient and the current auxilary. All other components
        //  need to persist until the multiplicative inverse is computed.
        m_quotient = 0;
        m_auxilary = 0;

        //  Repeat step one.
        doLongDivision();
    }

    else
        m_inverse = m_auxilary;
}


/*******************************************************************************
 *                          getMostSignificantBit()
 * This method is a utiliy that is responsible for returning the index or 
 * position of the most significant bit of a given number.
 * 
 * @param inputNumber   the number that the method must find the msb of.
 * @return              the most significant bit index of the input number.
*******************************************************************************/
unsigned short MultiplicativeInverse::getMostSignificantBit(unsigned short inputNumber)
{
    //  Number of bits of the input number that must tested for the potential
    //  most significant bit.
    unsigned short bitSize = 16;

    //  Current bit index starting from most significant bit to least 
    //  significant bit (left -> right) of the input number.
    unsigned short currentIndex = 0;

    //  Index of the most significant bit that will be returned to the caller.
    unsigned short msbIndex = 0; 

    while (currentIndex < bitSize)
    {
        //  The first index where the bit is set is the most significant bit.
        if (inputNumber & 0x8000)
            break;

        //  Conduct a left shift by 1 to determine if the next index is a 
        //  potential MSB.
        inputNumber <<= 1;

        currentIndex++;
    }

    //  The index or the position of the most significant bit of the input 
    //  number. From least to most significant bit (right -> left).
    msbIndex = bitSize - (currentIndex + 1);

    return msbIndex;
}