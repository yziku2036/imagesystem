gcc -o img_process  no21-$1.c bmpfile550.o -lm
if [ $# -eq 1 ]; then
    ./img_process in21.bmp in21-$1t.bmp ans21-$1hoge.bmp > out.txt
    echo "Compile Finished"
else
    echo "Invalid Argument"
fi
