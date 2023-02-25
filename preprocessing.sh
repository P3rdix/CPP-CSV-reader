if [ $# -lt 1 ]
    then
        echo "No arguments provided"
        return 1
else
    if [[ -f $1 && $1 == *.csv ]]
        then
            echo "File exists and is a csv"
            return 0
    elif [[ -f $1 && $1 != *.csv ]]
        then
            echo "File exists and is not a csv"
            return 1
    else
        echo "File does not exist"
        return 1
    fi
fi
