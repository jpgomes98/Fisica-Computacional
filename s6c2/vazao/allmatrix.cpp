#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

class Complex{
public:
  
  double re;
  double im;

  Complex();
  Complex(double a,double b);


  void operator= (const Complex& z);
  Complex operator+ (const Complex& z);
  friend Complex operator+ (double a, const Complex& z);  
  Complex operator+ (double a);
  Complex operator* (const Complex& z);
  friend Complex operator* (double a,const Complex& z);
  Complex operator* (double a);
  Complex operator- (const Complex& z);
  friend Complex operator- (double a, const Complex& z);  
  Complex operator- (double a);
  Complex operator/ (const Complex& z);
  Complex operator/ (double a);
  friend Complex operator/ (double a,const Complex& z);
  friend ostream& operator<<( ostream& out, const Complex& z);
  void operator() (double a, double b);
};

Complex::Complex(){

  re=0;
  im=0;
  
}

Complex::Complex(double a, double b){

  re=a;
  im=b;
  
}

void Complex::operator= (const Complex& z){

  re = z.re;
  im = z.im;

}

Complex Complex::operator+ (const Complex& z){

  Complex y;

  y.re = re + z.re;
  y.im = im + z.im;

  return y;

}

Complex operator+ (double a,const Complex& z){

  Complex y;

  y.re = a + z.re;
  y.im = z.im;

  return y;

}

Complex Complex::operator+ (double a){

  Complex y;

  y.re = re + a;
  y.im = im;

  return y;

}

Complex operator- (double a,const Complex& z){

  Complex y;

  y.re = a - z.re;
  y.im = - z.im;

  return y;

}

Complex Complex::operator- (double a){

  Complex y;

  y.re = re - a;
  y.im = im;

  return y;

}

Complex Complex::operator* (const Complex& z){

  Complex w;

  w.re= re*z.re - im*z.im;
  w.im= re*z.im + im*z.re;

  return w;
}

Complex operator*(double a, const Complex& z){

  Complex w;

  w.re=a*z.re;
  w.im=a*z.im;

  return w;

}

Complex Complex::operator* (double a){

  Complex w;

  w.re=a*re;
  w.im=a*im;

  return w;
}

Complex Complex::operator- (const Complex& z){

  Complex y;

  y.re = re - z.re;
  y.im = im - z.im;

  return y;

}

Complex mod(const Complex& z){

  Complex w;

  w.re = sqrt(z.re*z.re + z.im*z.im);

  return w;
}

double norma(const Complex& z){

  double w;

  w = sqrt(z.re*z.re + z.im*z.im);

  return w;
}

double norma(double z){

  double w;

  w = fabs(z);

  return w;
}

Complex Complex::operator/ (const Complex& z){

  Complex w;

  w.re = (re*z.re + im*z.im)/(z.re*z.re + z.im*z.im);
  w.im = (-re*z.im + im*z.re)/(z.re*z.re + z.im*z.im);

  return w;
}

Complex Complex::operator/ (double a){

  Complex w;

  w.re=re/a;
  w.im=im/a;

  return w;
}

Complex operator/ (double a,const Complex& z){

  Complex w;

  w.re = (a*z.re)/(z.re*z.re + z.im*z.im);
  w.im = -(a*z.im)/(z.re*z.re + z.im*z.im);

  return w;
}

ostream& operator<<( ostream& out, const Complex& z){

  if(z.im>0){
    out << z.re << " + i" << z.im;
  }

  else if(z.im<0){
    out << z.re << " - i" << -z.im;
  }

  else{
    out << z.re;
  }

  return out;
}

void Complex::operator() (double a, double b){

  re=a;
  im=b;

}

Complex gen_rand_complex(){

  Complex w;

  double a, b;

  a = rand()%20;
  b = rand()%20;

  w.re=a;
  w.im=b;

  return w; 
}

template <typename Tipo>
class Matrix{
 public:
  
  Tipo **ptr;
  int col;
  int line;

  Matrix(int M, int N);
  
  ~Matrix();

