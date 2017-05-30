#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint>

#pragma pack(2)
struct BitmapFileHeader
{
  char header[2]{ 'B', 'M' };
  int32_t file_size;
  int32_t reserved{0};
  int32_t data_offset;
};

#pragma pack()
#endif
