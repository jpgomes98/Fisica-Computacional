
# FC / Série 3/ Gnuplot configuração

set terminal png size 1920,1080
set output '6_quantumstates.png'
set print "-"
set macros

print "Inicializando o gnuplot..."

set xrange [-5:5]
set yrange [-0.2:0.2]
set format y "%.1f"
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

# Margens 

if (!exists("MP_LEFT"))   MP_LEFT = .1
if (!exists("MP_RIGHT"))  MP_RIGHT = .95
if (!exists("MP_BOTTOM")) MP_BOTTOM = .1
if (!exists("MP_TOP"))    MP_TOP = .9
if (!exists("MP_GAP"))    MP_GAP = 0.05

print "A preparar impressão..."
### Start multiplot (1x4 layout)

set multiplot layout 2, 3 columnsfirst title "{/:Bold=15 Oscilador Harmónico Quântico - 6 Estados}" \
  margins screen MP_LEFT, MP_RIGHT, MP_BOTTOM, MP_TOP spacing screen MP_GAP

# --- n = 0
@Alabels
set label 1 sprintf("E(0) = %s", ARG1) at graph 0.1, 0.9 font '40'
plot myFile u 1:2 w @style1,

# --- n = 1
@Alabels
unset label 1
set label 2 sprintf("E(1) = %s", ARG2) at graph 0.1, 0.9 font '40'
plot myFile u 1:3 w @style2,
# --- n = 2
@Alabels
unset label 2
set label 3 sprintf("E(2) = %s", ARG3) at graph 0.1, 0.9 font '40'
plot myFile u 1:4 w @style3,
# --- n = 3
@Alabels
unset label 3
set label 4 sprintf("E(3) = %s", ARG4) at graph 0.1, 0.9 font '40'
plot myFile u 1:5 w @style4,
# --- n = 4
@Alabels
unset label 4
set label 5 sprintf("E(4) = %s", ARG5) at graph 0.1, 0.9 font '40'
plot myFile u 1:6 w @style5,
# --- n = 5
@Alabels
unset label 5
set label 6 sprintf("E(5) = %s", ARG6) at graph 0.1, 0.9 font '40'
plot myFile u 1:7 w @style6,

unset multiplot
### End multiplot


print "A gerar ficheiro .png..."
replot
set output
print "Sucesso! Procure o ficheiro '6_quantumstates.png'."

pause 1