  Matrix operator+ (const Matrix& y);
  Matrix operator* (const Matrix& y);
  Matrix& operator= (const Matrix& y);
  Tipo operator()(unsigned i, unsigned j) const;
  Tipo& operator()(unsigned i, unsigned j);
  template <class U>
  friend Matrix<U> operator*(U a, Matrix<U> const& A);
  Matrix operator*(const Tipo a);
  template <class U>
  friend ostream& operator<<( ostream& out, const Matrix<U> & r );
  template <class U>
  friend Matrix operator-(const Matrix& A);

  Matrix Hvec(int i);
  Matrix Vvec(int i);
};

template <>
class Matrix<double>{
  public:

  double **ptr;
  int col;
  int line;

  Matrix(int M,int N) : col(M), line(N) {
  
    ptr = new double*[col];
 
    for(int i =0;i<col;i++){
      ptr[i]=new double [line];
    }

    for(int i=0;i<M;i++){
      for(int j=0;j<N;j++){
	ptr[i][j]=0;
      }
    }
  }
  
  Matrix<double> operator*(double a){

    Matrix<double> B(col,line);
    for(int i=0;i<col;i++){
      for(int j=0;j<line;j++){
	B.ptr[i][j]=ptr[i][j]*a;
      }
    }
    return B;
  }
  
};

template <typename Tipo>
Matrix<Tipo>::~Matrix(){
  for(int i=0;i<col;i++){
    delete[] ptr[i];
  }
  delete[] ptr;
}

template <typename Tipo>
Matrix<Tipo>::Matrix(int M,int N) : col(M), line(N) {
  
  ptr = new Tipo*[col];
 
  for(int i =0;i<col;i++){
    ptr[i]=new Tipo [line];
  }

  Complex z(0,0);
  
  for(int i=0;i<M;i++){
    for(int j=0;j<N;j++){
      ptr[i][j]=z;
    }
  }
}

template <typename Tipo>
Matrix<Tipo> Matrix<Tipo>::operator+ (const Matrix<Tipo>& y){
  Matrix m(col,line);

  if((col==y.col)&&(line==y.line)){

    for(int j=0;j<col;j++){

      for(int i=0;i<line;i++){
	m.ptr[j][i] = ptr[j][i] + y.ptr[j][i];

      }
    }
  }
  return m;
}


template <class Tipo>
Matrix<Tipo> Matrix<Tipo>::operator* (const Matrix& y){
  Matrix m(y.col,line);

  if(col==y.line){

    for(int i=0;i<line;i++){
      for(int j=0;j<y.col;j++){
	for(int k=0;k<line;k++){
	  m.ptr[j][i] = m.ptr[j][i] + ptr[k][i]*y.ptr[j][k];
	}
	
      }
    }

    return m;
  }
  else{cout<<"Can't multiply!"<<endl;return m;}
  
  }

template <typename Tipo>
Matrix<Tipo>& Matrix<Tipo>::operator= (const Matrix& y){
    
  for(int i=0;i<col;i++){
    delete[] ptr[i];
  }
  delete[] ptr;

  ptr = new Tipo*[y.col];

  for(int i =0;i<y.col;i++){
    ptr[i]=new Tipo [y.line];
  }
  
  for(int i=0;i<y.col;i++){
    for(int j=0;j<y.line;j++){
      ptr[i][j]= y.ptr[i][j];
    }
  }

  col=y.col;
  line=y.line;
  
  return *this;
}


template <typename Tipo>
ostream& operator<< ( ostream& out, const Matrix<Tipo> & r ) { 
  cout << "\n";
  for( unsigned i = 0; i < r.line; ++i ){
    for(unsigned j=0;j<r.col;j++){
      out  << r.ptr[j][i] << "\t ";
    }
    cout << "\n\n";
  }
  cout << "\n\n";
  return out;
}

template <typename Tipo>
Tipo Matrix<Tipo>::operator()(unsigned i, unsigned j) const { return ptr[i][j]; }

template <typename Tipo>
Tipo& Matrix<Tipo>::operator()(unsigned i, unsigned j) { return ptr[i][j]; }

template <typename Tipo>
Matrix<Tipo> operator*(Tipo a, Matrix<Tipo> const& A){

  Matrix<Tipo> B(A.col,A.line);
  
  for(int i=0;i<A.col;i++){
    for(int j=0;j<A.line;j++){
      B.ptr[i][j]=A.ptr[i][j]*a;
    }
  }
  return B;
}

