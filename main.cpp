/**
 * ALVIN ANTO
 * NET ID: AXA220139
 * UTD ID: 2021686750
 * CS 2337.002
 * PROJECT 3
 */

//importing required libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctype.h>
#include "BinTree.h"
#include "Node.h"
#include "Term.h"

//using std namespace
using namespace std;

//prototypes
void processLine(string line); //function to process each line in the file and storing that to the BST
void calculateIntegral(Node<Term>* node, string& result); //recursive function that calculates the indefinite integral of the expression
void calculateDefiniteIntegral(Node<Term>* node, double& definiteIntegral, int l1, int l2); //recursive function that calculates the definite integral of the expression
void processTerm(string temp, BinTree<Term>& expressionBST, bool isTrig); //function that processes each term in an expression

//main function that openss the file and parses each line with the help of other methods
int main()
{
    //declaring a string variable fileName and storing the file name input by the user to it and opening the file
    string fileName;
    cout << "Enter the filename: " << endl;
    cin >> fileName;
    ifstream input;
    input.open(fileName);
    
    //declaring the string line to store each line of the input file
    string line;
    
    //checking if the file is open
    if (input)
    {
        //while loop that runs until the end of the file is reached
        while (!input.eof())
        {
            //gets each line from the line and stores that in the string variable line
            getline(input, line);
            //if the line is empty, continue to the next line
            if (line == "")
            {
                continue;
            }
            //calling processLine method with the string line as the parameter
            processLine(line);
        }
    }
    //if the file was not open, diplaying an error message
    else
    {
        cout << "File not found. Check the filename and try again." << endl;
    }
    
    //closing the file after using it
    input.close();
    
    //return statement for main
    return 0;
}


