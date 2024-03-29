```c++
struct info {
    int type, argNum;
    SYSTEMTIME st;
    char argName[10][30] = { 0 };
    char argValue[10][70] = { 0 };
};

info sendInfo;
HANDLE hSemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, L"mySemaphore");
HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemory");
LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(info));
```

这几行代码定义了一个结构体 `info`，创建了一个 `info` 类型的变量 `sendInfo`，以及使用 Windows API 创建了一个命名信号量和一个命名共享内存对象，并将共享内存映射到当前进程的地址空间中。

具体来说：
1. `struct info`: 这是一个结构体，用于存储一些信息。它包含了以下成员：
   - `int type`: 表示信息的类型。
   - `int argNum`: 表示参数的数量。
   - `SYSTEMTIME st`: 表示系统时间。
   - `char argName[10][30]`: 一个二维数组，用于存储参数名，最多可以存储 10 个字符串，每个字符串长度最长为 29 个字符。
   - `char argValue[10][70]`: 一个二维数组，用于存储参数值，最多可以存储 10 个字符串，每个字符串长度最长为 69 个字符。

2. `info sendInfo`: 这是一个 `info` 类型的变量，用于存储要发送的信息。

3. `HANDLE hSemaphore`: 这是一个 Windows 命名信号量的句柄，通过 `OpenSemaphore` 函数打开，它用于在多个进程之间同步对共享资源的访问。

4. `HANDLE hMapFile`: 这是一个 Windows 命名共享内存对象的句柄，通过 `OpenFileMapping` 函数打开，它用于在多个进程之间共享数据。

5. `LPVOID lpBase`: 这是将共享内存映射到当前进程地址空间的指针，通过 `MapViewOfFile` 函数实现。这个指针指向共享内存的起始地址，允许程序直接在内存中读写共享数据。



```c++
HANDLE hSemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, L"mySemaphore");
```

这段代码使用了 `OpenSemaphore` 函数打开了一个**命名信号量对象**，并将返回的句柄存储在 `HANDLE hSemaphore` 中。

具体来说：
- `OpenSemaphore`: 这是一个 Windows API 函数，用于打开一个已存在的命名信号量对象。
- `EVENT_ALL_ACCESS`: 这是一个访问权限掩码，指定了对信号量的所有可能操作的访问权限。在这个例子中，`EVENT_ALL_ACCESS` 表示允许完全控制信号量，包括修改信号量的状态、等待和释放信号量等操作。
- `FALSE`: 这个参数指示函数不会创建新的信号量对象，而是打开一个已存在的对象。
- `"mySemaphore"`: 这是命名信号量的名称。命名信号量是一种可以跨进程使用的同步对象，通过指定名称，不同的进程可以共享同一个信号量对象。

因此，这行代码的作用是打开一个名为 `"mySemaphore"` 的命名信号量，并将其句柄存储在 `hSemaphore` 中，以便后续的代码可以使用该句柄来对信号量进行操作，如等待信号量或释放信号量。



```c++
HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemory");
```

这段代码使用了 `OpenFileMapping` 函数打开了一个命名的**共享内存对象**，并将返回的句柄存储在 `HANDLE hMapFile` 中。

具体来说：
- `OpenFileMapping`: 这是一个 Windows API 函数，用于打开一个已存在的文件映射对象。
- `FILE_MAP_ALL_ACCESS`: 这是一个访问权限掩码，指定了对文件映射对象的所有可能操作的访问权限。在这个例子中，`FILE_MAP_ALL_ACCESS` 表示允许完全控制文件映射对象，包括读取和写入文件映射、修改映射的大小等操作。
- `NULL`: 这是一个指向安全属性的指针，表示不使用任何安全属性。
- `"ShareMemory"`: 这是命名的共享内存对象的名称。命名的共享内存对象是一种允许不同进程之间共享数据的机制，通过指定名称，不同的进程可以访问同一个共享内存对象。

因此，这行代码的作用是打开一个名为 `"ShareMemory"` 的命名共享内存对象，并将其句柄存储在 `hMapFile` 中，以便后续的代码可以使用该句柄来对共享内存进行操作，如读取和写入共享数据。



```c++
LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(info));
```

这段代码调用了 `MapViewOfFile` 函数，将一个已存在的文件映射对象映射到当前进程的地址空间中，并返回该映射的起始地址。

具体解释如下：
- `MapViewOfFile`：这是一个 Windows API 函数，用于将文件映射对象映射到进程的地址空间中。
- `hMapFile`：这是一个已存在的文件映射对象的句柄，通过前面调用 `OpenFileMapping` 函数获取。
- `FILE_MAP_ALL_ACCESS`：这个参数指定了对映射对象的访问权限。在这里，`FILE_MAP_ALL_ACCESS` 表示允许完全控制映射对象，包括读取和写入映射。
- `0, 0`：这两个参数指定了映射对象的偏移量。在这里，偏移量为 0，表示从文件或文件映射对象的起始位置开始映射。
- `sizeof(info)`：这个参数指定了要映射的字节数。在这里，`sizeof(info)` 表示要映射的字节数等于 `info` 结构体的大小。

因此，这行代码的作用是将大小为 `sizeof(info)` 字节的文件映射对象映射到当前进程的地址空间中，并返回该映射的起始地址，该地址存储在 `LPVOID lpBase` 变量中。这样，程序就可以直接访问这块共享内存，用于读取和写入数据。



> 后面的部分都是在实现了通用的函数 Hook 操作，即在某个特定函数被调用前后，注入自定义的逻辑。这个过程可以分为以下几个步骤：
>
> 1. **定义原始函数指针：**
>    - 定义一个指针，用于保存原始函数的地址。
>
> 2. **定义替换函数：**
>    - 实现一个新的函数来替换原始函数，新函数拥有与原始函数相同的签名。
>    - 在新函数中，首先记录函数参数的信息，例如参数的值和函数调用的时间。
>    - 将记录的信息写入共享内存中，以便其他进程可以访问。
>    - 通过信号量通知其他进程有新的信息可供读取。
>    - 调用原始函数，并将其返回值返回给调用方。
>
> 3. **通过 Hook 替换函数：**
>    - 将新函数地址赋值给原始函数指针，从而将新函数替换原始函数。
>    - 这样，当原始函数被调用时，实际执行的是新函数，从而实现了对原始函数的 Hook 操作。
>
> 4. **共享信息：**
>    - 使用共享内存来存储记录的函数参数信息，以便其他进程可以访问和处理。
>    - 使用信号量来通知其他进程有新的信息可供读取，实现进程间的同步和通信。
>
> 通过这个通用的 Hook 操作，可以实现对任意函数的调用监控和记录，从而实现诸如调试、性能分析、安全监控等功能。



> Hook（钩子）操作是一种在计算机编程中常用的技术，用于拦截和修改特定函数或事件的行为。通过Hook操作，可以在目标函数执行前后插入自定义的代码，从而实现对函数行为的监视、修改或扩展。
>
> Hook操作通常分为两种类型：
>
> 1. **API Hooking（API钩子）**：这种类型的Hook操作针对系统API函数。通过修改系统函数的地址或在函数执行时拦截函数调用，可以实现对系统函数行为的监视和修改。API钩子可以用于实现诸如监视系统调用、键盘输入、鼠标事件等功能。
>
> 2. **函数Hooking（函数钩子）**：这种类型的Hook操作针对自定义的函数。通过替换目标函数的地址或在函数执行时插入自定义的代码，可以实现对函数行为的监视、修改或扩展。函数钩子可以用于实现诸如调试、性能分析、安全监控等功能。
>
> Hook操作通常涉及以下步骤：
>
> - **定位目标函数**：确定需要Hook的目标函数，并获取其地址或指针。
>   
> - **替换或拦截函数**：通过修改目标函数的地址或指针，将其指向自定义的函数或代码段，从而实现对函数行为的修改或拦截。
>
> - **执行自定义逻辑**：在自定义的函数或代码段中执行所需的逻辑，例如记录参数信息、修改返回值、拦截错误等。
>
> - **调用原始函数**：在必要时调用原始函数，以确保程序的正常运行。
>
> Hook操作在计算机编程中有着广泛的应用，可以用于实现各种功能，如调试、监控、安全检测等。然而，需要注意的是，Hook操作可能会对系统或程序的稳定性和安全性产生影响，因此在实现Hook操作时需要谨慎考虑。



# NewMessageBoxA

```c++
static int (WINAPI* OldMessageBoxA)(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType) = MessageBoxA;
```

这段代码实现了一个函数指针 `OldMessageBoxA`，用于保存原始的 `MessageBoxA` 函数的地址。

具体解释如下：

- `static int (WINAPI* OldMessageBoxA)(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType)`: 这是一个函数指针的声明。它的类型为 `int (WINAPI*)(HWND, LPCSTR, LPCSTR, UINT)`，表示指向一个返回类型为 `int`、参数类型为 `HWND`、`LPCSTR`、`LPCSTR` 和 `UINT` 的函数的指针。`WINAPI` 是一种调用约定，用于指定函数的调用规则。这里的函数指针名为 `OldMessageBoxA`。

