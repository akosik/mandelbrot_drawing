#ifndef RGB_H_
#define RGB_H_

struct RGB
{
  double r, g, b;

  RGB(double r, double g, double b);
};

RGB operator-(const RGB &first, const RGB &second);

#endif
