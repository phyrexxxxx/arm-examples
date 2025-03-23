## 如何執行?
```
$ cd hello-as
$ make default qemu
```
輸出以下訊息:
```
arm-linux-gnueabihf-as -c  -o hello.o hello.s
hello.s: Assembler messages:
hello.s: Warning: end of file not at end of a line; newline inserted
arm-linux-gnueabihf-ld  -o hello hello.o
qemu-arm ./hello
Hello, world!
```

### 使用 `arm-linux-gnueabihf-objdump -d` 來 Disassemble
```
$ arm-linux-gnueabihf-objdump -d hello > dump.txt
```
這樣會把反組譯 (disassemble) `hello` 執行檔的結果輸出到 `dump.txt` 檔案中

擷取 `dump.txt` 中的 Assembly Code:
```asm
Disassembly of section .text:

00010054 <_start>:
   10054:	e3a00001 	mov	r0, #1
   10058:	e28f1014 	add	r1, pc, #20
   1005c:	e3a0200e 	mov	r2, #14
   10060:	e3a07004 	mov	r7, #4
   10064:	ef000000 	svc	0x00000000
   10068:	e3a00000 	mov	r0, #0
   1006c:	e3a07001 	mov	r7, #1
   10070:	ef000000 	svc	0x00000000

00010074 <msg>:
   10074:	6c6c6548 	.word	0x6c6c6548
   10078:	77202c6f 	.word	0x77202c6f
   1007c:	646c726f 	.word	0x646c726f
   10080:	0a21      	.short	0x0a21
	...
```
