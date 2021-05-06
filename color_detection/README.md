cd accessing_pixel

mkdir build

cmake -S . -B ./build

cd build

make

./change_to_gray ../input_image/chicken.jpg
