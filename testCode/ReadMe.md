# heapCreateAndDestory

```c++
void heapCreateAndDestory() {
    printf("Press any key to start HeapCreate!\n");
    getchar();
    HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

    int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
    for (int i = 0; i < 30; ++i) {
        pArr[i] = i + 1;
    }
    printf("Successfully created!\n");
    for (int i = 0; i < 30; ++i) {
        if (i % 5 == 0)
            printf_s("\n");
        printf("%3d ", pArr[i]);
    }
    printf_s("\n\n");
    printf("Press any key to start HeapFree!\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("Press any key to start HeapDestory!\n");
    getchar();
    HeapDestroy(hHeap);

    printf("Successfully destory!\n");
}
```



```c++
HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);
```

这段代码调用了Windows API中的HeapCreate函数来创建一个堆（Heap）。让我们逐个解释其参数和作用：

1. `HEAP_NO_SERIALIZE`：这是HeapCreate函数的第一个参数，它指定了堆的行为标志。在这里，使用了`HEAP_NO_SERIALIZE`，表示堆操作不需要进行同步。通常情况下，如果多个线程会同时对堆进行操作，应该选择使用`0`以保证线程安全。但在一些单线程的场景下，使用`HEAP_NO_SERIALIZE`可以提高性能。

2. `PAGE_SIZE * 10`：这是HeapCreate函数的第二个参数，表示创建的堆的初始大小。在Windows中，内存是以页面（page）为单位进行管理的，而`PAGE_SIZE`是一个常量，表示页面的大小。在这里，初始堆大小被设置为10页的大小。

3. `PAGE_SIZE * 100`：这是HeapCreate函数的第三个参数，表示创建的堆的最大大小。这里将堆的最大大小设置为100页的大小。

因此，这段代码的作用是创建了一个堆，其初始大小为10页，最大大小为100页，并且不需要进行同步操作。创建成功后，函数将返回一个指向该堆的句柄（HANDLE类型），可以用于后续的堆操作。



```c++
int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
```

这行代码使用了Windows API中的HeapAlloc函数在之前创建的堆（由变量hHeap表示）上分配内存空间，然后将返回的指针转换为整型指针。让我们逐个解释其参数和作用：

1. `hHeap`：这是之前通过HeapCreate函数创建的堆的句柄（HANDLE类型），它指定了在哪个堆上进行内存分配。

2. `0`：这是HeapAlloc函数的第二个参数，它表示分配内存的标志。在这里，使用了0，表示默认行为。通常情况下，如果需要指定额外的标志，可以在此处传递相应的值。

3. `sizeof(int) * 30`：这是HeapAlloc函数的第三个参数，表示要分配的内存空间大小。在这里，分配了30个整数大小的内存空间，即 `sizeof(int) * 30` 字节的空间。

4. `(int*)`：这是一种类型转换，将HeapAlloc返回的指针转换为整型指针。因为HeapAlloc返回的是一个void类型的指针，而我们知道这个指针指向了一个整型数组，因此在这里进行了强制类型转换。

最终，该行代码的作用是在之前创建的堆上分配了足够大小的内存空间，用于存储一个包含30个整数的数组，并将分配的内存空间的首地址赋值给整型指针变量pArr。



所以在HeapCreate之后还需要HeapAlloc？这二者的关系是什么？

对的，HeapCreate用于创建一个堆，它只是在操作系统中分配了一块内存区域作为堆的基础结构。这个时候这个堆还没有分配任何内存给具体的数据。而HeapAlloc则是在已经创建的堆上分配内存给特定的数据使用。

简单来说，HeapCreate是创建一个堆的基础结构，而HeapAlloc则是在这个堆上实际分配内存给具体的数据对象使用。

在典型的使用情景下，通常会先调用HeapCreate来创建一个堆，然后通过HeapAlloc在这个堆上分配内存给需要存储的数据。



```c++
HeapFree(hHeap, 0, pArr);
```

这段代码使用了Windows API中的HeapFree函数来释放之前在堆上分配的内存空间。让我们逐个解释其参数和作用：

1. `hHeap`：这是之前通过HeapCreate函数创建的堆的句柄（HANDLE类型），它指定了在哪个堆上进行内存释放操作。

2. `0`：这是HeapFree函数的第二个参数，它表示释放内存的标志。在这里，使用了0，表示默认行为。通常情况下，如果需要指定额外的标志，可以在此处传递相应的值。

3. `pArr`：这是之前通过HeapAlloc函数分配的内存空间的指针，它指向要释放的内存块的起始地址。

HeapFree函数会释放之前通过HeapAlloc函数在堆上分配的内存空间。调用HeapFree后，该内存空间就不再被程序所占用，可以被系统回收。这样做可以避免内存泄漏问题，即释放不再使用的内存，以便系统可以重新分配给其他程序使用。



```c++
HeapDestroy(hHeap);
```

这行代码使用了Windows API中的HeapDestroy函数来销毁先前通过HeapCreate函数创建的堆。让我们逐个解释其参数和作用：

1. `hHeap`：这是之前通过HeapCreate函数创建的堆的句柄（HANDLE类型），它指定了要销毁的堆。

HeapDestroy函数接受一个堆的句柄作为参数，并将该堆从系统中销毁。调用HeapDestroy函数后，该堆不再可用，并且之前通过该堆分配的所有内存空间也将被释放。这样做可以释放系统资源并避免内存泄漏问题。需要注意的是，调用HeapDestroy函数后，指向该堆的句柄将不再有效，任何对该句柄的后续引用都将导致未定义的行为。



HeapFree和HeapDestroy有什么区别？请详细解释一下

HeapFree和HeapDestroy是Windows API中用于管理堆的两个不同函数，它们有着不同的作用和用途：

1. **HeapFree**:
   - **作用**：HeapFree函数用于释放先前在堆上分配的内存空间。
   - **参数**：HeapFree函数接受三个参数：堆句柄（HANDLE）、内存释放标志和指向要释放的内存块的指针。
   - **功能**：调用HeapFree函数会释放先前在堆上通过HeapAlloc等函数分配的内存空间，使得该内存空间可以被系统回收并重新分配给其他程序使用。

2. **HeapDestroy**:
   - **作用**：HeapDestroy函数用于销毁先前通过HeapCreate函数创建的堆。
   - **参数**：HeapDestroy函数接受一个参数，即要销毁的堆的句柄（HANDLE）。
   - **功能**：调用HeapDestroy函数会销毁指定的堆，并释放其占用的系统资源。这样做会导致该堆不再可用，并且之前通过该堆分配的所有内存空间也将被释放。

**区别**:
- 主要区别在于它们的作用对象不同：
  - HeapFree作用于堆上的内存块，用于释放先前分配的内存空间。
  - HeapDestroy作用于整个堆，用于销毁先前创建的堆。

- 使用情景：
  - HeapFree通常用于释放堆上分配的内存空间，当某个内存块不再需要时，可以调用HeapFree来释放它，从而避免内存泄漏问题。
  - HeapDestroy通常用于在不再需要使用某个堆时，释放该堆所占用的系统资源。例如，当某个应用程序退出时，可以调用HeapDestroy来销毁该应用程序创建的堆，从而释放其占用的系统资源，确保资源的正确释放和系统的性能。

综上所述，HeapFree用于释放堆上的内存块，而HeapDestroy用于销毁整个堆，它们在功能和使用情景上有所不同，但都是用于管理堆的重要函数。



那是不是当我要使用HeapDestroyd 时候，即便这个堆上有些内存块还没有被HeapFree掉，也不会造成内存泄漏？也就是说当执行HeapDestroy的时候默认对堆上所有已经分配的空间执行HeapFree？

是的，当你调用HeapDestroy销毁一个堆时，系统会自动释放该堆上所有已分配的内存空间，包括那些尚未通过HeapFree函数手动释放的内存块。这确保了在销毁堆的过程中不会发生内存泄漏。

HeapDestroy函数在销毁堆之前会执行必要的清理操作，包括释放堆上所有已分配的内存空间以及释放系统分配给该堆的资源。这样做可以确保在销毁堆之后，系统中不会留下任何未释放的内存块或者资源，从而避免内存泄漏问题。

因此，即使你没有手动调用HeapFree函数释放所有内存块，当调用HeapDestroy销毁堆时，系统也会负责释放所有已分配的内存空间，确保内存资源得到正确释放，避免内存泄漏。



