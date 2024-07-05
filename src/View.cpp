/**
 * File: View.cpp
 * Date: 2024.07.05
 * Author: Nulla
 * Description: Source file of view.
 */

#include "View.h"
#include <cstdlib>
//#ifdef _WIN32
//#include <windows.h>
//#endif

using namespace std;

//void View::clearScreen() {
//    #ifdef _WIN32
//    system("cls");
//    #else
//    system("clear");
//    #endif
//}

void View::displayLoginMenu() {
    cout << "=====| Login Menu |=====" << endl;
    cout << "1. Login" << endl;
    cout << "2. Quit" << endl;
    cout << "========================" << endl;
    cout << "(Enter the number): ";
}