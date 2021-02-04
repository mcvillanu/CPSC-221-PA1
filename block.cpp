#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
  if (this->data.empty()) {
    return 0;
  }
  
  vector<HSLAPixel> arr = this->data[0];
  int size = arr.size();
  return size;
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
  int h = this->height();
  int w = this->width();
  
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      HSLAPixel * pixel = im.getPixel(x+i, j);
      // cout << this->data[i][j].h << endl;
      // cout << this->data[i][j].s << endl;
      // cout << this->data[i][j].l << endl;
      // cout << this->data[i][j].a << endl;


      pixel->h = this->data[i][j].h;
      pixel->s = this->data[i][j].s;
      pixel->l = this->data[i][j].l;
      pixel->a = this->data[i][j].a;
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
  int height = im.height();

  for (int i = 0; i < width; i++) {
    vector<HSLAPixel> vec(height);
    this->data.push_back(vec);

    for (int y = 0; y < height; y++) {
      this->data[i][y]=(*im.getPixel(x+i, y)); 
    }
  }
}