> HeapCreate以及HeapAlloc和malloc在运行机制上有什么区别？
>
> HeapCreate、HeapAlloc和malloc都是用于在内存中动态分配内存空间的函数，但它们之间有一些区别：
>
> 1. **平台和API**：
>    - `HeapCreate` 和 `HeapAlloc` 是 Windows API 中提供的函数，用于在 Windows 系统上进行堆的创建和内存分配。
>    - `malloc` 是 C 标准库（stdlib.h）中提供的函数，是 C/C++ 语言通用的内存分配函数，可以在多种操作系统和平台上使用。
>
> 2. **功能和用法**：
>    - `HeapCreate` 用于创建一个新的堆，并返回一个指向该堆的句柄（HANDLE），可以通过这个句柄在堆上进行内存分配、释放等操作。
>    - `HeapAlloc` 用于在已经创建的堆上分配指定大小的内存块，并返回分配内存块的起始地址。它的参数中需要指定堆的句柄以及要分配的内存大小。
>    - `malloc` 用于在程序的堆上动态分配内存空间，它不需要显式地创建堆，而是在程序启动时会自动分配一块堆空间，然后通过 malloc 函数在这块堆上进行内存分配。
>
> 3. **跨平台性**：
>    - `HeapCreate` 和 `HeapAlloc` 是 Windows 特定的函数，只能在 Windows 系统上使用。
>    - `malloc` 是标准 C/C++ 库函数，可以在各种操作系统和平台上使用，包括 Windows、Linux、macOS 等。
>
> 4. **内存管理策略**：
>    - 在内存管理策略上，这三个函数都可以实现动态内存分配和释放。但在具体实现上可能有所不同，例如在多线程环境下的内存分配策略、内存分配效率等方面会有差异。
>
> 总的来说，这三个函数都是用于动态内存分配的，但它们的功能、平台适用性、用法等方面有所差异，开发者在选择使用时需要根据具体的需求和环境进行考量。



# writeFileString

```c++
void writeFileString() {
    CHAR* pBuffer;
    int fileSize = 0;
    char writeString[100];
    bool flag;
    HANDLE hOpenFile = (HANDLE)CreateFile(L"a.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
        NULL, NULL);
    if (hOpenFile == INVALID_HANDLE_VALUE) {
        hOpenFile = NULL;
        printf("Can not open the file\n");
        return;
    }
    printf("successfully open a file\n");
    printf("input a string:");
    scanf("%s", writeString);
    flag = WriteFile(hOpenFile, writeString, strlen(writeString), NULL, NULL);
    if (flag) {
        printf("successful writed!\n");
    }
    FlushFileBuffers(hOpenFile);
    CloseHandle(hOpenFile);
}
```



```c++
HANDLE hOpenFile = (HANDLE)CreateFile(L"a.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
```

这段代码是用来创建或打开一个名为"a.txt"的文件。让我们逐个解释其参数和作用：

1. `L"a.txt"`：这是要创建或打开的文件的路径和名称。在这里，`L` 是一个宽字符字符串的前缀，表示这是一个Unicode字符串。

2. `GENERIC_READ | GENERIC_WRITE`：这是文件的访问权限，表示允许对文件进行读和写操作。`GENERIC_READ` 表示允许读取文件，`GENERIC_WRITE` 表示允许写入文件。

3. `FILE_SHARE_READ`：这是共享模式，表示允许其他进程以只读方式打开该文件。

4. `NULL`：这是安全属性，指定了文件的安全属性。在这里设置为NULL，表示使用默认的安全设置。

5. `CREATE_ALWAYS`：这是创建选项，表示如果文件已经存在，则覆盖原有文件，如果文件不存在，则创建一个新文件。

6. `NULL`：这是文件属性，用于指定要创建的文件的属性。在这里设置为NULL，表示不设置特殊属性。

7. `NULL`：这是模板句柄，用于指定一个已经打开的文件的句柄作为模板。在这里设置为NULL，表示不使用模板句柄。

整个操作会尝试创建或打开名为"a.txt"的文件，并返回一个文件句柄（HANDLE类型），该句柄用于后续对文件进行读写操作。如果文件打开成功，则返回的文件句柄可以用于后续的文件读写操作；如果文件打开失败，则返回值为INVALID_HANDLE_VALUE。



> 在Windows编程中，`HANDLE` 类型是一个非常重要的数据类型，它用来表示操作系统内核对象的句柄。操作系统内核对象包括文件、进程、线程、事件、信号量、互斥体等。`HANDLE` 本质上是一个指向内核对象的指针或句柄值。
>
> Windows API函数通常会返回一个 `HANDLE` 类型的值，用于标识和操作被创建或打开的内核对象。通过使用句柄，程序可以对内核对象进行诸如读取、写入、关闭、等待等操作。在许多情况下，句柄是唯一标识一个内核对象的方式。
>
> 一些常见的操作系统内核对象的句柄包括：
> - 文件句柄：用于表示已打开的文件或设备。
> - 进程句柄：用于表示操作系统中正在运行的进程。
> - 线程句柄：用于表示操作系统中正在运行的线程。
> - 事件、信号量、互斥体句柄：用于表示同步和互斥机制。
> - 窗口句柄：用于表示用户界面中的窗口。
>
> 在使用 `HANDLE` 类型的值时，需要小心处理，确保不会出现资源泄漏等问题。比如，对于已经打开的文件，需要及时关闭文件句柄；对于创建的进程或线程，需要等待其执行完毕并释放相关资源等。



```c++
flag = WriteFile(hOpenFile, writeString, strlen(writeString), NULL, NULL);
```

这行代码使用了Windows API中的WriteFile函数向打开的文件中写入数据。让我们逐个解释其参数和作用：

1. `hOpenFile`：这是先前通过CreateFile函数打开的文件的句柄（HANDLE类型），它指定了要写入数据的文件。

2. `writeString`：这是要写入文件的数据，即用户输入的字符串。writeString是一个字符数组，存储了用户输入的字符串。

3. `strlen(writeString)`：这是要写入的数据的大小，即用户输入的字符串的长度。strlen函数用于获取字符串的长度，以确定要写入的数据的大小。

4. `NULL`：这是指向一个DWORD类型的指针，用于接收写入的字节数。在这里设置为NULL，表示不需要获取写入的字节数。

5. `NULL`：这是指向OVERLAPPED结构体的指针，用于指定一些特殊的写入操作选项。在这里设置为NULL，表示不使用任何特殊选项。

函数会将指定的数据写入到已打开的文件中。如果写入成功，函数返回值为真（TRUE），否则返回值为假（FALSE）。通常情况下，如果写入成功，表示数据已经成功写入到文件中。



```c++
FlushFileBuffers(hOpenFile);
```

这行代码使用了Windows API中的FlushFileBuffers函数，它用于刷新文件的缓冲区，确保所有已经写入的数据都被写入到文件中。让我们逐个解释其参数和作用：

1. `hOpenFile`：这是先前通过CreateFile函数打开的文件的句柄（HANDLE类型），它指定了要刷新缓冲区的文件。

调用FlushFileBuffers函数会将文件缓冲区中的数据立即写入到文件中，而不是等到系统自行决定何时写入。这样做可以确保文件中包含最新的数据，并且可以及时地将数据写入到物理存储介质（如磁盘）中，而不是仅停留在内存中。

在文件写入操作之后调用FlushFileBuffers函数是一个良好的实践，可以确保数据的一致性和可靠性。



```c++
CloseHandle(hOpenFile);
```

这行代码使用了Windows API中的CloseHandle函数，它用于关闭之前打开的文件句柄，释放相关资源。让我们逐个解释其参数和作用：

1. `hOpenFile`：这是先前通过CreateFile函数打开的文件的句柄（HANDLE类型），它指定了要关闭的文件句柄。

调用CloseHandle函数会关闭文件句柄，并释放系统为该句柄所分配的资源。这包括文件对象、文件缓冲区、文件描述符等资源。关闭文件句柄后，程序将不能再对该文件进行任何读写操作。

关闭文件句柄是一个良好的编程习惯，可以避免资源泄漏和系统资源的浪费。通常情况下，当文件使用完毕后，应该及时地调用CloseHandle函数来关闭文件句柄，释放相关资源。



