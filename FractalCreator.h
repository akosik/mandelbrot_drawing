#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include "Bitmap.h"
#include "ZoomList.h"
#include "Mandelbrot.h"
#include "RGB.h"
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class FractalCreator
{
 private:
  int _width{0},
    _height{0};
    double _min{999999},
    _max = {-999999};
  uint8_t _color,
    _red,
    _green,
    _blue;
  int _total{0};

  unique_ptr<int[]> _histogram{nullptr};
  unique_ptr<int[]> _fractal{nullptr};
  Bitmap _bitmap;
  ZoomList _zoom_list;
  vector<int> _range_ends;
  vector<RGB> _rgbs;
  vector<int> _range_totals;
  bool b_got_first_range{false};

  void calculate_iterations();
  void calculate_total_iterations();
  void calculate_range_totals();
  void draw_fractal();
  void write_bitmap(string filename);
  int get_range(int iterations) const;

 public:
  FractalCreator(int width, int height);
  virtual ~FractalCreator();
  void add_zoom(const Zoom& zoom);
  void add_range(double range_end, const RGB &rgb);
  void run(string name);
};
#endif
