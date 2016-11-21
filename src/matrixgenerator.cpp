#include "matrixgenerator.h"

using namespace std;

MatrixGenerator::MatrixGenerator(int n, int m) :
  n_(n), m_(m), generator_(n), current_(n) {

  for(int i=0; i< n_; ++i)
    generator_[i] = new GrayCodes(m_);

  generator_[n_-1]->get_next(); // no all-zeros row
  has_next_ = cascade(n_-1);
}


vector<MatrixGenerator::int_t> MatrixGenerator::get_next() {

  vector<MatrixGenerator::int_t> next = current_;

  // now try to get the next next one, updating has_next_ accordingly
  for(int i=0; i< n_; ++i) {

    has_next_ = cascade(i);
    if(has_next_) // don't search any further
      break;
  }

  return next;
}


// auxiliary (private) functions
/**********************************************************************/

bool MatrixGenerator::cascade(int pos) {

  if(!generator_[pos]->has_next())
    return false;

  current_[pos] = generator_[pos]->get_next(); // +1
  for(int i=pos-1; i>= 0; --i) {

    (*generator_[i]) = (*generator_[i+1]);

    if(generator_[i]->has_next())
      current_[i] = generator_[i]->get_next();
    else // we hit the boundary, cannot cascade from pos
      return false;
  }

  return true;
}
