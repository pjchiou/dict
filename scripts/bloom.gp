reset
set xlabel 'idx'
set ylabel 'time(micro-sec)'
set title 'Search Time'
set term png enhanced font 'Verdana,10'
set output 'Bloom_performance.png'
set xtic

plot './bench_ref.txt' using 1:3 with points title 'bloom',\
'./bench_ref.txt' using 1:4 with lines title 'tst',\


