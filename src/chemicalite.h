#ifndef CHEMICALITE_TYPES_INCLUDED
#define CHEMICALITE_TYPES_INCLUDED
#include <stdint.h>

typedef uint32_t u32;
typedef uint8_t u8;

typedef struct Mol Mol;
typedef struct Bfp Bfp;

#define DEFAULT_SSS_BFP_LENGTH 2048
#define DEFAULT_LAYERED_BFP_LENGTH 1024
#define DEFAULT_MORGAN_BFP_LENGTH 512
#define DEFAULT_HASHED_TORSION_BFP_LENGTH 1024
#define DEFAULT_HASHED_PAIR_BFP_LENGTH 2048

#endif
