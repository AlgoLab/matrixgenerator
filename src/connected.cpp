#include "connected.h"

using namespace std;

Connected::Connected(vector<Connected::int_t> rows, vector<Connected::int_t> columns) :
  rows_(rows), cols_(columns),
  rows_seen_(rows.size()), cols_seen_(columns.size()) {}


bool Connected::is_connected() {

  dfs_row(0); // get rows (cols) reachable from first row (col)
  dfs_col(0);

  for(int i = 0; i < rows_seen_.size(); ++i)
    if(!rows_seen_[i])
      return false;

  for(int j = 0; j < cols_seen_.size(); ++j)
    if(!cols_seen_[j])
      return false;

  return true;
}


// auxiliary (private) functions
/**********************************************************************/

void Connected::dfs_row(int row) {

  // go no further if already seen
  if(rows_seen_[row])
    return;

  rows_seen_[row] = true;
  for(int i = 0; i < rows_.size(); ++i)
    if((row != i) and (rows_[row] & rows_[i])) 
      dfs_row(i);
}


void Connected::dfs_col(int col) {

  if(cols_seen_[col])
    return;

  cols_seen_[col] = true;
  for(int j = 0; j < cols_.size(); ++j)
    if((col != j) and (cols_[col] & cols_[j]))
      dfs_col(j);
}
