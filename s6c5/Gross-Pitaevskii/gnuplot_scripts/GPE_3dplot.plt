reset

set samples 250
set isosamples 200

set pm3d; 
set palette model XYZ functions gray**0.35, gray**0.5, gray**0.8
#set palette rgbformulae 20,13,10

set cbrange [0:0.02]

i = 0

while( i < (ARG1 + 0)) {
myfile = sprintf('../data/wavefunction_%d.dat',i)
splot [-10:10.01][-10:10.01][0:0.04] myfile u 1:2:3 w pm3d ls 1
#plot 'time_'.t.'.txt' u 1:2:3 w image title 'Gross '.t
i = i + (ARG2 + 0)
pause 0.01
}

