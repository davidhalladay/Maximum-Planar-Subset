/*************************************************
File name : Main.cpp
Name      : Wan-Cyuan Fan
Student ID: b04502105
*************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <sstream>
#include "mpsMgr.h"

using namespace std;

int main(int argc, char const *argv[])
{
   mpsMgr my_mpsMgr;
   int _n;

   cout << "Please make sure the file you want to load is contained in the directory \"tests\" " << endl;
   if(my_mpsMgr.loadfile(argv[1])){
      _n = my_mpsMgr.getnumber();
      cout << "The number of chords : " << _n << endl;
      cout << "Processing MPS..." << endl;
      int mps_valve = my_mpsMgr.mps(0,2*_n - 1);
      cout << "Processing MPS_k..." << endl;
      my_mpsMgr.mps_k(0,2*_n - 1);
      //my_mpsMgr.showmpsk();
      //cout << "value " << mps_valve << endl;
      //my_mpsMgr.self_check();
   }

   if(my_mpsMgr.oputfile( argv[2])){
      cout << "File output successed!" << endl;
   }
   return 0;
}
