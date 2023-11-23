/*
 * Genommen von:
 * https://de.wikipedia.org/wiki/Mersenne-Twister#TT800
 */

#ifndef MERSENNE_TWISTER_800_H
#define MERSENNE_TWISTER_800_H

// #include <stdio.h>

#define N 25
#define M 7

typedef unsigned int uint32_t;

/*
 * Initialisiere den Vektor mit Pseudozufallszahlen.
 */

static void TT800_vector_init(uint32_t *const p, const int len)
{
  const uint32_t mult = 509845221ul;
  const uint32_t add = 3ul;
  uint32_t seed1 = 9;
  uint32_t seed2 = 3402;
  int i;

  for (i = 0; i < len; i++)
  {
    seed1 = seed1 * mult + add;
    seed2 *= seed2 + 1;
    p[i] = seed2 + (seed1 >> 10);
  }
}

/*
 * Berechne neuen Zustandsvektor aus altem Zustandsvektor
 * Dies erfolgt periodisch alle N=25 Aufrufe von TT800().
 *
 * Der folgende Code stellt eine optimierte Version von
 *   ...
 *   for (i = 0; i < N; i++)
 *     Proc2 (p[i], p[(i+M) % N]);
 *   ...
 * mit
 *   void Proc2 (uint32_t &a0, uint32_t aM)
 *   {
 *     a0 = aM ^ (a0 >> 1) ^ A[a0 & 1];
 *   }
 * dar, in der die (zeitintensiven) Modulo N-Operationen vermieden werden.
 */

static void TT800_vector_update(uint32_t *const p)
{
  static const uint32_t A[2] = {0, 0x8ebfd028};
  int i = 0;

  for (; i < N - M; i++)
    p[i] = p[i + (M)] ^ (p[i] >> 1) ^ A[p[i] & 1];
  for (; i < N; i++)
    p[i] = p[i + (M - N)] ^ (p[i] >> 1) ^ A[p[i] & 1];
}

/*
 * Die eigentliche Funktion:
 * - beim 1. Aufruf wird der Vektor mittels TT800_vector_init() initialisiert.
 * - beim 1., 26., 51., ... Aufruf wird ein neuer Vektor mittels TT800_vector_update berechnet.
 * - bei jedem Aufruf wird eine Zufallszahl aus dem Vektor ausgelesen und noch einem Tempering unterzogen.
 */

uint32_t TT800()
{
  static uint32_t vektor[N]; /* Zustandsvektor */
  static int idx = N + 1;    /* Auslese-Index; idx >= N: neuer Vektor muss berechnet werden, */
                             /* idx=N+1: Vektor muss überhaupt erst mal initialisiert werden */
  uint32_t e;

  if (idx >= N)
  {
    if (idx > N)
      TT800_vector_init(vektor, N);
    TT800_vector_update(vektor);
    idx = 0;
  }

  e = vektor[idx++];
  e ^= (e << 7) & 0x2b5b2500; /* Tempering */
  e ^= (e << 15) & 0xdb8b0000;
  e ^= (e >> 16);
  return e;
}

#undef N
#undef M

#endif
