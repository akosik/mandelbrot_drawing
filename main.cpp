#include "FractalCreator.h"
#include "RGB.h"
#include "Zoom.h"
#include <iostream>

using namespace std;

int main()
{
  FractalCreator fractal_creator(800,600);

  fractal_creator.add_range(0.0, RGB(255,127,80));
  fractal_creator.add_range(.0002, RGB(230,230,50));
  fractal_creator.add_range(.0003, RGB(216,191,216));
  fractal_creator.add_range(.0004, RGB(181,216,218));
  fractal_creator.add_range(.0005, RGB(113,174,179));
  fractal_creator.add_range(1.0, RGB(87,103,129));

  fractal_creator.add_zoom( Zoom(295, 202, .1) );
  fractal_creator.add_zoom( Zoom(312, 304, .1) );

  fractal_creator.run("test.bmp");

  cout << "Finished writing bitmap file." << endl;
  return 0;
}
