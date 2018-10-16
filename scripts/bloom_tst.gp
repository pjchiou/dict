reset
set xlabel 'idx'
set ylabel 'time(micro-sec)'
set title 'Search Time'
set term png enhanced font 'Verdana,10'
set output 'Bloom_vs_tst.png'
set xtic

plot './bench_ref.txt' using 1:($4-$3) with points title 'tst-bloom',\

