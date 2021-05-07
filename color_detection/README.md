cd color_detection

mkdir build

cmake -S . -B ./build

cd build

make

Ex: 

./color_detection -f=../newconfig.yml -i=../images/car2.jpg

If yml already exist and want to use new parameter to detect color

./color_detection -f=path/existed/yml/file -t

By default: -i=../images/car.jpg -f=../configcolor.yml
