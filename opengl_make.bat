ld -r -b binary -o gui0.data.o gui0.data
ld -r -b binary -o numbers.data.o numbers.data
gcc -std=c11 opengl.c numbers.data.o gui0.data.o -Wall -lopengl32 -lglu32 -lglut32 -lcomdlg32 -Wl,-subsystem,windows -o vgamapedit
del numbers.data.o
del gui0.data.o
pause