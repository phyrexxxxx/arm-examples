## 如何執行?
```
$ cd hello-c
$ make default qemu
```

輸出以下訊息:
```
arm-linux-gnueabihf-gcc -c -O2 -ggdb -Wall -fno-stack-protector -o hello.o hello.c
arm-linux-gnueabihf-gcc -o hello hello.o
qemu-arm -L /usr/arm-linux-gnueabihf ./hello
Hello world!
```


### 使用 `arm-linux-gnueabihf-objdump -d` 來 Disassemble
```
$ arm-linux-gnueabihf-objdump -d hello > dump.txt
```
這樣會把反組譯 (disassemble) `hello` 執行檔的結果輸出到 `dump.txt` 檔案中

擷取 `dump.txt` 中的 Assembly Code:
```asm
Disassembly of section .text:

00000408 <main>:
 408:	4803      	ldr	r0, [pc, #12]	@ (418 <main+0x10>)
 40a:	b508      	push	{r3, lr}
 40c:	4478      	add	r0, pc
 40e:	f7ff efea 	blx	3e4 <puts@plt>
 412:	2000      	movs	r0, #0
 414:	bd08      	pop	{r3, pc}
 416:	bf00      	nop
 418:	000001a4 	.word	0x000001a4
```
