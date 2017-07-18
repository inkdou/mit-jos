SRC_DIRS="/root/Robux"

if [[ "$SRC_DIRS" = "" ]]; then
    echo "Please set SRC_DIRS!"
    return ; 
fi

find $SRC_DIRS -regex '.*\.\(c\|cpp\|java\|h\)' ! -path "*svn*" -type f -printf "%f	%p	1\n" | sort -f > $LOCAL_PATH/filenametags

echo "let g:LookupFile_TagExpr=string('$LOCAL_PATH/filenametags')"  >> $LOCAL_PATH/db.vim