template <class Tipo>
Matrix<Tipo> Matrix<Tipo>::operator*(Tipo a){

  Matrix<Tipo> B(col,line);
  for(int i=0;i<col;i++){
    for(int j=0;j<line;j++){
      B.ptr[i][j]=ptr[i][j]*a;
    }
  }
  return B;
}


template <typename Tipo>
Matrix<Tipo> operator-(const Matrix<Tipo>& A){

  Matrix<Tipo> B(A.col,A.line);

  for(int i=0;i<A.col;i++){
    for(int j=0;j<A.line;j++){
	B.ptr[i][j]=(-1)*A.ptr[i][j];
    }
  }

  return B;
}

template <typename Tipo>
Matrix<Tipo> Matrix<Tipo>::Hvec(int i){

  Matrix y(col,1);

  for(int j=0;j<col;++j){
    y.ptr[j][0]=ptr[j][i-1];
  }

  return y;
}

template <typename Tipo>
Matrix<Tipo> Matrix<Tipo>::Vvec(int i){

  Matrix y(1,line);

  for(int j=0;j<line;++j){
    y.ptr[0][j]=ptr[i][j];
  }

  return y;
}


template <typename Tipo>
Matrix<Tipo> I(int i){

  Matrix<Tipo> y(i,i);

  Complex z(1,0);
  Complex w(0,0);

  for(int j=0;j<i;j++){
    for(int k=0;k<i;k++){
      if(j==k){
	y.ptr[j][k]=z;
      }
      else{y.ptr[j][k]=w;}
    }
  }
  
  return y;
}

template <>
Matrix<double> I(int i){

  Matrix<double> y(i,i);

  for(int j=0;j<i;j++){
    for(int k=0;k<i;k++){
      if(j==k){
	y.ptr[j][k]=1;
      }
      else{y.ptr[j][k]=0;}
    }
  }
  
  return y;
}

template <typename Tipo>
Tipo det(const Matrix<Tipo> & A){

  Tipo h,y;
  Complex c(1,0);
  Matrix<Tipo> C(1,1);
  C=A;
  
  for(int i=0;i<C.line;++i){

    for(int k=C.line-1;k>i;--k){
      if(norma(C.ptr[i][k])>norma(C.ptr[i][k-1])){
	for(int t=0;t<C.col;++t){
	  y=C.ptr[t][k];
	  C.ptr[t][k]=C.ptr[t][k-1];
	  C.ptr[t][k-1]=y;
	}
      }
    }
    
    for(int j=i;j<C.col;++j){
      if(j!=i){
	h=C.ptr[i][j]/C.ptr[i][i];
	for(int k=0;k<C.col;k++){
	  C.ptr[k][j]= C.ptr[k][j] - C.ptr[k][i]*h;
	}
      }
    }
  }

  for(int i=0;i<A.line;++i){
    c = c*C.ptr[i][i];
  }

  return c;
}

template <>
double det(const Matrix<double> & A){

  double h=0,y=0,c=1;
  Matrix<double> C(1,1);
  C=A;
  
  for(int i=0;i<C.line;++i){

    for(int k=C.line-1;k>i;--k){
      if(C.ptr[i][k]>C.ptr[i][k-1]){
	for(int t=0;t<C.col;++t){
	  y=C.ptr[t][k];
	  C.ptr[t][k]=C.ptr[t][k-1];
	  C.ptr[t][k-1]=y;
	}
      }
    }
    
    for(int j=i;j<C.col;++j){
      if(j!=i){
	h=C.ptr[i][j]/C.ptr[i][i];
	for(int k=0;k<C.col;k++){
	  C.ptr[k][j]-=C.ptr[k][i]*h;
	}
      }
    }
  }

  for(int i=0;i<A.line;++i){
    c*=C.ptr[i][i];
  }

  return c;
}

