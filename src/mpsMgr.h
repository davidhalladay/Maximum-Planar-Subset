/*************************************************
File name : mpsMgr.h
Name      : Wan-Cyuan Fan
Student ID: b04502105
*************************************************/
#ifndef MPS_MGR_H
#define MPS_MGR_H

#include <cassert>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <stdlib.h>

using namespace std;
typedef pair<int,int> int_pair;


class mpsMgr
{
public:
   mpsMgr(): _num(1) {}

   ~mpsMgr(){}
   // the funstions of loading file
   bool loadfile( const char*&);
   bool oputfile( const string&);
   // the functions of controling the private data
   int getnumber();
   int getpair( const int,const int);
   void showmpsarray();
   void showmpsk();
   // the functions of mps processing
   int mps( int , int);
   void mps_k( int i , int j);

   // self-check
   void self_check();
private:
   int _num;               //store the number of the chords

   int _num_point;

   map<int_pair,int> _result_tab;

   map<int,int> _chord_tab;

   vector<int> _k_array;         //store the j,k endpoints
};


#endif //MPS_MGR_H
