#Compile the code
# if the file densemult exits then remove it
if [ -f btree ]; then
    rm btree
fi
g++ -std=c++11 *.cpp -o btree
# if the file densemult does not exit then exit the test
if [ ! -f btree ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
if [ -f *.out ]; then
    rm *.out
fi
if [ -f *.stderr ]; then
    rm *.stderr
fi
if [ -f *.stdcout ]; then
    rm *.stdcout
fi
#rm *.out *.stderr *.stdcout
# For test case 1
# input 1.txt and output 1.out
./btree "input=input41.txt;output=output41.txt;command=command41.txt" 1>1.stdcout 2>1.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu answ41.txt output41.txt > 1.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
if [ $? -ne 0 ]; then
    # display "test case 1 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    echo -e "Test case 1    \033[1;91mFAILED.\033[0m"
else
    # display "test case 1 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    echo -e "Test case 1    \033[1;92mPASSED.\033[0m"
    # remove the file 1.diff
    rm -f 1.diff
fi
# For test case 2
./btree "input=input42.txt;output=output42.txt;command=command42.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ42.txt output42.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
fi
# For test case 3
./btree "input=input43.txt;output=output43.txt;command=command43.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ43.txt output43.txt > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
    rm -f 3.diff
fi
# For test case 4
./btree "input=input44.txt;output=output44.txt;command=command44.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ44.txt output44.txt > 4.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 4    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 4    \033[1;92mPASSED.\033[0m"
    rm -f 4.diff
fi
# For test case 5
./btree "input=input45.txt;output=output45.txt;command=command45.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ45.txt output45.txt > 5.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 5    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 5    \033[1;92mPASSED.\033[0m"
    rm -f 5.diff
fi
# For test case 6
./btree "input=input46.txt;output=output46.txt;command=command46.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ46.txt output46.txt > 6.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 6    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 6    \033[1;92mPASSED.\033[0m"
    rm -f 6.diff
fi
# For test case 7
./btree "input=input47.txt;output=output47.txt;command=command47.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ47.txt output47.txt > 7.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 7    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 7    \033[1;92mPASSED.\033[0m"
    rm -f 7.diff
fi
# For test case 8
./btree "input=input48.txt;output=output48.txt;command=command48.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ48.txt output48.txt > 8.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 8    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 8    \033[1;92mPASSED.\033[0m"
    rm -f 8.diff
fi
# For test case 9
./btree "input=input49.txt;output=output49.txt;command=command49.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu answ49.txt output49.txt > 9.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 9    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 9    \033[1;92mPASSED.\033[0m"
    rm -f 9.diff
fi