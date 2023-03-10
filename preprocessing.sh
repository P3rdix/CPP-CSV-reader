if [ $# -lt 1 ]
    then
        echo "No arguments provided"
        exit 1
else
    if [[ -f $1 && $1 == *.csv ]]
        then
            
            return 0
    elif [[ -f $1 && $1 != *.csv ]]
        then
            echo "Wrong file type"
            return 2
    else
        echo "File does not exist"
        return 3
    fi
fi
