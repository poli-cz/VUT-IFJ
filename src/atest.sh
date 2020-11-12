
var1=0
touch temp.txt


echo -e  "=======\e[32m BASIC TESTS \e[0m========\n"
echo ""
echo "Testing files example1/2/3..."

./proj < examples/example3.go 2> temp.txt

if [ "$?" -eq 0 ]; then
var1=`expr $var1 + 1`
fi

rm -r temp.txt

./proj < examples/example2.go 2> temp.txt

if [ "$?" -eq 0 ]; then
var1=`expr $var1 + 1`
fi

rm -r temp.txt

./proj < examples/example1.go 2> temp.txt

if [ "$?" -eq 0 ]; then
var1=`expr $var1 + 1`
fi

./proj < examples/hello.go 2> temp.txt

if [ "$?" -eq 0 ]; then
var1=`expr $var1 + 1`
fi

rm -r temp.txt

./proj < examples/input.go 2> temp.txt

if [ "$?" -eq 0 ]; then
var1=`expr $var1 + 1`
fi

rm -r temp.txt

./proj < examples/scope.go 2> temp.txt

if [ "$?" -eq 0 ]; then
var1=`expr $var1 + 1`
fi

rm -r temp.txt

echo "============================"
if [ "$var1" -ne 6 ]; then
  echo -e "\e[31m some test not passed\e[0m"
fi

echo "============================"
echo -e " \e[32m  $var1/6 OK BASIC TESTS\e[0m"
echo "============================"
echo ""
echo -e "\e[33mTESTING CORRECT RETURN VALUE \e[0m"


echo "=========RETVAL 1========="




for (( i = 0; i < 10; i++ )); do

  FILE=examples/Error_01/1er0$i.go
if ! test -f "$FILE"; then
echo -e "\e[36mTest file 2er0$i.go not found, skipping... \e[0m"
else
  test examples/Error_01/1er0$i.go

  ./proj < examples/Error_01/1er0$i.go 2> temp.txt
 var2=$?

 if [ "$var2" -eq 1 ]; then
   echo -e "\e[32mOK\e[0m returned--> $var2"
 else
   echo -e "\e[31mFAILED\e[0m returned--> $var2 "
 fi
fi

done


echo ""
echo "=========RETVAL 2========="


for (( i = 0; i < 10; i++ )); do

  FILE=examples/Error_02/2er0$i.go
if ! test -f "$FILE"; then
echo -e "\e[36mTest file 2er0$i.go not found, skipping... \e[0m"
else
  test examples/Error_02/2er0$i.go

  ./proj < examples/Error_02/2er0$i.go 2> temp.txt
 var2=$?

 if [ "$var2" -eq 2 ]; then
   echo -e "\e[32mOK\e[0m returned--> $var2"
 else
   echo -e "\e[31mFAILED\e[0m returned--> $var2 "
 fi
fi

done


rm -r temp.txt
rm -r 1
