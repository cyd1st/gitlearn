path=$(cd $(dirname $0);pwd)
echo $path


if [ -s $path ]; then
        echo "file $path exist."
fi

if [ -z $path ]; then
        echo "$path is empty."
fi

if [ -n $path ]; then
        echo "string is not empty."
fi
