#include <stdlib.h>
#include <cassert>
#include "matrixgenerator.h"

using namespace std;

// output matrix corresponding to array of bit representation of rows
void output_matrix(vector<MatrixGenerator::int_t> v, int m) {

  int n = v.size();
  vector<string> rows(n);

  MatrixGenerator::int_t mask = 1;
  for(int j=0; j< m; ++j) {
    for(int i=0; i< n; ++i)
      rows[i] += (v[i] & mask)?"1 ":"0 ";    

    mask <<= 1;
  }

  cout << endl;
  for(int i=0; i< n; ++i)
    cout << rows[i] << endl;
}


// MAIN
int main(int argc, char * argv[]) {

  assert(argc == 3);
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  cout << n << " " << m << endl;

  MatrixGenerator generator(n,m);

  while(generator.has_next())
    output_matrix(generator.get_next(),m);
}
