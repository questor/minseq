
#ifndef __TINY_MATH_H__
#define __TINY_MATH_H__

#if 0
// https://nic.schraudolph.org/pubs/Schraudolph99.pdf
static union {
   double d;
   struct {
#ifdef LITTLE_ENDIAN
      int j,i;
#else
      int i,j;
#endif
   } n; 
} eco;

#define EXP_A (1048576/M_LN2)  /* use 1512775 for integer version */
#define EXP_C  60801
#define EXP(y) (eco.n.i = EXP_A*(y) + (1072693248 - EXP_C), eco.d)

#endif



#if 0
// https://martin.ankerl.com/2007/10/04/optimized-pow-approximation-for-java-and-c-c/
double fastPow(double a, double b) {
    union {
        double d;
        int x[2];
    } u = { a };
    u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;
    return u.d;
}
#endif


#if 0
// much less error when the exponent is larger than 1
// should be much more precise with large b
inline double fastPrecisePow(double a, double b) {
  // calculate approximation with fraction of the exponent
  int e = (int) b;
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)((b - e) * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;

  // exponentiation by squaring with the exponent's integer part
  // double r = u.d makes everything much slower, not sure why
  double r = 1.0;
  while (e) {
    if (e & 1) {
      r *= a;
    }
    a *= a;
    e >>= 1;
  }

  return r * u.d;
}
#endif



#if 0
const float _2p23 = 8388608.0f;


/**
 * Initialize powFast lookup table.
 *
 * @pTable     length must be 2 ^ precision
 * @precision  number of mantissa bits used, >= 0 and <= 18
 */
void powFastSetTable
(
   unsigned int* const pTable,
   const unsigned int  precision
)
{
   /* step along table elements and x-axis positions */
   float zeroToOne = 1.0f / ((float)(1 << precision) * 2.0f);        /* A */
   int   i;                                                          /* B */
   for( i = 0;  i < (1 << precision);  ++i )                         /* C */
   {
      /* make y-axis value for table element */
      const float f = ((float)pow( 2.0f, zeroToOne ) - 1.0f) * _2p23;
      pTable[i] = (unsigned int)( f < _2p23 ? f : (_2p23 - 1.0f) );

      zeroToOne += 1.0f / (float)(1 << precision);
   }                                                                 /* D */
}


/**
 * Get pow (fast!).
 *
 * @val        power to raise radix to
 * @ilog2      one over log, to required radix, of two
 * @pTable     length must be 2 ^ precision
 * @precision  number of mantissa bits used, >= 0 and <= 18
 */
float powFastLookup
(
   const float         val,
   const float         ilog2,
   unsigned int* const pTable,
   const unsigned int  precision
)
{
   /* build float bits */
   const int i = (int)( (val * (_2p23 * ilog2)) + (127.0f * _2p23) );

   /* replace mantissa with lookup */
   const int it = (i & 0xFF800000) | pTable[(i & 0x7FFFFF) >>        /* E */
      (23 - precision)];                                             /* F */

   /* convert bits to float */
   return *(const float*)( &it );
}
#endif

#endif

