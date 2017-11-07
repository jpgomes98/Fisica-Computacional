
#Inicialização do script

set terminal wxt size 700,700
set size 1, 1.5
set macros

#Ficheiros disponíveis

FC_s4c3 = "'iteradas_w.dat'"

#Estilos e títulos

style1 = "impulses lt 4 lw 3 title \"iter = f(w)\""
#style2 = "lines lt 3 lw 2 title \"\""
#style3 = "lines lt 2 lw 2 title \"\""

#Ranges
#range2_6 = "using 2:6"
#range2_10 = "using 2:10"
#range1_4 = "using 1:4"
#range3_4 = "using 3:4"
range_normal = "using 1:2"

Alabels = "set xlabel 't'; set ylabel 'd'"
Blabels = "set xlabel 't'; set ylabel '|v|'"
Clabels = "set xlabel 'x'; set ylabel 'y'"
Dlabels = "set xlabel 'w'; set ylabel 'Iteradas'"

#Ticks in the axels

#ntics = 4

#stats @FC_2b using 3 name 'x' nooutput
#stats @FC_2b using 2 name 't' nooutput


### Start multiplot (1x2 layout)
set multiplot layout 1,1 rowsfirst

# --- GRAPH iter = f(w) 1
@Dlabels
set label 1 'Ex.s4c3' at graph 0.60,0.7 font ',15'
plot @FC_s4c3 @range_normal with @style1

# --- GRAPH ro
#@Alabels
#set label 1 'A' at graph 0.92,0.9 font ',8'
#set xtics t_max/ntics
#plot @FC_2b @range2_6 with @style1
# --- GRAPH v
#@Blabels
#set label 1 'B' at graph 0.92,0.9 font ',8'
#set xtics t_max/ntics
#plot @FC_2b @range2_10 with @style2
# --- GRAPH traj
#unset xtics
#@Clabels
#set mxtics 
#set label 1 'C' at graph 0.92,0.9 font ',8'
#plot @FC_2b @range3_4 with @style3


unset multiplot
### End multiplot

#plot "dados_2a.txt" @range1 with @style1

#pause -1
pause mouse button3,keypress
