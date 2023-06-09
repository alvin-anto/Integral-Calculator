/**
 * ALVIN ANTO
 * NET ID: AXA220139
 * UTD ID: 2021686750
 * CS 2337.002
 * PROJECT 3
 */

#ifndef Term_h
#define Term_h

//importing required libraries
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

//struct Fraction to hold the coefficient in a fraction form
struct Fraction
{
    //instance variable declarations
    int numerator; //variable to hold the numerator of the fraction
    int denominator; //variable to hold the denominator of the fraction
    //constructors
    Fraction(){numerator = 0; denominator = 1;} //empty constructor
    Fraction(int num){numerator = num; denominator = 1;} //overloaded constructor
    Fraction(int num, int deno){numerator = num; denominator = deno;} //overloaded constructor
};

//class Term to hold each term in the expression
class Term
{
private:
    //instance variable declarations
    Fraction coefficient;
    int exponent;
    std::string trigTerm;
    //private methods
    void simplify(); //method to simplify the fraction coefficient
    int getNumCoefficient(){return coefficient.numerator;} //method that returns the numerator of the fraction coefficient
    int getDenoCoefficient(){return coefficient.denominator;} //method that returns the denominator of the fraction coefficient
    
public:
    //empty constructor
    Term(){coefficient = Fraction();}
    //overloaded constructors
    Term(Fraction f){coefficient = f; exponent = 0; trigTerm = "";}
    Term(Fraction f, int exp){coefficient = f; exponent = exp; trigTerm = "";}
    Term(Fraction f, int exp, std::string trig){coefficient = f; exponent = exp; trigTerm = trig;}
    
    //accessor methods
    Fraction getCoefficient(){return coefficient;} //method to return the coeffient in Fraction form
    int getExponent(){return exponent;} //method to return the exponent
    std::string getTrigTerm(){return trigTerm;} //method to return the trignometric term
    
    //mutator methods
    void setCoefficient(Fraction f){coefficient = f;} //method to set the coefficient of the Term to the Fraction passed in as argument
    void setExponent(int exp){exponent = exp;} //method to set the exponent of the Term to the value passed in as argument
    
    //other methods
    void addToCoefficient(Fraction f); //method that adds the argument fraction to the fraction coeffiecient of the term
    std::string getIntegral(); //method that finds the integral of the term and returns it as a string
    double getDefiniteIntegral(int limit1, int limit2); //method that finds the defininte integral of the term and returns it as a double
    
    //overloaded operators
    friend std::ostream& operator<<(std::ostream &o, const Term &termObj); //overloaded << operator
    bool operator>(Term &termObj); //overloaded > operator
    bool operator<(Term &termObj); //overloaded < operator
    bool operator==(Term &termObj); //overloaded == operator
};

#endif /* Term_h */









//    template <typename T>
//    T getIntegral()
//    {
//        if (isDefinite)
//        {
//            int exp = getExponent() + 1;
//            Fraction temp(exp);
//            Fraction f = getCoefficient() / temp;
//            double coeff = (f.getNumerator()*1.0)/(f.getDenominator()*1.0);
//            double xEval1 = pow((limit1*1.0), exp);
//            double xEval2 = pow((limit2*1.0), exp);
//            double xEval = xEval2 - xEval1;
//            double result = coeff*xEval;
//            return result;
//        }
//        else
//        {
//            std::string integral = "";
//            int exp = getExponent() + 1;
//            //std::cout << "EXP: " << exp << std::endl;
//            Fraction temp(exp);
//            Fraction f = getCoefficient() / temp;
//            //std::cout << "Fraction: " << f.getNumerator() << "/" << f.getDenominator() << std::endl;
//            if (f.getDenominator() == 1)
//            {
//                integral += std::to_string(f.getNumerator());
//            }
//            else
//            {
//                integral += "(";
//                integral += std::to_string(f.getNumerator());
//                integral += "/";
//                integral += std::to_string(f.getDenominator());
//                integral += ")";
//            }
//            if (exp == 1)
//            {
//                integral += "x";
//            }
//            else
//            {
//                integral += "x^";
//                integral += std::to_string(exp);
//            }
//            return integral;
//        }
//    }




//overloaded << operator that prints the numerator, then a "/" and then the denominator
//    friend std::ostream& operator<<(std::ostream &o, const Fraction &fractionObj){
//        //if (fractionObj.denominator != 1)
//        //{
//            o << "(" << fractionObj.numerator << "/" << fractionObj.denominator << ")";
//        //}
//        //else
//        //{
//        //    o << fractionObj.numerator;
//        //}
//        return o;
//
//    //overloaded >> operator that takes in the numerator and denominator as inputs from the user and
//    //assign those values to the corresponding instance variables
//    friend std::istream& operator>>(std::istream &i, Fraction &fractionObj){
//        int num;
//        std::cout << "Enter the numerator: " << std::endl;
//        i >> num;
//        fractionObj.setNumerator(num);
//        std::cout << "Enter the denominator: " << std::endl;
//        i >> num;
//        if (num==0){
//            std::cout << "Denominator cannot be zero." << std::endl;
//            std::cout << "Program Terminated" <<  std::endl;
//            exit(0);}
//        fractionObj.setDenominator(num);
//        return i;
//    }
