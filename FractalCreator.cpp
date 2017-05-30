#include "FractalCreator.h"
#include <assert.h>
#include <iostream>

FractalCreator::FractalCreator(int width, int height) : _width(width),
                                                        _height(height),
                                                        _histogram(new int[Mandelbrot::MAX_ITERATIONS]{}),
                                                        _fractal(new int[width*height]{}),
                                                        _bitmap(width,height),
                                                        _zoom_list(width,height)
{
    _zoom_list.add( Zoom(width/2, height/2, 4.0/width) );

}

FractalCreator::~FractalCreator() { }

void FractalCreator::calculate_iterations()
{
  // Mandelbrot Escape Algorithm
  for(int i = 0; i < _width; ++i)
    {
      for(int j = 0; j < _height; ++j)
        {
          // Locate x and y coordinate pixels in complex plane
          double x_fractal, y_fractal;
          tie(x_fractal,y_fractal) = _zoom_list.do_zoom(i,j);

          // get number of iterations before escape
          int iterations = Mandelbrot::get_iterations(x_fractal,y_fractal);

          // save number of iterations
          _fractal[j * _width + i] = iterations;

          // build up distirbution of pixels over escape times
          if(iterations < Mandelbrot::MAX_ITERATIONS) ++_histogram[iterations];
        }
    }
}

void FractalCreator::calculate_total_iterations()
{
  for(int i = 0; i <= Mandelbrot::MAX_ITERATIONS; ++i)
    _total += _histogram[i];
}

void FractalCreator::calculate_range_totals()
{
  int range_index = 0;

  for(int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
    {
      int pixels = _histogram[i];

      if(i >= _range_ends[range_index + 1])
        ++range_index;

      _range_totals[range_index] += pixels;
    }
}

void FractalCreator::draw_fractal()
{

  // color pixels
  for(int i = 0; i < _width; ++i)
    {
      for(int j = 0; j < _height; ++j)
        {
          // retrieve escape time
          int iterations = _fractal[j * _width + i];

          // find color range
          int range = get_range(iterations);
          int range_total = _range_totals[range];
          int range_start = _range_ends[range];

          RGB &start_color = _rgbs[range];
          RGB &end_color = _rgbs[range+1];
          RGB color_diff = end_color - start_color;

            _red = 0, _blue = 0, _green = 0;

            if(iterations < Mandelbrot::MAX_ITERATIONS)
              {
                // balance image colors
                int total_pixels = 0;
                for(int k = range_start; k <= iterations; ++k)
                  total_pixels += _histogram[k];

                // set RGB
                _red = start_color.r + color_diff.r * (double) total_pixels / range_total;
                _green = start_color.g + color_diff.g * (double) total_pixels / range_total;
                _blue = start_color.b + color_diff.b * (double) total_pixels / range_total;
              }

          _bitmap.set_pixel(i, j, _red, _green, _blue);
        }
    }
}

void FractalCreator::add_zoom(const Zoom& zoom)
{
    _zoom_list.add( zoom );
}

void FractalCreator::add_range(double range_end, const RGB &rgb)
{
  _range_ends.push_back(range_end*Mandelbrot::MAX_ITERATIONS);
  _rgbs.push_back(rgb);

  if(b_got_first_range)
    _range_totals.push_back(0);
  b_got_first_range = true;
}

void FractalCreator::write_bitmap(string filename)
{
  _bitmap.write( filename );
}

int FractalCreator::get_range(int iterations) const
{
  int range = 0;
  for(int i = 1; i < _range_ends.size(); ++i)
    {
      range = i;

      if(_range_ends[i] > iterations)
        break;
    }
  --range;

  assert(range > -1 && range < _range_ends.size());
  return range;
}

void FractalCreator::run(string name)
{
  calculate_iterations();
  calculate_total_iterations();
  calculate_range_totals();
  draw_fractal();
  write_bitmap("test.bmp");
}
