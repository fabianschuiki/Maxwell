
../debug.mw.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000400390 <_init>:
  400390:	48 83 ec 08          	sub    $0x8,%rsp
  400394:	e8 67 00 00 00       	callq  400400 <call_gmon_start>
  400399:	e8 f2 00 00 00       	callq  400490 <frame_dummy>
  40039e:	e8 ed 01 00 00       	callq  400590 <__do_global_ctors_aux>
  4003a3:	48 83 c4 08          	add    $0x8,%rsp
  4003a7:	c3                   	retq   

Disassembly of section .plt:

00000000004003b0 <__libc_start_main@plt-0x10>:
  4003b0:	ff 35 3a 0c 20 00    	pushq  0x200c3a(%rip)        # 600ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  4003b6:	ff 25 3c 0c 20 00    	jmpq   *0x200c3c(%rip)        # 600ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  4003bc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004003c0 <__libc_start_main@plt>:
  4003c0:	ff 25 3a 0c 20 00    	jmpq   *0x200c3a(%rip)        # 601000 <_GLOBAL_OFFSET_TABLE_+0x18>
  4003c6:	68 00 00 00 00       	pushq  $0x0
  4003cb:	e9 e0 ff ff ff       	jmpq   4003b0 <_init+0x20>

Disassembly of section .text:

00000000004003d0 <main>:
  4003d0:	31 c0                	xor    %eax,%eax
  4003d2:	c3                   	retq   
  4003d3:	90                   	nop

00000000004003d4 <_start>:
  4003d4:	31 ed                	xor    %ebp,%ebp
  4003d6:	49 89 d1             	mov    %rdx,%r9
  4003d9:	5e                   	pop    %rsi
  4003da:	48 89 e2             	mov    %rsp,%rdx
  4003dd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4003e1:	50                   	push   %rax
  4003e2:	54                   	push   %rsp
  4003e3:	49 c7 c0 80 05 40 00 	mov    $0x400580,%r8
  4003ea:	48 c7 c1 f0 04 40 00 	mov    $0x4004f0,%rcx
  4003f1:	48 c7 c7 d0 03 40 00 	mov    $0x4003d0,%rdi
  4003f8:	e8 c3 ff ff ff       	callq  4003c0 <__libc_start_main@plt>
  4003fd:	f4                   	hlt    
  4003fe:	90                   	nop
  4003ff:	90                   	nop

0000000000400400 <call_gmon_start>:
  400400:	48 83 ec 08          	sub    $0x8,%rsp
  400404:	48 8b 05 d5 0b 20 00 	mov    0x200bd5(%rip),%rax        # 600fe0 <_DYNAMIC+0x190>
  40040b:	48 85 c0             	test   %rax,%rax
  40040e:	74 02                	je     400412 <call_gmon_start+0x12>
  400410:	ff d0                	callq  *%rax
  400412:	48 83 c4 08          	add    $0x8,%rsp
  400416:	c3                   	retq   
  400417:	90                   	nop
  400418:	90                   	nop
  400419:	90                   	nop
  40041a:	90                   	nop
  40041b:	90                   	nop
  40041c:	90                   	nop
  40041d:	90                   	nop
  40041e:	90                   	nop
  40041f:	90                   	nop

