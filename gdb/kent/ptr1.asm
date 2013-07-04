
ptr1:     file format elf64-x86-64

Disassembly of section .init:

0000000000400338 <_init>:
  400338:	48 83 ec 08          	sub    $0x8,%rsp
  40033c:	e8 5b 00 00 00       	callq  40039c <call_gmon_start>
  400341:	e8 da 00 00 00       	callq  400420 <frame_dummy>
  400346:	e8 c5 01 00 00       	callq  400510 <__do_global_ctors_aux>
  40034b:	48 83 c4 08          	add    $0x8,%rsp
  40034f:	c3                   	retq   
Disassembly of section .plt:

0000000000400350 <__libc_start_main@plt-0x10>:
  400350:	ff 35 d2 04 20 00    	pushq  2098386(%rip)        # 600828 <_GLOBAL_OFFSET_TABLE_+0x8>
  400356:	ff 25 d4 04 20 00    	jmpq   *2098388(%rip)        # 600830 <_GLOBAL_OFFSET_TABLE_+0x10>
  40035c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400360 <__libc_start_main@plt>:
  400360:	ff 25 d2 04 20 00    	jmpq   *2098386(%rip)        # 600838 <_GLOBAL_OFFSET_TABLE_+0x18>
  400366:	68 00 00 00 00       	pushq  $0x0
  40036b:	e9 e0 ff ff ff       	jmpq   400350 <_init+0x18>
Disassembly of section .text:

0000000000400370 <_start>:
  400370:	31 ed                	xor    %ebp,%ebp
  400372:	49 89 d1             	mov    %rdx,%r9
  400375:	5e                   	pop    %rsi
  400376:	48 89 e2             	mov    %rsp,%rdx
  400379:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40037d:	50                   	push   %rax
  40037e:	54                   	push   %rsp
  40037f:	49 c7 c0 70 04 40 00 	mov    $0x400470,%r8
  400386:	48 c7 c1 80 04 40 00 	mov    $0x400480,%rcx
  40038d:	48 c7 c7 5d 04 40 00 	mov    $0x40045d,%rdi
  400394:	e8 c7 ff ff ff       	callq  400360 <__libc_start_main@plt>
  400399:	f4                   	hlt    
  40039a:	90                   	nop    
  40039b:	90                   	nop    

000000000040039c <call_gmon_start>:
  40039c:	48 83 ec 08          	sub    $0x8,%rsp
  4003a0:	48 8b 05 71 04 20 00 	mov    2098289(%rip),%rax        # 600818 <_DYNAMIC+0x190>
  4003a7:	48 85 c0             	test   %rax,%rax
  4003aa:	74 02                	je     4003ae <call_gmon_start+0x12>
  4003ac:	ff d0                	callq  *%rax
  4003ae:	48 83 c4 08          	add    $0x8,%rsp
  4003b2:	c3                   	retq   
  4003b3:	90                   	nop    
  4003b4:	90                   	nop    
  4003b5:	90                   	nop    
  4003b6:	90                   	nop    
  4003b7:	90                   	nop    
  4003b8:	90                   	nop    
  4003b9:	90                   	nop    
  4003ba:	90                   	nop    
  4003bb:	90                   	nop    
  4003bc:	90                   	nop    
  4003bd:	90                   	nop    
  4003be:	90                   	nop    
  4003bf:	90                   	nop    

