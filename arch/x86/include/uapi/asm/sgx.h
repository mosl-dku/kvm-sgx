/* SPDX-License-Identifier: (GPL-2.0 OR BSD-3-Clause) */
/**
 * Copyright(c) 2016-18 Intel Corporation.
 */
#ifndef _UAPI_ASM_X86_SGX_H
#define _UAPI_ASM_X86_SGX_H

#include <linux/types.h>
#include <linux/ioctl.h>

#define SGX_MAGIC 0xA4

#define SGX_IOC_ENCLAVE_CREATE \
	_IOW(SGX_MAGIC, 0x00, struct sgx_enclave_create)
#define SGX_IOC_ENCLAVE_ADD_PAGE \
	_IOW(SGX_MAGIC, 0x01, struct sgx_enclave_add_page)
#define SGX_IOC_ENCLAVE_INIT \
	_IOW(SGX_MAGIC, 0x02, struct sgx_enclave_init)
#define SGX_IOC_ENCLAVE_SET_ATTRIBUTE \
	_IOW(SGX_MAGIC, 0x03, struct sgx_enclave_set_attribute)
#define SGX_IOC_ENCLAVE_REMOVE_PAGES \
	_IOW(SGX_MAGIC, 0x04, struct sgx_enclave_remove_pages)
#define SGX_IOC_ENCLAVE_MODIFY_PAGES \
	_IOW(SGX_MAGIC, 0x05, struct sgx_enclave_modify_pages)

#define SGX_VIRT_EPC_CREATE \
	_IOW(SGX_MAGIC, 0x80, struct sgx_virt_epc_create)

/* IOCTL return values */
#define SGX_POWER_LOST_ENCLAVE		0x40000000

/**
 * struct sgx_enclave_create - parameter structure for the
 *                             %SGX_IOC_ENCLAVE_CREATE ioctl
 * @src:	address for the SECS page data
 */
struct sgx_enclave_create  {
	__u64	src;
};

/**
 * struct sgx_enclave_add_page - parameter structure for the
 *                               %SGX_IOC_ENCLAVE_ADD_PAGE ioctl
 * @addr:	address within the ELRANGE
 * @src:	address for the page data
 * @secinfo:	address for the SECINFO data
 * @mrmask:	bitmask for the measured 256 byte chunks
 */
struct sgx_enclave_add_page {
	__u64	addr;
	__u64	src;
	__u64	secinfo;
	__u16	mrmask;
} __attribute__((__packed__));


/**
 * struct sgx_enclave_init - parameter structure for the
 *                           %SGX_IOC_ENCLAVE_INIT ioctl
 * @addr:	address within the ELRANGE
 * @sigstruct:	address for the SIGSTRUCT data
 */
struct sgx_enclave_init {
	__u64	addr;
	__u64	sigstruct;
};

/**
 * struct sgx_enclave_set_attribute - parameter structure for the
 *				      %SGX_IOC_ENCLAVE_INIT ioctl
 * @addr:		address within the ELRANGE
 * @attribute_fd:	file handle of the attribute file in the securityfs
 */
struct sgx_enclave_set_attribute {
	__u64	addr;
	__u64	attribute_fd;
};

/**
 * struct sgx_enclave_remove_pages - parameter structure for the
 *                                   %SGX_IOC_ENCLAVE_REMOVE_PAGES ioctl
 * @addr:	address in the ELRANGE for the first page
 * @length:	length of the address range (must be multiple of the page size)
 */
struct sgx_enclave_remove_pages {
	__u64	addr;
	__u64	length;
} __packed;

/**
 * enum sgx_enclave_modify_ops - page modification operations
 * @SGX_ENCLAVE_MODIFY_PERMISSIONS:	change page permissions
 * @SGX_ENCLAVE_MODIFY_TYPES:		change page type
 */
enum sgx_enclave_modify_ops {
	SGX_ENCLAVE_MODIFY_PERMISSIONS	= 0,
	SGX_ENCLAVE_MODIFY_TYPES	= 1,
};

/**
 * struct sgx_enclave_modify_pages - parameter structure for the
 *                                   %SGX_IOC_ENCLAVE_MOD_PAGES ioctl
 * @addr:	address in the ELRANGE for the first page
 * @length:	length of the address range (must be multiple of the page size)
 * @secinfo:	address of the new SECINFO data
 * @op:		a value of &sgx_enclave_modify_ops
 */
struct sgx_enclave_modify_pages {
	__u64	addr;
	__u64	length;
	__u64	secinfo;
	__u8	op;
} __attribute__((__packed__));

/**
 * struct sgx_virt_epc_create - parameter structure for the
 *				%SGX_VIRT_EPC_CREATE ioctl
 *
 * @size:		size, in bytes, of the virtual EPC
 * @attribute_fd:	file handle to the securityfs attribute file
 */
struct sgx_virt_epc_create  {
	__u64	size;
	__u64	attribute_fd;
};

/**
 * struct sgx_enclave_exception - structure to report exceptions encountered in
 *				  __vdso_sgx_enter_enclave
 *
 * @leaf:	ENCLU leaf from %rax at time of exception
 * @trapnr:	exception trap number, a.k.a. fault vector
 * @error_cdde:	exception error code
 * @address:	exception address, e.g. CR2 on a #PF
 * @reserved:	reserved for future use
 */
struct sgx_enclave_exception {
	__u32 leaf;
	__u16 trapnr;
	__u16 error_code;
	__u64 address;
	__u64 reserved[2];
};

#endif /* _UAPI_ASM_X86_SGX_H */
