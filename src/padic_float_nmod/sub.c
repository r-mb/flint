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
padic_float_nmod_sub(padic_float_nmod_t res, const padic_float_nmod_t a,
                     const padic_float_nmod_t b, gr_ctx_t ctx)
{
    if (a->man == 0)
    {
        padic_float_nmod_neg(res, b, ctx);
    }
    else if (b->man == 0)
    {
        padic_float_nmod_set(res, a, ctx);
    }
    else
    {
        if (a->val == b->val)
        {
            res->man = nmod_sub(a->man, b->man,
                                PADIC_FLOAT_NMOD_CTX_PN_MOD(ctx));
            res->val = a->val;

            _padic_float_nmod_canonicalise(res, ctx);
            /* Underflow */
            if (res->val > PADIC_EMAX)
                return GR_UNABLE;
        }
        else if (a->val < b->val)
        {
            nmod_t pn = PADIC_FLOAT_NMOD_CTX_PN_MOD(ctx);
            ulong f, n;

            f = nmod_pow_ui(PADIC_FLOAT_NMOD_CTX_P(ctx), b->val - a->val,
                            pn);//TODO precompute
            n = nmod_neg(b->man, pn);
            res->man = a->man;
            NMOD_ADDMUL(res->man, f, n, pn);
            res->val = a->val;
        }
        else  /* a->val > b->val */
        {
            nmod_t pn = PADIC_FLOAT_NMOD_CTX_PN_MOD(ctx);
            ulong f;

            f = nmod_pow_ui(PADIC_FLOAT_NMOD_CTX_P(ctx), a->val - b->val, pn);
            res->man = nmod_neg(b->man, pn);
            NMOD_ADDMUL(res->man, f, a->man, pn);
            res->val = b->val;
        }
    }

    return GR_SUCCESS;
}
