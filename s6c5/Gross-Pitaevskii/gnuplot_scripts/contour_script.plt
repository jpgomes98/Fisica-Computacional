# set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 600, 400 
# set output 'contours.16.png'

set key at screen 1, 0.9 right top vertical Right noreverse enhanced autotitle nobox
set style textbox opaque 
set view 60, 30, 1, 1.1
set samples 50, 50
set isosamples 26, 26
set dgrid3d
set contour base
set cntrlabel  format '%8.3g' font ',7' start 5 interval 20
set cntrparam order 8
set cntrparam bspline
set style data lines
set title "Gross-Pitaevskii Contourplot" 
set xlabel "X" 
set ylabel "Y" 
set zlabel "|{/Symbol f}|" 
set zlabel  offset character 1, 0, 0 font "" textcolor lt -1 norotate
set zrange [ -1.00000 : 1.00000 ] noreverse nowriteback
DEBUG_TERM_HTIC = 119
DEBUG_TERM_VTIC = 119
splot [-10:10.01] [-10:10.01] "wavefunction_4000.dat" u 1:2:3 w dots

pause -1
