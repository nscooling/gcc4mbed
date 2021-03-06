/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef MBED_LOCALFILESYSTEM_H
#define MBED_LOCALFILESYSTEM_H

#include "platform.h"

#if DEVICE_LOCALFILESYSTEM

#include "FileSystemLike.h"

namespace mbed {

FILEHANDLE local_file_open(const char* name, int flags);

class LocalFileHandle : public FileHandle {

public:
    LocalFileHandle(FILEHANDLE fh);
    
    virtual int close();
    
    virtual ssize_t write(const void *buffer, size_t length);
    
    virtual ssize_t read(void *buffer, size_t length);
    
    virtual int isatty();
    
    virtual off_t lseek(off_t position, int whence);
    
    virtual int fsync();
    
    virtual off_t flen();

protected:
    FILEHANDLE _fh;
    int pos;
};

/** A filesystem for accessing the local mbed Microcontroller USB disk drive 
 *
 *  This allows programs to read and write files on the same disk drive that is used to program the 
 *  mbed Microcontroller. Once created, the standard C file access functions are used to open, 
 *  read and write files.
 *
 * Example:
 * @code
 * #include "mbed.h"
 *
 * LocalFileSystem local("local");               // Create the local filesystem under the name "local"
 *
 * int main() {
 *     FILE *fp = fopen("/local/out.txt", "w");  // Open "out.txt" on the local file system for writing
 *     fprintf(fp, "Hello World!");              
 *     fclose(fp);                               
 *     remove("/local/out.txt");                 // Removes the file "out.txt" from the local file system
 *
 *     DIR *d = opendir("/local");               // Opens the root directory of the local file system
 *     struct dirent *p;
 *     while((p = readdir(d)) != NULL) {         // Print the names of the files in the local file system
 *       printf("%s\n", p->d_name);              // to stdout.
 *     }
 *     closedir(d);
 * }
 * @endcode
 *
 * @note
 *  If the microcontroller program makes an access to the local drive, it will be marked as "removed"
 *  on the Host computer. This means it is no longer accessible from the Host Computer.
 *
 *  The drive will only re-appear when the microcontroller program exists. Note that if the program does
 *  not exit, you will need to hold down reset on the mbed Microcontroller to be able to see the drive again!
 */
class LocalFileSystem : public FileSystemLike {

public:
    LocalFileSystem(const char* n) : FileSystemLike(n) {
        
    }

    virtual FileHandle *open(const char* name, int flags);
    virtual int remove(const char *filename);
    virtual DirHandle *opendir(const char *name);
};

} // namespace mbed

#endif

#endif