> CloseHandle可以用来关闭别的类型的句柄吗？
>
> 是的，CloseHandle函数不仅可以用来关闭文件句柄，还可以关闭其他类型的句柄，包括但不限于：
>
> 1. **进程句柄**：表示操作系统中正在运行的进程。当一个进程不再需要时，可以使用CloseHandle函数关闭其进程句柄，释放相关资源。
>
> 2. **线程句柄**：表示操作系统中正在执行的线程。当一个线程执行完毕或不再需要时，可以使用CloseHandle函数关闭其线程句柄，释放相关资源。
>
> 3. **事件句柄**：用于实现线程间的同步和通信。当一个事件不再需要时，可以使用CloseHandle函数关闭其事件句柄，释放相关资源。
>
> 4. **信号量句柄**：用于实现资源的控制和同步。当一个信号量不再需要时，可以使用CloseHandle函数关闭其信号量句柄，释放相关资源。
>
> 5. **互斥体句柄**：用于实现资源的互斥访问。当一个互斥体不再需要时，可以使用CloseHandle函数关闭其互斥体句柄，释放相关资源。
>
> 6. **共享内存句柄**：用于实现多个进程之间的内存共享。当一个共享内存不再需要时，可以使用CloseHandle函数关闭其共享内存句柄，释放相关资源。
>
> 总的来说，CloseHandle函数可以用来关闭任何类型的内核对象句柄，它会释放相关资源并将句柄置为无效。这样做可以避免资源泄漏和系统资源的浪费。



# readFileString

```c++
void readFileString() {
    CHAR* pBuffer;
    int fileSize = 0;
    bool flag;
    HANDLE hOpenFile = (HANDLE)CreateFile(L"a.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
    if (hOpenFile == INVALID_HANDLE_VALUE) {
        hOpenFile = NULL;
        printf("无法打开文件\n");
        return;
    }
    printf("成功打开文件\n");
    fileSize = GetFileSize(hOpenFile, NULL);
    pBuffer = (char*)malloc((fileSize + 1) * sizeof(char));
    flag = ReadFile(hOpenFile, pBuffer, fileSize, NULL, NULL);
    pBuffer[fileSize] = 0;
    if (flag) {
        printf("成功读取字符串:%s!\n", pBuffer);
    }
    free(pBuffer);
    CloseHandle(hOpenFile);
}
```



```c++
HANDLE hOpenFile = (HANDLE)CreateFile(L"a.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
```

这段代码使用了Windows API中的CreateFile函数来打开一个名为"a.txt"的文件。让我们逐个解释其参数和作用：

1. `L"a.txt"`：这是要打开的文件的路径和名称。在这里，`L` 是一个宽字符字符串的前缀，表示这是一个Unicode字符串。

2. `GENERIC_READ`：这是文件的访问权限，表示允许对文件进行读取操作。`GENERIC_READ` 表示只允许读取文件，不允许写入文件。

3. `FILE_SHARE_READ`：这是共享模式，表示允许其他进程以只读方式打开该文件。

4. `NULL`：这是安全属性，指定了文件的安全属性。在这里设置为NULL，表示使用默认的安全设置。

5. `OPEN_ALWAYS`：这是打开选项，表示如果文件存在，则打开该文件；如果文件不存在，则创建一个新文件。即使文件已经存在，也可以打开它，而不会覆盖原有文件。

6. `NULL`：这是文件属性，用于指定要创建的文件的属性。在这里设置为NULL，表示不设置特殊属性。

7. `NULL`：这是模板句柄，用于指定一个已经打开的文件的句柄作为模板。在这里设置为NULL，表示不使用模板句柄。

函数会尝试打开名为"a.txt"的文件，如果文件不存在，则会创建一个新文件；如果文件已经存在，则直接打开该文件。如果打开成功，将返回文件的句柄（HANDLE类型），该句柄可以用于后续对文件进行读取操作。如果打开失败，则返回值为INVALID_HANDLE_VALUE。



```c++
fileSize = GetFileSize(hOpenFile, NULL);
```

这行代码使用了Windows API中的GetFileSize函数来获取指定文件的大小。让我们逐个解释其参数和作用：

1. `hOpenFile`：这是先前通过CreateFile函数打开的文件的句柄（HANDLE类型），它指定了要获取大小的文件。

2. `NULL`：这是指向一个DWORD类型的指针，用于接收文件大小的高位DWORD。在这里设置为NULL，表示不需要获取高位DWORD。

GetFileSize函数会返回指定文件的大小，以字节为单位。如果操作成功，返回值是文件大小的低位DWORD（32位无符号整数）。如果文件大小超过4GB，则需要使用返回值中的高位DWORD来获取完整的文件大小。

这段代码将获取的文件大小存储在变量fileSize中，以便后续程序使用。getFilesize用于判断文件大小是否符合要求。



> GetFileSize函数可以用于获取任何类型的文件的大小，包括但不限于txt、doc、pdf等。无论文件的类型是文本文件、二进制文件还是其他类型的文件，GetFileSize都可以获取到文件的大小信息。
>
> GetFileSize函数是基于文件系统的操作，它通过查询文件的元数据来获取文件的大小，而不关心文件的具体内容或格式。因此，它对文件的类型没有限制，可以用于任何类型的文件。
>
> 无论文件是文本文件（如txt文件）、Microsoft Word文档（.doc、.docx）、Adobe PDF文件（.pdf）、图像文件、音频文件还是视频文件等，GetFileSize函数都可以准确地获取文件的大小，以字节为单位。
>
> 因此，GetFileSize函数是一个通用的文件操作函数，适用于各种类型的文件，可以方便地获取文件的大小信息。



```c++
flag = ReadFile(hOpenFile, pBuffer, fileSize, NULL, NULL);
```

这段代码使用了Windows API中的ReadFile函数来从打开的文件中读取数据。让我们逐个解释其参数和作用：

1. `hOpenFile`：这是先前通过CreateFile函数打开的文件的句柄（HANDLE类型），它指定了要读取数据的文件。

2. `pBuffer`：这是一个指向存储读取数据的缓冲区的指针。ReadFile函数会将读取的数据存储到这个缓冲区中。

3. `fileSize`：这是要读取的数据的大小，即读取的字节数。通常情况下，fileSize应该等于要读取的数据的实际大小。

4. `NULL`：这是指向一个DWORD类型的指针，用于接收读取的字节数。在这里设置为NULL，表示不需要获取读取的字节数。

5. `NULL`：这是指向OVERLAPPED结构体的指针，用于指定一些特殊的读取操作选项。在这里设置为NULL，表示不使用任何特殊选项。

函数会从指定的文件中读取数据，并将读取的数据存储到缓冲区pBuffer中。如果读取成功，函数返回值为真（TRUE），否则返回值为假（FALSE）。通常情况下，如果读取成功，表示数据已经成功读取到缓冲区中，程序可以继续处理这些数据。



# regCreateAndSetValue

```c++
void regCreateAndSetValue() {
    // 创建注册表并设置键值
    HKEY hKey = NULL;
    TCHAR Data[254];
    memset(Data, 0, sizeof(Data));
    wcsncpy_s(Data, TEXT("https://github.com/AgentGuo"), 254);

    size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, NULL, REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS, NULL, &hKey, NULL);
    if (lRet == ERROR_SUCCESS) {
        printf("成功创建注册表!\n");
    }
    else {
        printf("创建注册表失败!\n");
    }
    // 修改注册表键值，没有则创建它
    size_t iLen = wcslen(Data);
    // 设置键值
    lRet = RegSetValueEx(hKey, L"panfeng", 0, REG_SZ, (CONST BYTE*) Data, sizeof(TCHAR) * iLen);
    if (lRet == ERROR_SUCCESS) {
        printf("成功为注册表设置键值!\n");
        return;
    }
    else {
        printf("为注册表设置键值失败!\n");
    }
    RegCloseKey(hKey);
}
```



```c++
HKEY hKey = NULL;
```

`HKEY hKey = NULL;` 是声明了一个句柄变量 `hKey`，并将其初始化为 `NULL`。在这个代码中，`hKey` 变量用于存储一个指向注册表项的句柄。

在 Windows 编程中，句柄（Handle）是一种特殊的数据类型，用于标识和引用操作系统所管理的资源，如文件、内存、设备、窗口等。在这里，`HKEY` 是一个代表注册表项的特殊句柄类型。

将 `hKey` 初始化为 `NULL` 的目的是为了确保在后续的代码中，如果没有成功地获得一个有效的注册表项句柄，`hKey` 将保持为空，以免产生未定义的行为。

通常，在进行资源管理时，经常会将句柄初始化为 `NULL` 或者 `INVALID_HANDLE_VALUE`（对于文件句柄）等特定的值，以便在需要使用句柄之前进行判断和检查。



```c++
	TCHAR Data[254];
    memset(Data, 0, sizeof(Data));
    wcsncpy_s(Data, TEXT("https://github.com/AgentGuo"), 254);
```

这三行代码的作用是：

