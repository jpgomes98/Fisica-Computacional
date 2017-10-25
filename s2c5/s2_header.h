/*Funções a integrar*/

double pdf(double x);
double wavefunc(double x);  // alpha = 1, N = 1/(pow((M_PI), 1/4))
double seno(double x);
double coss(double x);
double expo(double x);
double iden(double x);
double quadra(double x);
double quarta(double x);

/*Métodos de integração*/

double integra_rect(double a, double b, int N, double (*f)(double x));
double integra_trap(double a, double b, int N, double (*f)(double x));
double integra_simp(double a, double b, int N, double (*f)(double x));
double *markov(double (*pdf)(double x), double a, int n_conf, int m, double r);
double integra_montecarlo(double *confs, double **mat, int n, double (*f)(double x));