- `= MessageBoxA;`：这是一个赋值语句，将 `MessageBoxA` 函数的地址赋值给了 `OldMessageBoxA`。因为 `MessageBoxA` 是 Windows API 中用于创建消息框的函数，通过将其地址赋值给 `OldMessageBoxA`，我们就可以在后续的代码中使用 `OldMessageBoxA` 来调用原始的 `MessageBoxA` 函数。

在这段代码中，参数的意思如下：

- `_In_opt_ HWND hWnd`：表示窗口句柄。`_In_opt_` 是 Microsoft Windows 数据类型标记，表示这个参数是一个输入参数，但可以为NULL（可选的）。`HWND` 是一个 Windows 数据类型，表示窗口句柄，它是一个指向窗口数据结构的指针。

- `_In_opt_ LPCSTR lpText`：表示消息框中显示的文本。`_In_opt_` 表示这个参数是一个输入参数，但可以为NULL（可选的）。`LPCSTR` 是一个 Windows 数据类型，表示一个指向以 null 结尾的字符串的指针，这里用来指向要显示的文本。

- `_In_opt_ LPCSTR lpCaption`：表示消息框的标题。`_In_opt_` 表示这个参数是一个输入参数，但可以为NULL（可选的）。`LPCSTR` 同上，用来指向消息框的标题。

- `_In_ UINT uType`：表示消息框的类型。`_In_` 表示这个参数是一个输入参数，不能为NULL。`UINT` 是一个 Windows 数据类型，表示无符号整数，这里用来指定消息框的类型，例如信息、警告、错误等。

总之，这些参数一起定义了 `MessageBoxA` 函数的原型，它们用于指定消息框的显示内容、样式和行为。



```c++
// 定义需要替换的新的函数
extern "C" __declspec(dllexport) int WINAPI
NewMessageBoxA(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType) {
    // 向sendInfo中写入数据
    sendInfo.type = MESSAGEBOXA;
    GetLocalTime(&(sendInfo.st));
    sendInfo.argNum = 4;
    // 参数名
    sprintf(sendInfo.argName[0], "hWnd");
    sprintf(sendInfo.argName[1], "lpText");
    sprintf(sendInfo.argName[2], "lpCaption");
    sprintf(sendInfo.argName[3], "uType");
    // 参数值
    sprintf(sendInfo.argValue[0], "%08X", hWnd);
    sprintf(sendInfo.argValue[1], "%s", lpText);
    sprintf(sendInfo.argValue[2], "%s", lpCaption);
    sprintf(sendInfo.argValue[3], "%08X", uType);
    // 将sendinfo赋值到共享内存
    memcpy(lpBase, &sendInfo, sizeof(info));
    // 进行V操作，使得信号量+1
    ReleaseSemaphore(hSemaphore, 1, NULL);
    sendInfo.argNum = 0;
    // 返回原始接口
    return OldMessageBoxA(hWnd, lpText, lpCaption, uType);
}
```

这段代码实现了一个新的函数 `NewMessageBoxA`，用于替换原始的 `MessageBoxA` 函数。

具体解释如下：

- `extern "C" __declspec(dllexport) int WINAPI NewMessageBoxA(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType)`: 这是一个新函数的声明。`extern "C"` 用于指定 C++ 编译器按照 C 语言的方式进行名称修饰，以便外部程序能够正确地调用这个函数。`__declspec(dllexport)` 用于指定这个函数应该被导出，以便外部程序可以调用它。`int WINAPI` 表示这个函数返回一个整数，使用了 `WINAPI` 调用约定，确保函数调用规则与 Windows API 函数一致。

- 函数体内部实现了对 `MessageBoxA` 函数的替换逻辑：
   - 首先，将函数的参数信息写入到一个名为 `sendInfo` 的结构体中，包括函数的类型、系统时间、参数数量、参数名和参数值。
   - 然后，将 `sendInfo` 结构体的内容复制到共享内存区域中，以便其他进程可以读取到这些信息。
   - 接着，通过信号量的释放操作，通知其他进程有新的信息可供读取。
   - 最后，调用原始的 `MessageBoxA` 函数，并将其返回值返回给调用方。

通过这段代码，我们实现了对 `MessageBoxA` 函数的 Hook 操作，即在函数调用前后执行了自定义的逻辑，并且保留了原始函数的功能。

四个参数分别是 `MessageBoxA` 函数的四个参数的名称，对应于 `MessageBoxA` 函数的四个参数，即：

1. `hWnd`：窗口句柄，表示消息框的父窗口句柄或者拥有者窗口句柄。

2. `lpText`：消息框中显示的文本。

3. `lpCaption`：消息框的标题文本。

4. `uType`：消息框的类型，指定消息框的样式，如信息、警告、错误等。

在这段代码中，通过 `sprintf` 函数将这些参数的名称依次写入了一个名为 `sendInfo` 的结构体中的 `argName` 数组中，以便在后续的操作中记录和共享这些参数的名称信息。



# NewMessageBoxW

> `MessageBoxA` 和 `MessageBoxW` 是 Windows API 中用于创建消息框（MessageBox）的函数，它们的区别在于它们所使用的字符集不同。
>
> - `MessageBoxA`：以 ANSI 字符集（ASCII）编码处理参数，即单字节字符集。通常在使用英文版 Windows 系统或需要与旧版本 Windows 兼容时使用。
>
> - `MessageBoxW`：以宽字符集（Unicode）编码处理参数，即双字节字符集。通常在需要支持多语言、国际化的程序中使用，因为 Unicode 能够表示世界上所有的字符。
>
> 在一般情况下，建议使用 `MessageBoxW`，因为它更加通用、能够支持更多的语言和字符集。如果你的应用程序不需要与旧版本的 Windows 兼容，并且需要支持多语言或特殊字符，那么最好使用 `MessageBoxW`。



```c++
WideCharToMultiByte(CP_ACP, 0, lpText, wcslen(lpText), temp, sizeof(temp), NULL, NULL);
```

这段代码使用了 Windows API 函数 `WideCharToMultiByte`，用于将宽字符（Unicode）转换为多字节字符（ANSI）。

具体解释如下：

- `WideCharToMultiByte`：这是一个 Windows API 函数，用于将宽字符（Unicode）字符串转换为多字节字符（ANSI）字符串。

- `CP_ACP`：这是一个常量，表示当前用户的 ANSI 代码页（代码页默认由当前用户的区域设置决定），即当前系统使用的 ANSI 字符集。在这里，`CP_ACP` 表示使用当前系统的 ANSI 字符集进行转换。

- `0`：这是一个标志参数，通常设置为0。

- `lpText`：这是一个指向宽字符（Unicode）字符串的指针，即需要进行转换的字符串。

- `wcslen(lpText)`：这是一个函数调用，用于获取宽字符字符串的长度，`wcslen` 是一个计算宽字符字符串长度的函数。

- `temp`：这是一个缓冲区，用于存储转换后的多字节字符（ANSI）字符串。

- `sizeof(temp)`：这是缓冲区 `temp` 的大小，用于指定转换后的多字节字符（ANSI）字符串的最大长度。

- `NULL, NULL`：这两个参数用于指定默认值，分别表示默认的字符默认替换字符和指向默认字符是否使用的指针。

通过调用 `WideCharToMultiByte` 函数，可以将宽字符（Unicode）字符串 `lpText` 转换为多字节字符（ANSI）字符串，并存储在缓冲区 `temp` 中。

四个参数分别对应于 `MessageBoxW` 函数的四个参数：

1. `hWnd`：表示窗口句柄，即消息框的父窗口句柄或者拥有者窗口句柄。
2. `lpText`：表示消息框中显示的文本。
3. `lpCaption`：表示消息框的标题文本。
4. `uType`：表示消息框的类型，指定消息框的样式，例如信息、警告、错误等。



# NewCreateFile

```c++
static HANDLE(WINAPI* OldCreateFile)(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    ) = CreateFile;
```

这段代码定义了一个函数指针 `OldCreateFile`，用于保存原始的 `CreateFile` 函数的地址。

具体解释如下：

