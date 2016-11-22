#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include <vector>
#include "graycodes.h"

/* A class to generate all nxm binary matrices in a smart way.  Based
 * for the most part on Gray codes.
 */
class MatrixGenerator {

 public :

  typedef GrayCodes::int_t int_t;

  // constructor
  MatrixGenerator(int n, int m);

  // true if generator has another matrix, o.w., false
  bool has_next() { return has_next_; }

  // get next nxm marix
  std::vector<int_t> get_next();

 private :

  int n_;
  int m_;

  std::vector<GrayCodes *> generator_;
  std::vector<int_t> current_;
  std::vector<int_t> columns_; // column representation of current_

  bool has_next_; // generator has another matrix

  /* attempt to increment row pos by 1, and then cascade backwards
   * from pos, to ensure that rows are strictly decreasing to pos.
   * Return false if this is not possible
   */
  bool cascade(int pos);

};

#endif
