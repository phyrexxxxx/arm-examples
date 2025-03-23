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