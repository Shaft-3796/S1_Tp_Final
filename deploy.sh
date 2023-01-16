# shellcheck disable=SC2035
# shellcheck disable=SC2164
cd src/ShootEmUp
gcc -Wall *.c -lm -lSDL2 -lSDL2_image -lSDL2_mixer
./a.out