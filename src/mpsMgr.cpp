/*************************************************
File name : mps.cpp
Name      : Wan-Cyuan Fan
Student ID: b04502105
*************************************************/

#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "mpsMgr.h"

using namespace std;
//----------------------------------------------------//
//                   MPS processing                   //
//----------------------------------------------------//

int
mpsMgr::mps( int i , int j)
{
   int k = 0;
   vector<int> tem_k_array,tem_k_array_s1,tem_k_array_s2;
   k = _chord_tab[j];
   map<int_pair,int>::iterator it;
   it = _result_tab.find(int_pair(i,j));
   if( it != _result_tab.end()){
      return _result_tab[int_pair(i,j)];
   }
   else{
      if ( i >= j ) {
         _result_tab[int_pair(i,j)] = 0;
         return _result_tab[int_pair(i,j)];
      }
      //case 1
      else if ( k > j || k < i ){
         _result_tab[int_pair(i,j)] = mps(i,j-1);
         return _result_tab[int_pair(i,j)];
      }
      //case 2
      else if ( i < k && k < j){
         int s1 = mps(i,k-1) + mps(k,j);
         int s2 = mps(i,j-1);
         if( s1 > s2 ){
            _result_tab[int_pair(i,j)] = s1;
            return _result_tab[int_pair(i,j)];
         }
         else{
            _result_tab[int_pair(i,j)] = s2;
            return _result_tab[int_pair(i,j)];
         }
      }
      //case 3 ( k == i )
      else{
         _result_tab[int_pair(i,j)] = mps(i+1,j-1) + 1;
         return _result_tab[int_pair(i,j)];
      }
   }
}

void
mpsMgr::mps_k( int i , int j)
{
   int k = 0;
   //cout << " i = " << i << ", j = "<< j << endl;
   k = _chord_tab[j];
   //cout << " k = " << k << endl;
   if ( j > i) {
      //case 1
      if ( k > j || k < i ){
         mps_k(i,j-1);
      }
      //case 2
      else if ( i < k && k < j){
         int s1 = _result_tab[int_pair(i,k-1)] + _result_tab[int_pair(k,j)];
         int s2 = _result_tab[int_pair(i,j-1)];
         if( s1 > s2 ){
            mps_k(i,k-1);
            mps_k(k,j);
         }
         else{
            mps_k(i,j-1);
         }
      }
      //case 3 ( k == i )
      else{
         _k_array.push_back(k);
         mps_k(i+1,j-1);
      }
   }
}

//----------------------------------------------------//
//                    support_fun                     //
//----------------------------------------------------//

int
mpsMgr::getnumber()
{
   return _num;
}

int
mpsMgr::getpair( const int i,const int j)
{
   return _result_tab[int_pair(i,j)];
}

void
mpsMgr::showmpsarray(){
   for (map<int_pair,int>::iterator it = _result_tab.begin(); it != _result_tab.end(); it++) {
      cout  << " " << it->second << endl ;
   }
}

void
mpsMgr::showmpsk()
{
   cout << "size of k =  " << _k_array.size() << endl;
   for (size_t i = 0; i < _k_array.size(); i++) {
      int k = _k_array[i];
      cout << k << endl ;
   }
}

//----------------------------------------------------//
//                      loadfile                      //
//----------------------------------------------------//

bool
mpsMgr::loadfile( const char*& filename)
{
   int i,j,tmp_n;
   fstream myfile;
   myfile.open(filename,fstream::in);
   if (myfile.is_open()) {
      myfile >> tmp_n;
      _num_point = tmp_n;
      _num = tmp_n/2;
      while ( myfile >> i >> j){
   		_chord_tab[i] = j;
   		_chord_tab[j] = i;
   	}
      myfile.close();
      return true;
   }
   else {
      cerr << "Error : fail to open the file." << endl;
      return false;
   }
}

//----------------------------------------------------//
//                    outputfile                      //
//----------------------------------------------------//

bool
mpsMgr::oputfile( const string& filename)
{
   fstream outfile;
   outfile.open(filename,fstream::out);
   if (outfile.is_open()) {
      outfile << _result_tab[int_pair(0,_num_point-1)] << endl;
      sort(_k_array.begin(),_k_array.end());
      for (size_t i = 0; i < _k_array.size(); i++) {
         outfile << _k_array[i] << " " << _chord_tab[_k_array[i]] << endl;
      }
      return true;
   }
   else {
      cerr << "Error : fail to write the file." << endl;
      return false;
   }
}

//----------------------------------------------------//
//                    self_check                      //
//----------------------------------------------------//

void
mpsMgr::self_check()
{
   vector<int> check_vec;
   int s,j;
   for (int i = 0; i < _num_point; i++) {
      check_vec.push_back(0);
   }
   for (int i = 0; i < _k_array.size(); i++) {
      s = _k_array[i];
      j = _chord_tab[s];

      for (int m = s; m <= j; m++) {
         check_vec[m] += 1;
      }
   }
   cout << "###############" << endl;
   for (int i = 0; i < check_vec.size(); i++) {
      cout << check_vec[i];
   }
   cout << endl << "###############" << endl;
}
