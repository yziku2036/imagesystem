gcc -o img_process no22.c -lm 
if [ $# -eq 1 ]; then
    ./img_process in22-$1.txt ans22-$1.txt
    echo "Compile Finished"
else
    echo "Invalid Argument"
fi