- `static HANDLE(WINAPI* OldCreateFile)(...)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`HANDLE` 表示函数的返回类型是一个句柄（handle），表示文件或设备的句柄。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `(...) = CreateFile;`：这是一个赋值语句，将 `CreateFile` 函数的地址赋值给了 `OldCreateFile`。`CreateFile` 是一个 Windows API 函数，用于创建或打开文件或设备。这样一来，我们就可以通过 `OldCreateFile` 来调用原始的 `CreateFile` 函数。

关于参数的具体解释如下：

- `LPCWSTR lpFileName`：这是一个指向以 null 结尾的 Unicode 字符串的常量指针，表示要创建或打开的文件的名称。

- `DWORD dwDesiredAccess`：这是一个无符号双字长整数，表示请求的对文件的访问权限。

- `DWORD dwShareMode`：这是一个无符号双字长整数，表示文件的共享模式，即文件可以与其他进程共享的方式。

- `LPSECURITY_ATTRIBUTES lpSecurityAttributes`：这是一个指向 SECURITY_ATTRIBUTES 结构体的指针，用于指定文件的安全性属性。

- `DWORD dwCreationDisposition`：这是一个无符号双字长整数，表示如何创建或打开文件，以及操作如果文件已存在时应如何处理。

- `DWORD dwFlagsAndAttributes`：这是一个无符号双字长整数，表示文件的属性和标志。它可以包含文件的属性和一些特殊标志，如 FILE_ATTRIBUTE_NORMAL 等。

- `HANDLE hTemplateFile`：这是一个文件句柄，用于指定一个文件作为模板文件来创建新文件的属性。通常为 `NULL`。

这些参数共同定义了 `CreateFile` 函数的签名，其中 `CreateFile` 是一个 Windows API 函数，用于创建或打开文件或设备。通过将其地址赋值给 `OldCreateFile`，我们可以在后续代码中使用 `OldCreateFile` 来调用原始的 `CreateFile` 函数。



```c++
HANDLE hFile = OldCreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
```

这段代码调用了之前保存的原始 `CreateFile` 函数，创建或打开一个文件，并将返回的文件句柄存储在 `hFile` 变量中。

具体解释如下：

- `HANDLE hFile`：这是一个文件句柄变量，用于存储 `CreateFile` 函数返回的文件句柄，表示对创建或打开的文件的引用。

- `OldCreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile)`：这是调用之前保存的原始 `CreateFile` 函数的语句。根据之前给定的参数，它传递了文件名 `lpFileName`、期望的访问权限 `dwDesiredAccess`、共享模式 `dwShareMode`、安全属性 `lpSecurityAttributes`、创建方式 `dwCreationDisposition`、标志和属性 `dwFlagsAndAttributes` 以及模板文件句柄 `hTemplateFile`。这些参数与原始 `CreateFile` 函数的参数相匹配。

这样，`hFile` 变量就保存了 `CreateFile` 函数返回的文件句柄，可以在后续的代码中使用该句柄进行文件操作。

七个参数看上面。



# NewWriteFile

```c++
static BOOL(WINAPI* OldWriteFile)(
    HANDLE hFile,
    LPCVOID lpBuffer,
    DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    ) = WriteFile;
```

这段代码定义了一个函数指针 `OldWriteFile`，用于保存 `WriteFile` 函数的地址，并且指定了 `WriteFile` 函数的参数列表。

具体解释如下：

- `static BOOL(WINAPI* OldWriteFile)(...)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`BOOL` 表示函数的返回类型是一个布尔值，表示写入操作是否成功。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `(...) = WriteFile;`：这是一个赋值语句，将 `WriteFile` 函数的地址赋值给了 `OldWriteFile`。`WriteFile` 是一个 Windows API 函数，用于向文件中写入数据。这样一来，我们就可以通过 `OldWriteFile` 来调用原始的 `WriteFile` 函数。



```c++
HANDLE hFile,
LPCVOID lpBuffer,
DWORD nNumberOfBytesToWrite,
LPDWORD lpNumberOfBytesWritten,
LPOVERLAPPED lpOverlapped
```

这五个参数是 `WriteFile` 函数的参数，具体解释如下：

1. `HANDLE hFile`：
   - 这是一个文件句柄，表示要写入数据的文件的句柄。
   - `HANDLE` 是 Windows 平台上的数据类型，用于表示句柄（handle），它是一个指向文件、设备或内核对象的引用。

2. `LPCVOID lpBuffer`：
   - 这是一个指向常量缓冲区的指针，表示要写入的数据的起始地址。
   - `LPCVOID` 是 Windows 平台上的数据类型，表示一个指向常量内容的指针，因此在函数内部不能修改指向的数据。

3. `DWORD nNumberOfBytesToWrite`：
   - 这是一个双字长无符号整数，表示要写入的数据的字节数。
   - `DWORD` 是 Windows 平台上的数据类型，表示一个无符号双字长整数。

4. `LPDWORD lpNumberOfBytesWritten`：
   - 这是一个指向双字长无符号整数的指针，表示函数成功写入的字节数。
   - `LPDWORD` 是 Windows 平台上的数据类型，表示一个指向双字长无符号整数的指针。在函数调用完成后，该指针将被写入函数成功写入的字节数。

5. `LPOVERLAPPED lpOverlapped`：
   - 这是一个指向 `OVERLAPPED` 结构体的指针，用于指定文件操作的偏移量和异步操作的状态。
   - `LPOVERLAPPED` 是 Windows 平台上的数据类型，表示一个指向 `OVERLAPPED` 结构体的指针，该结构体用于指定文件操作的偏移量和异步操作的状态。如果是同步操作，可以传递 `NULL`。



# NewReadFile

```c++
static BOOL(WINAPI* OldReadFile)(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    ) = ReadFile;
```

这段代码定义了一个函数指针 `OldReadFile`，用于保存 `ReadFile` 函数的地址，并且指定了 `ReadFile` 函数的参数列表。

具体解释如下：

