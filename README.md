# **Substitution Box**
**Contents of File**
- [Introduction](#introduction)  
- [Requirements](#requirements)  
- [Usage](#usage)
- [Resources](#resources)  

---

## **Introduction**
The Substitution Box program is responsible for returning the Substitution Box or S-Box value of a input number between 0 - 256. This is accomplished by first utilizing the Multiplicative Inverse of the input value using the Extended Euclidean Algorithm. The result will then be passed to the affine transformation which will produce the substitution box value. Locating the S-Box value is the 1 of the 4 steps in encrypting data using the Advanced Encryption Standard (AES) cryptographic algorithm. The actual Substitution Box Tables can be located in the [Resources](#resources) section of this file.

---

## **Requirements**
This project was developed using the Linux operating system and includes three source files. A *makefile* was created to generate the executable from the program's source files. To determine if **make** is installed on the host machine enter the following in the terminal: <br/>
<code> make --version </code>

The above command should output something similar to below: <br/>
<code> GNU Make 3.81 </code> <br/>
<code> Copyright (C) 2006  Free Software Foundation, Inc. </code> <br/>
<code> This is free software; see the source for copying conditions. </code> <br/>
<code> There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A </code> <br/>
<code> PARTICULAR PURPOSE. </code> <br/>

If not, install make using the commands below: <br/>
<code> sudo apt-get update </code> <br/>
<code> sudo apt-get install make </code>

---

## **Usage**
After the Substitution Box repository has been cloned or downloaded, navigate into it.  

To display the S-Box values between 0 - 256 enter the following below: <br/>
<code> make </code> <br/>
<code> ./bin/sBox_demo </code>

To locate the multiplicative inverse of a desired value from 0 -> 255 enter the following below: <br/>
<code> make </code> <br/>
<code> ./bin/sBox_demo [INPUT_VALUE] </code>

If a value is entered out of bounds the following error will be displayed. <br />
<code>ERROR: Input value is out of range. </code> <br>
<code>Please enter a value (0 - 255). </code>

---

## **Resources**
*   [Finite Field](https://en.wikipedia.org/wiki/Finite_field_arithmetic#Rijndael's_(AES)_finite_field)  
*   [Galois Field in Cryptography](https://sites.math.washington.edu/~morrow/336_12/papers/juan.pdf)
*   [Substitution Box Tables](https://en.wikipedia.org/wiki/Rijndael_S-box)
