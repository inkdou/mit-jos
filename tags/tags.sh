CMD_CTAGS=`which ctags`

$CMD_CTAGS -I __THROW --c++-kinds=+p --fields=+ialS --extra=+q -L $LOCAL_PATH/cscope.files -o $LOCAL_PATH/tags

echo "set tags+=$LOCAL_PATH/tags" >> $LOCAL_PATH/db.vim
