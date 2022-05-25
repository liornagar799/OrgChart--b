#include <iostream>
#include "OrgChart.hpp"
#include <string>
using namespace ariel;
using namespace std;

 int main(){
  OrgChart organization;
  string a;
  cout << "please enter a name to the root" << endl;
  cin >> a;
  organization.add_root(a);
  

  string b;
  cout << "please enter a name to Add below " << a << endl;
  cin >> b;
  organization.add_sub(a,b);    

  string c;
  cout << "please enter a name to Add below " << a << endl;
  cin >> c;
  organization.add_sub(a,c);

  string f;
  cout << "please enter a name to Add below " << a << endl;
  cin >> f;
  organization.add_sub(a,f); 

  string d;
  cout << "please enter a name to Add below " << b << endl;
  cin >> d;
  organization.add_sub(b,d); 

  string e;
  cout << "please enter a name to Add below " << c << endl;
  cin >> e;
  organization.add_sub(c,e); 
  
  cout << "My OrgChart :" << endl;
  cout << "        " << a << "   " <<  endl;
  cout << "   |     |     |   " <<  endl;
  cout << "  "<< b <<  "  " << c << "  " << f << endl;
  cout << "   |     |   " <<  endl;
  cout << "  "<< d <<  "  " << e <<  endl;
 

 };