- `static BOOL(WINAPI* OldReadFile)(...)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`BOOL` 表示函数的返回类型是一个布尔值，表示读取操作是否成功。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `(...) = ReadFile;`：这是一个赋值语句，将 `ReadFile` 函数的地址赋值给了 `OldReadFile`。`ReadFile` 是一个 Windows API 函数，用于从文件中读取数据。这样一来，我们就可以通过 `OldReadFile` 来调用原始的 `ReadFile` 函数。



```c++
HANDLE hFile,
LPVOID lpBuffer,
DWORD nNumberOfBytesToRead,
LPDWORD lpNumberOfBytesRead,
LPOVERLAPPED lpOverlapped
```

这五个参数是 `ReadFile` 函数的参数，具体解释如下：

1. `HANDLE hFile`：
   - 这是一个文件句柄，表示要读取数据的文件的句柄。
   - `HANDLE` 是 Windows 平台上的数据类型，用于表示句柄（handle），它是一个指向文件、设备或内核对象的引用。

2. `LPVOID lpBuffer`：
   - 这是一个指向缓冲区的指针，表示存储读取数据的缓冲区的起始地址。
   - `LPVOID` 是 Windows 平台上的数据类型，表示一个指向任意类型的指针。

3. `DWORD nNumberOfBytesToRead`：
   - 这是一个双字长无符号整数，表示要读取的数据的字节数。
   - `DWORD` 是 Windows 平台上的数据类型，表示一个无符号双字长整数。

4. `LPDWORD lpNumberOfBytesRead`：
   - 这是一个指向双字长无符号整数的指针，表示函数成功读取的字节数。
   - `LPDWORD` 是 Windows 平台上的数据类型，表示一个指向双字长无符号整数的指针。在函数调用完成后，该指针将被写入函数成功读取的字节数。

5. `LPOVERLAPPED lpOverlapped`：
   - 这是一个指向 `OVERLAPPED` 结构体的指针，用于指定文件操作的偏移量和异步操作的状态。
   - `LPOVERLAPPED` 是 Windows 平台上的数据类型，表示一个指向 `OVERLAPPED` 结构体的指针，该结构体用于指定文件操作的偏移量和异步操作的状态。如果是同步操作，可以传递 `NULL`。



# NewHeapCreate

```c++
static HANDLE(WINAPI* OldHeapCreate)(DWORD fIOoptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) = HeapCreate;
```

这段代码定义了一个函数指针 `OldHeapCreate`，用于保存 `HeapCreate` 函数的地址，并且指定了 `HeapCreate` 函数的参数列表。

具体解释如下：

- `static HANDLE(WINAPI* OldHeapCreate)(DWORD fIOoptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`HANDLE` 表示函数的返回类型是一个句柄（handle），表示创建的堆的句柄。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `(...) = HeapCreate;`：这是一个赋值语句，将 `HeapCreate` 函数的地址赋值给了 `OldHeapCreate`。`HeapCreate` 是一个 Windows API 函数，用于创建一个私有堆（heap）。这样一来，我们就可以通过 `OldHeapCreate` 来调用原始的 `HeapCreate` 函数。



```c++
sprintf(sendInfo.argName[0], "fIOoptions");
sprintf(sendInfo.argName[1], "dwInitialSize");
sprintf(sendInfo.argName[2], "dwMaximumSize");
sprintf(sendInfo.argName[3], "HANDLE");
```

以下是对这段代码中的四个参数的解释：

1. `DWORD fIOoptions`：
   - 这是一个双字长无符号整数，表示堆的选项标志。它指定了堆的属性，例如是否为可共享的、是否为可执行的等。
   
2. `SIZE_T dwInitialSize`：
   - 这是一个无符号长整数，表示堆的初始大小（以字节为单位）。它指定了堆在初始化时所分配的内存大小。

3. `SIZE_T dwMaximumSize`：
   - 这是一个无符号长整数，表示堆的最大大小（以字节为单位）。它指定了堆在需要时可以扩展到的最大大小。

4. `HANDLE hFile`：
   - 这是一个文件句柄，实际上是一个堆的句柄。在这段代码中，原始的 `HeapCreate` 函数返回的堆句柄被存储在这个变量中，然后作为参数传递给 `sprintf` 函数，以便将其值记录到 `sendInfo` 结构体中。

总的来说，这四个参数分别用于指定堆的选项、初始大小、最大大小以及堆的句柄。



# NewHeapDestory

```c++
static BOOL(WINAPI* OldHeapDestory)(HANDLE) = HeapDestroy;
```

这段代码定义了一个函数指针 `OldHeapDestroy`，用于保存 `HeapDestroy` 函数的地址，并且指定了 `HeapDestroy` 函数的参数列表。

具体解释如下：

- `static BOOL(WINAPI* OldHeapDestroy)(HANDLE)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`BOOL` 表示函数的返回类型是一个布尔值，表示销毁操作是否成功。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `= HeapDestroy;`：这是一个赋值语句，将 `HeapDestroy` 函数的地址赋值给了 `OldHeapDestroy`。`HeapDestroy` 是一个 Windows API 函数，用于销毁先前创建的堆。这样一来，我们就可以通过 `OldHeapDestroy` 来调用原始的 `HeapDestroy` 函数。



```c++
sprintf(sendInfo.argName[0], "hHeap");
```

在这段代码中，参数 `hHeap` 表示一个堆的句柄。具体解释如下：

- `HANDLE hHeap`：
   - 这是一个文件句柄，实际上是一个堆的句柄。在这段代码中，它作为参数传递给 `NewHeapDestory` 函数。这个参数表示要销毁的堆的句柄。函数 `HeapDestroy` 接受这个句柄作为参数，用于销毁对应的堆。

在函数 `NewHeapDestory` 中，首先将这个参数的名称记录到 `sendInfo` 结构体的 `argName` 数组中，然后将其值转换为十六进制格式，并存储到 `sendInfo` 结构体的 `argValue` 数组中。最后，将参数信息及其他信息写入共享内存，以便其他地方可以读取并进行相应的处理。



# NewHeapFree

```c++
static BOOL(WINAPI* OldHeapFree)(HANDLE hHeap, DWORD dwFlags, _Frees_ptr_opt_ LPVOID lpMem) = HeapFree;
```

这段代码定义了一个函数指针 `OldHeapFree`，用于保存 `HeapFree` 函数的地址，并且指定了 `HeapFree` 函数的参数列表。

具体解释如下：

- `static BOOL(WINAPI* OldHeapFree)(HANDLE hHeap, DWORD dwFlags, _Frees_ptr_opt_ LPVOID lpMem)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`BOOL` 表示函数的返回类型是一个布尔值，表示释放内存操作是否成功。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `= HeapFree;`：这是一个赋值语句，将 `HeapFree` 函数的地址赋值给了 `OldHeapFree`。`HeapFree` 是一个 Windows API 函数，用于释放先前分配的堆内存。这样一来，我们就可以通过 `OldHeapFree` 来调用原始的 `HeapFree` 函数。



```c++
sprintf(sendInfo.argName[0], "hHeap");
sprintf(sendInfo.argName[1], "dwFlags");
sprintf(sendInfo.argName[2], "lpMem");
```

这段代码是用于替换原始的 `HeapFree` 函数的新函数 `NewHeapFree`，并记录了函数调用的参数信息。

以下是对这段代码中的三个参数的解释：

1. `HANDLE hHeap`：
   - 这是一个文件句柄，实际上是一个堆的句柄。它表示要释放内存的堆的句柄。

2. `DWORD dwFlags`：
   - 这是一个双字长无符号整数，表示释放内存的选项标志。这些标志可以指定要释放的内存块的类型或行为。

3. `_Frees_ptr_opt_ LPVOID lpMem`：
   - 这是一个指向内存块的指针，表示要释放的内存的起始地址。由于 `_Frees_ptr_opt_` 是一个注解，用于指示内存指针是一个可选的释放指针，可以为 `NULL`。`LPVOID` 是一个指向任意类型的指针。

在函数 `NewHeapFree` 中，首先将这三个参数的名称记录到 `sendInfo` 结构体的 `argName` 数组中，然后将其值转换为十六进制格式，并存储到 `sendInfo` 结构体的 `argValue` 数组中。最后，将参数信息及其他信息写入共享内存，以便其他地方可以读取并进行相应的处理。



# NewRegCreateKeyEx

```c++
static LSTATUS(WINAPI* OldRegCreateKeyEx)(
    HKEY hKey,
    LPCWSTR lpSubKey,
    DWORD Reserved,
    LPWSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition) = RegCreateKeyEx;
```

这段代码定义了一个函数指针 `OldRegCreateKeyEx`，用于保存 `RegCreateKeyEx` 函数的地址，并且指定了 `RegCreateKeyEx` 函数的参数列表。

具体解释如下：

- `static LSTATUS(WINAPI* OldRegCreateKeyEx)(...)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`LSTATUS` 表示函数的返回类型是一个长整数，用于表示函数执行的状态。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `= RegCreateKeyEx;`：这是一个赋值语句，将 `RegCreateKeyEx` 函数的地址赋值给了 `OldRegCreateKeyEx`。`RegCreateKeyEx` 是一个 Windows API 函数，用于创建或打开注册表项。这样一来，我们就可以通过 `OldRegCreateKeyEx` 来调用原始的 `RegCreateKeyEx` 函数。



```c++
HKEY hKey,
LPCWSTR lpSubKey,
DWORD Reserved,
LPWSTR lpClass,
DWORD dwOptions,
REGSAM samDesired,
const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
PHKEY phkResult,
LPDWORD lpdwDisposition
```

这些参数是用于调用 `RegCreateKeyEx` 函数的，具体解释如下：

1. `HKEY hKey`：
   - 这是一个表示已经打开的注册表项的句柄，指定了要在其中创建或打开子项的父项。
   - `HKEY` 是 Windows 平台上的一个数据类型，表示注册表项的句柄。

2. `LPCWSTR lpSubKey`：
   - 这是一个以 null 结尾的字符串，指定了要创建或打开的子项的名称。
   - `LPCWSTR` 是 Windows 平台上的一个数据类型，表示一个指向以 null 结尾的 Unicode 字符串的指针。

3. `DWORD Reserved`：
   - 这是一个保留参数，必须为零。

4. `LPWSTR lpClass`：
   - 这是一个以 null 结尾的字符串，指定了新创建子项的类的名称。
   - `LPWSTR` 是 Windows 平台上的一个数据类型，表示一个指向以 null 结尾的 Unicode 字符串的指针。

5. `DWORD dwOptions`：
   - 这是一个双字长无符号整数，指定了创建子项的选项。
   
6. `REGSAM samDesired`：
   - 这是一个双字长无符号整数，指定了子项的访问权限。
   
7. `const LPSECURITY_ATTRIBUTES lpSecurityAttributes`：
   - 这是一个指向 `SECURITY_ATTRIBUTES` 结构的指针，指定了新创建的子项的安全描述符。
   
8. `PHKEY phkResult`：
   - 这是一个指向 `HKEY` 类型的指针，用于接收新创建或打开的子项的句柄。

9. `LPDWORD lpdwDisposition`：
   - 这是一个指向双字长无符号整数的指针，用于接收指示操作结果的值。



# NewRegSetValueEx

```c++
static LSTATUS(WINAPI* OldRegSetValueEx)(
    HKEY hKey,
    LPCWSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    const BYTE* lpData,
    DWORD cbData
    ) = RegSetValueEx;
```

这段代码定义了一个函数指针 `OldRegSetValueEx`，用于保存 `RegSetValueEx` 函数的地址，并且指定了 `RegSetValueEx` 函数的参数列表。

具体解释如下：

- `static LSTATUS(WINAPI* OldRegSetValueEx)(...)`：这是一个函数指针的声明。`static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。`LSTATUS` 表示函数的返回类型是一个长整数，用于表示函数执行的状态。`WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。括号中的参数列表表示这个函数指针指向的函数的参数列表。

- `= RegSetValueEx;`：这是一个赋值语句，将 `RegSetValueEx` 函数的地址赋值给了 `OldRegSetValueEx`。`RegSetValueEx` 是一个 Windows API 函数，用于设置指定注册表项的值。这样一来，我们就可以通过 `OldRegSetValueEx` 来调用原始的 `RegSetValueEx` 函数。



```c++
HKEY hKey,
LPCWSTR lpValueName,
DWORD Reserved,
DWORD dwType,
const BYTE* lpData,
DWORD cbData
```

这六个参数是用于调用 `RegSetValueEx` 函数的，具体解释如下：

1. `HKEY hKey`：
   - 这是一个表示已经打开的注册表项的句柄，指定了要设置其值的注册表项。
   - `HKEY` 是 Windows 平台上的一个数据类型，表示注册表项的句柄。

2. `LPCWSTR lpValueName`：
   - 这是一个以 null 结尾的字符串，指定了要设置的注册表项的值的名称。
   - `LPCWSTR` 是 Windows 平台上的一个数据类型，表示一个指向以 null 结尾的 Unicode 字符串的指针。

3. `DWORD Reserved`：
   - 这是一个保留参数，必须为零。

4. `DWORD dwType`：
   - 这是一个双字长无符号整数，指定了要设置的注册表项值的数据类型。
   - 数据类型可以是诸如 `REG_SZ`（字符串值）、`REG_DWORD`（双字长整数值）等。

5. `const BYTE* lpData`：
   - 这是一个指向数据的指针，指定了要设置的注册表项的值的数据。
   - 数据以字节为单位，并且可以是任意类型的数据。

6. `DWORD cbData`：
   - 这是一个双字长无符号整数，指定了要设置的注册表项的值的数据的大小（以字节为单位）。
   - 它指定了参数 `lpData` 指向的数据的长度。



# NewRegCloseKey

```c++
static LSTATUS(WINAPI* OldRegCloseKey)(HKEY hKey) = RegCloseKey;
```

这段代码定义了一个函数指针 `OldRegCloseKey`，用于保存 `RegCloseKey` 函数的地址，并且指定了 `RegCloseKey` 函数的参数列表。

具体解释如下：

- `static LSTATUS(WINAPI* OldRegCloseKey)(HKEY hKey)`：
  - `static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。
  - `LSTATUS` 表示函数的返回类型是一个长整数，用于表示函数执行的状态。
  - `WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。
  - 括号中的参数列表表示这个函数指针指向的函数的参数列表，其中 `HKEY hKey` 表示要关闭的注册表项的句柄。

- `= RegCloseKey;`：
  - 这是一个赋值语句，将 `RegCloseKey` 函数的地址赋值给了 `OldRegCloseKey`。
  - `RegCloseKey` 是一个 Windows API 函数，用于关闭先前打开的注册表项。这样一来，我们就可以通过 `OldRegCloseKey` 来调用原始的 `RegCloseKey` 函数。



```c++
HKEY hKey
```

`HKEY hKey` 这个参数表示注册表项的句柄。在 Windows 系统中，注册表是一个重要的数据库，用于存储系统配置信息、应用程序设置等。注册表中的数据以树形结构组织，每个节点称为一个注册表项。`HKEY` 是一个抽象数据类型，用于表示注册表项的句柄。在 Windows API 中，大多数注册表操作都需要一个注册表项的句柄作为参数，以指定要操作的注册表项。`hKey` 参数就是用于传递这个注册表项的句柄的。



# NewRegOpenKeyEx

```c++
static LSTATUS(WINAPI* OldRegOpenKeyEx)(
    HKEY hKey,
    LPCWSTR lpSubKey,
    DWORD ulOptions,
    REGSAM samDesired,
    PHKEY phkResult
    ) = RegOpenKeyEx;
```



```c++
HKEY hKey,
LPCWSTR lpSubKey,
DWORD ulOptions,
REGSAM samDesired,
PHKEY phkResult
```

这段代码是用于替换原始的 `RegOpenKeyEx` 函数的新函数 `NewRegOpenKeyEx`，并记录了函数调用的参数信息。

以下是对这段代码中的五个参数的解释：

1. `HKEY hKey`：
   - 这是一个表示已经打开的注册表项的句柄，指定了要在其中打开子项的父项。
   - `HKEY` 是 Windows 平台上的一个数据类型，表示注册表项的句柄。

2. `LPCWSTR lpSubKey`：
   - 这是一个以 null 结尾的字符串，指定了要打开的子项的名称。
   - `LPCWSTR` 是 Windows 平台上的一个数据类型，表示一个指向以 null 结尾的 Unicode 字符串的指针。

3. `DWORD ulOptions`：
   - 这是一个双字长无符号整数，指定了打开子项的选项。
   
4. `REGSAM samDesired`：
   - 这是一个双字长无符号整数，指定了子项的访问权限。
   
5. `PHKEY phkResult`：
   - 这是一个指向 `HKEY` 类型的指针，用于接收新打开的子项的句柄。

在函数 `NewRegOpenKeyEx` 中，首先将这五个参数的名称记录到 `sendInfo` 结构体的 `argName` 数组中，然后将其值转换为十六进制格式，并存储到 `sendInfo` 结构体的 `argValue` 数组中。最后，将参数信息及其他信息写入共享内存，以便其他地方可以读取并进行相应的处理。



> `NewRegCloseKey` 和 `OldRegOpenKeyEx` 是两个不同的函数，分别用于关闭注册表项和打开注册表项。
>
> 1. `NewRegCloseKey`:
>    - 这是一个新函数，用于关闭注册表项。
>    - 这个函数可能是在原始函数的基础上进行了一些修改，比如添加了日志记录功能或者其他一些定制的功能。
>    - 它并不是 Windows API 中的标准函数，而是根据实际需求自定义的函数。
>
> 2. `OldRegOpenKeyEx`:
>    - 这是 Windows API 中的标准函数，用于打开注册表项。
>    - 在函数名中的 "Ex" 后缀表示 "Extended"，表示这是一个扩展的版本，通常会比原始版本提供更多的功能或者更灵活的参数选项。
>
> 所以，这两个函数的区别在于功能和实现。`NewRegCloseKey` 可能是一个自定义的函数，而 `OldRegOpenKeyEx` 是一个标准的 Windows API 函数，用于打开注册表项。



> `RegOpenKeyEx` 是一个 Windows API 函数，用于打开指定的注册表项，允许应用程序访问或修改该注册表项的值。
>
> 具体而言，`RegOpenKeyEx` 函数允许应用程序根据指定的注册表项路径和访问权限来打开一个注册表项。通过打开注册表项，应用程序可以读取或修改该注册表项的值，或者进一步访问该注册表项的子项。这在应用程序需要读取或修改特定配置信息、保存用户设置或者进行系统配置时非常有用。
>
> 该函数的参数包括要打开的注册表项的父项句柄、注册表项的路径、访问权限等等。通过合适的参数组合，应用程序可以在注册表中进行各种操作，从而实现对系统配置和应用程序设置的管理。



# NewRegDeleteValue

```c++
static LSTATUS(WINAPI* OldRegDeleteValue)(
    HKEY hKey,
    LPCWSTR lpValueName
    ) = RegDeleteValue;
```

这段代码定义了一个函数指针 `OldRegDeleteValue`，用于保存 `RegDeleteValue` 函数的地址，并且指定了 `RegDeleteValue` 函数的参数列表。

具体解释如下：

- `static LSTATUS(WINAPI* OldRegDeleteValue)(HKEY hKey, LPCWSTR lpValueName)`：
  - `static` 关键字表示这个函数指针是静态的，它在全局范围内可见，但只能在当前文件中使用。
  - `LSTATUS` 表示函数的返回类型是一个长整数，用于表示函数执行的状态。
  - `WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。
  - 括号中的参数列表表示这个函数指针指向的函数的参数列表，其中 `HKEY hKey` 表示要操作的注册表项的句柄，`LPCWSTR lpValueName` 表示要删除的注册表项的名称。

- `= RegDeleteValue;`：
  - 这是一个赋值语句，将 `RegDeleteValue` 函数的地址赋值给了 `OldRegDeleteValue`。
  - `RegDeleteValue` 是一个 Windows API 函数，用于删除指定注册表项下的特定值。



```c++
HKEY hKey,
LPCWSTR lpValueName
```

这段代码定义了一个新的函数 `NewRegDeleteValue`，用于替换原始的 `RegDeleteValue` 函数，并记录了函数调用的参数信息。

具体解释如下：

- `HKEY hKey`：
  - 这是一个表示注册表项的句柄，指定要在其中删除注册表值的注册表项。
  - `HKEY` 是 Windows 平台上的一个数据类型，用于表示注册表项的句柄。

- `LPCWSTR lpValueName`：
  - 这是一个指向以 null 结尾的 Unicode 字符串的指针，指定要删除的注册表值的名称。
  - `LPCWSTR` 是 Windows 平台上的一个数据类型，表示一个指向以 null 结尾的 Unicode 字符串的指针。

在函数 `NewRegDeleteValue` 中，首先将这两个参数的名称记录到 `sendInfo` 结构体的 `argName` 数组中，然后将其值转换为十六进制格式，并存储到 `sendInfo` 结构体的 `argValue` 数组中。最后，将参数信息及其他信息写入共享内存，以便其他地方可以读取并进行相应的处理。



# Newsocket

```c++
static SOCKET(WINAPI* Oldsocket)(
    int af,
    int type,
    int protocol
    ) = socket;
```

这段代码定义了一个名为 `Oldsocket` 的函数指针，它用于保存 `socket` 函数的地址，并指定了 `socket` 函数的参数列表。

具体解释如下：

- `static SOCKET(WINAPI* Oldsocket)(int af, int type, int protocol)`：
  - `static` 关键字表示这个函数指针是静态的，在全局范围内可见，但只能在当前文件中使用。
  - `SOCKET` 表示函数的返回类型是一个套接字类型，即在网络编程中用于表示一个网络套接字的数据类型。
  - `WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。
  - 括号中的参数列表表示这个函数指针指向的函数的参数列表，其中 `int af` 表示地址族（Address Family），`int type` 表示套接字类型，`int protocol` 表示协议类型。

- `= socket;`：
  - 这是一个赋值语句，将 `socket` 函数的地址赋值给了 `Oldsocket`。 
  - `socket` 是一个用于创建套接字的函数，其中参数 `af` 表示地址族，`type` 表示套接字类型，`protocol` 表示协议类型。



```c++
int af,
int type,
int protocol
```

这段代码定义了 `socket` 函数的参数列表，具体解释如下：

- `int af`：
  - `af` 是 `socket` 函数的第一个参数，表示地址族（Address Family），用于指定要创建的套接字使用的地址族。地址族决定了套接字的通信方式，例如 IPv4 或 IPv6。
  - 可能的取值包括：
    - `AF_INET`：表示 IPv4 地址族。
    - `AF_INET6`：表示 IPv6 地址族。
    - 其他自定义的地址族。

- `int type`：
  - `type` 是 `socket` 函数的第二个参数，表示套接字类型，用于指定套接字的通信方式。不同的套接字类型支持不同的通信特性。
  - 可能的取值包括：
    - `SOCK_STREAM`：表示流套接字，提供面向连接的、可靠的、双向的数据传输。常用于 TCP 协议。
    - `SOCK_DGRAM`：表示数据报套接字，提供无连接的、不可靠的数据传输。常用于 UDP 协议。
    - `SOCK_RAW`：表示原始套接字，提供对数据链路层的访问，允许用户定义自己的协议或发送原始数据帧。
    - 其他自定义的套接字类型。

- `int protocol`：
  - `protocol` 是 `socket` 函数的第三个参数，表示协议类型，用于指定要使用的传输协议。当 `type` 参数指定的套接字类型支持多种协议时，可以使用 `protocol` 参数来选择具体的协议。
  - 对于大多数情况，可以将 `protocol` 参数指定为 0，表示由系统自动选择适当的协议。

总之，这三个参数共同决定了创建套接字的方式，包括使用的地址族、套接字类型和传输协议。



# Newbind

```c++
static int (WINAPI* Oldbind)(
    SOCKET s,
    const sockaddr* name,
    int namelen
    ) = bind;
```

这段代码定义了一个名为 `Oldbind` 的函数指针，用于保存 `bind` 函数的地址，并指定了 `bind` 函数的参数列表。

具体解释如下：

- `static int (WINAPI* Oldbind)(SOCKET s, const sockaddr* name, int namelen)`：
  - `static` 关键字表示这个函数指针是静态的，在全局范围内可见，但只能在当前文件中使用。
  - `int` 表示函数的返回类型是一个整数，表示 `bind` 函数执行的结果或状态。
  - `WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。
  - 括号中的参数列表表示这个函数指针指向的函数的参数列表，其中 `SOCKET s` 表示套接字描述符，`const sockaddr* name` 表示指向地址结构体的指针，`int namelen` 表示地址结构体的长度。

- `= bind;`：
  - 这是一个赋值语句，将 `bind` 函数的地址赋值给了 `Oldbind`。 
  - `bind` 函数用于将一个套接字绑定到一个特定的地址和端口号上，以便应用程序能够通过该地址和端口号进行通信。



```c++
sprintf(sendInfo.argName[0], "s");
sprintf(sendInfo.argName[1], "name");
sprintf(sendInfo.argName[2], "namelen");
sprintf(sendInfo.argName[3], "IP");
sprintf(sendInfo.argName[4], "port");
```

这五个参数的含义解释如下：

1. `s`：
   - 表示套接字描述符（Socket Descriptor），用于标识正在操作的套接字。套接字描述符是一个整数值，由操作系统分配和管理。在网络编程中，套接字描述符是一个关键的标识符，用于在应用程序和操作系统之间传递套接字信息。

2. `name`：
   - 表示指向 `sockaddr` 结构体的指针，用于指定要绑定到套接字的地址和端口号信息。`sockaddr` 结构体是一个通用的地址结构体，用于表示各种类型的网络地址信息。

3. `namelen`：
   - 表示地址结构体的长度，即参数 `name` 所指向的地址结构体的大小。

4. `IP`：
   - 表示要绑定的主机的 IP 地址。在这里，通过解析 `name` 参数中的地址结构体，获取到其中的 IP 地址信息。

5. `port`：
   - 表示要绑定的端口号。在这里，通过解析 `name` 参数中的地址结构体，获取到其中的端口号信息。



> 在 bind 函数中，name 参数通常包含了要绑定的目标主机的 IP 地址和端口号信息。通过解析 name 参数中的地址结构体，可以从中提取出目标主机的 IP 地址和端口号，并将当前的套接字与指定的 IP 地址和端口号绑定起来，以便进行后续的网络通信。



# Newsend

```c++
static int (WINAPI* Oldsend)(
    SOCKET s,
    const char* buf,
    int len,
    int flags
    ) = send;
```

这段代码定义了一个名为 `Oldsend` 的函数指针，用于保存 `send` 函数的地址，并指定了 `send` 函数的参数列表。

具体解释如下：

- `static int (WINAPI* Oldsend)(SOCKET s, const char* buf, int len, int flags)`：
  - `static` 关键字表示这个函数指针是静态的，在全局范围内可见，但只能在当前文件中使用。
  - `int` 表示函数的返回类型是一个整数，表示 `send` 函数执行的结果或状态。
  - `WINAPI*` 表示这是一个使用 WINAPI 调用约定的函数指针。
  - 括号中的参数列表表示这个函数指针指向的函数的参数列表，其中 `SOCKET s` 表示套接字描述符，`const char* buf` 表示指向发送数据缓冲区的指针，`int len` 表示要发送的数据长度，`int flags` 表示标志位，用于指定发送数据的选项。

- `= send;`：
  - 这是一个赋值语句，将 `send` 函数的地址赋值给了 `Oldsend`。 
  - `send` 函数用于向已连接的套接字发送数据。

总的来说，这段代码的目的是定义一个函数指针 `Oldsend`，用于保存 `send` 函数的地址，以便后续通过该函数指针调用 `send` 函数。



```c++
sprintf(sendInfo.argName[0], "s");
sprintf(sendInfo.argName[1], "buf");
sprintf(sendInfo.argName[2], "len");
sprintf(sendInfo.argName[3], "flags");
sprintf(sendInfo.argName[4], "data");
```

这段代码是一个名为 `Newsend` 的函数，它是用来替换原始 `send` 函数的。下面是对每个参数的解释：

1. **`SOCKET s`**：
   - 这是一个套接字描述符，表示要发送数据的套接字。

2. **`const char* buf`**：
   - 这是一个指向要发送数据的缓冲区的指针。缓冲区中的数据将被发送到指定的套接字。

3. **`int len`**：
   - 这是一个整数，表示要发送的数据的长度（以字节为单位）。

4. **`int flags`**：
   - 这是一个整数，表示发送操作的标志位。可以用来指定一些特定的选项，例如在发送过程中的行为。

5. **`data`**：
   - 这不是函数的参数，而是将要发送的数据本身。在这段代码中，使用 `%s` 格式化字符串，将缓冲区中的数据作为字符串发送到共享内存中，以便记录发送的实际数据。

综上所述，这段代码中的五个参数用于指定要发送的数据、数据的长度以及发送数据的目标套接字和选项。



> 套接字（Socket）是计算机网络通信中的一种抽象概念，用于描述网络中的通信端点。它可以看作是应用层和传输层之间的接口，使得应用程序能够通过网络进行数据交换。
>
> 在TCP/IP协议栈中，套接字由IP地址和端口号组成，它们之间有着密切的关系：
>
> - **IP地址**：标识网络中的主机。IP地址由32位或128位的二进制数字组成，用于唯一标识网络中的每个设备。在套接字中，IP地址用于指定数据传输的目标或来源。
>
> - **端口号**：标识主机上的进程。端口号是一个16位的整数，范围从0到65535，用于标识主机上不同的服务或进程。在套接字中，端口号用于标识数据传输的目标或来源的应用程序。
>
> 因此，套接字描述符（Socket Descriptor）是一个用于唯一标识套接字的整数值。它实际上是操作系统为了方便应用程序管理网络通信而提供的一种抽象表示形式，可以用于在应用程序中引用和操作特定的套接字。



# Newconnect

```c++
static int (WINAPI* Oldconnect)(
    SOCKET s,
    const sockaddr* name,
    int namelen
    ) = connect;
```

这段代码定义了一个名为 `Oldconnect` 的函数指针，用于保存 `connect` 函数的地址。`connect` 函数通常用于客户端与服务器建立连接。

具体解释如下：

- **`SOCKET s`**：这是一个套接字描述符，表示要连接的套接字。

- **`const sockaddr* name`**：这是一个指向目标地址结构的指针。该结构包含要连接的目标地址信息，如IP地址和端口号。

- **`int namelen`**：这是目标地址结构的长度。

该函数的作用是使用给定的套接字 `s`，向指定地址 `name` 建立连接，连接成功返回0，否则返回SOCKET_ERROR。



```c++
sprintf(sendInfo.argName[0], "s");
sprintf(sendInfo.argName[1], "name");
sprintf(sendInfo.argName[2], "namelen");
sprintf(sendInfo.argName[3], "IP");
sprintf(sendInfo.argName[4], "port");
```

这五行代码用于设置参数名，其中每一行对应一个参数的名称。具体解释如下：

- **`sprintf(sendInfo.argName[0], "s");`**：表示第一个参数的名称是 "s"，对应套接字描述符。

- **`sprintf(sendInfo.argName[1], "name");`**：表示第二个参数的名称是 "name"，对应目标地址结构指针。

- **`sprintf(sendInfo.argName[2], "namelen");`**：表示第三个参数的名称是 "namelen"，对应目标地址结构的长度。

- **`sprintf(sendInfo.argName[3], "IP");`**：表示第四个参数的名称是 "IP"，对应目标IP地址。

- **`sprintf(sendInfo.argName[4], "port");`**：表示第五个参数的名称是 "port"，对应目标端口号。

这些参数名用于记录连接操作的相关信息，以便在共享内存中记录连接信息时进行标识和区分。



# Newrecv

```c++
static int (WINAPI* Oldrecv)(
    SOCKET s,
    char* buf,
    int len,
    int flags
    ) = recv;
```

这段代码是将原始的 `recv` 函数赋值给名为 `Oldrecv` 的函数指针。具体解释如下：

- **`static int (WINAPI* Oldrecv)(SOCKET s, char* buf, int len, int flags) = recv;`**：这行代码定义了一个名为 `Oldrecv` 的函数指针，该指针指向一个具有相同参数和返回类型的 `recv` 函数。这个指针可以用于调用原始的 `recv` 函数，而不是我们所定义的新函数。

在这里，`Oldrecv` 是一个指向 `recv` 函数的函数指针，它接受四个参数：

1. `s`：表示一个套接字描述符，用于标识要接收数据的套接字。
2. `buf`：指向一个用于接收数据的缓冲区的指针。
3. `len`：表示要接收的数据的最大长度。
4. `flags`：表示接收操作的附加标志。

这段代码的目的是用于记录和替换原始的 `recv` 函数，以便我们可以在新的 `recv` 函数中添加额外的逻辑来实现我们的需求。



# DllMain

```c++
BOOL WINAPI DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        DisableThreadLibraryCalls(hModule);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)OldMessageBoxW, NewMessageBoxW);
        DetourAttach(&(PVOID&)OldMessageBoxA, NewMessageBoxA);
        DetourAttach(&(PVOID&)OldCreateFile, NewCreateFile);
        DetourAttach(&(PVOID&)OldWriteFile, NewWriteFile);
        DetourAttach(&(PVOID&)OldReadFile, NewReadFile);
        DetourAttach(&(PVOID&)OldHeapCreate, NewHeapCreate);
        DetourAttach(&(PVOID&)OldHeapDestory, NewHeapDestory);
        //OldHeapFree
        DetourAttach(&(PVOID&)OldHeapFree, NewHeapFree);
        DetourAttach(&(PVOID&)OldRegCreateKeyEx, NewRegCreateKeyEx);
        DetourAttach(&(PVOID&)OldRegSetValueEx, NewRegSetValueEx);
        DetourAttach(&(PVOID&)OldRegDeleteValue, NewRegDeleteValue);
        DetourAttach(&(PVOID&)OldRegCloseKey, NewRegCloseKey);
        DetourAttach(&(PVOID&)OldRegOpenKeyEx, NewRegOpenKeyEx);
        DetourAttach(&(PVOID&)Oldsocket, Newsocket);
        DetourAttach(&(PVOID&)Oldbind, Newbind);
        DetourAttach(&(PVOID&)Oldsend, Newsend);
        DetourAttach(&(PVOID&)Oldconnect, Newconnect);
        DetourAttach(&(PVOID&)Oldrecv, Newrecv);

        DetourTransactionCommit();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH: {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)OldMessageBoxW, NewMessageBoxW);
        DetourDetach(&(PVOID&)OldMessageBoxA, NewMessageBoxA);
        DetourDetach(&(PVOID&)OldCreateFile, NewCreateFile);
        DetourDetach(&(PVOID&)OldWriteFile, NewWriteFile);
        DetourDetach(&(PVOID&)OldReadFile, NewReadFile);
        DetourDetach(&(PVOID&)OldHeapCreate, NewHeapCreate);
        DetourDetach(&(PVOID&)OldHeapDestory, NewHeapDestory);
        DetourDetach(&(PVOID&)OldHeapFree, NewHeapFree);
        DetourDetach(&(PVOID&)OldRegCreateKeyEx, NewRegCreateKeyEx);
        DetourDetach(&(PVOID&)OldRegSetValueEx, NewRegSetValueEx);
        DetourDetach(&(PVOID&)OldRegDeleteValue, NewRegDeleteValue);
        DetourDetach(&(PVOID&)OldRegCloseKey, NewRegCloseKey);
        DetourDetach(&(PVOID&)OldRegOpenKeyEx, NewRegOpenKeyEx);
        DetourDetach(&(PVOID&)Oldsocket, Newsocket);
        DetourDetach(&(PVOID&)Oldbind, Newbind);
        DetourDetach(&(PVOID&)Oldsend, Newsend);
        DetourDetach(&(PVOID&)Oldconnect, Newconnect);
        DetourDetach(&(PVOID&)Oldrecv, Newrecv);

        DetourTransactionCommit();
        UnmapViewOfFile(lpBase);
        CloseHandle(hMapFile);
        break;
    }
    }
    return true;
}
```



```c++
HMODULE hModule,
DWORD ul_reason_for_call,
LPVOID lpReserved
```

这三个参数是 `DllMain` 函数的输入参数：

1. **`HMODULE hModule`**：表示当前加载了该 DLL 的模块的句柄。这个句柄可以被用来调用诸如 `GetModuleFileName` 和 `GetModuleHandle` 等函数，以获取该模块的文件名或句柄等信息。

2. **`DWORD ul_reason_for_call`**：表示调用原因，即标识了 `DllMain` 函数被调用的原因。它可以是以下四个值之一：
   - `DLL_PROCESS_ATTACH`：表示 DLL 被进程附加。
   - `DLL_PROCESS_DETACH`：表示 DLL 从进程分离。
   - `DLL_THREAD_ATTACH`：表示新线程被创建。
   - `DLL_THREAD_DETACH`：表示线程被销毁。

3. **`LPVOID lpReserved`**：在不同情况下的意义不同。
   - 对于 `DLL_PROCESS_ATTACH`，`lpReserved` 是 `NULL`，表示该 DLL 是由 `LoadLibrary` 函数加载的。
   - 对于 `DLL_PROCESS_DETACH`，`lpReserved` 也是 `NULL`。
   - 对于 `DLL_THREAD_ATTACH` 和 `DLL_THREAD_DETACH`，`lpReserved` 是指向线程的 `lpParameter` 参数的指针。

在通常情况下，开发者不需要使用 `lpReserved` 参数。



## DLL_PROCESS_ATTACH

```c++
case DLL_PROCESS_ATTACH:
```

`DLL_PROCESS_ATTACH` 表示 DLL 被附加到进程中。这种情况发生在以下情形之一：

1. 当进程启动时，系统加载了 DLL 并将其附加到进程中。
2. 当调用 `LoadLibrary` 函数加载了该 DLL 时，将其附加到进程中。

在 `DLL_PROCESS_ATTACH` 情况下，通常执行一些初始化工作，例如分配资源、设置全局变量、创建线程等。

```c++
DisableThreadLibraryCalls(hModule);
```

`DisableThreadLibraryCalls(hModule)` 是一个函数调用，它禁用了 DLL 的 `DLL_THREAD_ATTACH` 和 `DLL_THREAD_DETACH` 通知。在 Windows 平台上，当线程与 DLL 相关联时，系统会发送 `DLL_THREAD_ATTACH` 通知，当线程与 DLL 断开关联时，系统会发送 `DLL_THREAD_DETACH` 通知。这些通知允许 DLL 在线程附加和分离时执行特定的操作。

然而，在某些情况下，DLL 可能不需要这些通知，特别是当 DLL 不依赖于线程的生命周期时。通过调用 `DisableThreadLibraryCalls(hModule)`，可以通知系统不要发送这些通知，从而提高性能并减少系统负担。

```c++
DetourTransactionBegin();
```

`DetourTransactionBegin()` 是 Microsoft Detours 库中的一个函数调用，用于启动一个新的挂钩事务。Detours 库是用于创建挂钩（hook）的库，可以在运行时修改目标函数的行为。

调用 `DetourTransactionBegin()` 表示开始一个新的挂钩事务，该事务可以包含一个或多个挂钩的添加或移除操作。**挂钩事务的目的是确保在添加或移除挂钩时，操作的原子性，即要么全部操作成功完成，要么全部操作失败，以避免系统处于不一致的状态。**

在使用 Detours 库创建挂钩时，通常会在事务开始时调用 `DetourTransactionBegin()`，然后添加挂钩，最后通过调用 `DetourTransactionCommit()` 提交事务。 Detours 库提供了一系列函数来添加和移除挂钩，例如 `DetourAttach()` 用于添加挂钩，`DetourDetach()` 用于移除挂钩。

**一旦事务开始，就可以添加或移除多个挂钩。事务结束时，需要调用 `DetourTransactionCommit()` 提交事务，以确保所有操作都成功应用到目标函数上。如果事务失败或者不提交，则之前添加或移除的所有挂钩都会被撤销，恢复到之前的状态。**

```c++
DetourUpdateThread(GetCurrentThread());
```

`DetourUpdateThread(GetCurrentThread())` 是 Microsoft Detours 库中的一个函数调用，用于更新当前线程的挂钩信息。在使用 Detours 库创建挂钩时，通常需要在当前线程上更新挂钩信息，以确保新的挂钩能够正确地生效。

具体地，`DetourUpdateThread()` 函数会通知当前线程的 Detours 库，以便它能够在当前线程上生效所添加的挂钩。这个函数通常在添加挂钩之后调用，以确保新的挂钩能够立即对当前线程生效，而不需要等待下一次线程调度。

通过传递 `GetCurrentThread()` 函数返回的当前线程句柄作为参数，`DetourUpdateThread()` 函数会更新当前线程上的挂钩信息，使新添加的挂钩能够立即生效。这样，新添加的挂钩就可以在当前线程的目标函数中拦截并修改行为。

```c++
DetourAttach(&(PVOID&)OldMessageBoxW, NewMessageBoxW);
```

这段代码使用了 Microsoft Detours 库中的 `DetourAttach` 函数，该函数用于将一个自定义的函数挂钩（hook）到目标函数上，从而实现对目标函数行为的修改或拦截。

具体来说，`DetourAttach` 函数的作用是将自定义的新函数（例如 `NewMessageBoxW`）挂钩到目标函数（例如 `MessageBoxW`）上，使得在调用目标函数时实际执行的是新函数的代码逻辑。这样可以在新函数中对原始功能进行修改或添加额外的操作，同时保留原始函数的功能。

在这段代码中，`OldMessageBoxW` 是一个函数指针，指向原始的 `MessageBoxW` 函数。`NewMessageBoxW` 则是自定义的新函数，用于替换原始函数。通过 `DetourAttach(&(PVOID&)OldMessageBoxW, NewMessageBoxW)`，将新函数挂钩到原始函数上，以实现对 `MessageBoxW` 函数行为的修改或增强。

```c++
DetourTransactionCommit();
```

`DetourTransactionCommit()` 是 Microsoft Detours 库中的函数，用于提交事务，将挂钩（hook）操作应用到目标函数上。在使用 Detours 库进行挂钩时，需要将挂钩操作放置在一个事务中，然后通过 `DetourTransactionCommit()` 函数来提交该事务，使得挂钩操作生效。

具体来说，当调用 `DetourTransactionCommit()` 函数时，Detours 库将应用之前通过 `DetourAttach()` 函数添加的所有挂钩操作，并确保这些操作对目标函数生效。这样，之后调用目标函数时，实际执行的将是挂钩函数中的代码逻辑，而不是原始的目标函数逻辑。

在上面提到的代码中，在 `DLL_PROCESS_ATTACH` 阶段，通过 `DetourTransactionBegin()` 开启一个新的事务，并通过多次调用 `DetourAttach()` 函数添加了一系列的挂钩操作。最后，通过 `DetourTransactionCommit()` 函数提交了该事务，使得挂钩操作生效。



## DLL_PROCESS_DETACH

```c++
case DLL_PROCESS_DETACH:
```

`DLL_PROCESS_DETACH` 是指动态链接库（DLL）从进程中分离（detach）的情况。在 Windows 操作系统中，当一个进程终止时，加载到该进程中的 DLL 会被卸载，此时会触发 DLL 的 `DllMain` 函数，并将 `DLL_PROCESS_DETACH` 作为 `ul_reason_for_call` 参数传递给 `DllMain` 函数。

在 `DLL_PROCESS_DETACH` 情况下，通常会进行一些清理工作，例如释放资源、关闭句柄等。这样可以确保在 DLL 从进程中分离时，不会留下任何未释放的资源或状态，以确保系统的稳定性和安全性。

在上面提到的代码中，当 `DllMain` 函数接收到 `DLL_PROCESS_DETACH` 情况时，会执行相应的清理工作，包括提交之前的挂钩操作、释放资源并关闭句柄等。



```c++
    case DLL_PROCESS_DETACH: {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)OldMessageBoxW, NewMessageBoxW);
        DetourDetach(&(PVOID&)OldMessageBoxA, NewMessageBoxA);
        DetourDetach(&(PVOID&)OldCreateFile, NewCreateFile);
        DetourDetach(&(PVOID&)OldWriteFile, NewWriteFile);
        DetourDetach(&(PVOID&)OldReadFile, NewReadFile);
        DetourDetach(&(PVOID&)OldHeapCreate, NewHeapCreate);
        DetourDetach(&(PVOID&)OldHeapDestory, NewHeapDestory);
        DetourDetach(&(PVOID&)OldHeapFree, NewHeapFree);
        DetourDetach(&(PVOID&)OldRegCreateKeyEx, NewRegCreateKeyEx);
        DetourDetach(&(PVOID&)OldRegSetValueEx, NewRegSetValueEx);
        DetourDetach(&(PVOID&)OldRegDeleteValue, NewRegDeleteValue);
        DetourDetach(&(PVOID&)OldRegCloseKey, NewRegCloseKey);
        DetourDetach(&(PVOID&)OldRegOpenKeyEx, NewRegOpenKeyEx);
        DetourDetach(&(PVOID&)Oldsocket, Newsocket);
        DetourDetach(&(PVOID&)Oldbind, Newbind);
        DetourDetach(&(PVOID&)Oldsend, Newsend);
        DetourDetach(&(PVOID&)Oldconnect, Newconnect);
        DetourDetach(&(PVOID&)Oldrecv, Newrecv);

        DetourTransactionCommit();
        UnmapViewOfFile(lpBase);
        CloseHandle(hMapFile);
        break;
    }
```

这段代码是在处理 DLL 分离（`DLL_PROCESS_DETACH`）的情况。在 DLL 卸载时，通常需要执行一些清理工作以确保程序的正常运行和系统资源的释放。

1. `DetourTransactionBegin()`：开始一个事务，用于组织一系列的挂钩操作。

2. `DetourUpdateThread(GetCurrentThread())`：更新当前线程的状态，以确保线程状态正确，这样才能成功地解除挂钩。

3. `DetourDetach(&(PVOID&)OldFunction, NewFunction)`：解除挂钩操作。对于每一个原始函数（如 `OldMessageBoxW`、`OldCreateFile` 等），都调用 `DetourDetach` 函数解除与之对应的新函数（如 `NewMessageBoxW`、`NewCreateFile` 等）的挂钩。

4. `DetourTransactionCommit()`：提交事务，将之前的挂钩解除操作生效。

5. `UnmapViewOfFile(lpBase)`：关闭之前创建的共享内存映射。

6. `CloseHandle(hMapFile)`：关闭之前打开的文件映射对象句柄。

通过以上操作，确保了在 DLL 卸载时，所有的挂钩操作都被正确地解除，同时释放了相关的资源，以确保程序的安全退出。



```c++
DetourTransactionBegin();
```

`DetourTransactionBegin()` 是 Microsoft Detours 库中的一个函数，用于开始一个事务。在这个事务中，可以执行一系列的挂钩操作，然后通过 `DetourTransactionCommit()` 来提交这些操作，使其生效，或者通过 `DetourTransactionAbort()` 来取消这些操作。

在这段代码中，`DetourTransactionBegin()` 表示开始一个挂钩事务，意味着接下来的操作将被组织在一个事务中，这些操作通常涉及挂钩的附加（`DetourAttach`）或解除（`DetourDetach`）等操作。

```c++
DetourUpdateThread(GetCurrentThread());
```

`DetourUpdateThread(GetCurrentThread())` 是 Microsoft Detours 库中的一个函数调用。它的作用是更新当前线程的内部状态，以确保后续的挂钩操作会在当前线程上生效。

在这段代码中，`DetourUpdateThread(GetCurrentThread())` 用于更新当前线程的状态，以确保当前线程上的挂钩操作会生效。

```c++
DetourTransactionCommit();
```

`DetourTransactionCommit()` 是 Microsoft Detours 库中的一个函数调用，用于提交挂钩事务。在使用 Detours 库进行挂钩操作时，通常需要将挂钩操作封装在一个事务中，并通过调用 `DetourTransactionCommit()` 函数来提交该事务。

在上述代码中，`DetourTransactionCommit()` 表示提交了之前通过 `DetourTransactionBegin()` 开始的挂钩事务。这意味着所有挂钩操作都已经完成，并且准备将这些操作应用到系统中。

```c++
UnmapViewOfFile(lpBase);
```

`UnmapViewOfFile(lpBase)` 是用于取消映射先前由 `MapViewOfFile` 函数创建的文件映射对象的内存区域的函数。在这段代码中，`lpBase` 是指向共享内存区域的指针，通过调用 `UnmapViewOfFile(lpBase)` 函数，将取消该共享内存区域的映射，释放相应的内存资源。

```c++
CloseHandle(hMapFile);
```

这段代码调用了 `CloseHandle` 函数，其作用是关闭先前打开的文件映射对象句柄 `hMapFile`。

在Windows操作系统中，每次使用诸如 `OpenFileMapping` 或 `CreateFileMapping` 等函数创建或打开一个文件映射对象时，都会返回一个句柄。这些句柄需要在使用完毕后通过调用 `CloseHandle` 函数进行关闭，以释放资源并防止资源泄露。



```c++
HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemory");
LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(info));
```

这段代码的作用是将先前创建的文件映射对象映射到当前进程的地址空间，并返回一个指向映射内存区域的指针。

- `OpenFileMapping`: 这是一个函数，用于打开一个已经存在的文件映射对象。
  - `FILE_MAP_ALL_ACCESS`: 表示对文件映射对象的完全访问权限，包括读、写、复制等操作。
  - `NULL`: 表示不使用安全描述符。
  - `"ShareMemory"`: 是要打开的文件映射对象的名称，该名称与创建文件映射对象时使用的名称相匹配。

- `MapViewOfFile`: 这也是一个函数，用于将文件映射对象映射到当前进程的地址空间。
  - `hMapFile`: 是前面打开的文件映射对象的句柄。
  - `FILE_MAP_ALL_ACCESS`: 表示对映射内存区域的完全访问权限。
  - `0, 0`: 表示从文件映射的开头开始映射，并映射整个文件映射对象。
  - `sizeof(info)`: 表示要映射的内存大小，这里假设 `info` 是一个结构体或类型，`sizeof(info)` 返回该结构体或类型的大小。

这段代码的效果是将名为 "ShareMemory" 的文件映射对象映射到当前进程的地址空间中，并返回一个指向映射内存区域的指针 `lpBase`。