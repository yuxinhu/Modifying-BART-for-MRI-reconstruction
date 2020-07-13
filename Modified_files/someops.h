/* Copyright 2014. The Regents of the University of California.
 * All rights reserved. Use of this source code is governed by 
 * a BSD-style license which can be found in the LICENSE file.
 */

#ifndef __SOMEOPS_H
#define __SOMEOPS_H

#include <stdbool.h>

#include "misc/cppwrap.h"

extern struct linop_s* linop_cdiag_create(unsigned int N, const long dims[__VLA(N)], unsigned int flags, const _Complex float* diag);
extern struct linop_s* linop_rdiag_create(unsigned int N, const long dims[__VLA(N)], unsigned int flags, const _Complex float* diag);

extern struct linop_s* linop_identity_create(unsigned int N, const long dims[__VLA(N)]);

extern struct linop_s* linop_resize_create(unsigned int N, const long out_dims[__VLA(N)], const long in_dims[__VLA(N)]);

extern struct linop_s* linop_fft_create(int N, const long dims[__VLA(N)], unsigned int flags, bool gpu);
extern struct linop_s* linop_ifft_create(int N, const long dims[__VLA(N)], unsigned int flags, bool gpu);
extern struct linop_s* linop_fftc_create(int N, const long dims[__VLA(N)], unsigned int flags, bool gpu);
extern struct linop_s* linop_ifftc_create(int N, const long dims[__VLA(N)], unsigned int flags, bool gpu);

extern struct linop_s* linop_cdf97_create(int N, const long dims[__VLA(N)], unsigned int flag);

#ifndef __CONV_ENUMS
#define __CONV_ENUMS
enum conv_mode { CONV_SYMMETRIC, CONV_CAUSAL, CONV_ANTICAUSAL };
enum conv_type { CONV_CYCLIC, CONV_TRUNCATED, CONV_VALID, CONV_EXTENDED };
#endif

extern struct linop_s* linop_conv_create(int N, unsigned int flags, enum conv_type ctype, enum conv_mode cmode, const long odims[__VLA(N)],
                const long idims1[__VLA(N)], const long idims2[__VLA(N)], const complex float* src2);

extern struct linop_s* linop_matrix_create(unsigned int N, const long out_dims[__VLA(N)], const long in_dims[__VLA(N)], const long matrix_dims[__VLA(N)], const _Complex float* matrix);
extern struct linop_s* linop_matrix_altcreate(unsigned int N, const long out_dims[__VLA(N)], const long in_dims[__VLA(N)], const unsigned int T_dim, const unsigned int K_dim, const complex float* matrix);

extern const struct iovec_s* compute_gram_matrix(unsigned int N, unsigned int T_dim, unsigned int T, unsigned int K_dim, unsigned int K, _Complex float** gram, const long matrix_dims[__VLA(N)], const _Complex float* matrix);

struct linop_s;

extern struct linop_s* linop_matrix_chain(const struct linop_s* a, const struct linop_s* b);

extern struct linop_s* linop_yuxinT2_create(unsigned int N, const long img_dims[__VLA(N)],const long img_dims1[__VLA(N)],const long img_dims2[__VLA(N)]);
extern struct linop_s* linop_yuxinT1_create(unsigned int N, const long img_dims[__VLA(N)],const long img_dims1[__VLA(N)],const long img_dims2[__VLA(N)]);
extern struct linop_s* linop_yuxinT0_create(unsigned int N, const long img_dims[__VLA(N)],const long img_dims1[__VLA(N)],const long img_dims2[__VLA(N)]);



#include "misc/cppwrap.h"
#endif // __SOMEOPS_H