00000000004003c0 <__do_global_dtors_aux>:
  4003c0:	55                   	push   %rbp
  4003c1:	48 89 e5             	mov    %rsp,%rbp
  4003c4:	53                   	push   %rbx
  4003c5:	48 83 ec 08          	sub    $0x8,%rsp
  4003c9:	80 3d 88 04 20 00 00 	cmpb   $0x0,2098312(%rip)        # 600858 <completed.6140>
  4003d0:	75 44                	jne    400416 <__do_global_dtors_aux+0x56>
  4003d2:	b8 78 06 60 00       	mov    $0x600678,%eax
  4003d7:	48 2d 70 06 60 00    	sub    $0x600670,%rax
  4003dd:	48 c1 f8 03          	sar    $0x3,%rax
  4003e1:	48 8d 58 ff          	lea    0xffffffffffffffff(%rax),%rbx
  4003e5:	48 8b 05 64 04 20 00 	mov    2098276(%rip),%rax        # 600850 <__bss_start>
  4003ec:	48 39 c3             	cmp    %rax,%rbx
  4003ef:	76 1e                	jbe    40040f <__do_global_dtors_aux+0x4f>
  4003f1:	48 83 c0 01          	add    $0x1,%rax
  4003f5:	48 89 05 54 04 20 00 	mov    %rax,2098260(%rip)        # 600850 <__bss_start>
  4003fc:	ff 14 c5 70 06 60 00 	callq  *0x600670(,%rax,8)
  400403:	48 8b 05 46 04 20 00 	mov    2098246(%rip),%rax        # 600850 <__bss_start>
  40040a:	48 39 c3             	cmp    %rax,%rbx
  40040d:	77 e2                	ja     4003f1 <__do_global_dtors_aux+0x31>
  40040f:	c6 05 42 04 20 00 01 	movb   $0x1,2098242(%rip)        # 600858 <completed.6140>
  400416:	48 83 c4 08          	add    $0x8,%rsp
  40041a:	5b                   	pop    %rbx
  40041b:	c9                   	leaveq 
  40041c:	c3                   	retq   
  40041d:	0f 1f 00             	nopl   (%rax)

0000000000400420 <frame_dummy>:
  400420:	55                   	push   %rbp
  400421:	48 83 3d 57 02 20 00 	cmpq   $0x0,2097751(%rip)        # 600680 <__JCR_END__>
  400428:	00 
  400429:	48 89 e5             	mov    %rsp,%rbp
  40042c:	74 16                	je     400444 <frame_dummy+0x24>
  40042e:	b8 00 00 00 00       	mov    $0x0,%eax
  400433:	48 85 c0             	test   %rax,%rax
  400436:	74 0c                	je     400444 <frame_dummy+0x24>
  400438:	bf 80 06 60 00       	mov    $0x600680,%edi
  40043d:	49 89 c3             	mov    %rax,%r11
  400440:	c9                   	leaveq 
  400441:	41 ff e3             	jmpq   *%r11
  400444:	c9                   	leaveq 
  400445:	c3                   	retq   
  400446:	90                   	nop    
  400447:	90                   	nop    

0000000000400448 <dummy_function>:
  400448:	55                   	push   %rbp
  400449:	48 89 e5             	mov    %rsp,%rbp
  40044c:	48 c7 45 f8 00 00 00 	movq   $0x0,0xfffffffffffffff8(%rbp)
  400453:	00 
  400454:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
  400458:	c6 00 00             	movb   $0x0,(%rax)
  40045b:	c9                   	leaveq 
  40045c:	c3                   	retq   

000000000040045d <main>:
  40045d:	55                   	push   %rbp
  40045e:	48 89 e5             	mov    %rsp,%rbp
  400461:	e8 e2 ff ff ff       	callq  400448 <dummy_function>
  400466:	b8 00 00 00 00       	mov    $0x0,%eax
  40046b:	c9                   	leaveq 
  40046c:	c3                   	retq   
  40046d:	90                   	nop    
  40046e:	90                   	nop    
  40046f:	90                   	nop    

