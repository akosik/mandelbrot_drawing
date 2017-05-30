#ifndef BITMAP_H_
#define BITMAP_H_

#include <cstdint>
#include <string>

using namespace std;

class Bitmap
{
 private:
  int _width{0};
  int _height{0};
  unique_ptr<uint8_t[]> _pixels{nullptr};

 public:
  Bitmap(int width, int height);
  bool write(string filename);
  void set_pixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
  virtual ~Bitmap();
};

#endif
