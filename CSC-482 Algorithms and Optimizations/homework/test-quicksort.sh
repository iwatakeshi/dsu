touch quicksort-times.txt

# A.1 Time Quicksort (Random)
total_time=0
title="Timing Quicksort (Random)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
    let size=2**$power;
    let number=1000*$size;
    time_taken=$(./numgen.o $number -r | ./hw6-quicksort.o --silent --benchmark)
    echo -e "N:" $number, "\t"$time_taken >> quicksort-times.txt;
    echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
    total_time=$(bc <<< "scale=10;$total_time+$time_taken")
  done
done

# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt

# A.2 Time Quicksort (Random, Random)
total_time=0
title="Timing Quicksort (Random, Random)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
    let size=2**$power;
    let number=1000*$size;
    time_taken=$(./numgen.o $number -r | ./hw6-quicksort.o --random --silent --benchmark)
    echo -e "N:" $number, "\t"$time_taken >> quicksort-times.txt;
    echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
    total_time=$(bc <<< "scale=10;$total_time+$time_taken")
  done
done

# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt


# B.1.1 Time Quicksort (Ascending)
total_time=0
title="Timing Quicksort (Ascending)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
    let size=2**$power;
    let number=1000*$size;
    time_taken=$(./numgen.o $number -l | ./hw6-quicksort.o --silent --benchmark)
    echo -e "N:" $number, "\t"$time_taken >> quicksort-times.txt;
    echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
    total_time=$(bc <<< "scale=10;$total_time+$time_taken")
  done
done

# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt

# B.1.2 Time Quicksort (Ascending, Random)
total_time=0
title="Timing Quicksort (Ascending, Random)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
    let size=2**$power;
    let number=1000*$size;
    time_taken=$(./numgen.o $number -l | ./hw6-quicksort.o --random --silent --benchmark)
    echo -e "N:" $number, "\t"$time_taken >> quicksort-times.txt;
    echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
    total_time=$(bc <<< "scale=10;$total_time+$time_taken")
  done
done

# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt

# B.2.1 Time Quicksort (Descending)
total_time=0
title="Timing Quicksort (Descending)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
    let size=2**$power;
    let number=1000*$size;
    time_taken=$(./numgen.o $number -ld | ./hw6-quicksort.o --silent --benchmark)
    echo -e "N:" $number, "\t"$time_taken >> quicksort-times.txt;
     echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
    total_time=$(bc <<< "scale=10;$total_time+$time_taken")
  done
done

# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt

# B.2.2 Time Quicksort (Descending, Random)
total_time=0
title="Timing Quicksort (Descending, Random)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
    let size=2**$power;
    let number=1000*$size;
    time_taken=$(./numgen.o $number -ld | ./hw6-quicksort.o --random --silent --benchmark)
    echo -e "N:" $number, "\t"$time_taken >> quicksort-times.txt;
    echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
    total_time=$(bc <<< "scale=10;$total_time+$time_taken")
  done
done

# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt

# C.1 Time Quicksort (Shuffled)
total_time=0
title="Timing Quicksort (Shuffled)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
      let size=2**$power;
      let number=1000*$size;
      for p in $(seq -4 3); do
          shuffles=$(bc <<< "scale=4;((2^$p)*$number)");
          time_taken=$(./numgen.o $number -s ${shuffles%.*} | ./hw6-quicksort.o --silent --benchmark);
          echo -e "N:" $number, "\tS:" ${shuffles%.*}, "\t"$time_taken >> quicksort-times.txt;
          echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
          total_time=$(bc <<< "scale=10;$total_time+$time_taken")
        done
    done
done

# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt

# C.2 Time Quicksort (Shuffled, Random)
total_time=0
title="Timing Quicksort (Shuffled, Random)"
echo $title
echo $title >> quicksort-times.txt
for trial in $(seq 1 10); do
  echo "Trial "$trial;
  echo "Trial "$trial >> quicksort-times.txt;
  for power in $(seq 1 8); do
      let size=2**$power;
      let number=1000*$size;
      for p in $(seq -4 3); do
          shuffles=$(bc <<< "scale=4;((2^$p)*$number)");
          time_taken=$(./numgen.o $number -s ${shuffles%.*} | ./hw6-quicksort.o --random --silent --benchmark);
          echo -e "N:" $number, "\tS:" ${shuffles%.*}, "\t"$time_taken >> quicksort-times.txt;
          echo -e "N:" $number, "\ttime" $time_taken "\ttotal time" $total_time;
          total_time=$(bc <<< "scale=10;$total_time+$time_taken")
        done
    done
done
# Output total time and average time
echo "Total time: "$total_time >> quicksort-times.txt
avg_time=$(bc <<< "scale=10;$total_time/10")
echo "Average time: "$avg_time >> quicksort-times.txt