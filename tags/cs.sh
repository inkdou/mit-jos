CMD_CSCOPE=`which cscope`
CMD_CCGLUE=`which ccglue`

rm -f $LOCAL_PATH/cscope.files
cut -f2 $LOCAL_PATH/filenametags > $LOCAL_PATH/cscope.files

$CMD_CSCOPE -b -c -k -i $LOCAL_PATH/cscope.files -f $LOCAL_PATH/cscope.out

echo ":cs kill 0" >> $LOCAL_PATH/db.vim
echo ":cs kill 1" >> $LOCAL_PATH/db.vim
echo ":cs kill 2" >> $LOCAL_PATH/db.vim
echo ":cs reset" >> $LOCAL_PATH/db.vim
echo ":cs add $LOCAL_PATH/cscope.out $LOCAL_PATH" >> $LOCAL_PATH/db.vim

#Only c , the ccglue work ok.
rm -f $LOCAL_PATH/.c.*
while read line;do
    if [[ "${line##*.}" = "c" ]]; then 
        echo $line >> $LOCAL_PATH/.c.cscope.files
    fi
done < $LOCAL_PATH/cscope.files

if [[ -f $LOCAL_PATH/.c.cscope.files ]]; then
    $CMD_CSCOPE -b -c -i $LOCAL_PATH/.c.cscope.files -f $LOCAL_PATH/.c.cscope.out
    $CMD_CCGLUE -S $LOCAL_PATH/.c.cscope.out -o $LOCAL_PATH/cctree.out
    echo ":CCTreeLoadXRefDBFromDisk $LOCAL_PATH/cctree.out" >> $LOCAL_PATH/db.vim
    rm -f $LOCAL_PATH/.c.*
fi
