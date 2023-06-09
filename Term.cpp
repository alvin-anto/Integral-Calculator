/**
 * ALVIN ANTO
 * NET ID: AXA220139
 * UTD ID: 2021686750
 * CS 2337.002
 * PROJECT 3
 */


//importing required libraries
#include <string>
#include "Term.h"


//method that adds the argument fraction to the fraction coeffiecient of the term
void Term::addToCoefficient(Fraction f)
{
    //gets the numerator of the current coefficients and adds the argument
    int newNum = getNumCoefficient() + f.numerator;
    //creates a Fraction with newNum
    Fraction tempFrac(newNum);
    //updating the coefficient of the term to the new coefficient
    setCoefficient(tempFrac);
}

//method to simplify the fraction coefficient
void Term::simplify()
{
    //initializing an int variable gcd to 1
    int gcd = 1;
    //declaring an int varibale limit
    int limit;
    //if the absolute value of the numerator is less than or equal to the denominator of the coefficient
    if (abs(getNumCoefficient()) <= abs(getDenoCoefficient()))
    {
        //set the limit to the absolute value of the numerator of the coefficient
        limit = abs(getNumCoefficient());
    }
    //if the absolute value of the numerator is greater than the denominator of the coefficient
    else
    {
        //set the limit to the absolute value of the denominator of the coefficient
        limit = abs(getDenoCoefficient());
    }
    //finding the greatest common divisor of the numerator and the denominator using the for loop
    //loop starts at 2 and runs until the limit is reached and exits with the gcd in the gcd variable
    for (int i = 2; i <= limit; i++)
    {
        //if the numerator and denominator can be divided by i, then set gcd equal to i
        if (getNumCoefficient() % i == 0 && getDenoCoefficient() % i == 0)
        {
            //set gcd equal to i
            gcd = i;
        }
    }
    
    //dividing both the numerator and denominator by the greatest common divisor and simplifying it and storing them to varibles
    int newNum = getNumCoefficient()/gcd;
    int newDeno = getDenoCoefficient()/gcd;
    
    //if the simplified numerator and denominator are both negative, the negatives cancel put and they both become positive numbers
    if (newNum < 0 && newDeno < 0)
    {
        newNum = 0 - newNum;
        newDeno = 0 - newDeno;
    }
    //if the numerator is positive and the denominator is negative, the negative sign shifts to the numerator
    else if (newDeno < 0)
    {
        newNum = 0 - newNum;
        newDeno = 0 - newDeno;
    }
    //creating a new Fraction object with the simplified new numerator and denominator and storing them to coefficient
    Fraction tempFrac(newNum, newDeno);
    coefficient = tempFrac;
}

