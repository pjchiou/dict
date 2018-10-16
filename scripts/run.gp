reset
set xlabel 'Count'
set ylabel 'time(sec)'
set title 'count vs. time'
set term png enhanced font 'Verdana,10'
set output 'CountTime.png'
set xtic 10
set xtics rotate by 45 right

plot [:100][:100] './analysis/sort.txt' using 2:4 with points title 'analysis',\




