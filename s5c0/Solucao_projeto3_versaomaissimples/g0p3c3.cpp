//----------------------------g0p3c3.cpp---------------------------------
// to solve the two-dimensional Fourier heat equation
// now using classes, in the files Matrix.h and Matrix.cpp
//
//



#include <iostream> // to in and out from the kerboard and to the screen
#include <fstream>  // to in and out with files
#include <stdlib.h> // to use the void function exit()
#include <iomanip>  // define the precision with std::setprecision
#include <math.h>   // to use the math library of C
#include "Matrix.h" // our classfor matrixes





  int main(){

    // opens file for the input
    std::cout<< "uses inut file data g0p3c3_out.txt" << std::endl; // output file
    std::ifstream input("g0p3c3_inputfourier.txt"); 
    if ( input.fail() ) {
      std::cerr << "Impossible to open file " << std::endl;
      exit(1); // this terminates the process
    }
    else
      std::cout<< "file opens well" << std::endl;
    // opens file for the output
    std::cout<< "uses output file data g0p3c3_out.txt" << std::endl; // output file
    std::ofstream output("g0p3c3_out.txt");
    if ( output.fail() ) {
      std::cerr << "Impossible to open file " << std::endl;
      exit(1); // this terminates the process
    }
    else
      std::cout<< "file opens well" << std::endl;
    // opens another file for the output
    std::cout<< "uses output file data g0p3c3_outend.txt" << std::endl; // output file
    std::ofstream outputend ("g0p3c3_outend.txt");
    if ( outputend.fail() ) {
      std::cerr << "Impossible to open file " << std::endl;
      exit(1); // this terminates the process
    }
    else
      std::cout<< "file opens well" << std::endl;


    // reads the input data,from a file
    std::cout<< "uses input file data" << std::endl; // execution data, from a file
    std::cout<< "parameters: conductibility k and length l " << std::endl;
    double k,l;
    input >> k >> l;
    std::cout<< "initial physical conditions: initial time t0, left temp ttl, right temp ttr, back temp ttb, front temp ttf, initial bulk temp ttib " << std::endl;
    double t0,t1; double ttl, ttr,ttf,ttb,ttib;
    input >> t0 >> ttl >> ttr >>  ttb >> ttf >> ttib ; 
    std::cout<< "iteration parameters: step hx, step ht, total number of iterations n_max, number of iterations before printng n_print,  " << std::endl;
    int n_max, n_print ; double hx, ht; 
    input >>  hx >> ht >> n_max >>  n_print; 

    // checks input
    std::cout << " " << k << " " << l << " " << t0 << " " << ttl << " " << ttr << " " << ttb << " " << ttf << " " << ttib << " " << hx << " " << ht << " " << n_max << " " << n_print << std::endl;
    
    // computes remaining parameters
    int nx= (int) (l/hx)+1;
    std::cout << "this is the number of points in space including boundaries " << nx << std::endl;
    double al=k*4.*ht/(hx*hx);



    // our objects, the matrices
    Matrix tt0(nx,nx), tt1(nx,nx);

    // initial contition to prepare the time cicle
    for(int j=0; j< nx ; j++) tt0(0,j)=ttl;
    for(int j=0; j< nx ; j++) tt0(nx-1,j)=ttr;
    for(int i=0; i< nx ; i++) tt0(i,0)=ttb;
    for(int i=0; i< nx ; i++) tt0(i,nx-1)=ttf;
    for(int i=1; i< nx-1 ; i++) for(int j=1; j< nx-1 ; j++) tt0(i,j)=ttib;


    // finally the cicle in time
    for(int n =0;  n < n_max; n++ ) { /* iterating cicle */

      tt1=(1.-al)*tt0+al*med(tt0); //updates temperature
      t1=t0+ht; //updates time
    
      // prints the output every n_print
      if( (n % n_print) ==0 ){
        std::cout << "tt0(" << (int)(nx/2.) << "," << (int)(nx/2.) << ")( t= " << t0 << ")= " << tt0((int)(nx/2.),(int)(nx/2.)) << std::endl; 
        for(int i=0; i< nx ; i++) for(int j=0; j< nx ; j++) output << hx*(double)i << " " << hx*(double)j << " " << tt0(i,j) << std::endl;
        }
      // prints another output once
      if( (n - n_print) ==0 ) for(int i=0; i< nx ; i++) for(int j=0; j< nx ; j++) outputend << hx*(double)i << " " << hx*(double)j << " " << tt0(i,j) << std::endl;

      // resets for the next iteration
      tt0= tt1;
      t0= t1; 
    }


    input.close();  //not needed in c++ but better for a cleaner code
    output.close();  //not needed in c++ but better for a cleaner code
    outputend.close();  //not needed in c++ but better for a cleaner code


    return 0; 
  } 
