#!/usr/bin/env bash

DIR=${1:-.}

tests="$(find $DIR/tests -name '*.cpp')"

declare -i pass=0
declare -i fail=0
failTests=""
# ulimit -s 524288
startTime=`date +%s.%N`

for test in $tests; do
  echo "$(basename $test): "
  g++ -Wall -Wfatal-errors -Wconversion -std=c++2a -O2 -o a.out $test && ./a.out
  res=$?
  if (($res != 0)); then
    echo "Failed with $res"
    fail+=1
    failTests="$failTests$(basename $test)\n"
  else
    pass+=1
  fi
  rm -f a.out
  echo
done
endTime=`date +%s.%N`

testingTime=$( echo "$endTime - $startTime" | bc -l )
echo "Testing took $testingTime seconds"

echo "$pass/$(($pass+$fail)) tests passed"
if (($fail==0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failTests"
    exit 1
fi
