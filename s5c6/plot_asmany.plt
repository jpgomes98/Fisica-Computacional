# FC / Série 3/ Gnuplot configuração

set terminal png size 1240,720
set output
set print "-"
set macros

print "Inicializando o gnuplot..."

set xrange [-10:10]
set yrange [-0.2:0.2]
set format y "%.3f"
set key box opaque

#Estilos e títulos

style1 = "points lt 6 lw 0.5 title \"n = 0\""
style2 = "points lt 1 lw 0.5 title \"n = 1\""
style3 = "points lt 4 lw 0.5 title \"n = 2\""
style4 = "points lt 7 lw 0.5 title \"{/Symbol f}(x)\"
style5 = "points lt 2 lw 0.5 title \"n = 4\""
style6 = "points lt 5 lw 0.5 title \"n = 5\""

Alabels = "set xlabel 'x'; set ylabel '{/Symbol f}'"
myFile =  'schrodinger_10000.dat' 

print "Imprimir todos os estados quânticos disponíveis..."
print "A preparar impressão..."
set title "{/:Bold=15 Oscilador Harmónico Quântico}"
@Alabels	
	do for [i=0:(ARG1-1)] {
		outfile = sprintf('many_quantumstates/quantumOsc_n%d.png', i)
		set output outfile	
		#plot myFile using 1:($2+i) with @style4	
		plot myFile using 1:(column(2 + i)) with @style4
	}


print "Sucesso! Procure os ficheiros na pasta 'many_quantumstates'"

pause 1
	
