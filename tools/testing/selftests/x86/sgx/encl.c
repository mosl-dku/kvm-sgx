// SPDX-License-Identifier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2016-18 Intel Corporation.

#include <stddef.h>
#include <asm/sgx_arch.h>
#include "defines.h"

static void *memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
		((char *)dest)[i] = ((char *)src)[i];

	return dest;
}

void encl_body(void *rdi, void *rsi)
{
	memcpy(rsi, rdi, 8);
}
