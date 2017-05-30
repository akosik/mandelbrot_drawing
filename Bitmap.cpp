#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <fstream>

Bitmap::Bitmap(int width, int height) : _width(width), _height(height), _pixels(new uint8_t[width * height * 3]{}) { }

void Bitmap::set_pixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t *pixel = _pixels.get();

  pixel += 3 * y * _width + 3 * x;

  pixel[0] = blue;
  pixel[1] = green;
  pixel[2] = red;
}

bool Bitmap::write(string filename)
{
  BitmapFileHeader file_header;
  BitmapInfoHeader info_header;

  file_header.file_size = sizeof(BitmapInfoHeader) + sizeof(BitmapFileHeader) + _width * _height * 3;
  file_header.data_offset = sizeof(BitmapInfoHeader) + sizeof(BitmapFileHeader);

  info_header.width = _width;
  info_header.height = _height;

  std::ofstream outfile(filename, ios::out | ios::binary);
  if(!outfile) { return false; }
  outfile.write((char *)(&file_header), sizeof(file_header));
  outfile.write((char *)(&info_header), sizeof(info_header));
  outfile.write((char *)(_pixels.get()), _width * _height * 3);
  outfile.close();
  return true;
}

Bitmap::~Bitmap() { }
