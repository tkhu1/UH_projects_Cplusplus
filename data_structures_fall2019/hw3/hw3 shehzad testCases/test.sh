#Compile the code
# if the file densemult exits then remove it
g=0;
if [ -f calculate ]; then
    rm calculate
fi
g++ -std=c++11 *.cpp -o calculate
# if the file densemult does not exit then exit the test
if [ ! -f calculate ]; then
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
./calculate "input=input31.txt;output=output31.txt" 1>1.stdcout 2>1.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu ans31.txt output31.txt > 1.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
if [ $? -ne 0 ]; then
    # display "test case 1 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    echo -e "Test case 1    \033[1;91mFAILED.\033[0m"
else
    # display "test case 1 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    echo -e "Test case 1    \033[1;92mPASSED.\033[0m"
    # remove the file 1.diff
	g=$[$g+10]
    rm -f 1.diff
fi
# For test case 2
./calculate "input=input32.txt;output=output32.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans32.txt output32.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
	g=$[$g+10]
fi
# For test case 3
./calculate "input=input33.txt;output=output33.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans33.txt output33.txt > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
	g=$[$g+10]
    rm -f 3.diff
fi
# For test case 4
./calculate "input=input34.txt;output=output34.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans34.txt output34.txt > 4.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 4    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 4    \033[1;92mPASSED.\033[0m"
    rm -f 4.diff
	g=$[$g + 10]
fi

./calculate "input=input35.txt;output=output35.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans35.txt output35.txt > 5.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 5    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 5    \033[1;92mPASSED.\033[0m"
    rm -f 5.diff
	g=$[$g+10]
fi
./calculate "input=input36.txt;output=output36.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans36.txt output36.txt > 6.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 6    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 6    \033[1;92mPASSED.\033[0m"
    rm -f 6.diff
	g=$[$g + 10]
fi
./calculate "input=input37.txt;output=output37.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans37.txt output37.txt > 7.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 7    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 7    \033[1;92mPASSED.\033[0m"
    rm -f 7.diff
	g=$[$g + 10]
fi

./calculate "input=input38.txt;output=output38.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans38.txt output38.txt > 8.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 8    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 8    \033[1;92mPASSED.\033[0m"
    rm -f 8.diff
	g=$[$g + 10]
fi
./calculate "input=input39.txt;output=output39.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans39.txt output39.txt > 9.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 9    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 9    \033[1;92mPASSED.\033[0m"
    rm -f 9.diff
	g=$[$g + 10]
fi
./calculate "input=input40.txt;output=output40.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans40.txt output40.txt > 10.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 10    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 10    \033[1;92mPASSED.\033[0m"
    rm -f 10.diff
g=$[$g+10]
fi
if [ $g -eq 100 ]; then 
echo -e "\033[1;32mCongradulations! You passed all the test cases!\033[0m";
else 
C_RED="\033[1;31m"
echo -e "${C_RED}Your Grade is a $g.\033[0m"
fi
echo -e "\033[1;31mWARNING! PLEASE READ! These test cases were done partially by hand. So, if you have any issues with them, please let Shehzad know.\033[0m"