template <typename Tipo>
Matrix<Tipo> inv(const Matrix<Tipo> & A){

  Matrix<Tipo> B(2*A.col,A.line);
  Matrix<Tipo> C(1,1);

  C=I<Tipo>(A.col);
  Tipo h;
  
  for(int i=0;i<A.col;++i){
    for(int j=0;j<A.line;j++){
      B.ptr[i][j]=A.ptr[i][j];
    }
  }

  for(int i=A.col;i<2*A.col;++i){
    for(int j=0;j<A.line;++j){
      B.ptr[i][j]=C.ptr[i-A.col][j];
    }
  }
  
  for(int i=A.line-1;i>0;--i){
    if(norma(A.ptr[0][i])>norma(A.ptr[0][i-1])){
      for(int j=0;j<2*A.col;j++){
	h=B.ptr[j][i];
	B.ptr[j][i]=B.ptr[j][i-1];
	B.ptr[j][i-1]=h;
      }
    }
  }

  for(int i=0;i<A.line;++i){
    for(int j=0;j<A.col;++j){
      if(j!=i){
	h=B.ptr[i][j]/B.ptr[i][i];
	for(int k=0;k<2*A.col;++k){
	  B.ptr[k][j]=B.ptr[k][j]-B.ptr[k][i]*h;
	}
      }
    }
  }

  for (int i=0; i<A.line; ++i){
    h = B.ptr[i][i];
    for (int j=0; j<A.col*2; ++j)
      B.ptr[j][i] = B.ptr[j][i] / h;
  }

  for(int i=A.col;i<2*A.col;++i){
    for(int j=0;j<A.line;++j){
      C.ptr[i-A.col][j]=B.ptr[i][j];
    }
  }
  
  return C;
}

/*
double tra(const Matrix& A){

  double c=0;

  for(int i=0;i<A.line;i++){
    c+=A.ptr[i][i];
  }

  return c;
}

double dot(const Matrix& A, const Matrix& B){

  double c=0;
  
  if((A.col==1)&&(B.col==1)&&(A.line==B.line)){
    for(int i=0;i<A.line;i++){
      c+=A.ptr[0][i]*B.ptr[0][i];
    }
  }

  return c;
}

Matrix cross(const Matrix& A, const Matrix& B){

  Matrix C(1,A.line);
  if((A.col==0)&&(B.col==0)&&(A.line==3)&&(B.line==3)){

    C.ptr[0][0]=A.ptr[0][1]*B.ptr[0][2]-A.ptr[0][2]*B.ptr[0][1];
    C.ptr[0][1]=-A.ptr[0][0]*B.ptr[0][2]+A.ptr[0][2]*B.ptr[0][0];
    C.ptr[0][2]=A.ptr[0][0]*B.ptr[0][1]-A.ptr[0][1]*B.ptr[0][0];
  }
  
  return C;
}

Matrix transpose(const Matrix& A){

  Matrix C(A.col,A.line);
  if(A.col==A.line){
    double h=0;

    for(int i=0;i<A.line;i++){
      for(int j=0;j<A.col;j++){
	C.ptr[j][i]=A.ptr[i][j];
      }
    }
  }

  return C;
}

Matrix triangular(const Matrix& A){

  double h=0,c=1;
  Matrix C(1,1);
  C=A;
  
  for(int i=0;i<A.line;i++){
    for(int j=i;j<A.col;j++){
      if(j!=i){
	h=C.ptr[i][j]/C.ptr[i][i];
	for(int k=0;k<A.col;k++){
	  C.ptr[k][j]-=C.ptr[k][i]*h;
	}
      }
    }
  }

  return C;
}


Matrix lineq(const Matrix& A, const Matrix& B){

  Matrix M(A.col,A.line);
  Matrix x(1,B.line);

  M=inv(A);

  x=M*B;

  return x; 
  }*/

template <typename Tipo>
Matrix<Tipo> gen_rand_matrix(int x, int y){

  Matrix<Tipo> M(x,y);
  
  for(int i=0;i<M.col;i++){
    for(int j=0;j<M.line;j++){
      M.ptr[i][j]= gen_rand_complex();
    }
  }

  return M;
}

template <>
Matrix<double> gen_rand_matrix(int x, int y){

  Matrix<double> M(x,y);
  
  for(int i=0;i<M.col;i++){
    for(int j=0;j<M.line;j++){
      M.ptr[i][j]= rand()%20;
    }
  }

  return M;
}



