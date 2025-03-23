## 如何執行?
執行:
```
$ cd example3-2
$ make default qemu
```

輸出以下訊息:
```
arm-linux-gnueabihf-gcc -c -O3 -ggdb -Wall -fno-stack-protector -o example3.o example3.c
arm-linux-gnueabihf-gcc -o example3 example3.o
qemu-arm -L /usr/arm-linux-gnueabihf ./example3
a/2 / b/2 is 0
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
 412:	2200      	movs	r2, #0
 414:	b508      	push	{r3, lr}
 416:	2002      	movs	r0, #2
 418:	4479      	add	r1, pc
 41a:	f7ff efee 	blx	3f8 <__printf_chk@plt>
 41e:	2000      	movs	r0, #0
 420:	bd08      	pop	{r3, pc}
 422:	bf00      	nop
 424:	000001ac 	.word	0x000001ac

00000524 <dividebytwo>:
 524:	eb00 70d0 	add.w	r0, r0, r0, lsr #31
 528:	1040      	asrs	r0, r0, #1
 52a:	4770      	bx	lr
```

⭐ 從 `dump.txt` 可以觀察到 `dividebytwo()` 被 `-O3` 最佳化成 `ASR` 指令