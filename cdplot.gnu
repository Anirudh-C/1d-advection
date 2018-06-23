unset key
set grid
set terminal gif animate delay 4
set output "cd.gif"
set xrange[0:1]
set yrange[-3:3]

do for [i=0:199] { plot sprintf("cd/cd%d.txt",i) using 1:2 with lines }
