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
  valid = valid and no_zero();
  valid = valid and no_one();
  valid = valid and no_duplicate();
  valid = valid and is_connected();

  return valid;
}


// the tests for validity
/**********************************************************************/

bool MatrixGenerator::no_zero() {

  for(int j=0; j < m_; ++j)
    if(columns_[j] == 0) {
      //cout << "zero j : " << j << endl;
      return false;
    }

  return true;
}


bool MatrixGenerator::no_one() {

  MatrixGenerator::int_t mask;
  for(int j=0; j < m_; ++j) {

    mask = 1;
    int count = 0;
    for(int i=0; i < n_; ++i) {

      if(columns_[j] & mask)
	++count;

      mask <<= 1;
    }

    if(count == 1) {
      //cout << "one j : " << j << endl;
      return false;
    }
  }

  return true;
}


bool MatrixGenerator::no_duplicate() {

  for(int i=0; i < m_; ++i)
    for(int j=0; j < i; ++j)
      if(columns_[i] == columns_[j]) {
	//cout << "duplicate i,j : " << i << "," << j << endl;
	return false;
      }

  return true;
}


bool MatrixGenerator::is_connected() {

  Connected conn(current_, columns_);

  //if(!conn.is_connected()) { cout << "not connected" << endl; }
  return conn.is_connected();
}
