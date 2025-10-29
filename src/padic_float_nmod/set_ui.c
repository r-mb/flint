/*
    Copyright (C) TODO

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#include "padic_float_nmod.h"

int
padic_float_nmod_set_ui(padic_float_nmod_t res, ulong x, gr_ctx_t ctx)
{
    if (x < PADIC_FLOAT_NMOD_CTX_P(ctx))
    {
        res->man = x;
        res->val = (x == 0) ? PADIC_EMAX : 0;
    }
    else
    {
        slong val = 0;
        ulong r, q;
        ulong p, pinv;

        p = PADIC_FLOAT_NMOD_CTX_P(ctx);
        pinv = PADIC_FLOAT_NMOD_CTX_P_MOD(ctx).ninv;

        while (1)
        {
            r = n_divrem2_preinv(&q, x, p, pinv);
            if (r == 0)
            {
                x = q;
                val++;
            }
            else
            {
                break;
            }
        }

        x = nmod_set_ui(x, PADIC_FLOAT_NMOD_CTX_PN_MOD(ctx));

        res->man = x;
        res->val = val;
    }

    return GR_SUCCESS;
}
