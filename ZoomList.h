#ifndef ZOOMLIST_H_
#define ZOOMLIST_H_

#include "Zoom.h"
#include <vector>
#include <utility>

using namespace std;

class ZoomList
{
 private:
  double _xcenter{0};
  double _ycenter{0};
  double _scale{1};

  int _width{0};
  int _height{0};
  vector<Zoom> zooms;

 public:
  ZoomList(int width, int height);
  void add(const Zoom& zoom);
  pair<double, double> do_zoom(int x, int y);
};

#endif
