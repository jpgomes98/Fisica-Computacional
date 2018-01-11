
#set view map
#set ylabel norotate offset 0,1

#set contour base
#set dgrid3d
#set pm3d
i = 0


set pm3d interpolate 0,0
set cbrange [0:0.02]

while( i < (ARG1 + 0)) {
#splot 'time_'.t.'.txt' using 1:2:3 w l title 'Gross '.t
plot '../data/wavefunction_'.i.'.dat' u 1:2:3 w image title 'Gross-Pitaevskii'.i
i = i + (ARG2 + 0)
pause 0.05
}

#pause -1


