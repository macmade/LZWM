#/bin/bash/

rm *.txt
rm *.lzwm

clear

if [ "$2" ] && [ "$2" -gt 0 ]; then
    
    ./build/bin/lzwm -d -c "test-files/$1" "$1.lzwm"
    
else
    
    ./build/bin/lzwm -c "test-files/$1" "$1.lzwm"
    
fi

if [ "$3" ] && [ "$3" -gt 0 ]; then
    
    ./build/bin/lzwm -d -x "$1.lzwm" "$1"
    
else
    
    ./build/bin/lzwm -x "$1.lzwm" "$1"
    
fi

