## 如何執行?
執行:
```
$ cd example3-1
$ make default qemu
```

輸出以下訊息:
```
arm-linux-gnueabihf-gcc -c -O3 -ggdb -Wall -fno-stack-protector -o example3.o example3.c
arm-linux-gnueabihf-gcc -o example3 example3.o
qemu-arm -L /usr/arm-linux-gnueabihf ./example3
2a * 2b is -192
```

### 使用 `arm-linux-gnueabihf-objdump -d` 來 Disassemble
```
$ arm-linux-gnueabihf-objdump -d example3 > dump.txt
```
這樣會把反組譯 (disassemble) `example3` 執行檔的結果輸出到 `dump.txt` 檔案中

擷取 `dump.txt` 中的 Assembly Code:
```arm
00000410 <main>:
 410:	4904      	ldr	r1, [pc, #16]	@ (424 <main+0x14>)
 412:	f06f 02bf 	mvn.w	r2, #191	@ 0xbf
 416:	b508      	push	{r3, lr}
 418:	2002      	movs	r0, #2
 41a:	4479      	add	r1, pc
 41c:	f7ff efec 	blx	3f8 <__printf_chk@plt>
 420:	2000      	movs	r0, #0
 422:	bd08      	pop	{r3, pc}
 424:	000001a6 	.word	0x000001a6

00000524 <multiplybytwo>:
 524:	0040      	lsls	r0, r0, #1
 526:	4770      	bx	lr
```

`example3-1` 展示了 ARM 編譯器最佳化 (`-O3`) 如何影響 C 程式編譯後的組合語言 (assembly)，以及為什麼要懂得觀察 disassembly 的輸出，才能更深入理解 ARM 指令集、function call inlining、簡化運算等核心概念

### 【補充】`multiplybytwo()` 被最佳化成 `LSL` 指令
原始 C 函式:
```c
int multiplybytwo(int a)
{
    return a * 2;
}
```

這個乘法其實可以被最佳化為位移運算: 

```c
return a << 1;
```

編譯後的 Assembly:
```arm
00000524 <multiplybytwo>:
 524:	0040      	lsls	r0, r0, #1
 526:	4770      	bx	lr
```

- `lsls r0, r0, #1`: 將 `r0` 左移 1 bit，相當於 `r0 = r0 * 2`
- `bx lr`: 回傳

這表示 compiler 完全理解這個 function 是簡單的乘 2 操作，因此用更快的 `LSL` 指令替代原本的乘法運算

### 【補充】`-O3`
- `-O3` 是 gcc 的最高階最佳化選項之一，它會開啟一系列 aggressive 的最佳化行為，例如:
  - inlining (將小函式直接展開在呼叫點)
  - strength reduction (將乘法變位移等)
  - loop unrolling
  - constant folding

所以看到的 `multiplybytwo()` 被簡化成 `LSL` 是 `-O3` 的成果

如果只用 `-O0`（無最佳化），則可能會看到完整的 `mul` 指令或甚至保留完整的 function call 架構

### 【補充】為什麼這裡沒有被 inline?
> 如果 multiplybytwo() 只是 `a * 2`，為什麼 `main()` 裡面還是呼叫 `multiplybytwo()`，沒被 inline？

分析: 
- 在這份 disassembly 中，`multiplybytwo()` 還是以一個獨立的 function 存在，代表它沒有被 inline
- 可能原因: 這份 code 使用了 `-ggdb`（加上 debug symbol），GCC 有時會保留部分函式結構方便除錯，即使開了 `-O3`
- 不過也可以試試去掉 `-ggdb` 看看 compiler 是否就會直接 inline 這個 function，或觀察 `main()` 是否直接變成 `lsls`
