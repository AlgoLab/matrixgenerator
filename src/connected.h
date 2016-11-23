#ifndef CONNECTED_H
#define CONNECTED_H

#include <vector>

/* A class to build the connectedness properties of a bipartite graph,
 * as represented by a binary matrix
 */
class Connected {

 public :

  typedef unsigned int int_t;

  // constructor
  Connected(std::vector<int_t> rows, std::vector<int_t> columns);

  // true if graph is connected, o.w., false
  bool is_connected();

 private :

  // binary matrix representation of graph
  std::vector<int_t> rows_;
  std::vector<int_t> cols_;

  // rows (resp., cols) seen in a dfs
  std::vector<bool> rows_seen_;
  std::vector<bool> cols_seen_;


  // auxiliary (private) functions
  /**********************************************************************/

 private :

  // do a depth-first search on the rows (resp., cols)
  void dfs_row(int row);
  void dfs_col(int col);

};

#endif
