set xlabel "Time"
set ylabel "Position"
set title "Position over time"
set grid
set autoscale
set style data lines
set key off

file = "data.txt"

plot file using 1:2, \
	 file using 1:4, \
	 file using 1:6, \
	 file using 1:8, \
	 file using 1:10, \
	 file using 1:12, \
	 file using 1:14, \
	 file using 1:16, \
	 file using 1:18
	 
	 

