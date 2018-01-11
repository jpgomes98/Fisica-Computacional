# invocar usando 'gnuplot -c png_maker.plt nmax print_step'

reset
set terminal pngcairo size 1024,720 enhanced font 'Verdana,13'

# color definitions

set samples 250
set isosamples 200

set title "Gross-Pitaevski"
set pm3d;  
#set palette model XYZ functions gray**0.35, gray**0.5, gray**0.8
set palette model XYZ functions gray**0.35, gray**0.5, gray**0.8

set cbrange [0:0.02]

N = (ARG1 + 0) - (ARG2 + 0) # somar zero converte para inteiros 
ToPrint = (ARG2 + 0)

dt = 0.00248
do for [i=0:N:+ToPrint] {
	t = i * dt
	outfile = sprintf('../gif/GPE_time_%fs.png', t)
	myfile = sprintf('../data/wavefunction_%d.dat', i)
	set output outfile
	splot [-10:10.01] [-10:10.01] [0:0.03] myfile u 1:2:3 w pm3d ls 1 title "|\{/Symbol f}(x, y)|²"
}

