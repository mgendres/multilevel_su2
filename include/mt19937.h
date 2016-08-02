#ifndef INCLUDED_MT19937
#define INCLUDED_MT19937

/* Period parameters */
////  These should be members of the class to avoid naming conflicts
#define N_ 624
#define M_ 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */


class mt19937
{
  private:

    unsigned long mt[N_]; /* the array for the state vector  */
    int mti; /* mti==N_+1 means mt[N_] is not initialized */

    mt19937& operator=(const mt19937&);
    mt19937(const mt19937&);

  public:
    explicit mt19937();
    explicit mt19937(unsigned long);
    explicit mt19937(unsigned long*, int);
    ~mt19937();
    void init_genrand(unsigned long);
    void init_by_array(unsigned long* , int);
    unsigned long genrand_int32(void);
    long genrand_int31(void);
    double genrand_real1(void);
    double genrand_real2(void);
    double genrand_real3(void);
    double genrand_res53(void);
    int genrand_int53(void);

    void write_state(char*);
    void read_state(char*);

};


extern mt19937 rng;

#endif
