mbrot: Bitmap.cpp main.cpp BitmapFileHeader.h BitmapInfoHeader.h Mandelbrot.h Mandelbrot.cpp Zoom.h ZoomList.h ZoomList.cpp FractalCreator.h FractalCreator.cpp RGB.h RGB.cpp
	g++ -std=c++11 Bitmap.cpp main.cpp Mandelbrot.cpp ZoomList.cpp FractalCreator.cpp RGB.cpp -o mbrot
mbrot_debug: Bitmap.cpp main.cpp
	g++ -std=c++11 -g Bitmap.cpp main.cpp -o mbrot
