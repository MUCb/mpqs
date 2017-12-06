#!/bin/sh
#find ./  -not -path "./\/*" -not -path "./qsdk\/staging_dir\/*" \( -name '*.c' -o -name '*.h' -o -name '*.sh' \) > cscope.files
#find ./library/ ./include/ ./tests/ \( -name '*.c' -o -name '*.h' -o -name '*.cpp' \) 
#find ./ -path "./*" -prune -o \( -name '*.c' -o -name '*.h' -o -name '*.cpp' \) 
find ./  \( -name '*.c' -o -name '*.h' -o -name '*.cpp' \) > ./cscope.files

cscope -Rb -q -k
