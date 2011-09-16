/* 
 * File:   main.cpp
 * Author: rikson
 *
 * Created on September 9, 2011, 10:54 PM
 */

#include <iostream>
#include <string>

#include "include/constants.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string code;

    cout << "Welcome to Falcon 1.0!" << endl;
    cout << endl << "Please enter the CODE: ";

    cin >> code;

    if (code == Constant::CODE) {
        cout << endl << "CODE match.";
        cout << endl << "Please be patient with us while we are still Wooting!" << endl;
    } else {
        cout << "CODE mismatch!" << endl;
    }

    return 0;
}


