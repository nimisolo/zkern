/*
 * Access kernel memory without faulting.
 */
#include <lwk/compiler.h>
#include <lwk/errno.h>
#include <lwk/types.h>
#include <lwk/string.h>
#include <lwk/linux_compat.h>
#include <arch/uaccess.h>
/**
 * probe_kernel_read(): safely attempt to read from a location
 * @dst: pointer to the buffer that shall take the data
 * @src: address to read from
 * @size: size of the data chunk
 *
 * Safely read from address @src to the buffer at @dst.  If a kernel fault
 * happens, handle that and return -EFAULT.
 */
long probe_kernel_read(void *dst, void *src, size_t size)
{
    long ret; 

    ret = __copy_from_user_inatomic(dst,
            (__force const void __user *)src, size);

    return ret ? -EFAULT : 0;
}
EXPORT_SYMBOL_GPL(probe_kernel_read);

/**
 * probe_kernel_write(): safely attempt to write to a location
 * @dst: address to write to
 * @src: pointer to the data that shall be written
 * @size: size of the data chunk
 *
 * Safely write to address @dst from the buffer at @src.  If a kernel fault
 * happens, handle that and return -EFAULT.
 */
long probe_kernel_write(void *dst, void *src, size_t size)
{
    long ret; 

    ret = __copy_to_user_inatomic((__force void __user *)dst, src, size);

    return ret ? -EFAULT : 0; 
}
EXPORT_SYMBOL_GPL(probe_kernel_write);
