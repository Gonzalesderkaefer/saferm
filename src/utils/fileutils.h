#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <sys/types.h>

/// This function creates a the directory speicified
/// by `path` and also creates its parent directories
/// on error this function returns -1. Cause of this
/// is either memory allocation failure, in which case
/// errno will be set by malloc() or a failure
/// caused by mkdir(2) in which case errno will be
/// set by mkdir(2)
int mkdir_p(const char *path, const mode_t mode);


/// This function copies a file from `src` to `dest`
/// on failure this function returns -1. Cause of 
/// this is either failrure to open the source
/// or destination file in which case errno will
/// be set by fopen or failure to read or write
/// from src or dest respectively.
int copy_file(const char *src, const char *dest);

/// This function copies the directory specified at `srcdir`
/// to `destdir` where destdir will not be the new parent dir
/// but will contain everyting that `srcdir` contained, if `destdir`
/// does not exist it will be created. On success this function returns 0
/// on error it returns -1. Cause for error is failure to create
/// `destdir` in which case errno will be set according to mkdir() or
/// or if source does not exist in which case only -1 is returned
int copy_r(const char *srcdir, const char *dest);







#endif //FILEUTILS_H
