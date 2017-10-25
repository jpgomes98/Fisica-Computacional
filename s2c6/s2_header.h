/*Funções a integrar*/

double dist(double *x_n, int k, double s, int dim);
double pdf(double x);
double pdf_Ndim(double x);
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
void markov_Ndim(double (*pdf)(double x), double a, int n_conf, int m, double r, int dim, double **confs_vect);
double integra_montecarlo_Ndim (double **confs_vect, int n_confs, double (*f)(double x), int dim);

