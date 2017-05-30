#ifndef MANDELBROT_H_
#define MANDELBROT_H_

class Mandelbrot
{
public:
  static const int MAX_ITERATIONS = 100000;

  Mandelbrot();
  virtual ~Mandelbrot();
  static int get_iterations(double , double y);
};

#endif
