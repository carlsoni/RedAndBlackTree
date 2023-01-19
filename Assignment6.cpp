//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author: Ian Carlson
// ASU ID: 1223065376
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
using namespace std;

//This function used to get the key of a Car which is the combination of vin, model & make
void getCarKey(string oneLine, int& vin, string& model, string& make);

//This function used to get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price);

int main()
{
   int vin;
   string model, make;
   double price;
   string command, oneLine, token;
   string delimiter = ",";
   int pos = 0;
   RedBlackTree *rbt = new RedBlackTree();

   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      
      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;
         delete rbt;
         break;
      }
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;
         
         //call the relevant function on the red black tree
         rbt->treePreorder();
      }
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;

         //call the relevant function on the red black tree
         rbt->treeInorder();
      }
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;

         //call the relevant function on the red black tree
         rbt->treePostorder();
      }
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;
         cout << "The MINIMUM is: " << endl;

         //call the relevant function on the red black tree
         rbt->treeMinimum();
      }
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;
         cout << "The MAXIMUM is: " << endl;
         //call the relevant function on the red black tree
         rbt->treeMaximum();
      }
      else if(command.compare("tree_predecessor")==0)
      {
         //call the getCarKey function to get the Car key first
         getCarKey(oneLine, vin, model, make);
         cout << "\nCommand: tree_predecessor" << endl;

         //call the relevant function on the red black tree
         rbt->treePredecessor(vin, model, make);
      }
      else if(command.compare("tree_successor")==0)
      {
         //call the getCarKey function to get the Car key first
         getCarKey(oneLine, vin, model, make);
         cout << "\nCommand: tree_successor" << endl;
         //call the relevant function on the red black tree
         rbt->treeSucessor(vin, model, make);
      }
      else if(command.compare("tree_search")==0)
      {
         //call the getCarKey function to get the Car key first
         getCarKey(oneLine, vin, model, make);
         cout << "\nCommand: tree_search" << endl;
         //call the relevant function on the red black tree
         rbt->treeSearch(vin, model, make);
      }
      else if(command.compare("tree_insert")==0)
      {
         
         getCarInfo(oneLine, vin, model, make, price);
         
         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(8)  << vin
              << setw(12) << model
              << setw(12) << make
              << setw(10) << fixed << setprecision(2) << price << endl;

         rbt->treeInsert(vin, model, make, price);
        }
   } while(true);  //continue until 'quit'
   return 0;
}

//*********************************************************************************
//This function from one line, extracts the vin, model, make of a Car
void getCarKey(string oneLine, int& vin, string& model, string& make)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
   
   pos =oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());

}

//************************************************************************************************
//This function from one line, extract tokens and get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price)
{

   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   vin = stoi(token);
   oneLine.erase(0, pos+delimiter.length());


   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   model = token;
   oneLine.erase(0, pos+delimiter.length());


   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   make = token;
   oneLine.erase(0, pos+delimiter.length());


   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   price = stod(token);
   oneLine.erase(0, pos+delimiter.length());
}