0000000000400420 <__do_global_dtors_aux>:
  400420:	55                   	push   %rbp
  400421:	48 89 e5             	mov    %rsp,%rbp
  400424:	53                   	push   %rbx
  400425:	48 83 ec 08          	sub    $0x8,%rsp
  400429:	80 3d 20 0c 20 00 00 	cmpb   $0x0,0x200c20(%rip)        # 601050 <__bss_start>
  400430:	75 4b                	jne    40047d <__do_global_dtors_aux+0x5d>
  400432:	bb 40 0e 60 00       	mov    $0x600e40,%ebx
  400437:	48 8b 05 1a 0c 20 00 	mov    0x200c1a(%rip),%rax        # 601058 <dtor_idx.6460>
  40043e:	48 81 eb 38 0e 60 00 	sub    $0x600e38,%rbx
  400445:	48 c1 fb 03          	sar    $0x3,%rbx
  400449:	48 83 eb 01          	sub    $0x1,%rbx
  40044d:	48 39 d8             	cmp    %rbx,%rax
  400450:	73 24                	jae    400476 <__do_global_dtors_aux+0x56>
  400452:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  400458:	48 83 c0 01          	add    $0x1,%rax
  40045c:	48 89 05 f5 0b 20 00 	mov    %rax,0x200bf5(%rip)        # 601058 <dtor_idx.6460>
  400463:	ff 14 c5 38 0e 60 00 	callq  *0x600e38(,%rax,8)
  40046a:	48 8b 05 e7 0b 20 00 	mov    0x200be7(%rip),%rax        # 601058 <dtor_idx.6460>
  400471:	48 39 d8             	cmp    %rbx,%rax
  400474:	72 e2                	jb     400458 <__do_global_dtors_aux+0x38>
  400476:	c6 05 d3 0b 20 00 01 	movb   $0x1,0x200bd3(%rip)        # 601050 <__bss_start>
  40047d:	48 83 c4 08          	add    $0x8,%rsp
  400481:	5b                   	pop    %rbx
  400482:	5d                   	pop    %rbp
  400483:	c3                   	retq   
  400484:	66 66 66 2e 0f 1f 84 	data32 data32 nopw %cs:0x0(%rax,%rax,1)
  40048b:	00 00 00 00 00 

0000000000400490 <frame_dummy>:
  400490:	48 83 3d b0 09 20 00 	cmpq   $0x0,0x2009b0(%rip)        # 600e48 <__JCR_END__>
  400497:	00 
  400498:	55                   	push   %rbp
  400499:	48 89 e5             	mov    %rsp,%rbp
  40049c:	74 12                	je     4004b0 <frame_dummy+0x20>
  40049e:	b8 00 00 00 00       	mov    $0x0,%eax
  4004a3:	48 85 c0             	test   %rax,%rax
  4004a6:	74 08                	je     4004b0 <frame_dummy+0x20>
  4004a8:	5d                   	pop    %rbp
  4004a9:	bf 48 0e 60 00       	mov    $0x600e48,%edi
  4004ae:	ff e0                	jmpq   *%rax
  4004b0:	5d                   	pop    %rbp
  4004b1:	c3                   	retq   
  4004b2:	90                   	nop
  4004b3:	90                   	nop
  4004b4:	90                   	nop
  4004b5:	90                   	nop
  4004b6:	90                   	nop
  4004b7:	90                   	nop
  4004b8:	90                   	nop
  4004b9:	90                   	nop
  4004ba:	90                   	nop
  4004bb:	90                   	nop
  4004bc:	90                   	nop
  4004bd:	90                   	nop
  4004be:	90                   	nop
  4004bf:	90                   	nop

00000000004004c0 <func_test>:
  4004c0:	f3 c3                	repz retq 
  4004c2:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  4004c9:	1f 84 00 00 00 00 00 

00000000004004d0 <func_cast>:
  4004d0:	f3 c3                	repz retq 
  4004d2:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  4004d9:	1f 84 00 00 00 00 00 

00000000004004e0 <func_main>:
  4004e0:	f3 c3                	repz retq 
  4004e2:	90                   	nop
  4004e3:	90                   	nop
  4004e4:	90                   	nop
  4004e5:	90                   	nop
  4004e6:	90                   	nop
  4004e7:	90                   	nop
  4004e8:	90                   	nop
  4004e9:	90                   	nop
  4004ea:	90                   	nop
  4004eb:	90                   	nop
  4004ec:	90                   	nop
  4004ed:	90                   	nop
  4004ee:	90                   	nop
  4004ef:	90                   	nop

