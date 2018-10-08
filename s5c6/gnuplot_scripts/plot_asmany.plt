# FC / Série 3/ Gnuplot configuração

set terminal png size 1240,720
set print "-"
set macros

print "Inicializando o gnuplot..."
print "Imprimir todos os estados quânticos disponíveis..."

set xrange [-5:5]
set yrange [-0.2:0.2]
set format y "%.2f"
set key box opaque

#Estilos e títulos

style1 = "points lt 6 lw 0.5 title \"n = 0\""
style2 = "points lt 1 lw 0.5 title \"n = 1\""
style3 = "points lt 4 lw 0.5 title \"n = 2\""
style4 = "points lt 7 lw 0.5 title \"n = 3\""
style5 = "points lt 2 lw 0.5 title \"n = 4\""
style6 = "points lt 5 lw 0.5 title \"n = 5\""

Alabels = "set xlabel 'x'; set ylabel '{/Symbol f}'"

filename = ""
myFile =  'schrodinger_1000.dat' 
#system(ls schrodinger_*.dat)
#print filename

print "A preparar impressão..."

do for [i=1:ARG1] {
	@Alabels
	set title "{/:Bold=15 Oscilador Harmónico Quântico}"
	set label 1 sprintf("n = %d", (i-1)) at graph 0.1, 0.9 font '40'
	outfile = sprintf('many_quantumstates/quantumOsc_n%d', (i-1))
	set output outfile	
	plot myFile u 1:($2+i) w @style4
}


print "Sucesso! Procure os ficheiros na pasta 'many_quantumstates'"

pause 1

