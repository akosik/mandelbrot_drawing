#include "ZoomList.h"

ZoomList::ZoomList(int width, int height) : _width(width), _height(height) { }

void ZoomList::add(const Zoom& zoom)
{
  zooms.push_back(zoom);

  _xcenter += (zoom.x - _width/2) * _scale;
  _ycenter += -(zoom.y - _height/2) * _scale;

  _scale *= zoom.scale;
}

pair<double, double> ZoomList::do_zoom(int x, int y)
{
  double x_fractal = (x - _width/2 - 200) * _scale + _xcenter;
  double y_fractal = (y - _height/2) * _scale + _ycenter;
  return make_pair(x_fractal,y_fractal);
}