//function to process each line in the file and storing that to the BST
void processLine(string line)
{
    //creating a BinTree object called expressionBST
    BinTree<Term> expressionBST;
    //initializing isTrig, limit1, limit2, to store data related to whether or not the term is a trig term
    bool isTrig = false;
    int limit1 = 0;
    int limit2 = 0;
    
    //initializing isDefinite to store if we need to find the definite integral
    bool isDefinite = true;
    
    //variable len store the length of the line
    size_t len = line.length();
    
    //if the first character in the line is |, meaning we do not need the definite integral, setting isDefinite to false
    if (line[0] == '|')
    {
        isDefinite = false;
    }
    
    //initialializing a string called expression to store the expression
    string expression = "";
    
    //since all the lines in the file will have its first space before the beginning of the expression, storing the index of the first space to variable startingIndex
    size_t startingIndex = line.find(" ");
    
    //if we need to find the definite integral, getting the lower limit from the left side of | and the higher limit from the right side of the |, and then storing the limits to limit1 and limit2
    if (isDefinite)
    {
        string limitsString = line.substr(0,startingIndex);
        limit1 = stoi(limitsString.substr(0,limitsString.find("|")));
        limit2 = stoi(limitsString.substr(limitsString.find("|")+1, limitsString.length()));
    }
    //since all the lines in the file will have its last space after the beginning of the expression, storing the index of the last space to variable endingIndex using a for loop
    size_t endingIndex = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (line[i] == ' ')
        {
            endingIndex = i;
        }
    }
    
    //getting the expression using the index of the first and last space and the expression will be in between those spaces
    expression = line.substr(startingIndex + 1, endingIndex-(startingIndex+1));
    
    //getting each term in the expression using the loop and then checking if it is a trig function or not and calling processTerm with that term
    string temp ;
    size_t lenExpression = expression.length();
    for (size_t i = 0; i < expression.length(); i++)
    {
        //resetting isTrig to false for the next iteration
        isTrig = false;
        //getting each term using the fact that each term is separated by a + or -, not after ^
        if (expression[i] == '+' || expression[i] == '-')
        {
            if (i != 0 && expression[i-1] != '^')
            {
                //each term
                temp = expression.substr(0, i);
                
                //determining if the term is a trig function by checking if the term contains either cos or sin
                if ((temp.find("sin") != std::string::npos) || (temp.find("cos") != std::string::npos))
                {
                    isTrig = true;
                }
                //calling processTerm with the term, the BST and isTrig as the arguments
                processTerm(temp, expressionBST, isTrig);
                //removing the part already processed from the expression for the next iteration
                expression = expression.substr(i, lenExpression);
                //making i = 0 for the iteration to start from the first character of the new expression
                i = 0;
            }
        }
    }
    //At this point, the variable expression will contain the last term
    //checking if the last term is a trig function by checking if the term contains either cos or sin
    if ((expression.find("sin") != std::string::npos) || (expression.find("cos") != std::string::npos))
    {
        isTrig = true;
    }
    //calling processTerm with the term, the BST and isTrig as the arguments
    processTerm(expression, expressionBST, isTrig);
    
    //initializing a string variable result to store the integral
    string result = "";
    //calling the calculateIntegral function with the root of the BST and the result string as arguments
    calculateIntegral(expressionBST.getRoot(), result);
    
    //at this point result will have the integral of the expression
    //if we do not need the definite integral, adding constant (C) to the end
    if (!(isDefinite))
    {
        result += "C";
        string res;
        //replacing all + - with -
        while (result.find("+ -") != std::string::npos)
        {
            res += result.substr(0, result.find("+ -")) + "- ";
            result = result.substr((result.find("+ -") + 3), result.length()-(result.find("+ -") + 3));
        }
        res += result;
        result = "";
        //replacing all + (- with - (
        while (res.find("+ (-") != std::string::npos)
        {
            result += res.substr(0, res.find("+ (-")) + "- (";
            res = res.substr((res.find("+ (-") + 4), res.length()-(res.find("+ (-") + 4));
        }
        result += res;
        //print the integral stored in result variable to the console
        cout << result << endl;
    }
    //if we need to find the definite integral
    else
    {
        string res;
        //replacing + - wth -
        while (result.find("+ -") != std::string::npos)
        {
            res += result.substr(0, result.find("+ -")) + "- ";
            result = result.substr((result.find("+ -") + 3), result.length()-(result.find("+ -") + 3));
        }
        res += result;
        result = "";
        //replacing all + (- with - (
        while (res.find("+ (-") != std::string::npos)
        {
            result += res.substr(0, res.find("+ (-")) + "- (";
            res = res.substr((res.find("+ (-") + 4), res.length()-(res.find("+ (-") + 4));
        }
        result += res;
        //removing the + sign at the end of the result variable
        result.replace(result.length()-2, 2, "");
        
        //appending the lower and upper limit separated by | and = sign to the result
        result += ", " + to_string(limit1) + "|" + to_string(limit2) + " = ";
        
        //initializing a double variable definiteIntegral to store the definite integral
        double definiteIntegral = 0.0;
        //calling the calculateDefiniteIntegral function with the root of the BST, definiteIntegral variable and lower and upper limits as arguments
        calculateDefiniteIntegral(expressionBST.getRoot(), definiteIntegral, limit1, limit2);
        
        //creating a stringstream tempRes
        std::stringstream tempRes;
        //loading the definite integral with 3 decimal places to the stringstream buffer
        tempRes << fixed << setprecision(3) << definiteIntegral;
        //appending the definite integral with 3 decimal places to the result variable
        result += tempRes.str();
        //printing out the integral stored in the variable result to the console
        cout << result << endl;
    }
    
    //deleting the BST using deleteBST function
    expressionBST.deleteBST();
    expressionBST.setRoot(nullptr);
}

