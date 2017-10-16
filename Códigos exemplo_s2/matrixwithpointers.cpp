// matrixwithpointers.cpp -  Script 6.1 - adapted for pointers

#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
    
    
    // just says the number of matriz elements is integer
    int ni , nj ;
   
       
    // create not really an array, but a pointer to a pointer
    float ** matrix = new float*[ni];
    for(int i = 0; i < ni; ++i) matrix[i] = new float[nj];

    // only now it reads the size of the matrix, in this case from the keys, 
    cout<< " you will be prompted to enter 2 integers for the size of the matriz. \n\n"; 
    cin>> ni >> nj;

    
    cout<< " you will be prompted to enter " << ni * nj << " real numbers. \n\n"; 

    // create the loop that takes the input
    // the loop should run once for each array element, notice that this is a double loop 
    for(int i=0; 
        i <ni; 
        i=i+1)
    for(int j=0; 
        j <nj; 
        ++j){
             // prompt the user
             cout<<"enter a number :";
             
             // take the input, validate and repronpt if necessary
             while(!(cin>>matrix[i][j])){
                                                  // problem! clear cin and reprompt
                                                  cin.clear();
                                                  cin.ignore(100, '\n');
                                                  cout<<"Please enter a valid float:";
                                                  }
            };
            
     // print another message
     std::cout<<"The following numbers have been recorded: \n";
     
     // also defines  a variable for the total
     float total=0;
     
     // loop again for the output
     for(int i=0; 
        i <ni; 
        i=i+1)
    for(int j=0; 
        j <nj
        ; 
        ++j){
             
             // prints all the numbers
             cout<<i<<" "<<j<<" "<<matrix[i][j]<<"\n"; 
             
             // adds to the total
             total+=matrix[i][j];
             
            };
            
    // prints the total
     cout<<"The sum of the numbers is: \n";
     cout<<total<<"\n";
     
     // frees the memory
     for(int i = 0; i < ni; ++i) delete[] matrix[i];
     delete[] matrix;


    system("PAUSE");
    return EXIT_SUCCESS;
}
