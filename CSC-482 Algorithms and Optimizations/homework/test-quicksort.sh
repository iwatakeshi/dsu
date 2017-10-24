# C. Generate list of shuffled numbers

# echo "Generating list of shuffled numbers"
touch quicksort-shuffled-times.txt
for power in $(seq 1 13)
  do
    let size=2**$power;
    let number=1000*$size;
    echo "Progress: "$power"/13"
    for p in $(seq -4 3)
      do
        shuffles=$(bc <<< "scale=4;((2^$p)*$number)");
        time_taken=$(./numgen.o $number --shuffle ${shuffles%.*} | ./hw6-quicksort.o --silent --benchmark);
        echo -e "N:" $number, "\tS:" ${shuffles%.*}, "\t"$time_taken >> quicksort-shuffled-times.txt;
      done
  done