/*
Matrix eigenvector(const Matrix& M){
  
  Matrix S(M.col,M.line);
  Matrix M1(M.col,M.line);
  Matrix V0(1,M.line);
  Matrix V2(1,M.line);
  int n=1000;
  
  M1=M;
   
  for(int k=0;k<M.col;++k){
   V0 = gen_rand_matrix(1,M.line);
    
    if(k==0){
      for(int t=0;t<n;++t){
  	V0=M1*V0;
  	V0=V0*(1/sqrt(dot(V0,V0)));
      }
    }
  
    else{
      for(int t=0;t<n;++t){
  	V0=M1*V0;
   	for(int i=0;i<k;++i){
   	  V2=S.Vvec(i);
  	  V0=V0+(-dot(V2,V0)*V2);
  	}
  	V0=V0*(1/sqrt(dot(V0,V0)));
      }
    }
                          
    for(int i=0;i<S.line;++i){
      S.ptr[k][i]=V0.ptr[0][i];
    }
  }
  
  return S;
} 
*/
template <typename Tipo>
Matrix<Tipo> gen_sym_matrix(int x, int y){

  Matrix<Tipo> M(x,y);
  
  for(int i=0;i<M.col;i++){
    for(int j=i;j<M.line;j++){
      M.ptr[i][j]= gen_rand_complex();
    }
  }

   for(int i=0;i<M.line;i++){
    for(int j=i+1;j<M.col;j++){
      M.ptr[j][i]= M.ptr[i][j];
    }
  }

 return M;
}

template <>
Matrix<double> gen_sym_matrix(int x, int y){

  Matrix<double> M(x,y);
  
  for(int i=0;i<M.col;i++){
    for(int j=i;j<M.line;j++){
      M.ptr[i][j]= rand()%20;
    }
  }

   for(int i=0;i<M.line;i++){
    for(int j=i+1;j<M.col;j++){
      M.ptr[j][i]= M.ptr[i][j];
    }
  }

 return M;
}

/*
Matrix eigenvalue(const Matrix& A){

  Matrix M(A.col,A.line);
  Matrix M1(A.col,A.line);
  Matrix E(A.col,A.line);
  Matrix P(1,A.line);
  
  M=A;
  E = eigenvector(A);
  for(int i=0;i<M.col;++i){
    P=M*E.Vvec(i);
    M1.ptr[i][i]=P.ptr[0][P.line-1]/E.ptr[i][E.line-1];
  }

  return M1;
}

Matrix eigenvector3(const Matrix& M){
  
  Matrix S(3,M.line);
  Matrix M1(M.col,M.line);
  Matrix V0(1,M.line);
  Matrix V2(1,M.line);
  int n=1000;
  
  M1=M;
   
  for(int k=0;k<3;++k){
   V0 = gen_rand_matrix(1,M.line);
    
    if(k==0){
      for(int t=0;t<n;++t){
  	V0=M1*V0;
  	V0=V0*(1/sqrt(dot(V0,V0)));
      }
    }
  
    else{
      for(int t=0;t<n;++t){
  	V0=M1*V0;
   	for(int i=0;i<k;++i){
   	  V2=S.Vvec(i);
  	  V0=V0+(-dot(V2,V0)*V2);
  	}
  	V0=V0*(1/sqrt(dot(V0,V0)));
      }
    }
                          
    for(int i=0;i<S.line;++i){
      S.ptr[k][i]=V0.ptr[0][i];
    }
  }
  
  return S;
}


Matrix eigenvalue3(const Matrix& A){

  Matrix M(A.col,A.line);
  Matrix M1(1,3);
  Matrix E(A.col,A.line);
  Matrix P(1,A.line);
  
  M=A;
  E = eigenvector3(A);
  for(int i=0;i<3;++i){
    P=M*E.Vvec(i);
    M1.ptr[0][i]=P.ptr[0][P.line-1]/E.ptr[i][E.line-1];
  }

  return M1;
  }*/

template class Matrix <Complex>;
template class Matrix <double>;

int main(){

  srand(time(NULL));

  Matrix <Complex> M(2,2);
  Matrix <double> N(4,4);
  Matrix <Complex> R(1,1);
  Matrix <Complex> O(1,1);
  Matrix <double> S(4,4);

  Matrix <double> D(2,2);

  Complex z(3,2);
  Complex w(1,2);

  M = gen_rand_matrix<Complex>(2,2);
  N = gen_rand_matrix<double>(4,4);

  R = -M*z;
  S = -N*2.;

  cout << R << endl;
  cout << S << endl;

  return 0;
}

