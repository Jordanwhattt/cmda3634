
typedef struct {

  int size;
  double *ptr;

} vector_t;

vector_t vectorReader(const char *fileName);
vector_t* vectorConstructor(int size);
void vectorDestructor(vector_t a);
double vectorGet(vector_t a, int n);
void vectorSet(vector_t a, int n, double val);
vector_t vectorAdd(vector_t a, vector_t b);
void vectorPrint(vector_t a);
int count_commont(vector_t a,vector_t b);

