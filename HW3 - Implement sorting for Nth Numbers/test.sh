#Compile the code
# if the file densemult exits then remove it
clear
if [ -f sort ]; then
    rm sort
fi
g++ -std=c++11 *.cpp -o sort
# if the file densemult does not exit then exit the test
if [ ! -f sort ]; then
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
res1=$(date +%s.%N)
./sort "input=input31.txt;command=command31.txt;output=output31.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.00796
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test case 1 time: $diff"
echo "Desired test case 1 time interval: $desired-$error ~ $desired+$error"

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
    rm -f 1.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 1 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]]; then
      echo -e "Test case 1 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 1 time  \033[1;92mPASSED.\033[0m"
fi


# For test case 2
res1=$(date +%s.%N)
./sort "input=input32.txt;command=command32.txt;output=output32.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.01015
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test case 2 time: $diff"
echo "Desired test case 2 time interval:$desired-$error ~ $desired+$error"
diff -iEBwu ans32.txt output32.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
      echo -e "Test case 2 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 2 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 2 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 3
res1=$(date +%s.%N)
./sort "input=input33.txt;command=command33.txt;output=output33.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.0086
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 3 Time: $diff"
echo "Desired test case 3 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans33.txt output33.txt > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
    rm -f 3.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 3 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 3 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 3 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 4
res1=$(date +%s.%N)
./sort "input=input34.txt;command=command34.txt;output=output34.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.005580
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 4 Time: $diff"
echo "Desired test case 4 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans34.txt output34.txt > 4.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 4    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 4    \033[1;92mPASSED.\033[0m"
    rm -f 4.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 4 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 4 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 4 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 5
res1=$(date +%s.%N)
./sort "input=input35.txt;command=command35.txt;output=output35.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.0075
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 5 Time: $diff"
echo "Desired test case 5 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans35.txt output35.txt > 5.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 5    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 5    \033[1;92mPASSED.\033[0m"
    rm -f 5.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 5 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 5 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 5 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 6
res1=$(date +%s.%N)
./sort "input=input36.txt;command=command36.txt;output=output36.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.006
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 6 Time: $diff"
echo "Desired test case 6 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans36.txt output36.txt > 6.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 6    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 6    \033[1;92mPASSED.\033[0m"
    rm -f 6.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 6 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 6 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 6 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 7
res1=$(date +%s.%N)
./sort "input=input37.txt;command=command37.txt;output=output37.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.0075
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 7 Time: $diff"
echo "Desired test case 7 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans37.txt output37.txt > 4.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 7   \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 7    \033[1;92mPASSED.\033[0m"
    rm -f 7.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 7 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 7 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 7 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 8
res1=$(date +%s.%N)
./sort "input=input38.txt;command=command38.txt;output=output38.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.0048
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 8 Time: $diff"
echo "Desired test case 8 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans38.txt output38.txt > 8.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 8    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 8    \033[1;92mPASSED.\033[0m"
    rm -f 8.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 8 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 8 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 8 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 9
res1=$(date +%s.%N)
./sort "input=input39.txt;command=command39.txt;output=output39.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.0048
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 9 Time: $diff"
echo "Desired test case 9 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans39.txt output39.txt > 9.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 9    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 9    \033[1;92mPASSED.\033[0m"
    rm -f 9.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 9 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 9 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 9 time  \033[1;92mPASSED.\033[0m"
fi

# BLUE='\033[1;34m' 
# GREY='\033[1;30m' 
# GREEN='\033[1;32m' # GREY 
# NC='\033[0m' 

# echo 
# echo -e "${BLUE}Command31.txt: ${NC}"  
# cat command31.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output31.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}" 
# cat ans31.txt 
# echo

# echo 
# echo -e "${BLUE}Command32.txt: ${NC}"  
# cat command32.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output32.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}" 
# cat ans32.txt 
# echo

# echo 
# echo -e "${BLUE}Command33.txt: ${NC}"  
# cat command33.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output33.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}" 
# cat ans33.txt 
# echo

# echo 
# echo -e "${BLUE}Command34.txt: ${NC}"  
# cat command34.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output34.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}" 
# cat ans34.txt 
# echo

# echo
# echo -e "${BLUE}Command35.txt: ${NC}" 
# cat command35.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output35.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}"
# cat ans35.txt 
# echo

# echo
# echo -e "${BLUE}Command36.txt: ${NC}" 
# cat command36.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output36.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}"
# cat ans36.txt 
# echo

# echo
# echo -e "${BLUE}Command37.txt: ${NC}" 
# cat command37.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output37.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}"
# cat ans37.txt 
# echo

# echo
# echo -e "${BLUE}Command38.txt: ${NC}" 
# cat command38.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output38.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}"
# cat ans38.txt 
# echo

# echo
# echo -e "${BLUE}Command39.txt: ${NC}" 
# cat command39.txt 
# echo
# echo -e "${GREY}Your Answer: ${NC}"
# cat output39.txt 
# echo
# echo -e "${GREEN}Correct Answer: ${NC}"
# cat ans39.txt 
# echo