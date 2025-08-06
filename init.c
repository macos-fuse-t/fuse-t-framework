//
//  init.c
//  fuse-t
//
//  Created by alex fishman on 25/02/2023.
//

#include <CoreFoundation/CoreFoundation.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

__attribute__((constructor))
static void initializer(int argc, char** argv, char** envp)
{
    CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR("org.fuse-t.fuse-t"));
    if (bundle == NULL) {
        fprintf(stderr, "Error: Failed to get bundle with identifier.\n");
        return;
    }

    CFURLRef bundleURL = CFBundleCopyResourcesDirectoryURL(bundle);
    if (bundleURL == NULL) {
        fprintf(stderr, "Error: Failed to get resources directory URL.\n");
        return;
    }

    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(bundleURL, TRUE, (UInt8 *)path, PATH_MAX)) {
        fprintf(stderr, "Error: Failed to get file system representation.\n");
        CFRelease(bundleURL);
        return;
    }

    CFRelease(bundleURL);
    strcat(path, "/go-nfsv4");
    setenv("FUSE_NFSSRV_PATH", path, 1);
}

