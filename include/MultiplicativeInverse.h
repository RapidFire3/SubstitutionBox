/*******************************************************************************
 *                              MultiplicativeInverse
 * This class is responsible for finding the multiplicative inverse of the 
 * giving input byte by utilizing the Extended Euclidean Algorithm. This class 
 * only operates on values 0 - 255 resulting in the result being a byte. 
 * 
 * @author      Jeff Gardner
********************************************************************************/

#ifndef MULTIPLICATIVE_INVERSE_H
#define MULTIPLICATIVE_INVERSE_H

class MultiplicativeInverse
{
public:
    //  Default Constructor
    MultiplicativeInverse();

    //  Default Destructor
    ~MultiplicativeInverse(){}

    //  Entry point to solve for the multiplicative inverse.
    void solveForInverse(unsigned short inputByte);

    //  Returns the multiplicative inverse.
    unsigned short getInverseValue();

private:
    //  Step 1: Conduct long division.
    void doLongDivision();

    //  Step 2: Solve for the current auxilary value.
    void calculateAuxilary();

    //  Utility method to locate the most significant.
    unsigned short getMostSignificantBit(unsigned short inputNumber);

    //  Provide member attributes with defaults.
    void initialize();
    

    //  The current divisor. Should always start with the value that had to  
    //  be inverted.
    unsigned short m_divisor;

    //  The current dividend. Should always start with the irreducible 
    //  polynomial.
    unsigned short m_dividend;

    //  The current auxilary.
    unsigned short m_auxilary;

    //  The auxilary value that is located in row - 1.
    unsigned short m_auxilaryPrev1;

    //  The auxilary value that is located in row - 2.
    unsigned short m_auxilaryPrev2;

    //  The current quotient.
    unsigned short m_quotient;

    //  The final result. 
    unsigned short m_inverse;
};

#endif