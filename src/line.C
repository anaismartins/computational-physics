#include "line.h"
#include <cstdio>
#include <cmath>

line::line() : uvector(point(0,0)) {
  printf("[%s] \n", __PRETTY_FUNCTION__);
}

line::line(const point& P1, const point& P2) : point(P1), uvector(P2) {
  printf("[%s] \n", __PRETTY_FUNCTION__);
  if ( fabs(!uvector - 1.) > 0.001 )
    uvector /= !uvector;
}

// ============= operators

ostream& operator<<(ostream& s, const line& L) {
  s << "point=[" << point(L.coo[0], L.coo[1]) << "] " << "uvector=[" << L.uvector;
  //  s << "point=[" << *(point*)&L << "] " << "uvector=[" << L.uvector; 
  /*
    s << "point=[" << L.coo[0] << " , " << L.coo[1] << "] " 
    << "uvector=[" << L.uvector[0] << " , " << L.uvector[1] << "]";
  */
  return s;
}
