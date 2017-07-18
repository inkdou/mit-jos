echo "remove all database files"

LOCAL_PATH="/root/Robux/tags"

find $LOCAL_PATH ! -path "*.sh" -type f | xargs rm -f

echo "Create filenametags database"
source $LOCAL_PATH/filenametags.sh 

if [[ -f $LOCAL_PATH/filenametags ]]; then
    echo "Create cscope database"
    source $LOCAL_PATH/cs.sh
fi

if [[ -f $LOCAL_PATH/cscope.files ]]; then
    echo "Create tags database"
    source $LOCAL_PATH/tags.sh
fi