//method that converts the term to its integral and returns the integral as astring
std::string Term::getIntegral()
{
    //declaring a string variable to store the integral
    std::string integral = "";
    
    //if the term is not a trig term
    if (trigTerm == "")
    {
        //adding the exponent by 1 and dividing it by the coefficient, and setting this as the new coeffecient and then simplifying the coefficient
        int exp = getExponent() + 1;
        Fraction f(getNumCoefficient(), exp);
        setCoefficient(f);
        setExponent(exp);
        simplify();
        
        //if the numerator of the coefficient is 0, 0 is appended to 0, regardless of the denominator because 0 divided by any number is 0.
        //Also, 'x' is ignored since the coefficient is 0
        if ((getNumCoefficient() == 0))
        {
            integral += "0";
        }
        //if the numerator of the coefficient is not 0
        else
        {
            //if the numerator and denominator of the coefficient is 1, then nothing is added to the integral because 1x = x
            if (getNumCoefficient() == 1 && getDenoCoefficient() == 1)
            {
                integral += "";
            }
            //if the denominator is 1 and numerator is not 1
            else if (getDenoCoefficient() == 1)
            {
                //if the absolute value of the numerator is 1, a minus sign is added to the integral without the 1, because -1x = -x
                if (abs(getNumCoefficient()) == 1)
                {
                    integral += "-";
                }
                //if numerator is not , -1, 0 or 1, the numerator is added to the integral
                else
                {
                    integral += std::to_string(getNumCoefficient());
                }
            }
            //if the denominator is not 1, then the coefficient fraction is added to the integral
            else
            {
                integral += "(";
                integral += std::to_string(getNumCoefficient());
                integral += "/";
                integral += std::to_string(getDenoCoefficient());
                integral += ")";
            }
            //if the exponent is 1, x is appended to the integral without the exponent because x^1 = x
            if (exp == 1)
            {
                integral += "x";
            }
            //if the exponent is not 1, x is appended to the integral along with the exponent
            else
            {
                integral += "x^";
                integral += std::to_string(exp);
            }
        }
    }
    //if it is a trig term
    else
    {
        //if the trig term is a sin term
        if (trigTerm.find("sin") != std::string::npos)
        {
            //getting the term between sin and x in the trig term (coefficient of x inside the sin function) and storing it in the variable k
            int k;
            if (trigTerm.length() > 3)
            {
                k = stoi(trigTerm.substr(trigTerm.find("sin")+3, trigTerm.length()-(trigTerm.find("sin")+3)));
            }
            else
            {
                k = 1;
            }
            //creating a new fraction with the coefficient of x inside the function as the denominator and setting that as the coefficient of the term and then simplifying it
            Fraction f(getNumCoefficient(), k);
            setCoefficient(f);
            setExponent(1);
            simplify();
            //if the numerator and denominator of the coefficient is 1, then "-" is added to the integral because integral of sinx = -cosx
            if (getNumCoefficient() == 1 && getDenoCoefficient() == 1)
            {
                integral += "-";
            }
            //if the denominator is 1 and numerator is not 1
            else if (getDenoCoefficient() == 1)
            {
                //if the absolute value of the numerator is 1, nothing is added to the integral
                if (abs(getNumCoefficient()) == 1)
                {
                    integral += "";
                }
                //if numerator is not , -1, 0 or 1, the numerator is added to the integral along with a - sign
                else
                {
                    integral += "-";
                    integral += std::to_string(abs(getNumCoefficient()));
                }
            }
            //if the denominator is not 1, then the coefficient fraction is added to the integral
            else
            {
                //if the numerator is a positive number, a negative sign is added and then the absolute value of the numerator and the value of the denominator are appended to the integral
                if (getNumCoefficient() >= 0)
                {
                    integral += "-(";
                }
                //else, the absolute value of the numerator and the value of the denominator are appended to the integral
                else
                {
                    integral += "(";
                }
                integral += std::to_string(abs(getNumCoefficient()));
                integral += "/";
                integral += std::to_string(getDenoCoefficient());
                integral += ")";
            }
            //Since the integral of sin is -cos and we have added - sign earlier, appending "cos " to the integral
            integral += "cos ";
            //if the coefficient of x inside the function is 1, then nothing is added to the intergral, because 1x = x
            if (k == 1)
            {
                integral += "";
            }
            //if the coefficient of x inside the function is -1, then "-" is added to the intergral without 1, because -1x = -x
            else if (k == -1)
            {
                integral += "-";
            }
            //else, the actual value of the coefficient of x is appended to the integral
            else
            {
                integral += std::to_string(k);
            }
            //finally, x is added to the integral
            integral += "x";
        }
        //if the trig term is a cosine term
        else
        {
            //getting the term between cos and x in the trig term (coefficient of x inside the cos function) and storing it in the variable k
            int k;
            if (trigTerm.length() > 3)
            {
                k = stoi(trigTerm.substr(trigTerm.find("cos")+3, trigTerm.length()-(trigTerm.find("cos")+3)));
            }
            else
            {
                k = 1;
            }
            //creating a new fraction with the coefficient of x inside the function as the denominator and setting that as the coefficient of the term and then simplifying it
            Fraction f(getNumCoefficient(), k);
            setCoefficient(f);
            setExponent(1);
            simplify();
            //if the numerator and denominator of the coefficient is 1, then nothing is added to the integral
            if (getNumCoefficient() == 1 && getDenoCoefficient() == 1)
            {
                integral += "";
            }
            //if the denominator is 1 and numerator is not 1
            else if (getDenoCoefficient() == 1)
            {
                //if the absolute value of the numerator is 1, then "-" is added to the integral
                if (abs(getNumCoefficient()) == 1)
                {
                    integral += "-";
                }
                //if numerator is not , -1, 0 or 1, the numerator is added to the integral
                else
                {
                    integral += std::to_string(getNumCoefficient());
                }
            }
            //if the denominator is not 1, then the coefficient fraction is added to the integral
            else
            {
                //if the numerator is a positive number, the absolute value of the numerator and the value of the denominator are appended to the integral
                if (getNumCoefficient() >= 0)
                {
                    integral += "(";
                }
                //else, a negative sign is added and then the absolute value of the numerator and the value of the denominator are appended to the integral
                else
                {
                    integral += "-(";
                }
                integral += std::to_string(abs(getNumCoefficient()));
                integral += "/";
                integral += std::to_string(getDenoCoefficient());
                integral += ")";
            }
            //since the integral of cosine is sin, "sin" is appended to the integral
            integral += "sin ";
            //if the coefficient of x inside the function is 1, then nothing is added to the intergral, because 1x = x
            if (k == 1)
            {
                integral += "";
            }
            //if the coefficient of x inside the function is -1, then "-" is added to the intergral without 1, because -1x = -x
            else if (k == -1)
            {
                integral += "-";
            }
            //else, the actual value of the coefficient of x is appended to the integral
            else
            {
                integral += std::to_string(k);
            }
            //finally, x is appended to the integral string
            integral += "x";
        }
    }
    //return the integral string containing the integral/anti-derivative of the term
    return integral;
}