1. `TCHAR Data[254];`：声明了一个名为 `Data` 的字符数组，数组元素的类型是 `TCHAR`，大小为 254。`TCHAR` 是 Windows 编程中用于处理字符的宏，它在不同的编译环境下会根据编译选项自动转换为 `char` 或 `wchar_t`。在这里，假设 `TCHAR` 被定义为 `wchar_t`，因此 `Data` 数组存储的是宽字符。

2. `memset(Data, 0, sizeof(Data));`：使用 `memset` 函数将 `Data` 数组中的所有元素初始化为 0。这一步是为了确保 `Data` 数组的所有元素都被清零，以防止在拷贝字符串时出现未知的内容残留。

3. `wcsncpy_s(Data, TEXT("https://github.com/AgentGuo"), 254);`：使用 `wcsncpy_s` 函数将指定的字符串复制到 `Data` 数组中。`wcsncpy_s` 是一个安全的字符串复制函数，它可以防止缓冲区溢出。在这里，它将字符串 `"https://github.com/AgentGuo"` 复制到 `Data` 数组中，最多复制 254 个字符。



```c++
size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
```

这段代码使用了Windows API中的RegCreateKeyEx函数来创建或打开一个注册表项。让我们逐个解释其参数和作用：

1. `HKEY_CURRENT_USER`：这是一个预定义的注册表根键，表示当前用户的注册表项。在这里，使用 `HKEY_CURRENT_USER` 表示要在当前用户的注册表中进行操作。

2. `(LPWSTR)L"aaaMykey"`：这是要创建或打开的注册表项的名称，以宽字符形式表示。在这里，"aaaMykey" 是注册表项的名称。

3. `0`：这是保留参数，用于指定注册表项的类字符串。在这里设置为0，表示不使用类字符串。

4. `NULL`：这是安全属性，用于指定注册表项的安全属性。在这里设置为NULL，表示使用默认的安全设置。

5. `REG_OPTION_NON_VOLATILE`：这是选项标志，表示注册表项是非易失性的，即注册表项的信息在系统重启后仍然保持不变。

6. `KEY_ALL_ACCESS`：这是访问权限，表示对注册表项具有完全访问权限，包括读取、写入、删除等操作。

7. `NULL`：这是指向一个SECURITY_ATTRIBUTES结构体的指针，用于指定注册表项的安全描述符。在这里设置为NULL，表示不设置安全描述符。

8. `&hKey`：这是一个指向HKEY类型的指针，用于接收创建或打开的注册表项的句柄。

9. `NULL`：这是指向DWORD类型的指针，用于接收操作的状态。在这里设置为NULL，表示不需要获取操作的状态。

函数会尝试创建或打开指定名称的注册表项。如果注册表项已经存在，则打开该项；如果不存在，则创建一个新的项。如果操作成功，函数返回值将是ERROR_SUCCESS，表示成功创建或打开注册表项；否则返回其他错误代码，表示操作失败。



> 如果在注册表操作中发生错误，函数通常会返回一个表示错误的错误代码，而不是 `ERROR_SUCCESS`。这样的错误代码可以帮助开发人员确定发生了什么问题，并采取适当的措施来处理它们。
>
> 一些常见的注册表操作失败的错误代码包括但不限于：
>
> - `ERROR_ACCESS_DENIED`（5）：表示访问被拒绝，通常是由于权限不足或者当前用户没有权限执行该操作。
>   
> - `ERROR_FILE_NOT_FOUND`（2）：表示指定的注册表项或键不存在，可能是由于指定的路径不正确或者该项尚未创建。
>
> - `ERROR_INVALID_PARAMETER`（87）：表示传递给函数的参数无效，可能是由于参数类型、值或者范围不正确。
>
> - `ERROR_ALREADY_EXISTS`（183）：表示尝试创建一个已经存在的注册表项，或者尝试创建一个重名的子项，这是一个错误。
>
> 当函数返回这些错误代码时，通常需要开发人员根据具体的情况来诊断问题，并采取适当的错误处理措施，例如输出错误信息、进行回退操作或者提示用户进行相应操作。



```c++
lRet = RegSetValueEx(hKey, L"qyf", 0, REG_SZ, (CONST BYTE*) Data, sizeof(TCHAR) * iLen);
```

这段代码使用了Windows API中的RegSetValueEx函数来设置注册表项的键值。让我们逐个解释其参数和作用：

1. `hKey`：这是先前通过RegCreateKeyEx函数创建或打开的注册表项的句柄（HANDLE类型），它指定了要设置键值的注册表项。

2. `L"qyf"`：这是要设置的键的名称，以宽字符形式表示。在这里，"qyf" 是键的名称。

3. `0`：这是保留参数，用于指定键值的类型。在这里设置为0，表示没有特殊的键值类型。

4. `REG_SZ`：这是数据类型，表示要设置的键值是字符串类型。在这里，将注册表项的键值设置为字符串类型。

5. `(CONST BYTE*) Data`：这是要设置的键值的数据，它是一个指向数据缓冲区的指针。在这里，`Data` 是之前准备好的字符串数组，包含要设置的字符串数据。

6. `sizeof(TCHAR) * iLen`：这是要设置的键值数据的大小，以字节为单位。`iLen` 是之前字符串的长度，通过 `wcslen` 函数获取。在这里，计算出要设置的字符串数据的大小。

函数会将指定的键值数据设置到指定的注册表项中。如果设置成功，函数返回值为 `ERROR_SUCCESS`，表示成功设置键值；否则返回其他错误代码，表示设置失败。



```c++
RegCloseKey(hKey);
```

这段代码使用了Windows API中的RegCloseKey函数来关闭先前创建或打开的注册表项的句柄，释放相关资源。让我们逐个解释其参数和作用：

1. `hKey`：这是先前通过RegCreateKeyEx函数创建或打开的注册表项的句柄（HANDLE类型），它指定了要关闭的注册表项。

函数调用将关闭先前创建或打开的注册表项，并释放系统为该句柄所分配的资源。这包括注册表项对象、内存缓冲区等资源。关闭注册表项句柄后，程序将不能再对该注册表项进行任何操作。

关闭注册表项句柄是一个良好的编程习惯，可以确保资源得到正确释放，避免资源泄漏和系统资源的浪费。通常情况下，当注册表项的操作完成后，应该及时地调用RegCloseKey函数来关闭注册表项句柄。



# regOpenAndDelValue

```c++
void regOpenAndDelValue() {
    HKEY hKey = NULL;
    size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, KEY_ALL_ACCESS, &hKey);
    if (lRet == ERROR_SUCCESS) {
        printf("成功打开注册表!\n");
    }
    else {
        printf("无法打开注册表!\n");
    }
    lRet = RegDeleteValue(hKey, L"qyf");
    if (lRet == ERROR_SUCCESS) {
        printf("成功删除!\n");
    }
    else {
        printf("删除失败!\n");
    }
    RegCloseKey(hKey);
}
```



```c++
size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, KEY_ALL_ACCESS, &hKey);
```

这段代码使用了Windows API中的RegOpenKeyEx函数来打开一个注册表项。让我们逐个解释其参数和作用：

1. `HKEY_CURRENT_USER`：这是一个预定义的注册表根键，表示当前用户的注册表项。在这里，使用 `HKEY_CURRENT_USER` 表示要在当前用户的注册表中进行操作。

2. `(LPWSTR)L"aaaMykey"`：这是要打开的注册表项的名称，以宽字符形式表示。在这里，"aaaMykey" 是注册表项的名称。

3. `0`：这是保留参数，用于指定注册表项的类字符串。在这里设置为0，表示不使用类字符串。

4. `KEY_ALL_ACCESS`：这是访问权限，表示对注册表项具有完全访问权限，包括读取、写入、删除等操作。在这里，设置为 `KEY_ALL_ACCESS` 表示可以进行所有操作。

5. `&hKey`：这是一个指向HKEY类型的指针，用于接收打开的注册表项的句柄。

函数调用将尝试打开指定名称的注册表项。如果注册表项存在且成功打开，则函数返回值将是 `ERROR_SUCCESS`，表示成功打开注册表项，并且通过 `hKey` 参数返回注册表项的句柄；否则返回其他错误代码，表示打开失败。



> `LPWSTR` 是一个指向宽字符形式的字符串的指针的类型，它在 Windows 编程中经常用于处理 Unicode 字符串。在 C/C++ 中，`LPWSTR` 是一个宏定义，它被定义为 `wchar_t*` 类型的指针。
>
> - `LP` 前缀表示 "long pointer"，在32位系统中，它实际上没有特殊含义，但在16位 Windows 操作系统时代，它用于指示指针是长指针，而不是普通指针。
>
> - `W` 表示 "wide"，用于表示宽字符，即 Unicode 字符。在 Windows 系统中，通常使用 Unicode 编码来处理字符串，所以 `LPWSTR` 实际上是指向 Unicode 字符串的指针。
>
> - `STR` 表示 "string"，即字符串。
>
> 因此，`LPWSTR` 表示指向以宽字符形式编码的字符串的指针，在 Windows 编程中经常用于处理 Unicode 字符串。



