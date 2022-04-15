// name: Jonah Yates
// project: Booths Algorithm project

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* Function Prototype Section */

// exits program if invalid input
void checkInvalidNumber(vector<int> & inputNum);

// will add 2 binary numbers stored in vectors and put result in store
void addBinary(vector<int> & store, vector<int> & source, const int size);

// debug print will print out the contents of AC Q q0
void debugPrint(vector<int> & AC, vector<int> & Q, const int q0);

// performs booths algorithm on the given binary numbers
string booths(vector<int> & q_multiplier, vector<int> & multiplicand, int & numAdd, int & numSub);

/* Constant Declaration Section */
const int C_ASCII_NUM_START = 48;

int main()
{
    /* Variable Declaration Section */
    string input;
    vector<int> AC;
    vector<int> q_multiplier = {};
    vector<int> multiplicand = {};
    int numLength, numAdd = 0, numSub = 0;

    cout<<"\nNote: when entering numbers, ensure you enter them in binary,\nand that there is no leading or trailing whitespace\n"<<endl;

    // getting input of the multiplier
    cout<<"Enter the 1st number, Q, multiplier: ";
    cin>>input;
    cout<<"";
    numLength = input.length();
    for (int i = 0; i < numLength; i++)
        q_multiplier.push_back(input[i]-C_ASCII_NUM_START);
    checkInvalidNumber(q_multiplier);

    // getting input of the multiplicand
    cout<<"Enter the 2nd number, B, multiplicand: ";
    cin>>input;
    cout<<"";
    for (int i = 0; i < numLength; i++)
        multiplicand.push_back(input[i]-C_ASCII_NUM_START);
    checkInvalidNumber(multiplicand);

    // calling booths algorithm and outputting the result
    cout<<"The result of multiplier (";
    for (auto & pos : q_multiplier)
        cout<<pos;
    cout<<") * multiplicand (";
    for (auto & pos : multiplicand)
        cout<<pos;
    cout<<") is: "<<booths(q_multiplier, multiplicand, numAdd, numSub)<<"."<<endl;

    return 0;
}

void checkInvalidNumber(vector<int> & inputNum)
{
    if (!(inputNum.size() >= 4 && inputNum.size() <= 12))
    {
        cout<<"\nCannot perform algorithm, input must be >= 4 and <= 12 digits in length."<<endl;
        exit(0);
    }
    for (auto & pos : inputNum)
        if (pos != 0 && pos != 1)
        {
            cout<<"\nCannot perform algorithm, an input number contains a character(s) that isn't a 1 or 0."<<endl;
            exit(0);
        }
}

void addBinary(vector<int> & store, vector<int> & source, const int length)
{
    /* Variable Declaration Section */
    int carry = 0, temp;

    for (int i = length-1; i >= 0 ; i--)
    {
        temp = store[i] ^ source[i] ^ carry;
        if (store[i] + source[i] + carry >= 2)
            carry = 1;
        else
            carry = 0;
        store[i] = temp;
    }    
}

void debugPrint(vector<int> & AC, vector<int> & Q, const int q0)
{
    /* Variable Declaration Section */
    int numLength = AC.size();

    for (int i = 0; i < numLength; i++)
        cout<<AC[i];
    cout<<" ";
    for (int i = 0; i < numLength; i++)
        cout<<Q[i];
    cout<<" "<<q0<<endl;
}

string booths(vector<int> & q_multiplier, vector<int> & multiplicand, int & numAdd, int & numSub)
{
    /* Variable Declaration Section */
    int numLength = q_multiplier.size(), q0 = 0;
    string twoNum, result = "";

    vector<int> twosComp = multiplicand;
    vector<int> AC = {};
    vector<int> addOne = {};
    
    AC.reserve(numLength);
    addOne.reserve(numLength);
    for (int i = 0; i < numLength; i++) /* filling the new vectors with all 0s */
    {
        AC.push_back(0);
        addOne.push_back(0);
    }
    addOne[numLength-1] = 1;

    // getting the 2s complement of multiplicand incase we need to perform a subtract
    for (int i = 0; i < numLength; i++)
    {
        if (twosComp[i] == 0)
            twosComp[i] = 1;
        else
            twosComp[i] = 0;
    }
    addBinary(twosComp, addOne, numLength);

    for (int i = 0; i < numLength; i++)
    {
        twoNum = "" + to_string(q_multiplier[numLength-1]) + to_string(q0);

                                                    /* 00 = no action */
        if (twoNum.compare("01") == 0)              /* 01 = add multiplicand */
        {
            addBinary(AC, multiplicand, numLength);
            numAdd++;
        }
        else if (twoNum.compare("10") == 0)         /* 10 = sub multiplicand */
        {
            addBinary(AC, twosComp, numLength);
            numSub++;
        }
                                                    /* 11 = no action */
                                                
        // shifting right after the appropriate action was taken
        q0 = q_multiplier[numLength-1];
        for (int i = numLength-1; i > 0; i--)
            q_multiplier[i] = q_multiplier[i-1];
        q_multiplier[0] = AC[numLength-1];
        for (int i = numLength-1; i > 0; i--)
            AC[i] = AC[i-1];
    }

    // turning the result into a string
    for (int i = 0; i < numLength; i++)
        result += to_string(AC.at(i));
    for (int i = 0; i < numLength; i++)
        result += to_string(q_multiplier.at(i));

    return result;
}
