# A. Generate list of random numbers
for power in $(seq 1 13)
  do
      let size=2**$power
      let number = 1000*$size
      if (($number < 10000000))
      then
        ./numgen.o $number -r >> $size"KRandomInts".txt;
      else
        ./numgen.o $number -r >> $size"MRandomInts".txt;
  done

# B.1 Generate list of ascending numbers
for power in $(seq 1 13)
  do
      let size=2**$power
      let number = 1000*$size
      if (($number < 10000000))
      then
        ./numgen.o $number -l >> $size"KAscendingInts".txt;
      else
        ./numgen.o $number -l >> $size"MAscendingInts".txt;
  done

# B.2 Generate list of descending numbers
for power in $(seq 1 13)
  do
      let size=2**$power
      let number = 1000*$size
      if (($number < 10000000))
      then
        ./numgen.o $number -ld >> $size"KDescendingInts".txt;
      else
        ./numgen.o $number -ld >> $size"MDescendingInts".txt;
  done

# C. Generate list of shuffled numbers

for power in $(seq 1 13)
  do
    let size=2**$power;
    let number=1000*$size;
    for p in $(seq -4 13)
      do
        shuffles=$(bc <<< "scale=4;2^$p");
        if (($number < 10000000))
        then
          ./numgen.o $number -s $shuffles >> $size"KShuffledInts".txt;
        else
          ./numgen.o $number -s $shuffles >> $size"MShuffledInts".txt;
      done
  done