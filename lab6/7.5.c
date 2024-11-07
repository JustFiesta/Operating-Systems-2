#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For windows compilation - need to link lversion: 
// gcc program.c -o program -lversion

#ifdef _WIN32
    #include <windows.h>
    #pragma comment(lib, "Version")
#else
    #include <gnu/libc-version.h>
    #include <unistd.h>
#endif

#ifdef _WIN32
void print_version_windows() {
    printf("Metoda 1: Użycie funkcji _get_osplatform\n");
    OSVERSIONINFO versionInfo;
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&versionInfo);
    printf("Windows Version: %ld.%ld\n\n", versionInfo.dwMajorVersion, versionInfo.dwMinorVersion);

    printf("Metoda 2: Wykorzystanie funkcji systemowej\n");
    system("ver");

    printf("\nMetoda 3: Użycie GetFileVersionInfo z MSVCRT.dll\n");
    DWORD verHandle = 0;
    UINT size = 0;
    LPBYTE lpBuffer = NULL;
    DWORD verSize = GetFileVersionInfoSize("msvcrt.dll", &verHandle);
    
    if (verSize > 0) {
        LPSTR verData = (LPSTR)malloc(verSize);

        if (GetFileVersionInfo("msvcrt.dll", verHandle, verSize, verData)) {
            if (VerQueryValue(verData, "\\", (VOID FAR* FAR*)&lpBuffer, &size)) {
                if (size) {
                    VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd) {
                        printf("MSVCRT Version: %d.%d.%d.%d\n",
                               (verInfo->dwFileVersionMS >> 16) & 0xffff,
                               (verInfo->dwFileVersionMS >> 0) & 0xffff,
                               (verInfo->dwFileVersionLS >> 16) & 0xffff,
                               (verInfo->dwFileVersionLS >> 0) & 0xffff
                        );
                    }
                }
            }
        }
        free(verData);
    }
}

#else
void print_version_linux() {
    printf("Metoda 1: Użycie funkcji gnu_get_libc_version()\n");
    printf("GLIBC Version: %s\n\n", gnu_get_libc_version());

    printf("Metoda 2: Sprawdzenie wersji w pliku libc\n");
    system("ldd --version | head -n 1");

    printf("\nMetoda 3: Użycie komendy z plikiem libc\n");
    system("ldd /bin/ls | grep libc");
}
#endif

int main() {
#ifdef _WIN32
    print_version_windows();
#else
    print_version_linux();
#endif
    return 0;
}
