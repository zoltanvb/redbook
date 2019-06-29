/* Copyright  (C) 2010-2019 The RetroArch team
*
* ---------------------------------------------------------------------------------------
* The following license statement only applies to this file (vfs_implementation.h).
* ---------------------------------------------------------------------------------------
*
* Permission is hereby granted, free of charge,
* to any person obtaining a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __LIBRETRO_SDK_VFS_IMPLEMENTATION_H
#define __LIBRETRO_SDK_VFS_IMPLEMENTATION_H

#include <stdint.h>
#include <libretro.h>

#ifdef HAVE_CDROM
#include <vfs/vfs_implementation_cdrom.h>
#endif

#ifdef _WIN32
typedef void* HANDLE;
#endif

enum vfs_scheme
{
   VFS_SCHEME_NONE = 0,
   VFS_SCHEME_CDROM
};

#ifdef VFS_FRONTEND
struct retro_vfs_file_handle
#else
struct libretro_vfs_implementation_file
#endif
{
   int fd;
   unsigned hints;
   int64_t size;
   char *buf;
   FILE *fp;
#ifdef _WIN32
   HANDLE fh;
#endif
   char* orig_path;
   uint64_t mappos;
   uint64_t mapsize;
   uint8_t *mapped;
   enum vfs_scheme scheme;
#ifdef HAVE_CDROM
   vfs_cdrom_t cdrom;
#endif
};

/* Replace the following symbol with something appropriate
 * to signify the file is being compiled for a front end instead of a core.
 * This allows the same code to act as reference implementation
 * for VFS and as fallbacks for when the front end does not provide VFS functionality.
 */

#ifdef VFS_FRONTEND
typedef struct retro_vfs_file_handle libretro_vfs_implementation_file;
#else
typedef struct libretro_vfs_implementation_file libretro_vfs_implementation_file;
#endif

#ifdef VFS_FRONTEND
typedef struct retro_vfs_dir_handle libretro_vfs_implementation_dir;
#else
typedef struct libretro_vfs_implementation_dir libretro_vfs_implementation_dir;
#endif

#ifdef __cplusplus
extern "C" {
#endif

libretro_vfs_implementation_file *retro_vfs_file_open_impl(const char *path, unsigned mode, unsigned hints);

int retro_vfs_file_close_impl(libretro_vfs_implementation_file *stream);

int retro_vfs_file_error_impl(libretro_vfs_implementation_file *stream);

int64_t retro_vfs_file_size_impl(libretro_vfs_implementation_file *stream);

int64_t retro_vfs_file_truncate_impl(libretro_vfs_implementation_file *stream, int64_t length);

int64_t retro_vfs_file_tell_impl(libretro_vfs_implementation_file *stream);

int64_t retro_vfs_file_seek_impl(libretro_vfs_implementation_file *stream, int64_t offset, int seek_position);

int64_t retro_vfs_file_read_impl(libretro_vfs_implementation_file *stream, void *s, uint64_t len);

int64_t retro_vfs_file_write_impl(libretro_vfs_implementation_file *stream, const void *s, uint64_t len);

int retro_vfs_file_flush_impl(libretro_vfs_implementation_file *stream);

int retro_vfs_file_remove_impl(const char *path);

int retro_vfs_file_rename_impl(const char *old_path, const char *new_path);

const char *retro_vfs_file_get_path_impl(libretro_vfs_implementation_file *stream);

int retro_vfs_stat_impl(const char *path, int32_t *size);

int retro_vfs_mkdir_impl(const char *dir);

libretro_vfs_implementation_dir *retro_vfs_opendir_impl(const char *dir, bool include_hidden);

bool retro_vfs_readdir_impl(libretro_vfs_implementation_dir *dirstream);

const char *retro_vfs_dirent_get_name_impl(libretro_vfs_implementation_dir *dirstream);

bool retro_vfs_dirent_is_dir_impl(libretro_vfs_implementation_dir *dirstream);

int retro_vfs_closedir_impl(libretro_vfs_implementation_dir *dirstream);

#ifdef __cplusplus
}
#endif

#endif