> 如果 `aaaMykey` 这个注册表项不存在，`RegOpenKeyEx` 函数将会失败，返回一个错误代码。在这种情况下，通常会在函数返回之后通过判断错误代码来确定注册表项是否成功打开。
>
> 常见的错误代码包括：
>
> - `ERROR_FILE_NOT_FOUND`（2）：指定的注册表项不存在，可能是由于指定的路径不正确或者该项尚未创建。
>   
> - `ERROR_ACCESS_DENIED`（5）：访问被拒绝，通常是由于权限不足或者当前用户没有权限执行该操作。
>
> - `ERROR_INVALID_HANDLE`（6）：指定的注册表项句柄无效，可能是由于该句柄未初始化或已关闭。
>
> 等等。
>
> 在程序中，可以根据返回的错误代码来进行适当的错误处理，例如输出错误信息、创建注册表项、请求用户权限等操作，以解决打开注册表项不存在的情况。



```c++
lRet = RegDeleteValue(hKey, L"qyf");
```

这段代码使用了Windows API中的RegDeleteValue函数来删除指定注册表项的指定键值。让我们逐个解释其参数和作用：

1. `hKey`：这是先前通过RegOpenKeyEx函数打开的注册表项的句柄（HANDLE类型），它指定了要删除键值的注册表项。

2. `L"qyf"`：这是要删除的键的名称，以宽字符形式表示。在这里，"qyf" 是要删除的键的名称。

函数调用将尝试删除指定注册表项中的指定键值。如果删除成功，函数返回值将是 `ERROR_SUCCESS`，表示成功删除键值；否则返回其他错误代码，表示删除失败。



# heapRepeatedRelease

```c++
void heapRepeatedRelease() {
    printf("按任意键启动 HeapCreate !\n");
    getchar();
    HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

    int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
    for (int i = 0; i < 30; ++i) {
        pArr[i] = i + 1;
    }
    printf("成功创建堆!\n");
    for (int i = 0; i < 30; ++i) {
        if (i % 5 == 0)
            printf_s("\n");
        printf("%3d ", pArr[i]);
    }
    printf_s("\n\n");
    printf("按任意键启动第一个 HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("按任意键启动第二个 HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("按任意键销毁堆!\n");
    getchar();
    HeapDestroy(hHeap);
}
```



```c++
HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);
```

这段代码使用了 Windows API 中的 `HeapCreate` 函数来创建一个新的堆。让我们逐个解释其参数和作用：

1. `HEAP_NO_SERIALIZE`：这是堆的选项参数，指定了创建的堆不需要进行序列化。在多线程环境中，如果不需要在多个线程之间同步访问堆，可以使用这个选项来提高性能。这意味着在对堆进行操作时，不会执行额外的同步操作。

2. `PAGE_SIZE * 10`：这是堆的初始大小。在这里，`PAGE_SIZE` 是一个常量，表示页面大小。通过将页面大小乘以10，我们设定了初始堆的大小为10个页面。

3. `PAGE_SIZE * 100`：这是堆的最大大小。在这里，我们将最大堆的大小设定为100个页面。如果需要更多的内存，堆可以自动扩展到这个大小。

函数调用将创建一个新的堆，并返回一个指向堆的句柄（`HANDLE` 类型）。这个句柄可以用于后续对堆进行操作，如分配和释放内存等。



```c++
HeapFree(hHeap, 0, pArr);
```

这段代码使用了 Windows API 中的 `HeapFree` 函数来释放先前通过堆分配的内存块。让我们逐个解释其参数和作用：

1. `hHeap`：这是先前通过 `HeapCreate` 函数创建的堆的句柄（HANDLE 类型），它标识了要释放内存的堆。

2. `0`：这是堆释放选项，用于指定额外的操作。在这里，设置为0表示没有特殊的选项，即使用默认选项。

3. `pArr`：这是一个指向先前通过堆分配的内存块的指针。在这里，`pArr` 指向一个整数数组，该数组是先前通过 `HeapAlloc` 函数在堆上分配的内存块。

函数调用将释放先前分配的内存块，使其可用于后续的分配。在释放内存块之后，指向该内存块的指针 `pArr` 不再有效，因为该内存块已经不再属于应用程序的控制范围内。



> 在连续执行两次 `HeapFree(hHeap, 0, pArr);` 的情况下，第一次调用会成功释放内存，但第二次调用可能会导致未定义的行为。
>
> 第一次调用 `HeapFree` 释放了指向堆中分配的内存块的指针 `pArr`。但在第一次调用之后，指针 `pArr` 的值并没有被重置或者修改，它仍然指向先前被释放的内存块。
>
> 在大多数情况下，第二次调用 `HeapFree` 会导致运行时错误，因为它试图释放一个已经被释放的内存块。具体行为取决于操作系统和堆管理器的实现，可能会导致程序崩溃、内存损坏或其他不可预测的行为。
>
> 因此，在使用 `HeapFree` 函数时，应该确保每个内存块只被释放一次。如果需要多次释放相同的内存块，应该确保在每次释放后将指针重置为 `NULL` 或者其他有效的值，以避免出现未定义的行为。



# modifyExProgram

```c++
void modifyExProgram() {
    HANDLE hOpenFile = (HANDLE)CreateFile(L"a.exe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
        NULL, NULL);
    CloseHandle(hOpenFile);
}
```



```c++
HANDLE hOpenFile = (HANDLE)CreateFile(L"a.exe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
```

这段代码使用 Windows API 中的 `CreateFile` 函数来创建或打开一个文件。让我们逐个解释其参数和作用：

1. `L"a.exe"`：这是要创建或打开的文件的名称。在这里，文件名为 "a.exe"。

2. `GENERIC_READ | GENERIC_WRITE`：这是访问权限参数，指定了对文件的读取和写入权限。`GENERIC_READ` 表示允许读取文件，`GENERIC_WRITE` 表示允许写入文件。在这里，指定了允许对文件进行读取和写入操作。

3. `FILE_SHARE_READ`：这是共享模式参数，指定了其他进程如何访问该文件。`FILE_SHARE_READ` 表示其他进程可以以只读方式访问该文件，但不能写入。这意味着允许其他进程读取该文件，但不允许其他进程修改该文件。

4. `NULL`：这是安全属性参数，用于指定安全描述符。在这里，未指定安全属性。

5. `CREATE_ALWAYS`：这是创建选项参数，指定了当文件已存在时的处理方式。`CREATE_ALWAYS` 表示如果文件已存在，则将其覆盖；如果文件不存在，则创建新文件。在这里，指定了总是创建新文件，即使文件已存在也会被覆盖。

6. `NULL, NULL`：这是模板文件句柄和文件属性参数，用于指定一个模板文件和文件属性。在这里，未指定模板文件和文件属性。

函数调用将尝试创建或打开名为 "a.exe" 的文件。如果文件已存在且成功打开，则返回一个指向文件的句柄（`HANDLE` 类型）；如果文件不存在且成功创建，则返回一个指向新创建文件的句柄。如果操作失败，则返回 `INVALID_HANDLE_VALUE`，表示创建或打开文件失败。



# selfReplication

```c++
void selfReplication() {
    HANDLE hOpenFile = (HANDLE)CreateFile(L"testCode.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL,
        NULL);
    CloseHandle(hOpenFile);
}
```



```c++
HANDLE hOpenFile = (HANDLE)CreateFile(L"testCode.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
```

这段代码使用了 Windows API 中的 `CreateFile` 函数来创建或打开一个文件。让我们逐个解释其参数和作用：

1. `L"testCode.exe"`：这是要创建或打开的文件的名称。在这里，文件名为 "testCode.exe"。

2. `GENERIC_READ`：这是访问权限参数，指定了对文件的读取权限。`GENERIC_READ` 表示允许读取文件，但不允许写入。在这里，指定了只允许对文件进行读取操作。

3. `FILE_SHARE_READ`：这是共享模式参数，指定了其他进程如何访问该文件。`FILE_SHARE_READ` 表示其他进程可以以只读方式访问该文件，但不能写入。这意味着允许其他进程读取该文件，但不允许其他进程修改该文件。

4. `NULL`：这是安全属性参数，用于指定安全描述符。在这里，未指定安全属性。

