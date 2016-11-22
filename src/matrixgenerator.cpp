#include "matrixgenerator.h"

using namespace std;

MatrixGenerator::MatrixGenerator(int n, int m) :
  n_(n), m_(m), generator_(n), current_(n), columns_(m) {

  for(int i=0; i < n_; ++i)
    generator_[i] = new GrayCodes(m_);

  generator_[n_-1]->get_next(); // no all-zeros row
  has_next_ = cascade(n_-1); // strictly decreasing

  // if initial matrix is not valid
  if(has_next_ and !is_valid())
    has_next_ = get_next_valid();
}


vector<MatrixGenerator::int_t> MatrixGenerator::get_next() {

  vector<MatrixGenerator::int_t> next = current_;

  has_next_ = get_next_valid(); // now try to get the next valid one

  return next;
}


// auxiliary (private) functions
/**********************************************************************/

bool MatrixGenerator::get_next_valid() {

  while(get_next_potential()) {
    //cout << "columns : "; for(int i=0;i<m_;++i) { cout << columns_[i] << " "; }
    //cout << endl;

    if(is_valid())
      return true;
  }
  return false;
}


bool MatrixGenerator::get_next_potential() {

  for(int i=0; i < n_; ++i)
    if(cascade(i))
      return true;

  return false;
}


bool MatrixGenerator::cascade(int pos) {

  if(!generator_[pos]->has_next())
    return false;

  int next;
  current_[pos] = generator_[pos]->get_next(&next); // +1
  
  // cascade backwards from pos
  for(int i=pos-1; i>= 0; --i) {

    (*generator_[i]) = (*generator_[i+1]);

    if(generator_[i]->has_next())
      current_[i] = generator_[i]->get_next();
    else // we hit the boundary, cannot cascade from pos
      return false;
  }

  // at this point, cascade is successful: update columns_
  columns_[next] ^= 1 << pos; // toggle affected column at pos

  MatrixGenerator::int_t mask;
  for(int i=0; i < pos; ++i) { // update all column content upto pos

    mask = 1;
    for(int j=0; j < m_; ++j) {

      if(current_[i] & mask)
	columns_[j] |= 1 << i; // set to 1
      else
	columns_[j] &= ~(1 << i); // set to 0

      mask <<= 1;
    }
  }

  // return
  return true;
}


bool MatrixGenerator::is_valid() {
  bool valid = true;

  // apply the tests, e.g.,
  // valid = valid and has_some_property();

  return valid;
}
