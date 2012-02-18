
../debug.mw.out:     file format elf64-x86-64


Disassembly of section .init:

00000000004003f0 <_init>:
  4003f0:	48 83 ec 08          	sub    $0x8,%rsp
  4003f4:	e8 7b 00 00 00       	callq  400474 <call_gmon_start>
  4003f9:	e8 02 01 00 00       	callq  400500 <frame_dummy>
  4003fe:	e8 7d 02 00 00       	callq  400680 <__do_global_ctors_aux>
  400403:	48 83 c4 08          	add    $0x8,%rsp
  400407:	c3                   	retq   

Disassembly of section .plt:

0000000000400410 <__libc_start_main@plt-0x10>:
  400410:	ff 35 da 0b 20 00    	pushq  0x200bda(%rip)        # 600ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  400416:	ff 25 dc 0b 20 00    	jmpq   *0x200bdc(%rip)        # 600ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40041c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400420 <__libc_start_main@plt>:
  400420:	ff 25 da 0b 20 00    	jmpq   *0x200bda(%rip)        # 601000 <_GLOBAL_OFFSET_TABLE_+0x18>
  400426:	68 00 00 00 00       	pushq  $0x0
  40042b:	e9 e0 ff ff ff       	jmpq   400410 <_init+0x20>

0000000000400430 <__printf_chk@plt>:
  400430:	ff 25 d2 0b 20 00    	jmpq   *0x200bd2(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x20>
  400436:	68 01 00 00 00       	pushq  $0x1
  40043b:	e9 d0 ff ff ff       	jmpq   400410 <_init+0x20>

Disassembly of section .text:

0000000000400440 <main>:
  400440:	31 c0                	xor    %eax,%eax
  400442:	e9 79 01 00 00       	jmpq   4005c0 <func_main>
  400447:	90                   	nop

0000000000400448 <_start>:
  400448:	31 ed                	xor    %ebp,%ebp
  40044a:	49 89 d1             	mov    %rdx,%r9
  40044d:	5e                   	pop    %rsi
  40044e:	48 89 e2             	mov    %rsp,%rdx
  400451:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400455:	50                   	push   %rax
  400456:	54                   	push   %rsp
  400457:	49 c7 c0 70 06 40 00 	mov    $0x400670,%r8
  40045e:	48 c7 c1 e0 05 40 00 	mov    $0x4005e0,%rcx
  400465:	48 c7 c7 40 04 40 00 	mov    $0x400440,%rdi
  40046c:	e8 af ff ff ff       	callq  400420 <__libc_start_main@plt>
  400471:	f4                   	hlt    
  400472:	90                   	nop
  400473:	90                   	nop

0000000000400474 <call_gmon_start>:
  400474:	48 83 ec 08          	sub    $0x8,%rsp
  400478:	48 8b 05 61 0b 20 00 	mov    0x200b61(%rip),%rax        # 600fe0 <_DYNAMIC+0x190>
  40047f:	48 85 c0             	test   %rax,%rax
  400482:	74 02                	je     400486 <call_gmon_start+0x12>
  400484:	ff d0                	callq  *%rax
  400486:	48 83 c4 08          	add    $0x8,%rsp
  40048a:	c3                   	retq   
  40048b:	90                   	nop
  40048c:	90                   	nop
  40048d:	90                   	nop
  40048e:	90                   	nop
  40048f:	90                   	nop

0000000000400490 <__do_global_dtors_aux>:
  400490:	55                   	push   %rbp
  400491:	48 89 e5             	mov    %rsp,%rbp
  400494:	53                   	push   %rbx
  400495:	48 83 ec 08          	sub    $0x8,%rsp
  400499:	80 3d 80 0b 20 00 00 	cmpb   $0x0,0x200b80(%rip)        # 601020 <__bss_start>
  4004a0:	75 4b                	jne    4004ed <__do_global_dtors_aux+0x5d>
  4004a2:	bb 40 0e 60 00       	mov    $0x600e40,%ebx
  4004a7:	48 8b 05 7a 0b 20 00 	mov    0x200b7a(%rip),%rax        # 601028 <dtor_idx.6460>
  4004ae:	48 81 eb 38 0e 60 00 	sub    $0x600e38,%rbx
  4004b5:	48 c1 fb 03          	sar    $0x3,%rbx
  4004b9:	48 83 eb 01          	sub    $0x1,%rbx
  4004bd:	48 39 d8             	cmp    %rbx,%rax
  4004c0:	73 24                	jae    4004e6 <__do_global_dtors_aux+0x56>
  4004c2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  4004c8:	48 83 c0 01          	add    $0x1,%rax
  4004cc:	48 89 05 55 0b 20 00 	mov    %rax,0x200b55(%rip)        # 601028 <dtor_idx.6460>
  4004d3:	ff 14 c5 38 0e 60 00 	callq  *0x600e38(,%rax,8)
  4004da:	48 8b 05 47 0b 20 00 	mov    0x200b47(%rip),%rax        # 601028 <dtor_idx.6460>
  4004e1:	48 39 d8             	cmp    %rbx,%rax
  4004e4:	72 e2                	jb     4004c8 <__do_global_dtors_aux+0x38>
  4004e6:	c6 05 33 0b 20 00 01 	movb   $0x1,0x200b33(%rip)        # 601020 <__bss_start>
  4004ed:	48 83 c4 08          	add    $0x8,%rsp
  4004f1:	5b                   	pop    %rbx
  4004f2:	5d                   	pop    %rbp
  4004f3:	c3                   	retq   
  4004f4:	66 66 66 2e 0f 1f 84 	data32 data32 nopw %cs:0x0(%rax,%rax,1)
  4004fb:	00 00 00 00 00 

0000000000400500 <frame_dummy>:
  400500:	48 83 3d 40 09 20 00 	cmpq   $0x0,0x200940(%rip)        # 600e48 <__JCR_END__>
  400507:	00 
  400508:	55                   	push   %rbp
  400509:	48 89 e5             	mov    %rsp,%rbp
  40050c:	74 12                	je     400520 <frame_dummy+0x20>
  40050e:	b8 00 00 00 00       	mov    $0x0,%eax
  400513:	48 85 c0             	test   %rax,%rax
  400516:	74 08                	je     400520 <frame_dummy+0x20>
  400518:	5d                   	pop    %rbp
  400519:	bf 48 0e 60 00       	mov    $0x600e48,%edi
  40051e:	ff e0                	jmpq   *%rax
  400520:	5d                   	pop    %rbp
  400521:	c3                   	retq   
  400522:	90                   	nop
  400523:	90                   	nop
  400524:	90                   	nop
  400525:	90                   	nop
  400526:	90                   	nop
  400527:	90                   	nop
  400528:	90                   	nop
  400529:	90                   	nop
  40052a:	90                   	nop
  40052b:	90                   	nop
  40052c:	90                   	nop
  40052d:	90                   	nop
  40052e:	90                   	nop
  40052f:	90                   	nop

0000000000400530 <operator_3D>:
  400530:	8b 06                	mov    (%rsi),%eax
  400532:	89 07                	mov    %eax,(%rdi)
  400534:	c3                   	retq   
  400535:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40053c:	00 00 00 00 

0000000000400540 <operator_2B>:
  400540:	8b 07                	mov    (%rdi),%eax
  400542:	03 06                	add    (%rsi),%eax
  400544:	c3                   	retq   
  400545:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40054c:	00 00 00 00 

0000000000400550 <operator_2A>:
  400550:	8b 07                	mov    (%rdi),%eax
  400552:	0f af 06             	imul   (%rsi),%eax
  400555:	c3                   	retq   
  400556:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40055d:	00 00 00 

0000000000400560 <operator_2F>:
  400560:	8b 07                	mov    (%rdi),%eax
  400562:	89 c2                	mov    %eax,%edx
  400564:	c1 fa 1f             	sar    $0x1f,%edx
  400567:	f7 3e                	idivl  (%rsi)
  400569:	c3                   	retq   
  40056a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400570 <operator_3D3D>:
  400570:	8b 06                	mov    (%rsi),%eax
  400572:	39 07                	cmp    %eax,(%rdi)
  400574:	0f 94 c0             	sete   %al
  400577:	0f b6 c0             	movzbl %al,%eax
  40057a:	c3                   	retq   
  40057b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400580 <operator_3C>:
  400580:	8b 06                	mov    (%rsi),%eax
  400582:	39 07                	cmp    %eax,(%rdi)
  400584:	0f 9c c0             	setl   %al
  400587:	0f b6 c0             	movzbl %al,%eax
  40058a:	c3                   	retq   
  40058b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000400590 <unary_2D>:
  400590:	8b 07                	mov    (%rdi),%eax
  400592:	f7 d8                	neg    %eax
  400594:	c3                   	retq   
  400595:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40059c:	00 00 00 00 

00000000004005a0 <show>:
  4005a0:	48 83 ec 08          	sub    $0x8,%rsp
  4005a4:	8b 17                	mov    (%rdi),%edx
  4005a6:	be cc 06 40 00       	mov    $0x4006cc,%esi
  4005ab:	bf 01 00 00 00       	mov    $0x1,%edi
  4005b0:	31 c0                	xor    %eax,%eax
  4005b2:	e8 79 fe ff ff       	callq  400430 <__printf_chk@plt>
  4005b7:	31 c0                	xor    %eax,%eax
  4005b9:	48 83 c4 08          	add    $0x8,%rsp
  4005bd:	c3                   	retq   
  4005be:	66 90                	xchg   %ax,%ax

00000000004005c0 <func_main>:
  4005c0:	ba 02 00 00 00       	mov    $0x2,%edx
  4005c5:	be cc 06 40 00       	mov    $0x4006cc,%esi
  4005ca:	bf 01 00 00 00       	mov    $0x1,%edi
  4005cf:	31 c0                	xor    %eax,%eax
  4005d1:	e9 5a fe ff ff       	jmpq   400430 <__printf_chk@plt>
  4005d6:	90                   	nop
  4005d7:	90                   	nop
  4005d8:	90                   	nop
  4005d9:	90                   	nop
  4005da:	90                   	nop
  4005db:	90                   	nop
  4005dc:	90                   	nop
  4005dd:	90                   	nop
  4005de:	90                   	nop
  4005df:	90                   	nop

00000000004005e0 <__libc_csu_init>:
  4005e0:	48 89 6c 24 d8       	mov    %rbp,-0x28(%rsp)
  4005e5:	4c 89 64 24 e0       	mov    %r12,-0x20(%rsp)
  4005ea:	48 8d 2d 33 08 20 00 	lea    0x200833(%rip),%rbp        # 600e24 <__init_array_end>
  4005f1:	4c 8d 25 2c 08 20 00 	lea    0x20082c(%rip),%r12        # 600e24 <__init_array_end>
  4005f8:	4c 89 6c 24 e8       	mov    %r13,-0x18(%rsp)
  4005fd:	4c 89 74 24 f0       	mov    %r14,-0x10(%rsp)
  400602:	4c 89 7c 24 f8       	mov    %r15,-0x8(%rsp)
  400607:	48 89 5c 24 d0       	mov    %rbx,-0x30(%rsp)
  40060c:	48 83 ec 38          	sub    $0x38,%rsp
  400610:	4c 29 e5             	sub    %r12,%rbp
  400613:	41 89 fd             	mov    %edi,%r13d
  400616:	49 89 f6             	mov    %rsi,%r14
  400619:	48 c1 fd 03          	sar    $0x3,%rbp
  40061d:	49 89 d7             	mov    %rdx,%r15
  400620:	e8 cb fd ff ff       	callq  4003f0 <_init>
  400625:	48 85 ed             	test   %rbp,%rbp
  400628:	74 1c                	je     400646 <__libc_csu_init+0x66>
  40062a:	31 db                	xor    %ebx,%ebx
  40062c:	0f 1f 40 00          	nopl   0x0(%rax)
  400630:	4c 89 fa             	mov    %r15,%rdx
  400633:	4c 89 f6             	mov    %r14,%rsi
  400636:	44 89 ef             	mov    %r13d,%edi
  400639:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40063d:	48 83 c3 01          	add    $0x1,%rbx
  400641:	48 39 eb             	cmp    %rbp,%rbx
  400644:	75 ea                	jne    400630 <__libc_csu_init+0x50>
  400646:	48 8b 5c 24 08       	mov    0x8(%rsp),%rbx
  40064b:	48 8b 6c 24 10       	mov    0x10(%rsp),%rbp
  400650:	4c 8b 64 24 18       	mov    0x18(%rsp),%r12
  400655:	4c 8b 6c 24 20       	mov    0x20(%rsp),%r13
  40065a:	4c 8b 74 24 28       	mov    0x28(%rsp),%r14
  40065f:	4c 8b 7c 24 30       	mov    0x30(%rsp),%r15
  400664:	48 83 c4 38          	add    $0x38,%rsp
  400668:	c3                   	retq   
  400669:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000400670 <__libc_csu_fini>:
  400670:	f3 c3                	repz retq 
  400672:	90                   	nop
  400673:	90                   	nop
  400674:	90                   	nop
  400675:	90                   	nop
  400676:	90                   	nop
  400677:	90                   	nop
  400678:	90                   	nop
  400679:	90                   	nop
  40067a:	90                   	nop
  40067b:	90                   	nop
  40067c:	90                   	nop
  40067d:	90                   	nop
  40067e:	90                   	nop
  40067f:	90                   	nop

0000000000400680 <__do_global_ctors_aux>:
  400680:	55                   	push   %rbp
  400681:	48 89 e5             	mov    %rsp,%rbp
  400684:	53                   	push   %rbx
  400685:	48 83 ec 08          	sub    $0x8,%rsp
  400689:	48 8b 05 98 07 20 00 	mov    0x200798(%rip),%rax        # 600e28 <__CTOR_LIST__>
  400690:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  400694:	74 19                	je     4006af <__do_global_ctors_aux+0x2f>
  400696:	bb 28 0e 60 00       	mov    $0x600e28,%ebx
  40069b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4006a0:	48 83 eb 08          	sub    $0x8,%rbx
  4006a4:	ff d0                	callq  *%rax
  4006a6:	48 8b 03             	mov    (%rbx),%rax
  4006a9:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
  4006ad:	75 f1                	jne    4006a0 <__do_global_ctors_aux+0x20>
  4006af:	48 83 c4 08          	add    $0x8,%rsp
  4006b3:	5b                   	pop    %rbx
  4006b4:	5d                   	pop    %rbp
  4006b5:	c3                   	retq   
  4006b6:	90                   	nop
  4006b7:	90                   	nop

Disassembly of section .fini:

00000000004006b8 <_fini>:
  4006b8:	48 83 ec 08          	sub    $0x8,%rsp
  4006bc:	e8 cf fd ff ff       	callq  400490 <__do_global_dtors_aux>
  4006c1:	48 83 c4 08          	add    $0x8,%rsp
  4006c5:	c3                   	retq   
