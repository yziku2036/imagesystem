gcc -o img_process no$1.c bmpfile.o -lm
if [ $# -eq 1 ]; then
    ./img_process in$1.bmp ans$1.bmp
    echo "Compile Finished"
elif [ $# -eq 2 ]; then
    ./img_process in$1.bmp ans$1-$2.bmp
    echo "File saved as ans$1-$2.bmp"
else
    echo "Invalid Argument"
fi
