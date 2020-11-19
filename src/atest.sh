


touch out.txt
score=0

var1=0
echo -e  "\n==========\e[33m BASIC TESTS \e[0m==========="



################### BASIC TESTS ###################
./proj < examples/example3.go 1> out.txt 2> temp.txt

if [ "$?" -eq 0 ]; then
  var1=`expr $var1 + 1`
  echo -e "\e[32mOK\e[0m example3.go "
else
  echo -e "\e[31mFAILED\e[0m example3.go "
fi

rm -r temp.txt

./proj < examples/example2.go 1> out.txt 2> temp.txt

if [ "$?" -eq 0 ]; then
  var1=`expr $var1 + 1`
  echo -e "\e[32mOK\e[0m example2.go"
else
  echo -e "\e[31mFAILED\e[0m example2.go "
fi

rm -r temp.txt

./proj < examples/example1.go 1> out.txt 2> temp.txt

if [ "$?" -eq 0 ]; then
  var1=`expr $var1 + 1`
  echo -e "\e[32mOK\e[0m example1.go"
else
  echo -e "\e[31mFAILED\e[0m example1.go"
fi

./proj < examples/hello.go 1> out.txt 2> temp.txt

if [ "$?" -eq 0 ]; then
  var1=`expr $var1 + 1`
  echo -e "\e[32mOK\e[0m hello.go"
else
  echo -e "\e[31mFAILED\e[0m hello.go"
fi

rm -r temp.txt

./proj < examples/input.go 1> out.txt 2> temp.txt

if [ "$?" -eq 0 ]; then
  var1=`expr $var1 + 1`
  echo -e "\e[32mOK\e[0m input.go"
else
  echo -e "\e[31mFAILED\e[0m input.go"
fi

rm -r temp.txt

./proj < examples/scope.go 1> out.txt 2> temp.txt

if [ "$?" -eq 0 ]; then
  var1=`expr $var1 + 1`
  echo -e "\e[32mOK\e[0m scope.go"
else
  echo -e "\e[31mFAILED\e[0m scope.go"
fi

rm -r temp.txt

if [ "$var1" -ne 6 ]; then
  echo "============================"
  echo -e "        \e[33m  $var1/6 PASSED\e[0m"
  echo "============================"
else
  echo "============================"
  echo -e "        \e[32m  $var1/6 OK BASIC TESTS\e[0m"
  echo "============================"
fi

score=$var1
################### END OF BASIC TESTS ###################


echo ""
echo -e "=======\e[33mTESTING CORRECT RETURN VALUE \e[0m========\n"


echo "====RETVAL 1===="

# number of tests in this scope
ok2=0
count=10

################################

for (( i = 0; i < $count; i++ )); do
  FILE=examples/Error_01/1er0$i.go
if ! test -f "$FILE"; then
echo -e "\e[36mTest file 2er0$i.go not found, skipping... \e[0m"
else
  test examples/Error_01/1er0$i.go

  ./proj < examples/Error_01/1er0$i.go 1> out.txt 2> temp.txt
 var2=$?

 if [ "$var2" -eq 1 ]; then

   echo -e "\e[32mOK\e[0m returned--> $var2"
   ok=`expr $ok + 1`

 else
   echo -e "\e[31mFAILED\e[0m returned--> $var2 "
 fi
fi

done
if [[ "$ok" -eq 10 ]]; then
  echo "================"
  echo -e "\e[32m$ok from $count OK\e[0m"
  echo "================"
else
  echo "================"
  echo -e "\e[31m$ok from $count OK\e[0m"
  echo "================"

fi

score=`expr $ok2 + $score`

# Retval 2 down there
# hmmm Im really depresed, life has no meaning, we all die alone
echo ""
echo "====RETVAL 2===="


# number of tests in this scope
ok2=0
count=15

################################

for (( i = 0; i < $count; i++ )); do

  FILE=examples/Error_02/2er$i.go
if ! test -f "$FILE"; then
echo -e "\e[36mTest file 2er0$i.go not found, skipping... \e[0m"
else
  test examples/Error_02/2er$i.go

  ./proj < examples/Error_02/2er$i.go 1> out.txt 2> temp.txt
 var2=$?

 if [ "$var2" -eq 2 ]; then
   echo -e "\e[32mOK\e[0m returned--> $var2"
   ok2=`expr $ok2 + 1`

 else
   echo -e "\e[31mFAILED\e[0m returned--> $var2 "
 fi
fi

done
if [[ "$ok2" -eq 15 ]]; then
  echo "================"
  echo -e "\e[32m$ok2 from $count\e[0m"
  echo "================"
else
  echo "================"
  echo -e "\e[31m$ok2 from $count\e[0m"
  echo "================"

fi

score=`expr $ok2 + $score`

echo ""
echo "====RETVAL 3===="


# number of tests in this scope
ok2=0
count=5

################################

for (( i = 0; i < $count; i++ )); do

  FILE=examples/Error_03/3er$i.go
if ! test -f "$FILE"; then
echo -e "\e[36mTest file 3er0$i.go not found, skipping... \e[0m"
else
  test examples/Error_03/3er$i.go

  ./proj < examples/Error_03/3er$i.go 1> out.txt 2> temp.txt
 var2=$?

 if [ "$var2" -eq 3 ]; then
   echo -e "\e[32mOK\e[0m returned--> $var2"
   ok2=`expr $ok2 + 1`

 else
   echo -e "\e[31mFAILED\e[0m returned--> $var2 "
 fi
fi

done
if [[ "$ok2" -eq "$count" ]]; then
  echo "================"
  echo -e "\e[32m$ok2 from $count\e[0m"
  echo "================"
else
  echo "================"
  echo -e "\e[31m$ok2 from $count\e[0m"
  echo "================"

fi

echo ""
echo "====RETVAL 5===="


# number of tests in this scope
ok2=0
count=10

################################

for (( i = 0; i < $count; i++ )); do

  FILE=examples/Error_05/5er$i.go
if ! test -f "$FILE"; then
echo -e "\e[36mTest file 5er0$i.go not found, skipping... \e[0m"
else
  test examples/Error_05/5er$i.go

  ./proj < examples/Error_05/5er$i.go 1> out.txt 2> temp.txt
 var2=$?

 if [ "$var2" -eq 5 ]; then
   echo -e "\e[32mOK\e[0m returned--> $var2"
   ok2=`expr $ok2 + 1`

 else
   echo -e "\e[31mFAILED\e[0m returned--> $var2 "
 fi
fi

done
if [[ "$ok2" -eq "$count" ]]; then
  echo "================"
  echo -e "\e[32m$ok2 from $count\e[0m"
  echo "================"
else
  echo "================"
  echo -e "\e[31m$ok2 from $count\e[0m"
  echo "================"

fi







score=`expr $ok2 + $score`



if [[ "$1" == "--silent" ]]; then
  echo  -e "SKIPPING out test"
  rm -r temp.txt
  exit
fi

  echo -e  "\n=======\e[33m TESTING OUTPUT TO STDOUT \e[0m========\n"
  if [[ -s out.txt ]]; then
      cat out.txt
      echo  -e "\e[31mFAILED\e[0m some output to STDOUT found"
  else
     echo -e "\e[32mOK\e[0m no output generated.."
fi

echo "=========DONE========="


rm -r temp.txt
