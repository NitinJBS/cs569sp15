#include <stdio.h>
#include "mergesort.h"
#include "assert.h"

int a[SIZE];

int nondet_int();
unsigned int nondet_unsigned_int();

int main ()
 {
        int i, v, last, val;
        int refc = 0;
        int acount = 0;
        unsigned int s = nondet_unsigned_int();
        __CPROVER_assume (s <= SIZE);
        int val = nondet_int();
        printf ("LOG: size = %u, val = %d\n", SIZE, val);

        for (i = 0; i < SIZE; i++)
        {
                v = nondet_int();
                printf ("LOG: a[%d] = %d\n", i, v);
                a[i] = v;

                if (v == val)
                {
                        refc++;
                }
        }

        mergeSort(a,0,SIZE-1);
        printf ("LOG: sorted a\n");

        if (SIZE > 0)
        {
                last = a[0];

                if (a[0] == val)
                {
                        acount++;
                }
        }

        for (i = 1; i < SIZE; i++)
        {
                printf ("LOG: last = %d, a[%d] = %d\n", last, i, a[i]);
                printf("Size of the array: %d" , SIZE);
                printf("LOG: a[%d] : %d ",i,a[i]);
                assert (a[i] >= last);

                if (a[i] == val)
                {
                        acount++;
                }

                last = a[i];
        }

        printf ("LOG: refc = %d, acount = %d\n", refc, acount);
        assert (refc == acount);
}
