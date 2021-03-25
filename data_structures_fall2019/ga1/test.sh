#Compile the code
# if the file densemult exits then remove it
g=0;
if [ -f ga1 ]; then
    rm ga1
fi
g++ -std=c++11 *.cpp -o ga1
# if the file densemult does not exit then exit the test
if [ ! -f ga1 ]; then
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
./ga1 "input=input11.txt;command=command11.txt;output=output11.txt" 1>1.stdcout 2>1.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu ans11.txt output11.txt > 1.diff
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
./ga1 "input=input12.txt;command=command12.txt;output=output12.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans12.txt output12.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
	g=$[$g+10]
fi
# For test case 3
./ga1 "input=input13.txt;command=command13.txt;output=output13.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans13.txt output13.txt > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
	g=$[$g+10]
    rm -f 3.diff
fi
# For test case 4
./ga1 "input=input14.txt;command=command14.txt;output=output14.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans14.txt output14.txt > 4.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 4    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 4    \033[1;92mPASSED.\033[0m"
    rm -f 4.diff
	g=$[$g + 10]
fi

./ga1 "input=input15.txt;command=command15.txt;output=output15.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans15.txt output15.txt > 5.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 5    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 5    \033[1;92mPASSED.\033[0m"
    rm -f 5.diff
	g=$[$g+10]
fi
./ga1 "input=input16.txt;command=command16.txt;output=output16.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans16.txt output16.txt > 6.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 6    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 6    \033[1;92mPASSED.\033[0m"
    rm -f 6.diff
	g=$[$g + 10]
fi
./ga1 "input=input17.txt;command=command17.txt;output=output17.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans17.txt output17.txt > 7.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 7    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 7    \033[1;92mPASSED.\033[0m"
    rm -f 7.diff
	g=$[$g + 10]
fi

./ga1 "input=input18.txt;command=command18.txt;output=output18.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans18.txt output18.txt > 8.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 8    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 8    \033[1;92mPASSED.\033[0m"
    rm -f 8.diff
	g=$[$g + 10]
fi
./ga1 "input=input19.txt;command=command19.txt;output=output19.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans19.txt output19.txt > 9.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 9    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 9    \033[1;92mPASSED.\033[0m"
    rm -f 9.diff
	g=$[$g + 10]
fi
./ga1 "input=input20.txt;command=command20.txt;output=output20.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans20.txt output20.txt > 10.diff
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
echo -e "\033[1;31mWARNING! These test cases were done partially by hand so if you have any issues with them, aside for input and command16's empty lines (intentional), please let Shehzad know.\033[0m"