0000000000400470 <__libc_csu_fini>:
  400470:	f3 c3                	repz retq 
  400472:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  400479:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400480 <__libc_csu_init>:
  400480:	4c 89 64 24 e0       	mov    %r12,0xffffffffffffffe0(%rsp)
  400485:	4c 89 6c 24 e8       	mov    %r13,0xffffffffffffffe8(%rsp)
  40048a:	4c 8d 25 cb 01 20 00 	lea    2097611(%rip),%r12        # 60065c <__fini_array_end>
  400491:	4c 89 74 24 f0       	mov    %r14,0xfffffffffffffff0(%rsp)
  400496:	4c 89 7c 24 f8       	mov    %r15,0xfffffffffffffff8(%rsp)
  40049b:	49 89 f6             	mov    %rsi,%r14
  40049e:	48 89 5c 24 d0       	mov    %rbx,0xffffffffffffffd0(%rsp)
  4004a3:	48 89 6c 24 d8       	mov    %rbp,0xffffffffffffffd8(%rsp)
  4004a8:	48 83 ec 38          	sub    $0x38,%rsp
  4004ac:	41 89 ff             	mov    %edi,%r15d
  4004af:	49 89 d5             	mov    %rdx,%r13
  4004b2:	e8 81 fe ff ff       	callq  400338 <_init>
  4004b7:	48 8d 05 9e 01 20 00 	lea    2097566(%rip),%rax        # 60065c <__fini_array_end>
  4004be:	49 29 c4             	sub    %rax,%r12
  4004c1:	49 c1 fc 03          	sar    $0x3,%r12
  4004c5:	4d 85 e4             	test   %r12,%r12
  4004c8:	74 1e                	je     4004e8 <__libc_csu_init+0x68>
  4004ca:	31 ed                	xor    %ebp,%ebp
  4004cc:	48 89 c3             	mov    %rax,%rbx
  4004cf:	90                   	nop    
  4004d0:	48 83 c5 01          	add    $0x1,%rbp
  4004d4:	4c 89 ea             	mov    %r13,%rdx
  4004d7:	4c 89 f6             	mov    %r14,%rsi
  4004da:	44 89 ff             	mov    %r15d,%edi
  4004dd:	ff 13                	callq  *(%rbx)
  4004df:	48 83 c3 08          	add    $0x8,%rbx
  4004e3:	49 39 ec             	cmp    %rbp,%r12
  4004e6:	75 e8                	jne    4004d0 <__libc_csu_init+0x50>
  4004e8:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  4004ed:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  4004f2:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  4004f7:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  4004fc:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  400501:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400506:	48 83 c4 38          	add    $0x38,%rsp
  40050a:	c3                   	retq   
  40050b:	90                   	nop    
  40050c:	90                   	nop    
  40050d:	90                   	nop    
  40050e:	90                   	nop    
  40050f:	90                   	nop    

0000000000400510 <__do_global_ctors_aux>:
  400510:	55                   	push   %rbp
  400511:	48 89 e5             	mov    %rsp,%rbp
  400514:	53                   	push   %rbx
  400515:	bb 60 06 60 00       	mov    $0x600660,%ebx
  40051a:	48 83 ec 08          	sub    $0x8,%rsp
  40051e:	48 8b 05 3b 01 20 00 	mov    2097467(%rip),%rax        # 600660 <__CTOR_LIST__>
  400525:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  400529:	74 14                	je     40053f <__do_global_ctors_aux+0x2f>
  40052b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  400530:	48 83 eb 08          	sub    $0x8,%rbx
  400534:	ff d0                	callq  *%rax
  400536:	48 8b 03             	mov    (%rbx),%rax
  400539:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  40053d:	75 f1                	jne    400530 <__do_global_ctors_aux+0x20>
  40053f:	48 83 c4 08          	add    $0x8,%rsp
  400543:	5b                   	pop    %rbx
  400544:	c9                   	leaveq 
  400545:	c3                   	retq   
  400546:	90                   	nop    
  400547:	90                   	nop    
Disassembly of section .fini:

0000000000400548 <_fini>:
  400548:	48 83 ec 08          	sub    $0x8,%rsp
  40054c:	e8 6f fe ff ff       	callq  4003c0 <__do_global_dtors_aux>
  400551:	48 83 c4 08          	add    $0x8,%rsp
  400555:	c3                   	retq   
