// arrays1.cpp -  Script 6.1

#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
    
    // create a constant representing the
    // number of array elements
    const unsigned short ni=4;
    const unsigned short nj=3;
    
    // create an array
    int matnumbers[ni][nj];
    
    
    std:cout<< " you will be prompted to enter " << ni * nj << "numbers, positive or negative but without decimals or comas . \n\n "; 

    // create the loop that takes the input
    // the loop should run once for each array element, notice that this is a double loop 
    for(int i=0; 
        i <ni; 
        i=i+1)
    for(int j=0; 
        j <nj; 
        ++j){
             // prompt the user
             std::cout<<"enter a number :";
             
             // take the input, validate and repronpt if necessary
             while(!(std::cin>>matnumbers[i][j])){
                                                  // problem! clear cin and reprompt
                                                  std::cin.clear();
                                                  std::cin.ignore(100, '\n');
                                                  std::cout<<"Please enter a valid integer:";
                                                  }
            };
            
     // print another message
     std::cout<<"The following numbers have been recorded: \n ";
     
     // defines  a variable for the total
     int total=0;
     
     // loop again for the output
     for(int i=0; 
        i <ni; 
        i=i+1)
    for(int j=0; 
        j <nj
        ; 
        ++j){
             
             // prints all the numbers
             std::cout<<i<<" "<<j<<" "<<matnumbers[i][j]<<"\n"; 
             
             // adds to the total
             total+=matnumbers[i][j];
             
            };
            
    // prints the total
     std::cout<<"The sum of the numbers is: \n";
     std::cout<<total<<"\n";

    system("PAUSE");
    return EXIT_SUCCESS;
}
