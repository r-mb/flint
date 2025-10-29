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
padic_float_nmod_inv(padic_float_nmod_t res, const padic_float_nmod_t a,
                     gr_ctx_t ctx)
{
    if (a->man == 0)
    {
        flint_throw(FLINT_ERROR, "Exception (padic_float_nmod_inv).  a is zero.\n");
        return GR_UNABLE;
    }

    res->man = nmod_inv(a->man, PADIC_FLOAT_NMOD_CTX_PN_MOD(ctx));
    res->val = - a->val;

    return GR_SUCCESS;
}
