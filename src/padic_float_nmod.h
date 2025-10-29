/*
    Copyright (C) TODO

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.  See <https://www.gnu.org/licenses/>.
*/

#ifndef PADIC_FLOAT_NMOD_H
#define PADIC_FLOAT_NMOD_H

#ifdef PADIC_FLOAT_NMOD_INLINES_C
#define PADIC_FLOAT_NMOD_INLINE
#else
#define PADIC_FLOAT_NMOD_INLINE static inline
#endif

#include "gr.h"
#include "nmod.h"
#include "padic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PADIC_EMIN (-(WORD_MAX / 4))
#define PADIC_EMAX ((WORD_MAX / 4))

#define PADIC_FLOAT_NMOD_CTX(ctx) ((_padic_float_nmod_ctx_struct *)(GR_CTX_DATA_AS_PTR(ctx)))
#define PADIC_FLOAT_NMOD_CTX_P(ctx) (PADIC_FLOAT_NMOD_CTX(ctx)->p)
#define PADIC_FLOAT_NMOD_CTX_PINV(ctx) (PADIC_FLOAT_NMOD_CTX(ctx)->pinv)
#define PADIC_FLOAT_NMOD_CTX_N(ctx) (PADIC_FLOAT_NMOD_CTX(ctx)->n)
#define PADIC_FLOAT_NMOD_CTX_P_MOD(ctx) (PADIC_FLOAT_NMOD_CTX(ctx)->p_mod)
#define PADIC_FLOAT_NMOD_CTX_PN_MOD(ctx) (PADIC_FLOAT_NMOD_CTX(ctx)->pn_mod)

/* Context *******************************************************************/

int padic_float_nmod_ctx_init(gr_ctx_t ctx, ulong p, slong n);
void padic_float_nmod_ctx_clear(gr_ctx_t ctx);

/* Memory management *********************************************************/

void padic_float_nmod_init(padic_float_nmod_t res, gr_ctx_t ctx);

PADIC_FLOAT_NMOD_INLINE
void _padic_float_nmod_canonicalise(padic_float_nmod_t x, gr_ctx_t ctx)
{
    if (x->man != 0)
    {
        if (x->man > 0)
        {
            x->man += n_remove2_precomp(&x->man, PADIC_FLOAT_NMOD_CTX_P(ctx),
                                        PADIC_FLOAT_NMOD_CTX_PINV(ctx));
        }
        else
        {
            ulong z = - x->man;
            slong e = n_remove2_precomp(&z, PADIC_FLOAT_NMOD_CTX_P(ctx),
                                        PADIC_FLOAT_NMOD_CTX_PINV(ctx));

            if (e > 0)
            {
                x->man = - (slong) z;
            }
            x->val += e;
        }
    }
    else
    {
        x->val = 0;
    }
}
/* Assignments and conversions ***********************************************/

int padic_float_nmod_set(padic_float_nmod_t res, const padic_float_nmod_t x,
                         gr_ctx_t ctx);

int padic_float_nmod_set_ui(padic_float_nmod_t res, ulong x, gr_ctx_t ctx);

PADIC_FLOAT_NMOD_INLINE
int padic_float_nmod_zero(padic_float_nmod_t res, gr_ctx_t ctx)
{
    res->man = 0;
    res->val = PADIC_EMAX;
    return GR_SUCCESS;
}

PADIC_FLOAT_NMOD_INLINE 
int padic_float_nmod_one(padic_float_nmod_t res, gr_ctx_t ctx)
{
    res->man = 1;
    res->val = 0;
    return GR_SUCCESS;
}

/* Comparison ****************************************************************/

PADIC_FLOAT_NMOD_INLINE
truth_t padic_float_nmod_is_zero(const padic_float_nmod_t x, gr_ctx_t ctx)
{
    return (x->man == 0) ? T_TRUE : T_FALSE;
}

PADIC_FLOAT_NMOD_INLINE
truth_t padic_float_nmod_is_one(const padic_float_nmod_t x, gr_ctx_t ctx)
{
    return (x->man == 1 && x->val == 0) ? T_TRUE : T_FALSE;
}

/* Arithmetic operations *****************************************************/

int padic_float_nmod_add(padic_float_nmod_t res, const padic_float_nmod_t a,
                         const padic_float_nmod_t b, gr_ctx_t ctx);
int padic_float_nmod_div(padic_float_nmod_t res, const padic_float_nmod_t a,
                         const padic_float_nmod_t b, gr_ctx_t ctx);
int padic_float_nmod_inv(padic_float_nmod_t res, const padic_float_nmod_t a,
                         gr_ctx_t ctx);
int padic_float_nmod_mul(padic_float_nmod_t res, const padic_float_nmod_t a,
                         const padic_float_nmod_t b, gr_ctx_t ctx);
int padic_float_nmod_neg(padic_float_nmod_t res, const padic_float_nmod_t a,
                         gr_ctx_t ctx);
int padic_float_nmod_sub(padic_float_nmod_t res, const padic_float_nmod_t a,
                         const padic_float_nmod_t b, gr_ctx_t ctx);

/* Input and output **********************************************************/

void padic_float_nmod_println(const padic_float_nmod_t x, gr_ctx_t ctx);

#ifdef __cplusplus
}
#endif

#endif
