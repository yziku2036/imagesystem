gcc -o img_process  no21.c bmpfile550.o -lm -O3
if [ $# -eq 1 ]; then
    ./img_process in21.bmp in21-$1t.bmp ans21-$1.bmp
    echo "Compile Finished"
else
    echo "Invalid Argument"
fi
