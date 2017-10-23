# C. Generate list of shuffled numbers


# echo "Generating list of shuffled numbers"
for power in $(seq 1 3)
  do
    let size=2**$power;
    let number=1000*$size;
    echo "Progress: "$power"/13"
    for p in $(seq -4 3)
      do
        shuffles=$(bc <<< "scale=4;((2^$p)*$number)");
        time_taken=$(echo $(numgen $number -s ${shuffles%.*})|./hw6-quicksort.o -r -s- -b);
        echo $time_taken;
      done
  done