//method that finds the defininte integral of the term and returns it as a double
double Term::getDefiniteIntegral(int limit1, int limit2)
{
    //divinf the numerator and denominator of the coefficient and saving the double value in the variable coeff
    double coeff = (getNumCoefficient()*1.0)/(getDenoCoefficient()*1.0);
    //solving the term with upper limit
    double xEval1 = pow((limit1*1.0), getExponent());
    //solving the term with lower limit
    double xEval2 = pow((limit2*1.0), getExponent());
    //subtracting the value with lower limit from the value with upper limit
    double xEval = xEval2 - xEval1;
    //mulitplying the coefficient with the solved x value and returning the definite integral result
    double result = coeff*xEval;
    return result;
}

//overloaded > operator which compares 2 terms.
bool Term::operator>(Term &termObj)
{
    //if both the operands are non-trig terms, then the exponent is compared to determine if the first operand is greater than the second operand
    if (trigTerm == "" && termObj.getTrigTerm() == "")
    {
        return (exponent > termObj.getExponent());
    }
    //if the first operand is not a trig term, but the second one is, then returning false, because trig terms should be diplayed at the end
    else if (trigTerm != "" && termObj.getTrigTerm() == "")
    {
        return false;
    }
    //if the first operand is a trig term, but the second one is not, then returning true, because trig terms should be diplayed at the end
    else if (trigTerm == "" && termObj.getTrigTerm() != "")
    {
        return true;
    }
    //if both terms are trig functions, returning false, because the integral of the terms should be printed in the order it was encountered
    else
    {
        return false;
    }
}

//overloaded < operator which compares 2 terms.
bool Term::operator<(Term &termObj)
{
    //if both the operands are non-trig terms, then the exponent is compared to determine if the first operand is less than the second operand
    if (trigTerm == "" && termObj.getTrigTerm() == "")
    {
        return (exponent < termObj.getExponent());
    }
    //if the first operand is not a trig term, but the second one is, then returning true, because trig terms should be diplayed at the end
    else if (trigTerm != "" && termObj.getTrigTerm() == "")
    {
        return true;
    }
    //if the first operand is a trig term, but the second one is not, then returning false, because trig terms should be diplayed at the end
    else if (trigTerm == "" && termObj.getTrigTerm() != "")
    {
        return false;
    }
    //if both terms are trig functions, returning true, because the integral of the terms should be printed in the order it was encountered
    else
    {
        return true;
    }
}

//overloaded == operator which compares 2 terms.
bool Term::operator==(Term &termObj)
{
    //if both the operands are non-trig terms, then the exponent is compared to determine if the first operand is equal to the second operand
    if (trigTerm == "" && termObj.getTrigTerm() == "")
    {
        return (exponent == termObj.getExponent());
    }
    //if the first operand is not a trig term, but the second one is, then returning false, because trig terms cannot be equal to a non-trig term
    else if (trigTerm != "" && termObj.getTrigTerm() == "")
    {
        return false;
    }
    //if the first operand is a trig term, but the second one is not, then returning false, because trig terms cannot be equal to a non-trig term
    else if (trigTerm == "" && termObj.getTrigTerm() != "")
    {
        return false;
    }
    //if both terms are trig functions, comparing the trigterms to see if it is the same trig term
    else
    {
        return (trigTerm == termObj.getTrigTerm());
    }
}

//overloaded << operator which prints the term
std::ostream& operator<<(std::ostream &o, const Term &termObj)
{
    if (termObj.coefficient.denominator != 1)
    {
        o << "(" << termObj.coefficient.numerator << "/" << termObj.coefficient.denominator << ")";
    }
    else
    {
        o << termObj.coefficient.numerator;
    }
    if (termObj.exponent == 1)
    {
        o << "x";
    }
    else if (termObj.exponent > 1)
    {
        o << "x^" << termObj.exponent;
    }
    return o;
}


























//adding the exponent by 1
//int exp = getExponent() + 1;
//dividing the numerator of the coefficient by the new exponent
//Fraction f(getNumCoefficient(), exp);
