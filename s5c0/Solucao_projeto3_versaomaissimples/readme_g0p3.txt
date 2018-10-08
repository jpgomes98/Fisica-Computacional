1.a) Equação no formato C++,
tt1[i][j]= tt0[i][j]) + ((k * ht) /(hx*hx))*(tt0[i+1][j]+tt0[i-1][j]+tt0[i][j+1]+tt0[i][j-1]-4*tt0[i][j])

Comentário: esta iteração é idêntica à iteração da eq. Laplace, com um fator de relaxação 4*k* ht/(hx*hx), a diferença é que a iteração agora tem significado físico pois corresponde à evolução da temperatura em função do tempo

1.b) g0p3c1.cpp , parâmetros e condições iniciais em g0p3c0_inputfourier.txt

1.c) o output está no código mathematica g0p3c1.nb

Comentário: no limite de grande t, a temperatura tende para uma constante T(x,y)=373oK, temperatura na fronteira.
Comentário: observamos que a cerca de t=210s, a temperatura no centro difere em neos de 1% (relativamente à diferença para a temperatura inicial) da temperatura fina.

2.a) novas versões dos códigos VecAnyD.h, VecAnyD.cpp, VecAnyD_main.cpp

2.b) compilar os códigos  VecAnyD.h, VecAnyD.cpp e g0p3c2.cpp, 
- com parâmetros e condições iniciais em g0p3c2_inputfourier.txt
- o output está no código mathematica g0p3c2.nb.

2.c) a nova classe para matrizes está nos códigos Matrix.h e Matrix.cpp
- a compilar juntamente com o código g0p3c3.cpp
- para compilar é fornecida uma Makefile, escrever make para compilar
- os parâmetros e condiçõe sinicias estão em g0p3c3_inputfourier.txt (semelhante a 1.b))
- o output está no código mathematica g0p3c3.nb (semelhante a 1.c)).


Nota: apresentamos na solução apenas os códigos do 2.c) pois generalizam todas as alíneas anteriores.
