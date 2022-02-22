prob_id="$1"
c_file="$2"

echo "------ JudgeGuest ------"
echo "Problem ID: ${prob_id}"
echo "Test on: ${c_file}"
echo "------------------------"

temp=`mktemp -d`

gcc -std=c99 -o ${temp}/a ${c_file} &> /dev/null

if [[ $? != 0 ]]; then
    echo "Compile Error"
    rm -r ${temp}
    exit
fi

for ((i=0; ; i++)); do
    wget --output-document ${temp}/${i}.in --no-check-certificate https://judgegirl.csie.org/downloads/testdata/${prob_id}/${i}.in &> /dev/null
    wget --output-document ${temp}/${i}.out --no-check-certificate https://judgegirl.csie.org/downloads/testdata/${prob_id}/${i}.out &> /dev/null
    if [[ $? != 0 ]]; then
        break
    fi
    timeout --kill-after=1s 1s ${temp}/a < ${temp}/${i}.in > ${temp}/out
    tle=$?
    df=`diff ${temp}/${i}.out ${temp}/out`
    if [[ ${tle} != 0 ]]; then
        echo -e "${i}\tTime Limit Exceeded"
    elif [[ ${df} == "" ]]; then
        echo -e "${i}\tAccepted"
    else
        echo -e "${i}\tWrong Answer"
    fi

done

rm -r ${temp}