//function that processes each term in an expression
void processTerm(string temp, BinTree<Term>& expressionBST, bool isTrig)
{
    //initializing the coefficient, exponent, trig term with default values
    int coefficient = 1;
    int exponent = 0;
    string trigTerm = "";
    
    //removing all the spaces from the term and storing it in termWithoutSpaces using the for loop
    string termWithoutSpaces = "";
    for (size_t j = 0; j < temp.length(); j++)
    {
        if (temp[j] != ' ')
        {
            termWithoutSpaces += temp[j];
        }
    }
    //if the term is a trig function
    if (isTrig)
    {
        //initializing tempString
        string tempString = "";
        //if the first character is + or -
        if (termWithoutSpaces[0] == '+' || termWithoutSpaces[0] == '-')
        {
            //if the second character is a digit, meaning there is a coefficient
            if (isdigit(termWithoutSpaces[1]))
            {
                //parsing the term and storing the coeffiecient in tempString
                int t = 1;
                while (isdigit(termWithoutSpaces[t]))
                {
                    tempString += termWithoutSpaces[t];
                    t++;
                }
                //converting the coefficient to an integer and storing it in tempString
                coefficient = stoi(tempString);
            }
            //if the second character is not a digit, meaning coefficicent = 1;
            else
            {
                coefficient = 1;
            }
            //if the first character is -, making the coefficient negative
            if (termWithoutSpaces[0] == '-')
            {
                coefficient = 0 - coefficient;
            }
        }
        //if the first character is not + or -
        else
        {
            //if the first character is a digit, meaning there is a coefficient
            if (isdigit(termWithoutSpaces[0]))
            {
                //parsing the term and storing the coeffiecient in tempString
                int t = 0;
                while (isdigit(termWithoutSpaces[t]))
                {
                    tempString += termWithoutSpaces[t];
                    t++;
                }
                //converting the coefficient to an integer and storing it in tempString
                coefficient = stoi(tempString);
            }
            //if the second character is not a digit, meaning coefficicent = 1;
            else
            {
                coefficient = 1;
            }
            
        }
        //setting exponent to 1 as a default value
        exponent = 1;
        //declaring index variable to store the index where sin or cos starts
        size_t index;
        
        //getting the trig Term and storing it in trigTerm varaible
        if (termWithoutSpaces.find("sin") != std::string::npos)
        {
            index = termWithoutSpaces.find("sin");
            trigTerm = termWithoutSpaces.substr(index, termWithoutSpaces.find("x")-index);
        }
        else if (termWithoutSpaces.find("cos") != std::string::npos)
        {
            index = termWithoutSpaces.find("cos");
            trigTerm = termWithoutSpaces.substr(index, termWithoutSpaces.find("x")-index);
        }
        
        //creating a new fraction with the coefficient and creating a new Term with the coefficient, exponent, and trigTerm
        Fraction temp1(coefficient);
        Term temp2(temp1, exponent, trigTerm);
        
        //if the BST already has the term with the same exponent(in the overloaded comparison)
        if (expressionBST.search(temp2))
        {
            //instead of creating a new node in the BST, adding the term to the existing term with the same exponent
            expressionBST.search(temp2)->getData()->addToCoefficient(temp1);
        }
        //if the BST does not already have the term with the same exponent(in the overloaded comparison)
        else
        {
            //inserting the Term object to the BST
            expressionBST.insert(temp2);
        }
    }
    
    //if the term is not a trig function
    else
    {
        //initializing a boolean variable foundX to store whether or not the term has an "x" in it or it is a constant
        bool foundX = false;
        //for loop that gets the coefficient and store it in the coefficient
        for  (size_t k = 0; k < termWithoutSpaces.length(); k++)
        {
            //if the current character is 'x' or 'X'
            if (termWithoutSpaces[k] == 'x' || termWithoutSpaces[k] == 'X')
            {
                //sets the exponent to 1 and set foundX to true
                exponent = 1;
                foundX = true;
                //if the loop control variable is not equal to 0, or, the current character is not the first character in the string
                if (k != 0)
                {
                    //if the first character is +, then the coefficient is set to 1
                    if (termWithoutSpaces.substr(0,k) == "+")
                    {
                        coefficient = 1;
                    }
                    //if the first character is -, then the coefficient is set to -1
                    else if (termWithoutSpaces.substr(0,k) == "-")
                    {
                        coefficient = -1;
                    }
                    //else, the characters between 0 and kth index is set as coeffient
                    else
                    {
                        coefficient = stoi(termWithoutSpaces.substr(0,k));
                    }
                }
                //removing the processed part from the string and resets the control variable to 0
                termWithoutSpaces = termWithoutSpaces.substr(k, termWithoutSpaces.length());
                k = 0;
            }
            //if the current character is ^, meaning there is an exponent in the term
            else if (termWithoutSpaces[k] == '^')
            {
                //finding the exponent from the string and storing it as integer in the variable exponent
                exponent = stoi(termWithoutSpaces.substr(k+1, termWithoutSpaces.length()));
                break;
            }
        }
        //if there is no "x" in the term
        if (!(foundX))
        {
            //at this point the termWithoutSpaces will only have the exponent
            //so storing the coefficient from the term to the coefficient variable
            coefficient = stoi(termWithoutSpaces);
        }
        
        //creating a new Fraction with coefficient and making a Term object with the coefficient and exponent
        Fraction temp1(coefficient);
        Term temp2(temp1, exponent);
        
        //if the BST already has the term with the same exponent(in the overloaded comparison)
        if (expressionBST.search(temp2))
        {
            //instead of creating a new node in the BST, adding the term to the existing term with the same exponent
            expressionBST.search(temp2)->getData()->addToCoefficient(temp1);
        }
        //if the BST does not already have the term with the same exponent(in the overloaded comparison)
        else
        {
            //inserting the Term object to the BST
            expressionBST.insert(temp2);
        }
    }
}


