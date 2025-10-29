/*
    Copyright (C) TODO

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "padic_float_nmod.h"

/* Not checked: p is prime */
int
padic_float_nmod_ctx_init(gr_ctx_t ctx, ulong p, slong n)
{
    slong i;
    ulong hi;

    if (n <= 0 || n >= FLINT_BITS)
        return GR_UNABLE;

    /* Compute p^n and verify that this doesn't overflow a ulong */
    ulong pn = p;
    for (i = 1; i < n; i++)
    {
        umul_ppmm(hi, pn, pn, p);
        if (hi != 0)
            return GR_UNABLE;
    }

    GR_CTX_DATA_AS_PTR(ctx) = flint_malloc(sizeof(_padic_float_nmod_ctx_struct));

    PADIC_FLOAT_NMOD_CTX_P(ctx) = p;
    PADIC_FLOAT_NMOD_CTX_N(ctx) = n;

    PADIC_FLOAT_NMOD_CTX_PINV(ctx) = n_precompute_inverse(p);

    nmod_init(&PADIC_FLOAT_NMOD_CTX_P_MOD(ctx), p);
    nmod_init(&PADIC_FLOAT_NMOD_CTX_PN_MOD(ctx), pn);

    return GR_SUCCESS;
}
