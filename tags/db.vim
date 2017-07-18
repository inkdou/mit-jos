let g:LookupFile_TagExpr=string('/root/Robux/tags/filenametags')
:cs kill 0
:cs kill 1
:cs kill 2
:cs reset
:cs add /root/Robux/tags/cscope.out /root/Robux/tags
:CCTreeLoadXRefDBFromDisk /root/Robux/tags/cctree.out
set tags+=/root/Robux/tags/tags