5. `OPEN_ALWAYS`：这是创建选项参数，指定了当文件已存在时的处理方式。`OPEN_ALWAYS` 表示如果文件已存在，则打开该文件；如果文件不存在，则创建新文件。在这里，指定了如果文件存在则打开，否则创建新文件。

6. `NULL, NULL`：这是模板文件句柄和文件属性参数，用于指定一个模板文件和文件属性。在这里，未指定模板文件和文件属性。

函数调用将尝试打开名为 "testCode.exe" 的文件。如果文件已存在则成功打开，如果文件不存在则创建新文件，然后返回一个指向文件的句柄（`HANDLE` 类型）。如果操作失败，则返回 `INVALID_HANDLE_VALUE`，表示创建或打开文件失败。



> 这两个函数的区别在于它们创建或打开的文件名不同以及文件的访问权限不同。
>
> 1. `modifyExProgram` 函数：
>    - 创建或打开的文件名为 "a.exe"。
>    - 设置了文件的访问权限为读取和写入（`GENERIC_READ | GENERIC_WRITE`）。
>    - 文件被总是创建为新文件（`CREATE_ALWAYS`）。
>
> 2. `selfReplication` 函数：
>    - 创建或打开的文件名为 "testCode.exe"。
>    - 设置了文件的访问权限为只读（`GENERIC_READ`）。
>    - 如果文件已经存在，则打开文件；否则创建新文件（`OPEN_ALWAYS`）。
>
> 因此，`modifyExProgram` 函数创建一个名为 "a.exe" 的新文件，并且可以对该文件进行读取和写入操作；而 `selfReplication` 函数创建或打开一个名为 "testCode.exe" 的文件，但只能读取该文件，无法进行写入操作。



# modifyStartupRegistry

```c++
void modifyStartupRegistry() {
    HKEY hKey = NULL;
    size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"SOFTWARE\Microsoft\Windows\CurrentVersion\Run", 0,
        KEY_READ, &hKey);
    if (lRet == ERROR_SUCCESS) {
        printf("打开成功！\n");
    }
    else {
        printf("打开失败！\n");
    }
    RegCloseKey(hKey);
}
```



```c++
HKEY hKey = NULL;
```

这段代码声明了一个句柄（handle）变量 `hKey`，并将其初始化为 `NULL`。在Windows编程中，句柄是一种特殊的数据类型，用于引用操作系统内核对象，例如文件、注册表项、窗口等。在这里，`hKey` 将被用作对注册表键的引用。

初始化 `hKey` 为 `NULL` 是一种良好的做法，因为在后续代码中，如果打开注册表失败或者出现异常情况，`hKey` 可能没有被正确地赋值，将保持为 `NULL`，这可以作为一个信号来表明注册表的操作没有成功。



```c++
size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"SOFTWARE\Microsoft\Windows\CurrentVersion\Run", 0, KEY_READ, &hKey);
```

这段代码使用了 Windows API 中的 `RegOpenKeyEx` 函数来打开注册表中的一个键。让我们逐个解释其参数和作用：

1. `HKEY_CURRENT_USER`：这是一个预定义的常量，表示当前用户的根注册表键。在这里，指定了要打开的注册表键相对于当前用户的根键。

2. `(LPWSTR)L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"`：这是要打开的注册表键的路径。这个路径指定了要打开的启动项键的位置。需要注意的是，路径是一个宽字符字符串（`LPWSTR`），前面的 `(LPWSTR)` 是一种类型转换，将字符串转换为宽字符格式。

3. `0`：这是保留参数，通常设置为0。

4. `KEY_READ`：这是访问权限参数，指定了打开注册表键的访问权限。在这里，指定了只读权限，即只允许读取注册表键的值，不能修改。

5. `&hKey`：这是一个指向 `HKEY` 类型变量的指针，用于接收打开的注册表键的句柄。在这里，`&hKey` 是 `hKey` 变量的地址，用于在函数调用后获取打开的注册表键的句柄。

6. `lRet`：这是函数调用的返回值，表示函数执行的结果。通常情况下，如果函数成功执行，则返回 `ERROR_SUCCESS`，否则返回其他错误代码。

函数调用将尝试打开指定路径的注册表键。如果操作成功，则 `lRet` 的值为 `ERROR_SUCCESS`，并且 `hKey` 变量将包含指向打开的注册表键的句柄；如果操作失败，则 `lRet` 的值为其他错误代码。



> 在 Windows 操作系统中，字符串通常以宽字符（wchar_t 类型）的形式表示，以支持国际化和特殊字符（如非 ASCII 字符）。在 Windows API 中，许多函数接受宽字符字符串作为参数，因此需要使用宽字符字符串来表示路径。
>
> 在给定的代码中，路径字符串被定义为 `L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"`，前缀 `L` 表示这是一个宽字符字符串的字面量。因此，将其转换为 `LPWSTR` 类型是为了与 `RegOpenKeyEx` 函数的参数类型匹配，因为该函数要求传入的路径参数为宽字符字符串类型。



> RegOpenKeyEx使用这个函数打开一个键，后期需不需要用某些操作来关闭呢？
>
> 是的，使用 `RegOpenKeyEx` 函数打开注册表键后，需要使用 `RegCloseKey` 函数来关闭打开的注册表键句柄。这样做是为了确保释放相关资源，防止资源泄漏。
>
> 例如，在你提供的代码中，打开注册表键后，使用了 `RegCloseKey(hKey);` 来关闭注册表键句柄 `hKey`。
>
> 通常情况下，打开注册表键后，只要不再需要访问该键，就应该立即将其关闭，以释放相关资源并确保系统资源的正确管理。



# openAnotherFolder

```c++
void openAnotherFolder() {
    HANDLE hOpenFile = (HANDLE)CreateFile(L".\\testFolder\\a.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
        CREATE_ALWAYS, NULL, NULL);
    CloseHandle(hOpenFile);
}
```



```c++
HANDLE hOpenFile = (HANDLE)CreateFile(L".\\testFolder\\a.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
```

这段代码使用了 Windows API 中的 `CreateFile` 函数来创建一个文件或者打开一个已存在的文件。让我们逐个解释其参数和作用：

1. `L".\\testFolder\\a.txt"`：这是要创建或打开的文件的路径。`.\\testFolder\\a.txt` 表示文件相对于当前目录下的 "testFolder" 文件夹，其中 `.` 表示当前目录，`\\` 表示路径分隔符，`testFolder` 是文件夹的名称，`a.txt` 是文件的名称。

2. `GENERIC_READ | GENERIC_WRITE`：这是访问权限参数，指定了对文件的读取和写入权限。`GENERIC_READ` 表示允许读取文件，`GENERIC_WRITE` 表示允许写入文件。在这里，指定了允许对文件进行读取和写入操作。

3. `FILE_SHARE_READ`：这是共享模式参数，指定了其他进程如何访问该文件。`FILE_SHARE_READ` 表示其他进程可以以只读方式访问该文件，但不能写入。这意味着允许其他进程读取该文件，但不允许其他进程修改该文件。

4. `NULL`：这是安全属性参数，用于指定安全描述符。在这里，未指定安全属性。

5. `CREATE_ALWAYS`：这是创建选项参数，指定了当文件已存在时的处理方式。`CREATE_ALWAYS` 表示如果文件已存在，则将其覆盖；如果文件不存在，则创建新文件。在这里，指定了总是创建新文件，即使文件已存在也会被覆盖。

6. `NULL, NULL`：这是模板文件句柄和文件属性参数，用于指定一个模板文件和文件属性。在这里，未指定模板文件和文件属性。

函数调用将尝试创建或打开名为 "a.txt" 的文件。如果文件已存在且成功打开，则返回一个指向文件的句柄（`HANDLE` 类型）；如果文件不存在且成功创建，则返回一个指向新创建文件的句柄。如果操作失败，则返回 `INVALID_HANDLE_VALUE`，表示创建或打开文件失败。



# recvData

```c++
void recvData() {
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    Sleep(500);
    //接收服务器传回的数据
    char szBuffer[MAXBYTE] = { 0 };
    recv(sock, szBuffer, MAXBYTE, NULL);
    //输出接收到的数据
    printf("Message form server: %s\n", szBuffer);
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
}
```



```c++
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
```

这段代码是用于初始化 Winsock 库的一部分，主要有两个函数调用：

1. **WSADATA 结构体声明**：
   - `WSADATA` 是一个结构体，用于保存 Winsock 库的信息，包括库的版本号等。在这里，声明了一个 `wsaData` 变量，用于存储初始化后的 Winsock 信息。

