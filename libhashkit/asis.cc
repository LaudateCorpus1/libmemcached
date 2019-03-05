/*
 *  This file is made available under the same terms as the rest of
 *  libmemcached.
 */

#include <libhashkit/common.h>
#include <sys/types.h>


/*
 * This hash function does no hashing; it returns up to the first four
 * bytes of the key as the hash value.  This can be useful when keys
 * are already well-distributed and need no additional hashing step.
 */
uint32_t hashkit_asis(const char *key, size_t length, void *)
{
  uint32_t result = 0;
  if (length >= 4) {
    result = ((uint32_t) (0xFF & key[0]) << 24)
      | ((uint32_t) (0xFF & key[1]) << 16)
      | ((uint32_t) (0xFF & key[2]) << 8)
      | (0xFF &  key[3]);
  } else if (length > 0) {
    result = (uint32_t) (0xFF & key[0]);
    if (length > 1) {
      result <<= 8;
      result |= (uint32_t) (0xFF & key[1]);
      if (length > 2) {
        result <<= 8;
        result |= (uint32_t) (0xFF & key[2]);
        if (length > 3) {
          result <<= 8;
          result |= (uint32_t) (0xFF & key[3]);
        }
      }
    }
  }
  return result;
}