//recursive function that calculates the indefinite integral of the expression
void calculateIntegral(Node<Term>* node, string& result)
{
    //if the current node is nullptr, exit the function
    if (node == nullptr)
    {
      return;
    }
    //recursively calling calculateIntegral with the right child of the current node and the result variable as the arguments
    calculateIntegral(node->getRight(), result);
    //getting the integral of the term in the current node and storing it in result
    stringstream tempStream;
    tempStream << node->getData()->getIntegral() << " + ";
    result += tempStream.str();
    
    //recursively calling calculateIntegral with the left child of the current node and the result variable as the arguments
    calculateIntegral(node->getLeft(), result);
}

//recursive function that calculates the definite integral of the expression
void calculateDefiniteIntegral(Node<Term>* node, double& definiteIntegral, int l1, int l2)
{
    //if the current node is nullptr, exit the function
    if (node == nullptr)
    {
      return;
    }
    //recursively calling calculateDefiniteIntegral with the right child of the current node and the result variable as the arguments
    calculateDefiniteIntegral(node->getRight(), definiteIntegral, l1, l2);
    
    //getting the definite integral of the term in the current node and storing it in definite integral
    definiteIntegral += node->getData()->getDefiniteIntegral(l1, l2);
    
    //recursively calling calculateDefiniteIntegral with the left child of the current node and the result variable as the arguments
    calculateDefiniteIntegral(node->getLeft(), definiteIntegral, l1, l2);
}











//
//stringstream resultStream;



//int numTerms = 0;
//numTerms++;


//if (result.find("+ -") != std::string::npos)
//{
//    result.replace(result.find("+ -"), 3, "- ");
//}




//    Fraction temp0(2);
//    Term term1(temp0, 1);
//    cout << "INTEGRAL: " << endl;
//    cout << term1.getIntegral() << endl;
//    cout << "###########" << endl;
//    cout << "DEFINITE INTEGRAL: " << endl;
//    cout << term1.getDefiniteIntegral(1,2) << endl;
//    cout << "###########" << endl;
//    BinTree<int> tree(new Node<int>(10));
//    tree.insert(new Node<int>(5));
//    tree.insert(new Node<int>(20));
//    tree.insert(new Node<int>(4));
//    tree.insert(new Node<int>(3));
//    tree.insert(new Node<int>(8));
//    tree.insert(new Node<int>(15));
//    tree.insert(new Node<int>(25));
//
//    //tree.inOrder(tree.getRoot());
//    tree.print2D(tree.getRoot());
//
//    if (tree.search(10))
//    {
//        cout << "10" << endl;
//    }
//    if (tree.search(5))
//    {
//        cout << "5" << endl;
//    }
//    if (tree.search(20))
//    {
//        cout << "20" << endl;
//    }
//    if (tree.search(4))
//    {
//        cout << "4" << endl;
//    }
//    if (tree.search(8))
//    {
//        cout << "8" << endl;
//    }
//    if (tree.search(15))
//    {
//        cout << "15" << endl;
//    }
//    if (tree.search(25))
//    {
//        cout << "25" << endl;
//    }
//    if (tree.search(35))
//    {
//        cout << "35" << endl;
//    }
//
//    //Node<int>* k = tree.remove(10);
//
//    cout << endl;
//
//    tree.print2D(tree.getRoot());
//
//    cout << endl;
//
//    tree.inorder(tree.getRoot());



//void printIntegral(Node<Term>* node) {
//    if (node == nullptr) {
//      return;
//    }
//    printIntegral(node->getRight());
//    cout << node->getData().getIntegral() << " + ";
//    printIntegral(node->getLeft());
//}