2. **WSAStartup 函数调用**：
   - `WSAStartup` 函数用于初始化 Winsock 库。它接受两个参数：一个用来表示 Winsock 库的版本号，另一个是指向 `WSADATA` 结构体的指针，用于接收初始化后的信息。
   - `MAKEWORD(2, 2)` 是一个宏，用于将两个字节的高低版本号组合成一个字，表示要请求初始化的 Winsock 库版本为 2.2。
   - `&wsaData` 是指向 `WSADATA` 结构体的指针，用于接收初始化后的信息。

调用 `WSAStartup` 函数后，如果初始化成功，`wsaData` 结构体中将包含有关 Winsock 库的信息，程序就可以在后续的网络通信中使用 Winsock 提供的函数。通常在使用 Winsock 函数之前需要先调用 `WSAStartup` 函数来初始化 Winsock 库，而在程序结束时需要调用 `WSACleanup` 函数来释放 Winsock 相关资源。



```c++
SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
```

这段代码用于创建一个套接字（Socket），并将其赋值给变量 `sock`。让我们逐个解释其参数和作用：

1. **`socket` 函数**：
   - `socket` 函数用于创建一个套接字，以便进行网络通信。它接受三个参数：地址族（Address Family）、套接字类型（Socket Type）和协议（Protocol）。
   - 第一个参数 `PF_INET` 表示使用 IPv4 地址族，即 Internet 地址族。在 Windows 中，`PF_INET` 和 `AF_INET` 是等价的，都表示 IPv4 地址族。
   - 第二个参数 `SOCK_STREAM` 表示创建的套接字类型是流套接字（Stream Socket），用于基于流的可靠的、双向的连接通信。流套接字提供面向连接的、可靠的、按序传输的数据流。
   - 第三个参数 `IPPROTO_TCP` 表示所使用的协议是 TCP 协议，即传输控制协议。TCP 是一种可靠的、面向连接的协议，用于在网络上可靠地传输数据流。

2. **`SOCKET` 类型**：
   - `SOCKET` 是 Windows API 中定义的一种数据类型，用于表示套接字句柄。在这里，将 `socket` 函数返回的套接字句柄存储在名为 `sock` 的变量中，以便后续使用该套接字进行网络通信。

总的来说，这段代码创建了一个 TCP 套接字，并将其赋值给变量 `sock`，以便在后续的网络通信中使用该套接字。



```c++
sockaddr_in sockAddr;
memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
sockAddr.sin_family = PF_INET;
sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
sockAddr.sin_port = htons(1234);
connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
```

这段代码是用于连接到指定的服务器地址和端口的过程。让我们逐步解释其功能和各个部分的作用：

1. **`sockaddr_in` 结构体声明**：
   - `sockaddr_in` 是一个用于表示 IPv4 地址的结构体，在 Windows 环境下用于指定套接字地址信息。
   - 在这里，声明了一个名为 `sockAddr` 的 `sockaddr_in` 结构体变量，用于存储要连接的目标服务器的地址信息。

2. **内存清零**：
   - 使用 `memset` 函数将 `sockAddr` 结构体的内存清零，以确保其中的所有字节都被初始化为0。这是一种常见的初始化结构体的方法。

3. **设置地址族和端口号**：
   - `sockAddr.sin_family = PF_INET;` 将地址族设置为 `PF_INET`，表示使用 IPv4 地址族。
   - `sockAddr.sin_port = htons(1234);` 将端口号设置为 1234，并使用 `htons` 函数将端口号从主机字节序转换为网络字节序。这是因为在网络通信中，使用网络字节序来表示端口号是标准做法。

4. **设置目标 IP 地址**：
   - `sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");` 将目标服务器的 IP 地址设置为 "127.0.0.1"，即本地回环地址。在网络编程中，这通常表示连接到本地计算机上的服务器。

5. **连接到服务器**：
   - 使用 `connect` 函数来连接到目标服务器。该函数接受套接字描述符 `sock`、指向目标地址信息的指针以及地址信息结构体的大小作为参数。
   - `(SOCKADDR*)&sockAddr` 将 `sockAddr` 结构体转换为通用的 `SOCKADDR` 结构体指针，以满足 `connect` 函数的参数类型要求。
   - `sizeof(SOCKADDR)` 用于指定地址信息结构体的大小，以确保 `connect` 函数能够正确地访问地址信息。

调用 `connect` 函数后，如果连接成功，则套接字 `sock` 将与指定的服务器建立连接，可以通过该套接字进行数据交换；如果连接失败，则需要根据返回值进行错误处理。



```c++
char szBuffer[MAXBYTE] = { 0 };
recv(sock, szBuffer, MAXBYTE, NULL);
```

这段代码用于从已连接的套接字 `sock` 中接收数据，并将接收到的数据存储到缓冲区 `szBuffer` 中。让我们逐步解释其功能和各个部分的作用：

1. **声明缓冲区**：
   - `char szBuffer[MAXBYTE] = { 0 };` 声明了一个名为 `szBuffer` 的字符数组，用于存储接收到的数据。
   - `MAXBYTE` 是一个宏，表示缓冲区的最大长度，即要接收的数据的最大字节数。这里假设 `MAXBYTE` 是一个合适的大小，可以容纳接收到的数据。

2. **接收数据**：
   - `recv` 函数用于从已连接的套接字中接收数据。它接受四个参数：套接字描述符、接收数据的缓冲区、要接收的数据的最大长度以及接收数据的标志。
   - `sock` 是一个已连接的套接字，用于接收数据。
   - `szBuffer` 是用于存储接收到的数据的缓冲区。
   - `MAXBYTE` 表示要接收的数据的最大长度，即缓冲区的大小。
   - `NULL` 是接收数据的标志，表示没有指定特殊的接收选项。

调用 `recv` 函数后，如果接收到数据，则数据将被存储到 `szBuffer` 缓冲区中；如果没有接收到数据，则 `szBuffer` 中的内容将保持不变。需要注意的是，`recv` 函数会阻塞当前线程，直到接收到数据或者发生错误。因此，在实际应用中，可能需要使用非阻塞方式接收数据，或者在合适的地方处理阻塞状态。



```c++
WSACleanup();
```

这段代码调用了 `WSACleanup()` 函数，用于终止使用 Winsock 库。让我们来详细解释一下：

1. **WSACleanup 函数**：
   - `WSACleanup()` 是 Windows Sockets 应用程序结束时调用的函数之一。它的作用是释放 Winsock 动态链接库 (DLL) 占用的系统资源，清理程序使用 Winsock 库所产生的所有资源。
   - 在程序结束时，调用 `WSACleanup()` 函数是一个良好的做法，以确保释放所有由 Winsock 库分配的资源，避免资源泄漏和系统资源的浪费。

2. **调用时机**：
   - 通常情况下，`WSACleanup()` 函数应该在程序的退出点处调用，即在不再需要使用 Winsock 库的时候调用。这可以是程序的 `main()` 函数的返回点，或者是在程序终止之前的任何一个退出点。
   - 如果在程序退出时没有调用 `WSACleanup()` 函数，系统可能会导致资源泄漏或其他不良后果。

总之，调用 `WSACleanup()` 函数是一个重要的步骤，用于释放 Winsock 库所占用的系统资源，确保程序的正常结束和资源的释放。



# sendData

```c++
void sendData() {
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //绑定套接字
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port = htons(1234);  //端口
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //进入监听状态
    listen(servSock, 20);
    //接收客户端请求
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
    //向客户端发送数据
    char str[32] = "Hello World!";
    send(clntSock, str, strlen(str) + sizeof(char), NULL);
    //关闭套接字
    closesocket(clntSock);
    closesocket(servSock);
    //终止 DLL 的使用
    WSACleanup();
}
```



```c++
bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
```

这段代码使用 `bind` 函数将套接字与特定的 IP 地址和端口绑定起来。让我们来详细解释一下：

1. **`bind` 函数**：
   - `bind` 函数用于将套接字与特定的 IP 地址和端口进行绑定，使套接字监听该地址和端口上的连接请求。
   - 它接受三个参数：要绑定的套接字描述符、指向 `sockaddr` 结构体的指针（通常为 `SOCKADDR*` 类型）、以及指定的地址结构体的大小。
   - 在这里，`servSock` 是要绑定的套接字描述符，`sockAddr` 是一个 `sockaddr_in` 结构体，存储了要绑定的 IP 地址和端口号。

2. **类型转换**：
   - 因为 `bind` 函数的第二个参数需要指向 `sockaddr` 结构体的指针，而 `sockAddr` 是一个 `sockaddr_in` 结构体，因此需要进行类型转换。
   - `(SOCKADDR*)&sockAddr` 将 `sockAddr` 结构体的地址转换为指向 `sockaddr` 结构体的指针，以满足 `bind` 函数参数的类型要求。

