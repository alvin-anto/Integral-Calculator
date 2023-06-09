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
