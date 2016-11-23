#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include <vector>
#include "graycodes.h"
#include "connected.h"

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


  // auxiliary (private) functions
  /**********************************************************************/

 private :

  /* move current matrix forward to the next valid matrix (by looping
   * through potentials), returning false should no such matrix exist
   */
  bool get_next_valid();

  /* move the current matrix forward to the next potential matrix (one
   * that can only be invalid), returning false should no such matrix
   * exist
   */
  bool get_next_potential();

  /* attempt to increment row pos by 1, and then cascade backwards
   * from pos, to ensure that rows are strictly decreasing to pos.
   * Return false if this is not possible.  Update columns_ upon
   * success.
   */
  bool cascade(int pos);

  // what it means for the current matrix to be valid
  bool is_valid();

  /* the tests for validity -- current matrix has:
   *   (a) no zero column,
   *   (b) no column with exactly one 1 and
   *   (c) no pair of identical columns
   *   (d) a single connected component (i.e., is connected)
   */
  bool no_zero(); // (a)
  bool no_one(); // (b)
  bool no_duplicate(); // (c)
  bool is_connected(); // (d)

};

#endif
