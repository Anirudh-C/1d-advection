unset key
set grid
set terminal gif animate delay 4
set output "fd.gif"
set xrange[0:1]
set yrange[-1:1]

do for [i=0:99] { plot sprintf("fd/fd%d.txt",i) using 1:2 with lines }
