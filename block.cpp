#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
  return this->data[0].size();
}

int Block::width() const {
  /* your code here */
  return this->data.size();
}

/**
   * Renders the given block onto img with its upper
   * left corner at (x, 0). Assumes block fits on the 
   * image.
   */
void Block::render(PNG &im, int x) const {
  /* your code here */
  unsigned int height = im.height();
  unsigned int width = im.width();

  for (int i = 0; i < this->width(); i++){
    for (int j = 0; j < this->height(); j++){
      *im.getPixel(x+i, j) = this->data[i][j];
    }
  }

}


/** 
   * Creates a block that is width X img.height pixels in size
   * by copying the pixels from (x, 0) to (x+width-1, img.height-1)
   * in img. Assumes img is large enough to supply these pixels.
   */
void Block::build(PNG &im, int x, int width) {
  /* your code here */
  unsigned int height = im.height();

  for (int i = x; x < width; x++) {
    for (int y = 0; y < height; y++) {
      this->data[i].push_back(*im.getPixel(i, y)); 
    }
  }
}
