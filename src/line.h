#ifndef __line__
#define __line__

/*

point
  ^
  |
line
  
*/

#include "point.h"
#include <cstdio>

class line: public point {

 protected:

  point uvector; // versor
  
 public:

  line();
  line(const point& , const point&);
  ~line() {
    printf("[%s] \n", __PRETTY_FUNCTION__);    
  };

  friend ostream& operator<<(ostream&, const line&);
  
};

#endif