00000000004004f0 <__libc_csu_init>:
  4004f0:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  4004f5:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  4004fa:	48 8d 2d 23 09 20 00 	lea    0x200923(%rip),%rbp        # 600e24 <__init_array_end>
  400501:	4c 8d 25 1c 09 20 00 	lea    0x20091c(%rip),%r12        # 600e24 <__init_array_end>
  400508:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  40050d:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  400512:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  400517:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  40051c:	48 83 ec 38          	sub    $0x38,%rsp
  400520:	4c 29 e5             	sub    %r12,%rbp
  400523:	41 89 fd             	mov    %edi,%r13d
  400526:	49 89 f6             	mov    %rsi,%r14
  400529:	48 c1 fd 03          	sar    $0x3,%rbp
  40052d:	49 89 d7             	mov    %rdx,%r15
  400530:	e8 5b fe ff ff       	callq  400390 <_init>
  400535:	48 85 ed             	test   %rbp,%rbp
  400538:	74 1c                	je     400556 <__libc_csu_init+0x66>
  40053a:	31 db                	xor    %ebx,%ebx
  40053c:	0f 1f 40 00          	nopl   0x0(%rax)
  400540:	4c 89 fa             	mov    %r15,%rdx
  400543:	4c 89 f6             	mov    %r14,%rsi
  400546:	44 89 ef             	mov    %r13d,%edi
  400549:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40054d:	48 83 c3 01          	add    $0x1,%rbx
  400551:	48 39 eb             	cmp    %rbp,%rbx
  400554:	75 ea                	jne    400540 <__libc_csu_init+0x50>
  400556:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40055b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  400560:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  400565:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40056a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40056f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400574:	48 83 c4 38          	add    $0x38,%rsp
  400578:	c3                   	retq   
  400579:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400580 <__libc_csu_fini>:
  400580:	f3 c3                	repz retq 
  400582:	90                   	nop
  400583:	90                   	nop
  400584:	90                   	nop
  400585:	90                   	nop
  400586:	90                   	nop
  400587:	90                   	nop
  400588:	90                   	nop
  400589:	90                   	nop
  40058a:	90                   	nop
  40058b:	90                   	nop
  40058c:	90                   	nop
  40058d:	90                   	nop
  40058e:	90                   	nop
  40058f:	90                   	nop

0000000000400590 <__do_global_ctors_aux>:
  400590:	55                   	push   %rbp
  400591:	48 89 e5             	mov    %rsp,%rbp
  400594:	53                   	push   %rbx
  400595:	48 83 ec 08          	sub    $0x8,%rsp
  400599:	48 8b 05 88 08 20 00 	mov    0x200888(%rip),%rax        # 600e28 <__CTOR_LIST__>
  4005a0:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  4005a4:	74 19                	je     4005bf <__do_global_ctors_aux+0x2f>
  4005a6:	bb 28 0e 60 00       	mov    $0x600e28,%ebx
  4005ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4005b0:	48 83 eb 08          	sub    $0x8,%rbx
  4005b4:	ff d0                	callq  *%rax
  4005b6:	48 8b 03             	mov    (%rbx),%rax
  4005b9:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  4005bd:	75 f1                	jne    4005b0 <__do_global_ctors_aux+0x20>
  4005bf:	48 83 c4 08          	add    $0x8,%rsp
  4005c3:	5b                   	pop    %rbx
  4005c4:	5d                   	pop    %rbp
  4005c5:	c3                   	retq   
  4005c6:	90                   	nop
  4005c7:	90                   	nop

Disassembly of section .fini:

00000000004005c8 <_fini>:
  4005c8:	48 83 ec 08          	sub    $0x8,%rsp
  4005cc:	e8 4f fe ff ff       	callq  400420 <__do_global_dtors_aux>
  4005d1:	48 83 c4 08          	add    $0x8,%rsp
  4005d5:	c3                   	retq   