3. **结构体大小**：
   - `sizeof(SOCKADDR)` 用于指定传递给 `bind` 函数的地址结构体的大小。这是为了确保 `bind` 函数能够正确地读取并处理传入的地址信息。

调用 `bind` 函数后，如果绑定成功，则服务器就会在指定的 IP 地址和端口上监听连接请求；如果绑定失败，则可能是由于指定的 IP 地址或端口已被占用，或者其他原因导致的绑定失败。



```c++
listen(servSock, 20);
```

这段代码使用 `listen` 函数将套接字设置为监听状态，以便接收客户端的连接请求。让我们来详细解释一下：

1. **`listen` 函数**：
   - `listen` 函数用于将套接字设置为监听状态，以便接收客户端的连接请求。
   - 它接受两个参数：要监听的套接字描述符和待处理连接请求的最大数量。
   - 在这里，`servSock` 是要设置为监听状态的套接字描述符，`20` 表示待处理连接请求的最大数量。

2. **待处理连接请求的最大数量**：
   - 第二个参数指定了待处理连接请求的最大数量，即队列的长度。当有新的连接请求到达时，它们会被放入待处理连接请求队列中，等待服务器接受并处理。
   - 如果待处理连接请求的数量超过了指定的最大值，新的连接请求可能会被拒绝或丢弃，直到队列中有空闲位置。

调用 `listen` 函数后，如果设置成功，则服务器就处于监听状态，可以接受客户端的连接请求；如果设置失败，则可能是由于参数错误或其他原因导致的设置失败。



```c++
SOCKADDR clntAddr;
int nSize = sizeof(SOCKADDR);
SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
```

这段代码用于接受客户端的连接请求，并创建一个新的套接字用于与客户端通信。让我们逐步解释其功能和各个部分的作用：

1. **声明变量**：
   - `SOCKADDR clntAddr;` 声明了一个名为 `clntAddr` 的 `SOCKADDR` 结构体变量，用于存储客户端的地址信息。
   - `int nSize = sizeof(SOCKADDR);` 声明了一个整型变量 `nSize`，用于存储地址结构体的大小。

2. **接受连接请求**：
   - 使用 `accept` 函数接受客户端的连接请求。该函数会阻塞程序的执行，直到有客户端连接进来。
   - 它接受三个参数：监听套接字描述符、指向客户端地址信息结构体的指针以及指向存储地址信息结构体大小的变量的指针。
   - `servSock` 是监听套接字描述符，用于接受客户端的连接请求。
   - `(SOCKADDR*)&clntAddr` 将 `clntAddr` 结构体转换为指向 `SOCKADDR` 结构体的指针，以便 `accept` 函数填充客户端的地址信息。
   - `&nSize` 是一个指向 `nSize` 变量的指针，用于告知 `accept` 函数地址结构体的大小。

3. **创建新的套接字**：
   - 如果 `accept` 函数调用成功，它将返回一个新的套接字描述符 `clntSock`，用于与客户端进行通信。
   - 这个新的套接字是专门为与该客户端通信而创建的，并且可以使用它来发送和接收数据。

调用 `accept` 函数后，如果成功接受到客户端的连接请求，则会返回一个新的套接字描述符 `clntSock`，可以使用它与客户端进行通信；如果没有连接请求到达，`accept` 函数可能会一直阻塞程序的执行，直到有连接请求到达为止。



> `listen` 和 `accept` 是 TCP 套接字编程中常用的两个函数，它们协同工作来实现服务器端的监听和接受客户端连接的功能。下面是它们的协同工作过程：
>
> 1. **`listen` 函数**：
>    - `listen` 函数被用来告诉操作系统监听特定套接字上的连接请求。它的第一个参数是服务器套接字描述符 `servSock`，这是服务器正在监听的套接字。
>    - `listen` 函数的第二个参数是待处理连接请求的最大数量，即监听队列的长度。当有新的连接请求到达时，它们会被放入待处理连接请求队列中，等待服务器接受并处理。
>    - 调用 `listen` 函数后，服务器套接字进入监听状态，可以接受客户端的连接请求。
>
> 2. **`accept` 函数**：
>    - `accept` 函数用于接受客户端的连接请求，并创建一个新的套接字用于与客户端进行通信。它的第一个参数是服务器套接字描述符 `servSock`，用于接受连接请求。
>    - `accept` 函数的第二个参数是指向客户端地址信息结构体的指针，用于存储客户端的地址信息。
>    - `accept` 函数的第三个参数是指向存储地址信息结构体大小的变量的指针，用于告知 `accept` 函数地址结构体的大小。
>    - 当调用 `accept` 函数时，它会阻塞程序的执行，直到有客户端连接进来。一旦有客户端连接成功，它会返回一个新的套接字描述符，即 `clntSock`，用于与该客户端通信。
>
> 这样，`listen` 函数负责将服务器套接字设置为监听状态，而 `accept` 函数负责接受客户端的连接请求，并创建一个新的套接字用于与客户端进行通信。两者配合起来，实现了服务器端的监听和接受连接的功能。



```c++
send(clntSock, str, strlen(str) + sizeof(char), NULL);
```

这段代码使用 `send` 函数向客户端发送数据。让我们逐步解释其功能和各个部分的作用：

1. **`send` 函数**：
   - `send` 函数用于将数据发送到已连接的套接字。
   - 它接受四个参数：要发送数据的套接字描述符、指向要发送数据的缓冲区的指针、要发送数据的字节数、以及一组标志位（在此处为 `NULL`）。
   - 在这里，`clntSock` 是已连接的客户端套接字描述符，用于与客户端进行通信。
   - `str` 是要发送的数据缓冲区的指针，其中存储着要发送的字符串数据。
   - `strlen(str) + sizeof(char)` 计算要发送的数据的字节数，其中 `strlen(str)` 返回字符串的长度，`sizeof(char)` 返回字符类型的大小。
   - 最后一个参数通常是一组标志位，用于指定发送数据的方式和行为，但在这里被设置为 `NULL`，表示使用默认行为。

2. **发送数据**：
   - `send` 函数会将指定长度的数据从缓冲区 `str` 发送到与 `clntSock` 关联的套接字上。

总的来说，这段代码通过 `send` 函数将字符串数据发送到与客户端连接的套接字上，从而向客户端发送消息。

> 在这段代码中，`strlen(str)` 返回的是字符串 `str` 的长度，单位是字节数。而 `sizeof(char)` 返回的是 `char` 类型的大小，通常是1字节。因此，`strlen(str) + sizeof(char)` 计算的是字符串数据的实际长度，包括了字符串中的字符数量以及一个终止符（null-terminator），用来表示字符串的结束。
>
> 在发送数据时，需要确保发送的数据长度是正确的，包括了整个字符串以及终止符，因此将字符串长度和一个字符的大小相加，可以得到实际要发送的数据的总长度。



# memoryOperation

```c++
void memoryOperation() {
    getchar();
    char temp[100] = "";
    printf("按任意键复制内存\n");
    getchar();
    memcpy(temp, "hello\n", 6);
    printf("%s", temp);
    printf("按任意键清空内存\n");
    getchar();
    memmove(temp, "world\n", 6);
    printf("%s", temp);
}
```



```c++
memmove(temp, "world\n", 6);
```

这段代码使用了 `memmove` 函数将字符串 "world\n" 的前 6 个字符复制到 `temp` 所指向的内存位置。下面是对代码的详细解释：

1. **`memmove` 函数**：
   - `memmove` 函数用于在内存中移动一块数据，即从源地址复制指定数量的字节到目标地址。
   - 它接受三个参数：目标地址指针、源地址指针、以及要复制的字节数。
   - 与 `memcpy` 函数相比，`memmove` 函数可以处理内存区域的重叠，即源地址和目标地址可以指向同一块内存，而 `memcpy` 函数在这种情况下的行为是未定义的。因此，通常建议在处理可能出现重叠的情况时使用 `memmove` 函数。

2. **参数解释**：
   - `temp` 是目标地址指针，指向要将数据复制到的内存位置。
   - `"world\n"` 是源地址指针，指向存储了要复制的数据的字符串常量。
   - `6` 是要复制的字节数，即复制 "world\n" 字符串的前 6 个字符（包括 "w"、"o"、"r"、"l"、"d" 和换行符 "\n"）。

3. **操作结果**：
   - 执行这行代码后，`temp` 指向的内存位置将被复制为 "world\n" 字符串的前 6 个字符，即 "world\n"。