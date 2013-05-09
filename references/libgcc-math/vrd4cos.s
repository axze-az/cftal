# Copyright (c) 2006 Free Software Foundation, Inc.
# 
# This file is part of GCC.
# Contributed by Advanced Micro Devices, Inc., 2006.
#
# GCC is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2, or (at your option) any later
# version.
#
# In addition to the permissions in the GNU General Public License, the
# Free Software Foundation gives you unlimited permission to link the
# compiled version of this file into combinations with other programs,
# and to distribute those combinations without any restriction coming
# from the use of this file.  (The General Public License restrictions 
# do apply in other respects; for example, they cover modification of
# the file, and distribution when not linked into a combine
# executable.)
#
# GCC is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with GCC; see the file COPYING.  If not, write to the Free
# Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.

# vrd4cos.s
#
# A vector implementation of the cos libm function.
#
# Prototype:
#
#    __m128d,__m128d __vrd4_cos(__m128d x1, __m128d x2);
#
# Computes Cosine of x for an array of input values.
# Places the results into the supplied y array.
# Does not perform error checking.
# Denormal inputs may produce unexpected results.
# This routine computes 4 double precision Cosine values at a time.
# The four values are passed as packed doubles in xmm0 and xmm1.
# The four results are returned as packed doubles in xmm0 and xmm1.
# Note that this represents a non-standard ABI usage, as no ABI
# ( and indeed C) currently allows returning 2 values for a function.
# It is expected that some compilers may be able to take advantage of this
# interface when implementing vectorized loops.  Using the array implementation
# of the routine requires putting the inputs into memory, and retrieving
# the results from memory.  This routine eliminates the need for this
# overhead if the data does not already reside in memory.
# This routine is derived directly from the array version.
# Author: Harsha Jagasia
# Email:  harsha.jagasia@amd.com




.section .rodata.cst16, "M", @progbits, 16
.align 16
.L__real_7fffffffffffffff: 	.quad 0x07fffffffffffffff	#Sign bit zero
				.quad 0x07fffffffffffffff
.L__real_3ff0000000000000: 	.quad 0x03ff0000000000000	# 1.0
				.quad 0x03ff0000000000000
.L__real_v2p__27:		.quad 0x03e40000000000000	# 2p-27
				.quad 0x03e40000000000000
.L__real_3fe0000000000000: 	.quad 0x03fe0000000000000	# 0.5
				.quad 0x03fe0000000000000
.L__real_3fc5555555555555: 	.quad 0x03fc5555555555555	# 0.166666666666
				.quad 0x03fc5555555555555
.L__real_3fe45f306dc9c883: 	.quad 0x03fe45f306dc9c883	# twobypi
				.quad 0x03fe45f306dc9c883
.L__real_3ff921fb54400000: 	.quad 0x03ff921fb54400000	# piby2_1
				.quad 0x03ff921fb54400000
.L__real_3dd0b4611a626331: 	.quad 0x03dd0b4611a626331	# piby2_1tail
				.quad 0x03dd0b4611a626331
.L__real_3dd0b4611a600000: 	.quad 0x03dd0b4611a600000	# piby2_2
				.quad 0x03dd0b4611a600000
.L__real_3ba3198a2e037073: 	.quad 0x03ba3198a2e037073	# piby2_2tail
				.quad 0x03ba3198a2e037073
.L__real_fffffffff8000000: 	.quad 0x0fffffffff8000000	# mask for stripping head and tail
				.quad 0x0fffffffff8000000
.L__real_8000000000000000:	.quad 0x08000000000000000	# -0  or signbit
				.quad 0x08000000000000000
.L__reald_one_one:		.quad 0x00000000100000001	#
				.quad 0
.L__reald_two_two:		.quad 0x00000000200000002	#
				.quad 0
.L__reald_one_zero:		.quad 0x00000000100000000	# sin_cos_filter
				.quad 0
.L__reald_zero_one:		.quad 0x00000000000000001	#
				.quad 0
.L__reald_two_zero:		.quad 0x00000000200000000	#
				.quad 0
.L__realq_one_one:		.quad 0x00000000000000001	#
				.quad 0x00000000000000001	#
.L__realq_two_two:		.quad 0x00000000000000002	#
				.quad 0x00000000000000002	#
.L__real_1_x_mask:		.quad 0x0ffffffffffffffff	#
				.quad 0x03ff0000000000000	#
.L__real_zero:			.quad 0x00000000000000000	#
				.quad 0x00000000000000000	#
.L__real_one:			.quad 0x00000000000000001	#
				.quad 0x00000000000000001	#
	
.section .rodata
.align 16
.Lcosarray:
	.quad	0x03fa5555555555555		# 0.0416667		   	c1
	.quad	0x03fa5555555555555
	.quad	0x0bf56c16c16c16967		# -0.00138889	   		c2
	.quad	0x0bf56c16c16c16967
	.quad	0x03efa01a019f4ec90		# 2.48016e-005			c3
	.quad	0x03efa01a019f4ec90
	.quad	0x0be927e4fa17f65f6		# -2.75573e-007			c4
	.quad	0x0be927e4fa17f65f6
	.quad	0x03e21eeb69037ab78		# 2.08761e-009			c5
	.quad	0x03e21eeb69037ab78
	.quad	0x0bda907db46cc5e42		# -1.13826e-011	   		c6
	.quad	0x0bda907db46cc5e42
.Lsinarray:
	.quad	0x0bfc5555555555555		# -0.166667	   		s1
	.quad	0x0bfc5555555555555
	.quad	0x03f81111111110bb3		# 0.00833333	   		s2
	.quad	0x03f81111111110bb3
	.quad	0x0bf2a01a019e83e5c		# -0.000198413			s3
	.quad	0x0bf2a01a019e83e5c
	.quad	0x03ec71de3796cde01		# 2.75573e-006			s4
	.quad	0x03ec71de3796cde01
	.quad	0x0be5ae600b42fdfa7		# -2.50511e-008			s5
	.quad	0x0be5ae600b42fdfa7
	.quad	0x03de5e0b2f9a43bb8		# 1.59181e-010	   		s6
	.quad	0x03de5e0b2f9a43bb8
.Lsincosarray:
	.quad	0x0bfc5555555555555		# -0.166667	   		s1
	.quad	0x03fa5555555555555		# 0.0416667		   	c1
	.quad	0x03f81111111110bb3		# 0.00833333	   		s2
	.quad	0x0bf56c16c16c16967
	.quad	0x0bf2a01a019e83e5c		# -0.000198413			s3
	.quad	0x03efa01a019f4ec90
	.quad	0x03ec71de3796cde01		# 2.75573e-006			s4
	.quad	0x0be927e4fa17f65f6
	.quad	0x0be5ae600b42fdfa7		# -2.50511e-008			s5
	.quad	0x03e21eeb69037ab78
	.quad	0x03de5e0b2f9a43bb8		# 1.59181e-010	   		s6
	.quad	0x0bda907db46cc5e42
.Lcossinarray:
	.quad	0x03fa5555555555555		# 0.0416667		   	c1
	.quad	0x0bfc5555555555555		# -0.166667	   		s1
	.quad	0x0bf56c16c16c16967
	.quad	0x03f81111111110bb3		# 0.00833333	   		s2
	.quad	0x03efa01a019f4ec90
	.quad	0x0bf2a01a019e83e5c		# -0.000198413			s3
	.quad	0x0be927e4fa17f65f6
	.quad	0x03ec71de3796cde01		# 2.75573e-006			s4
	.quad	0x03e21eeb69037ab78
	.quad	0x0be5ae600b42fdfa7		# -2.50511e-008			s5
	.quad	0x0bda907db46cc5e42
	.quad	0x03de5e0b2f9a43bb8		# 1.59181e-010	   		s6

.align 16
.Levencos_oddsin_tbl:
		.quad	.Lcoscos_coscos_piby4		# 0		*
		.quad	.Lcoscos_cossin_piby4		# 1		+
		.quad	.Lcoscos_sincos_piby4		# 2
		.quad	.Lcoscos_sinsin_piby4		# 3		+

		.quad	.Lcossin_coscos_piby4		# 4
		.quad	.Lcossin_cossin_piby4		# 5		*
		.quad	.Lcossin_sincos_piby4		# 6
		.quad	.Lcossin_sinsin_piby4		# 7

		.quad	.Lsincos_coscos_piby4		# 8
		.quad	.Lsincos_cossin_piby4		# 9
		.quad	.Lsincos_sincos_piby4		# 10		*
		.quad	.Lsincos_sinsin_piby4		# 11

		.quad	.Lsinsin_coscos_piby4		# 12
		.quad	.Lsinsin_cossin_piby4		# 13		+
		.quad	.Lsinsin_sincos_piby4		# 14
		.quad	.Lsinsin_sinsin_piby4		# 15		*

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    .text
    .align 16
    .p2align 4,,15

# define local variable storage offsets
.equ	p_temp,		0x00		# temporary for get/put bits operation
.equ	p_temp1,	0x10		# temporary for get/put bits operation

.equ	p_xmm6,		0x20		# temporary for get/put bits operation
.equ	p_xmm7,		0x30		# temporary for get/put bits operation
.equ	p_xmm8,		0x40		# temporary for get/put bits operation
.equ	p_xmm9,		0x50		# temporary for get/put bits operation
.equ	p_xmm10,	0x60		# temporary for get/put bits operation
.equ	p_xmm11,	0x70		# temporary for get/put bits operation
.equ	p_xmm12,	0x80		# temporary for get/put bits operation
.equ	p_xmm13,	0x90		# temporary for get/put bits operation
.equ	p_xmm14,	0x0A0		# temporary for get/put bits operation
.equ	p_xmm15,	0x0B0		# temporary for get/put bits operation
	
.equ	r,		0x0C0		# pointer to r for remainder_piby2
.equ	rr,		0x0D0		# pointer to r for remainder_piby2
.equ	region,		0x0E0		# pointer to r for remainder_piby2
	
.equ	r1,		0x0F0		# pointer to r for remainder_piby2
.equ	rr1,		0x0100		# pointer to r for remainder_piby2
.equ	region1,	0x0110		# pointer to r for remainder_piby2

.equ	p_temp2,	0x0120		# temporary for get/put bits operation
.equ	p_temp3,	0x0130		# temporary for get/put bits operation
	
.equ	p_temp4,	0x0140		# temporary for get/put bits operation
.equ	p_temp5,	0x0150		# temporary for get/put bits operation
	
.equ	p_original,	0x0160		# original x
.equ	p_mask,		0x0170		# original x
.equ	p_sign,		0x0180		# original x

.equ	p_original1,	0x0190		# original x
.equ	p_mask1,	0x01A0		# original x
.equ	p_sign1,	0x01B0		# original x

.globl __vrd4_cos
    .type   __vrd4_cos,@function
__vrd4_cos:
	sub		$0x1C8,%rsp

#DEBUG
#	add		$0x1C8,%rsp
#	ret
#	movapd	%xmm0,%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#STARTMAIN

movapd	.L__real_7fffffffffffffff(%rip),%xmm2
movdqa	%xmm0, p_original(%rsp) 
movdqa	%xmm1, p_original1(%rsp)

andpd 	%xmm2,%xmm0				#Unsign
andpd 	%xmm2,%xmm1				#Unsign

movd	%xmm0,%rax				#rax is lower arg
movhpd	%xmm0, p_temp+8(%rsp)			#
mov    	p_temp+8(%rsp),%rcx			#rcx = upper arg
movd	%xmm1,%r8				#rax is lower arg
movhpd	%xmm1, p_temp1+8(%rsp)			#
mov    	p_temp1+8(%rsp),%r9			#rcx = upper arg

mov 	$0x3FE921FB54442D18,%rdx		#piby4	+
mov	$0x411E848000000000,%r10		#5e5	+

movapd	.L__real_3fe0000000000000(%rip),%xmm4	#0.5 for later use

movapd	%xmm0,%xmm2				#x0
movapd	%xmm1,%xmm3				#x1
movapd	%xmm0,%xmm6				#x0
movapd	%xmm1,%xmm7				#x1

#DEBUG
#	add		$0x1C8,%rsp
#	ret
#	movapd	%xmm0,%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# xmm2 = x, xmm4 =0.5/t, xmm6 =x
# xmm3 = x, xmm5 =0.5/t, xmm7 =x
.align 16
.Leither_or_both_arg_gt_than_piby4:
	cmp	%r10,%rax
	jae	.Lfirst_or_next3_arg_gt_5e5

	cmp	%r10,%rcx
	jae	.Lsecond_or_next2_arg_gt_5e5

	cmp	%r10,%r8
	jae	.Lthird_or_fourth_arg_gt_5e5

	cmp	%r10,%r9
	jae	.Lfourth_arg_gt_5e5


#      /* Find out what multiple of piby2 */
#        npi2  = (int)(x * twobypi + 0.5);
	movapd	.L__real_3fe45f306dc9c883(%rip),%xmm0
	mulpd	%xmm0,%xmm2						# * twobypi
	mulpd	%xmm0,%xmm3						# * twobypi

	addpd	%xmm4,%xmm2						# +0.5, npi2
	addpd	%xmm4,%xmm3						# +0.5, npi2

	movapd	.L__real_3ff921fb54400000(%rip),%xmm0		# piby2_1
	movapd	.L__real_3ff921fb54400000(%rip),%xmm1		# piby2_1

	cvttpd2dq	%xmm2,%xmm4					# convert packed double to packed integers
	cvttpd2dq	%xmm3,%xmm5					# convert packed double to packed integers

	movapd	.L__real_3dd0b4611a600000(%rip),%xmm8		# piby2_2
	movapd	.L__real_3dd0b4611a600000(%rip),%xmm9		# piby2_2

	cvtdq2pd	%xmm4,%xmm2					# and back to double.
	cvtdq2pd	%xmm5,%xmm3					# and back to double.

#      /* Subtract the multiple from x to get an extra-precision remainder */

	movd	%xmm4,%rax						# Region
	movd	%xmm5,%rcx						# Region

	mov	%rax,%r8
	mov	%rcx,%r9

#      rhead  = x - npi2 * piby2_1;
       mulpd	%xmm2,%xmm0						# npi2 * piby2_1;
       mulpd	%xmm3,%xmm1						# npi2 * piby2_1;

#      rtail  = npi2 * piby2_2;
       mulpd	%xmm2,%xmm8						# rtail
       mulpd	%xmm3,%xmm9						# rtail

#      rhead  = x - npi2 * piby2_1;
       subpd	%xmm0,%xmm6						# rhead  = x - npi2 * piby2_1;
       subpd	%xmm1,%xmm7						# rhead  = x - npi2 * piby2_1;

#      t  = rhead;
       movapd	%xmm6,%xmm0						# t
       movapd	%xmm7,%xmm1						# t

#      rhead  = t - rtail;
       subpd	%xmm8,%xmm0						# rhead
       subpd	%xmm9,%xmm1						# rhead

#      rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulpd	.L__real_3ba3198a2e037073(%rip),%xmm2		# npi2 * piby2_2tail
       mulpd	.L__real_3ba3198a2e037073(%rip),%xmm3		# npi2 * piby2_2tail

       subpd	%xmm0,%xmm6						# t-rhead
       subpd	%xmm1,%xmm7						# t-rhead

       subpd	%xmm6,%xmm8						# - ((t - rhead) - rtail)
       subpd	%xmm7,%xmm9						# - ((t - rhead) - rtail)

       addpd	%xmm2,%xmm8						# rtail = npi2 * piby2_2tail - ((t - rhead) - rtail);
       addpd	%xmm3,%xmm9						# rtail = npi2 * piby2_2tail - ((t - rhead) - rtail);

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# xmm4  = npi2 (int), xmm0 =rhead, xmm8 =rtail
# xmm5  = npi2 (int), xmm1 =rhead, xmm9 =rtail

#	paddd		.L__reald_one_one(%rip),%xmm4		; Sign
#	paddd		.L__reald_one_one(%rip),%xmm5		; Sign
#	pand		.L__reald_two_two(%rip),%xmm4
#	pand		.L__reald_two_two(%rip),%xmm5
#	punpckldq 	%xmm4,%xmm4
#	punpckldq 	%xmm5,%xmm5
#	psllq		$62,%xmm4
#	psllq		$62,%xmm5


	add .L__reald_one_one(%rip),%r8
	add .L__reald_one_one(%rip),%r9
	and .L__reald_two_two(%rip),%r8
	and .L__reald_two_two(%rip),%r9

	mov %r8,%r10
	mov %r9,%r11
	shl $62,%r8
	and .L__reald_two_zero(%rip),%r10
	shl $30,%r10
	shl $62,%r9
	and .L__reald_two_zero(%rip),%r11
	shl $30,%r11

	mov	 %r8,p_sign(%rsp)
	mov	 %r10,p_sign+8(%rsp)
	mov	 %r9,p_sign1(%rsp)
	mov	 %r11,p_sign1+8(%rsp)

# GET_BITS_DP64(rhead-rtail, uy);			   		; originally only rhead
# xmm4  = Sign, xmm0 =rhead, xmm8 =rtail
# xmm5  = Sign, xmm1 =rhead, xmm9 =rtail
	movapd	%xmm0,%xmm6						# rhead
	movapd	%xmm1,%xmm7						# rhead

	and	.L__reald_one_one(%rip),%rax		# Region
	and	.L__reald_one_one(%rip),%rcx		# Region

	subpd	%xmm8,%xmm0						# r = rhead - rtail
	subpd	%xmm9,%xmm1						# r = rhead - rtail

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# xmm4  = Sign, xmm0 = r, xmm6 =rhead, xmm8 =rtail
# xmm5  = Sign, xmm1 = r, xmm7 =rhead, xmm9 =rtail

	subpd	%xmm0,%xmm6				#rr=rhead-r
	subpd	%xmm1,%xmm7				#rr=rhead-r

	mov	%rax,%r8
	mov	%rcx,%r9

	movapd	%xmm0,%xmm2
	movapd	%xmm1,%xmm3

	mulpd	%xmm0,%xmm2				# r2
	mulpd	%xmm1,%xmm3				# r2

	subpd	%xmm8,%xmm6				#rr=(rhead-r) -rtail
	subpd	%xmm9,%xmm7				#rr=(rhead-r) -rtail


	and	.L__reald_zero_one(%rip),%rax
	and	.L__reald_zero_one(%rip),%rcx
	shr	$31,%r8
	shr	$31,%r9
	or	%r8,%rax
	or	%r9,%rcx
	shl	$2,%rcx
	or	%rcx,%rax

	leaq	 .Levencos_oddsin_tbl(%rip),%rsi
	jmp	 *(%rsi,%rax,8)				#Jmp table for cos/sin calculation based on even/odd region

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lfirst_or_next3_arg_gt_5e5:
# %rcx,,%rax r8, r9

#DEBUG
#	movapd	%xmm0,%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

	cmp	%r10,%rcx				#is upper arg >= 5e5
	jae	.Lboth_arg_gt_5e5

.Llower_arg_gt_5e5:
# Upper Arg is < 5e5, Lower arg is >= 5e5
# %xmm2,,%xmm0 xmm6 = x, xmm4 = 0.5
# Be sure not to use %xmm3,%xmm1 and xmm7
# Use %xmm8,,%xmm5 xmm10, xmm12
#	    %xmm11,,%xmm9 xmm13


#DEBUG
#	movapd	%xmm0,%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG


	movlpd	 %xmm0,r(%rsp)		#Save lower fp arg for remainder_piby2 call
	movhlps	%xmm0,%xmm0			#Needed since we want to work on upper arg
	movhlps	%xmm2,%xmm2
	movhlps	%xmm6,%xmm6

# Work on Upper arg
# Lower arg might contain nan/inf, to avoid exception use only scalar instructions on upper arg which has been moved to lower portions of fp regs
	mulsd	.L__real_3fe45f306dc9c883(%rip),%xmm2		# x*twobypi
	addsd	%xmm4,%xmm2					# xmm2 = npi2=(x*twobypi+0.5)
	movsd	.L__real_3ff921fb54400000(%rip),%xmm8		# xmm8 = piby2_1
	cvttsd2si	%xmm2,%ecx				# ecx = npi2 trunc to ints
	movsd	.L__real_3dd0b4611a600000(%rip),%xmm10		# xmm10 = piby2_2
	cvtsi2sd	%ecx,%xmm2				# xmm2 = npi2 trunc to doubles

#/* Subtract the multiple from x to get an extra-precision remainder */
#rhead  = x - npi2 * piby2_1;
	mulsd	%xmm2,%xmm8					# npi2 * piby2_1
	subsd	%xmm8,%xmm6					# xmm6 = rhead =(x-npi2*piby2_1)
	movsd	.L__real_3ba3198a2e037073(%rip),%xmm12		# xmm12 =piby2_2tail

#t  = rhead;
       movsd	%xmm6,%xmm5					# xmm5 = t = rhead

#rtail  = npi2 * piby2_2;
       mulsd	%xmm2,%xmm10					# xmm1 =rtail=(npi2*piby2_2)

#rhead  = t - rtail
       subsd	%xmm10,%xmm6					# xmm6 =rhead=(t-rtail)

#rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulsd	%xmm2,%xmm12     					# npi2 * piby2_2tail
       subsd	%xmm6,%xmm5					# t-rhead
       subsd	%xmm5,%xmm10					# (rtail-(t-rhead))
       addsd	%xmm12,%xmm10					# rtail=npi2*piby2_2tail+(rtail-(t-rhead));

#r =  rhead - rtail
#rr = (rhead-r) -rtail
       mov	 %ecx,region+4(%rsp)			# store upper region
       movsd	 %xmm6,%xmm0
       subsd	 %xmm10,%xmm0					# xmm0 = r=(rhead-rtail)
       subsd	 %xmm0,%xmm6					# rr=rhead-r
       subsd	 %xmm10,%xmm6					# xmm6 = rr=((rhead-r) -rtail)
       movlpd	 %xmm0,r+8(%rsp)			# store upper r
       movlpd	 %xmm6,rr+8(%rsp)			# store upper rr

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#Note that volatiles will be trashed by the call
#We will construct r, rr, region and sign

# Work on Lower arg
	mov		$0x07ff0000000000000,%r11			# is lower arg nan/inf
	mov		%r11,%r10
	and		%rax,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_lower_naninf


	mov	  %r8,p_temp(%rsp)
	mov	  %r9,p_temp2(%rsp)
	movapd	  %xmm1,p_temp1(%rsp)
	movapd	  %xmm3,p_temp3(%rsp)
	movapd	  %xmm7,p_temp5(%rsp)

	lea	 region(%rsp),%rdx			# lower arg is **NOT** nan/inf
	lea	 rr(%rsp),%rsi
	lea	 r(%rsp),%rdi
	movlpd	 r(%rsp),%xmm0	#Restore lower fp arg for remainder_piby2 call
        call    __remainder_piby2@PLT

	mov	 p_temp(%rsp),%r8
	mov	 p_temp2(%rsp),%r9
	movapd	 p_temp1(%rsp),%xmm1
	movapd	 p_temp3(%rsp),%xmm3
	movapd	 p_temp5(%rsp),%xmm7
	jmp 	0f

.L__vrd4_cos_lower_naninf:
	mov	p_original(%rsp),%rax			# upper arg is nan/inf
	mov	$0x00008000000000000,%r11
	or	%r11,%rax
	mov	 %rax,r(%rsp)				# r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	 %r10,rr(%rsp)				# rr = 0
	mov	 %r10d,region(%rsp)			# region =0

.align 16
0:


#DEBUG
#	movapd	.LOWORD,%xmm4 PTR r[rsp]
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG



	jmp 	.Lcheck_next2_args


#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lboth_arg_gt_5e5:
#Upper Arg is >= 5e5, Lower arg is >= 5e5
# %rcx,,%rax r8, r9
# %xmm2,,%xmm0 xmm6 = x, xmm4 = 0.5


#DEBUG
#	movapd	%xmm0,%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG




	movhpd 	%xmm0,r+8(%rsp)		#Save upper fp arg for remainder_piby2 call

	mov		$0x07ff0000000000000,%r11			#is lower arg nan/inf
	mov		%r11,%r10
	and		%rax,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_lower_naninf_of_both_gt_5e5

	mov	  %rcx,p_temp(%rsp)			#Save upper arg
	mov	  %r8,p_temp2(%rsp)
	mov	  %r9,p_temp4(%rsp)
	movapd	  %xmm1,p_temp1(%rsp)
	movapd	  %xmm3,p_temp3(%rsp)
	movapd	  %xmm7,p_temp5(%rsp)

	lea	 region(%rsp),%rdx			#lower arg is **NOT** nan/inf
	lea	 rr(%rsp),%rsi
	lea	 r(%rsp),%rdi
        call    __remainder_piby2@PLT

	mov	 p_temp(%rsp),%rcx			#Restore upper arg
	mov	 p_temp2(%rsp),%r8
	mov	 p_temp4(%rsp),%r9
	movapd	 p_temp1(%rsp),%xmm1
	movapd	 p_temp3(%rsp),%xmm3
	movapd	 p_temp5(%rsp),%xmm7

	jmp 	0f

.L__vrd4_cos_lower_naninf_of_both_gt_5e5:				#lower arg is nan/inf
	mov	p_original(%rsp),%rax
	mov	$0x00008000000000000,%r11
	or	%r11,%rax
	mov	 %rax,r(%rsp)				#r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	 %r10,rr(%rsp)				#rr = 0
	mov	 %r10d,region(%rsp)			#region = 0

.align 16
0:
	mov		$0x07ff0000000000000,%r11			#is upper arg nan/inf
	mov		%r11,%r10
	and		%rcx,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_upper_naninf_of_both_gt_5e5


	mov	  %r8,p_temp(%rsp)
	mov	  %r9,p_temp2(%rsp)
	movapd	  %xmm1,p_temp1(%rsp)
	movapd	  %xmm3,p_temp3(%rsp)
	movapd	  %xmm7,p_temp5(%rsp)

	lea	 region+4(%rsp),%rdx			#upper arg is **NOT** nan/inf
	lea	 rr+8(%rsp),%rsi
	lea	 r+8(%rsp),%rdi
	movlpd	 r+8(%rsp),%xmm0			#Restore upper fp arg for remainder_piby2 call
        call    __remainder_piby2@PLT

	mov	 p_temp(%rsp),%r8
	mov	 p_temp2(%rsp),%r9
	movapd	 p_temp1(%rsp),%xmm1
	movapd	 p_temp3(%rsp),%xmm3
	movapd	 p_temp5(%rsp),%xmm7

	jmp 	0f

.L__vrd4_cos_upper_naninf_of_both_gt_5e5:
	mov	p_original+8(%rsp),%rcx		#upper arg is nan/inf
#	movd	%xmm6,%rcx					;upper arg is nan/inf
	mov	$0x00008000000000000,%r11
	or	%r11,%rcx
	mov	%rcx,r+8(%rsp)				#r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	%r10,rr+8(%rsp)			#rr = 0
	mov	%r10d,region+4(%rsp)			#region = 0

.align 16
0:
	jmp 	.Lcheck_next2_args

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lsecond_or_next2_arg_gt_5e5:
# Upper Arg is >= 5e5, Lower arg is < 5e5
# %rcx,,%rax r8, r9
# %xmm2,,%xmm0 xmm6 = x, xmm4 = 0.5
# Do not use %xmm3,,%xmm1 xmm7
# Restore xmm4 and %xmm3,,%xmm1 xmm7
# Can use %xmm10,,%xmm8 xmm12
#   %xmm9,,%xmm5 xmm11, xmm13

	movhpd	%xmm0,r+8(%rsp)	#Save upper fp arg for remainder_piby2 call
#	movlhps	%xmm0,%xmm0			;Not needed since we want to work on lower arg, but done just to be safe and avoide exceptions due to nan/inf and to mirror the lower_arg_gt_5e5 case
#	movlhps	%xmm2,%xmm2
#	movlhps	%xmm6,%xmm6

# Work on Lower arg
# Upper arg might contain nan/inf, to avoid exception use only scalar instructions on lower arg

	mulsd	.L__real_3fe45f306dc9c883(%rip),%xmm2		# x*twobypi
	addsd	%xmm4,%xmm2					# xmm2 = npi2=(x*twobypi+0.5)
	movsd	.L__real_3ff921fb54400000(%rip),%xmm8		# xmm3 = piby2_1
	cvttsd2si	%xmm2,%eax				# ecx = npi2 trunc to ints
	movsd	.L__real_3dd0b4611a600000(%rip),%xmm10		# xmm1 = piby2_2
	cvtsi2sd	%eax,%xmm2				# xmm2 = npi2 trunc to doubles

#/* Subtract the multiple from x to get an extra-precision remainder */
#rhead  = x - npi2 * piby2_1;
	mulsd	%xmm2,%xmm8					# npi2 * piby2_1
	subsd	%xmm8,%xmm6					# xmm6 = rhead =(x-npi2*piby2_1)
	movsd	.L__real_3ba3198a2e037073(%rip),%xmm12		# xmm7 =piby2_2tail

#t  = rhead;
       movsd	%xmm6,%xmm5					# xmm5 = t = rhead

#rtail  = npi2 * piby2_2;
       mulsd	%xmm2,%xmm10					# xmm1 =rtail=(npi2*piby2_2)

#rhead  = t - rtail
       subsd	%xmm10,%xmm6					# xmm6 =rhead=(t-rtail)

#rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulsd	%xmm2,%xmm12     					# npi2 * piby2_2tail
       subsd	%xmm6,%xmm5					# t-rhead
       subsd	%xmm5,%xmm10					# (rtail-(t-rhead))
       addsd	%xmm12,%xmm10					# rtail=npi2*piby2_2tail+(rtail-(t-rhead));

#r =  rhead - rtail
#rr = (rhead-r) -rtail
       mov	 %eax,region(%rsp)			# store upper region
       movsd	%xmm6,%xmm0
       subsd	%xmm10,%xmm0					# xmm0 = r=(rhead-rtail)
       subsd	%xmm0,%xmm6					# rr=rhead-r
       subsd	%xmm10,%xmm6					# xmm6 = rr=((rhead-r) -rtail)
       movlpd	 %xmm0,r(%rsp)				# store upper r
       movlpd	 %xmm6,rr(%rsp)				# store upper rr

#Work on Upper arg
#Note that volatiles will be trashed by the call
#We do not care since this is the last check
#We will construct r, rr, region and sign
	mov		$0x07ff0000000000000,%r11			# is upper arg nan/inf
	mov		%r11,%r10
	and		%rcx,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_upper_naninf


	mov	  %r8,p_temp(%rsp)
	mov	  %r9,p_temp2(%rsp)
	movapd	 %xmm1,p_temp1(%rsp)
	movapd	 %xmm3,p_temp3(%rsp)
	movapd	 %xmm7,p_temp5(%rsp)

	lea	 region+4(%rsp),%rdx			# upper arg is **NOT** nan/inf
	lea	 rr+8(%rsp),%rsi
	lea	 r+8(%rsp),%rdi
	movlpd	 r+8(%rsp),%xmm0	#Restore upper fp arg for remainder_piby2 call
        call    __remainder_piby2@PLT

	mov	 p_temp(%rsp),%r8
	mov	 p_temp2(%rsp),%r9
	movapd	p_temp1(%rsp),%xmm1
	movapd	p_temp3(%rsp),%xmm3
	movapd	p_temp5(%rsp),%xmm7
	jmp 	0f

.L__vrd4_cos_upper_naninf:
	mov	p_original+8(%rsp),%rcx		# upper arg is nan/inf
#	mov	r+8(%rsp),%rcx				; upper arg is nan/inf
	mov	$0x00008000000000000,%r11
	or	%r11,%rcx
	mov	 %rcx,r+8(%rsp)				# r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	 %r10,rr+8(%rsp)			# rr = 0
	mov	 %r10d,region+4(%rsp)			# region =0

.align 16
0:
	jmp 	.Lcheck_next2_args


#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lcheck_next2_args:

#DEBUG
#	movapd	r(%rsp),%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

	mov	$0x411E848000000000,%r10			#5e5	+

	cmp	%r10,%r8
	jae	.Lfirst_second_done_third_or_fourth_arg_gt_5e5

	cmp	%r10,%r9
	jae	.Lfirst_second_done_fourth_arg_gt_5e5

# Work on next two args, both < 5e5
# %xmm3,,%xmm1 xmm5 = x, xmm4 = 0.5

	movapd	.L__real_3fe0000000000000(%rip),%xmm4			#Restore 0.5

	mulpd	.L__real_3fe45f306dc9c883(%rip),%xmm3						# * twobypi
	addpd	%xmm4,%xmm3						# +0.5, npi2
	movapd	.L__real_3ff921fb54400000(%rip),%xmm1		# piby2_1
	cvttpd2dq	%xmm3,%xmm5					# convert packed double to packed integers
	movapd	.L__real_3dd0b4611a600000(%rip),%xmm9		# piby2_2
	cvtdq2pd	%xmm5,%xmm3					# and back to double.

#      /* Subtract the multiple from x to get an extra-precision remainder */
	movq	 %xmm5,region1(%rsp)						# Region

#      rhead  = x - npi2 * piby2_1;
       mulpd	%xmm3,%xmm1						# npi2 * piby2_1;

#      rtail  = npi2 * piby2_2;
       mulpd	%xmm3,%xmm9						# rtail

#      rhead  = x - npi2 * piby2_1;
       subpd	%xmm1,%xmm7						# rhead  = x - npi2 * piby2_1;

#      t  = rhead;
       movapd	%xmm7,%xmm1						# t

#      rhead  = t - rtail;
       subpd	%xmm9,%xmm1						# rhead

#      rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulpd	.L__real_3ba3198a2e037073(%rip),%xmm3		# npi2 * piby2_2tail

       subpd	%xmm1,%xmm7						# t-rhead
       subpd	%xmm7,%xmm9						# - ((t - rhead) - rtail)
       addpd	%xmm3,%xmm9						# rtail = npi2 * piby2_2tail - ((t - rhead) - rtail);

       movapd	%xmm1,%xmm7						# rhead
       subpd	%xmm9,%xmm1						# r = rhead - rtail
       movapd	 %xmm1,r1(%rsp)

       subpd	%xmm1,%xmm7						# rr=rhead-r
       subpd	%xmm9,%xmm7						# rr=(rhead-r) -rtail
       movapd	 %xmm7,rr1(%rsp)

	jmp	.L__vrd4_cos_reconstruct


#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lthird_or_fourth_arg_gt_5e5:
#first two args are < 5e5, third arg >= 5e5, fourth arg >= 5e5 or < 5e5
# %rcx,,%rax r8, r9
# %xmm2,,%xmm0 xmm6 = x, xmm4 = 0.5
# Do not use %xmm3,,%xmm1 xmm7
# Can use 	%xmm11,,%xmm9 xmm13
# 	%xmm8,,%xmm5 xmm10, xmm12
# Restore xmm4

# Work on first two args, both < 5e5

#DEBUG
#	movapd	%xmm0,%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG


	mulpd	.L__real_3fe45f306dc9c883(%rip),%xmm2						# * twobypi
	addpd	%xmm4,%xmm2						# +0.5, npi2
	movapd	.L__real_3ff921fb54400000(%rip),%xmm0		# piby2_1
	cvttpd2dq	%xmm2,%xmm4					# convert packed double to packed integers
	movapd	.L__real_3dd0b4611a600000(%rip),%xmm8		# piby2_2
	cvtdq2pd	%xmm4,%xmm2					# and back to double.

#      /* Subtract the multiple from x to get an extra-precision remainder */
	movq	 %xmm4,region(%rsp)						# Region

#      rhead  = x - npi2 * piby2_1;
       mulpd	%xmm2,%xmm0						# npi2 * piby2_1;
#      rtail  = npi2 * piby2_2;
       mulpd	%xmm2,%xmm8						# rtail

#      rhead  = x - npi2 * piby2_1;
       subpd	%xmm0,%xmm6						# rhead  = x - npi2 * piby2_1;

#      t  = rhead;
       movapd	%xmm6,%xmm0						# t

#      rhead  = t - rtail;
       subpd	%xmm8,%xmm0						# rhead

#      rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulpd	.L__real_3ba3198a2e037073(%rip),%xmm2		# npi2 * piby2_2tail

       subpd	%xmm0,%xmm6						# t-rhead
       subpd	%xmm6,%xmm8						# - ((t - rhead) - rtail)
       addpd	%xmm2,%xmm8						# rtail = npi2 * piby2_2tail - ((t - rhead) - rtail);

       movapd	%xmm0,%xmm6						# rhead
       subpd	%xmm8,%xmm0						# r = rhead - rtail
       movapd	 %xmm0,r(%rsp)

       subpd	%xmm0,%xmm6						# rr=rhead-r
       subpd	%xmm8,%xmm6						# rr=(rhead-r) -rtail
       movapd	 %xmm6,rr(%rsp)


# Work on next two args, third arg >= 5e5, fourth arg >= 5e5 or < 5e5

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.Lfirst_second_done_third_or_fourth_arg_gt_5e5:
# %rcx,,%rax r8, r9
# %xmm2,,%xmm0 xmm6 = x, xmm4 = 0.5


#DEBUG
#	movapd	r(%rsp),%xmm4
#	movapd	%xmm1,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

	mov	$0x411E848000000000,%r10			#5e5	+
	cmp	%r10,%r9
	jae	.Lboth_arg_gt_5e5_higher


# Upper Arg is <5e5, Lower arg is >= 5e5
# %r9,%r8
# %xmm3,,%xmm1 xmm7 = x, xmm4 = 0.5

	movlpd	 %xmm1,r1(%rsp)		#Save lower fp arg for remainder_piby2 call
	movhlps	%xmm1,%xmm1			#Needed since we want to work on upper arg
	movhlps	%xmm3,%xmm3
	movhlps	%xmm7,%xmm7
	movapd	.L__real_3fe0000000000000(%rip),%xmm4	#0.5 for later use

# Work on Upper arg
# Lower arg might contain nan/inf, to avoid exception use only scalar instructions on upper arg which has been moved to lower portions of fp regs
	mulsd	.L__real_3fe45f306dc9c883(%rip),%xmm3		# x*twobypi
	addsd	%xmm4,%xmm3					# xmm3 = npi2=(x*twobypi+0.5)
	movsd	.L__real_3ff921fb54400000(%rip),%xmm2		# xmm2 = piby2_1
	cvttsd2si	%xmm3,%r9d				# r9d = npi2 trunc to ints
	movsd	.L__real_3dd0b4611a600000(%rip),%xmm0		# xmm0 = piby2_2
	cvtsi2sd	%r9d,%xmm3				# xmm3 = npi2 trunc to doubles

#/* Subtract the multiple from x to get an extra-precision remainder */
#rhead  = x - npi2 * piby2_1;
	mulsd	%xmm3,%xmm2					# npi2 * piby2_1
	subsd	%xmm2,%xmm7					# xmm7 = rhead =(x-npi2*piby2_1)
	movsd	.L__real_3ba3198a2e037073(%rip),%xmm6		# xmm6 =piby2_2tail

#t  = rhead;
       movsd	%xmm7,%xmm5					# xmm5 = t = rhead

#rtail  = npi2 * piby2_2;
       mulsd	%xmm3,%xmm0					# xmm0 =rtail=(npi2*piby2_2)

#rhead  = t - rtail
       subsd	%xmm0,%xmm7					# xmm7 =rhead=(t-rtail)

#rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulsd	%xmm3,%xmm6     					# npi2 * piby2_2tail
       subsd	%xmm7,%xmm5					# t-rhead
       subsd	%xmm5,%xmm0					# (rtail-(t-rhead))
       addsd	%xmm6,%xmm0					# rtail=npi2*piby2_2tail+(rtail-(t-rhead));

#r =  rhead - rtail
#rr = (rhead-r) -rtail
       mov	 %r9d,region1+4(%rsp)			# store upper region
       movsd	%xmm7,%xmm1
       subsd	%xmm0,%xmm1					# xmm1 = r=(rhead-rtail)
       subsd	%xmm1,%xmm7					# rr=rhead-r
       subsd	%xmm0,%xmm7					# xmm7 = rr=((rhead-r) -rtail)
       movlpd	 %xmm1,r1+8(%rsp)			# store upper r
       movlpd	 %xmm7,rr1+8(%rsp)			# store upper rr

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#Note that volatiles will be trashed by the call
#We do not care since this is the last check
#We will construct r, rr, region and sign

# Work on Lower arg
	mov		$0x07ff0000000000000,%r11			# is lower arg nan/inf
	mov		%r11,%r10
	and		%r8,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_lower_naninf_higher

	lea	 region1(%rsp),%rdx			# lower arg is **NOT** nan/inf
	lea	 rr1(%rsp),%rsi
	lea	 r1(%rsp),%rdi
	movlpd	 r1(%rsp),%xmm0				#Restore lower fp arg for remainder_piby2 call
        call    __remainder_piby2@PLT
	jmp 	0f

.L__vrd4_cos_lower_naninf_higher:
	mov	p_original1(%rsp),%r8			# upper arg is nan/inf
	mov	$0x00008000000000000,%r11
	or	%r11,%r8
	mov	 %r8,r1(%rsp)				# r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	 %r10,rr1(%rsp)				# rr = 0
	mov	 %r10d,region1(%rsp)			# region =0

.align 16
0:


#DEBUG
#	movapd	rr(%rsp),%xmm4
#	movapd	rr1(%rsp),%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

	jmp 	.L__vrd4_cos_reconstruct







.align 16
.Lboth_arg_gt_5e5_higher:
# Upper Arg is >= 5e5, Lower arg is >= 5e5
# %r9,%r8
# %xmm3,,%xmm1 xmm7 = x, xmm4 = 0.5


#DEBUG
#	movapd	r(%rsp),%xmm4
#	movd	%r8,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

	movhpd 	%xmm1,r1+8(%rsp)				#Save upper fp arg for remainder_piby2 call

	mov		$0x07ff0000000000000,%r11			#is lower arg nan/inf
	mov		%r11,%r10
	and		%r8,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_lower_naninf_of_both_gt_5e5_higher

	mov	  %r9,p_temp1(%rsp)			#Save upper arg
	lea	 region1(%rsp),%rdx			#lower arg is **NOT** nan/inf
	lea	 rr1(%rsp),%rsi
	lea	 r1(%rsp),%rdi
	movsd	 %xmm1,%xmm0
        call    __remainder_piby2@PLT
	mov	 p_temp1(%rsp),%r9			#Restore upper arg


#DEBUG
#	movapd	 r(%rsp),%xmm4
#	mov	 QWORD PTR r1[rsp+8], r9
#	movapd	 r1(%rsp),%xmm5
#	xorpd	 %xmm0,%xmm0
#	xorpd	 %xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG



	jmp 	0f

.L__vrd4_cos_lower_naninf_of_both_gt_5e5_higher:				#lower arg is nan/inf
	mov	p_original1(%rsp),%r8
	mov	$0x00008000000000000,%r11
	or	%r11,%r8
	mov	 %r8,r1(%rsp)				#r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	 %r10,rr1(%rsp)				#rr = 0
	mov	 %r10d,region1(%rsp)			#region = 0

.align 16
0:
	mov		$0x07ff0000000000000,%r11			#is upper arg nan/inf
	mov		%r11,%r10
	and		%r9,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_upper_naninf_of_both_gt_5e5_higher

	lea	 region1+4(%rsp),%rdx			#upper arg is **NOT** nan/inf
	lea	 rr1+8(%rsp),%rsi
	lea	 r1+8(%rsp),%rdi
	movlpd	 r1+8(%rsp),%xmm0			#Restore upper fp arg for remainder_piby2 call
        call    __remainder_piby2@PLT
	jmp 	0f

.L__vrd4_cos_upper_naninf_of_both_gt_5e5_higher:
	mov	p_original1+8(%rsp),%r9		#upper arg is nan/inf
#	movd	%xmm6,%r9					;upper arg is nan/inf
	mov	$0x00008000000000000,%r11
	or	%r11,%r9
	mov	 %r9,r1+8(%rsp)				#r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	 %r10,rr1+8(%rsp)			#rr = 0
	mov	 %r10d,region1+4(%rsp)			#region = 0

.align 16
0:

#DEBUG
#	movapd	r(%rsp),%xmm4
#	movapd	r1(%rsp),%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG


	jmp 	.L__vrd4_cos_reconstruct

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lfourth_arg_gt_5e5:
#first two args are < 5e5, third arg < 5e5, fourth arg >= 5e5
#%rcx,,%rax r8, r9
#%xmm2,,%xmm0 xmm6 = x, xmm4 = 0.5

# Work on first two args, both < 5e5

	mulpd	.L__real_3fe45f306dc9c883(%rip),%xmm2						# * twobypi
	addpd	%xmm4,%xmm2						# +0.5, npi2
	movapd	.L__real_3ff921fb54400000(%rip),%xmm0		# piby2_1
	cvttpd2dq	%xmm2,%xmm4					# convert packed double to packed integers
	movapd	.L__real_3dd0b4611a600000(%rip),%xmm8		# piby2_2
	cvtdq2pd	%xmm4,%xmm2					# and back to double.

#      /* Subtract the multiple from x to get an extra-precision remainder */
	movq	 %xmm4,region(%rsp)						# Region

#      rhead  = x - npi2 * piby2_1;
       mulpd	%xmm2,%xmm0						# npi2 * piby2_1;
#      rtail  = npi2 * piby2_2;
       mulpd	%xmm2,%xmm8						# rtail

#      rhead  = x - npi2 * piby2_1;
       subpd	%xmm0,%xmm6						# rhead  = x - npi2 * piby2_1;

#      t  = rhead;
       movapd	%xmm6,%xmm0						# t

#      rhead  = t - rtail;
       subpd	%xmm8,%xmm0						# rhead

#      rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulpd	.L__real_3ba3198a2e037073(%rip),%xmm2		# npi2 * piby2_2tail

       subpd	%xmm0,%xmm6						# t-rhead
       subpd	%xmm6,%xmm8						# - ((t - rhead) - rtail)
       addpd	%xmm2,%xmm8						# rtail = npi2 * piby2_2tail - ((t - rhead) - rtail);

       movapd	%xmm0,%xmm6						# rhead
       subpd	%xmm8,%xmm0						# r = rhead - rtail
       movapd	 %xmm0,r(%rsp)

       subpd	%xmm0,%xmm6						# rr=rhead-r
       subpd	%xmm8,%xmm6						# rr=(rhead-r) -rtail
       movapd	 %xmm6,rr(%rsp)


# Work on next two args, third arg < 5e5, fourth arg >= 5e5
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.Lfirst_second_done_fourth_arg_gt_5e5:

# Upper Arg is >= 5e5, Lower arg is < 5e5
# %r9,%r8
# %xmm3,,%xmm1 xmm7 = x, xmm4 = 0.5

	movhpd	 %xmm1,r1+8(%rsp)	#Save upper fp arg for remainder_piby2 call
#	movlhps	%xmm1,%xmm1			;Not needed since we want to work on lower arg, but done just to be safe and avoide exceptions due to nan/inf and to mirror the lower_arg_gt_5e5 case
#	movlhps	%xmm3,%xmm3
#	movlhps	%xmm7,%xmm7
	movapd	.L__real_3fe0000000000000(%rip),%xmm4	#0.5 for later use

# Work on Lower arg
# Upper arg might contain nan/inf, to avoid exception use only scalar instructions on lower arg

	mulsd	.L__real_3fe45f306dc9c883(%rip),%xmm3		# x*twobypi
	addsd	%xmm4,%xmm3					# xmm3 = npi2=(x*twobypi+0.5)
	movsd	.L__real_3ff921fb54400000(%rip),%xmm2		# xmm2 = piby2_1
	cvttsd2si	%xmm3,%r8d				# r8d = npi2 trunc to ints
	movsd	.L__real_3dd0b4611a600000(%rip),%xmm0		# xmm0 = piby2_2
	cvtsi2sd	%r8d,%xmm3				# xmm3 = npi2 trunc to doubles

#/* Subtract the multiple from x to get an extra-precision remainder */
#rhead  = x - npi2 * piby2_1;
	mulsd	%xmm3,%xmm2					# npi2 * piby2_1
	subsd	%xmm2,%xmm7					# xmm7 = rhead =(x-npi2*piby2_1)
	movsd	.L__real_3ba3198a2e037073(%rip),%xmm6		# xmm6 =piby2_2tail

#t  = rhead;
       movsd	%xmm7,%xmm5					# xmm5 = t = rhead

#rtail  = npi2 * piby2_2;
       mulsd	%xmm3,%xmm0					# xmm0 =rtail=(npi2*piby2_2)

#rhead  = t - rtail
       subsd	%xmm0,%xmm7					# xmm7 =rhead=(t-rtail)

#rtail  = npi2 * piby2_2tail - ((t - rhead) - rtail);
       mulsd	%xmm3,%xmm6     					# npi2 * piby2_2tail
       subsd	%xmm7,%xmm5					# t-rhead
       subsd	%xmm5,%xmm0					# (rtail-(t-rhead))
       addsd	%xmm6,%xmm0					# rtail=npi2*piby2_2tail+(rtail-(t-rhead));

#r =  rhead - rtail
#rr = (rhead-r) -rtail
       mov	 %r8d,region1(%rsp)			# store lower region
       movsd	%xmm7,%xmm1
       subsd	%xmm0,%xmm1					# xmm0 = r=(rhead-rtail)
       subsd	%xmm1,%xmm7					# rr=rhead-r
       subsd	%xmm0,%xmm7					# xmm6 = rr=((rhead-r) -rtail)

       movlpd	 %xmm1,r1(%rsp)				# store upper r
       movlpd	 %xmm7,rr1(%rsp)				# store upper rr

#Work on Upper arg
#Note that volatiles will be trashed by the call
#We do not care since this is the last check
#We will construct r, rr, region and sign
	mov		$0x07ff0000000000000,%r11			# is upper arg nan/inf
	mov		%r11,%r10
	and		%r9,%r10
	cmp		%r11,%r10
	jz		.L__vrd4_cos_upper_naninf_higher

	lea	 region1+4(%rsp),%rdx			# upper arg is **NOT** nan/inf
	lea	 rr1+8(%rsp),%rsi
	lea	 r1+8(%rsp),%rdi
	movlpd	 r1+8(%rsp),%xmm0	#Restore upper fp arg for remainder_piby2 call
        call    __remainder_piby2@PLT
	jmp 	0f

.L__vrd4_cos_upper_naninf_higher:
	mov	p_original1+8(%rsp),%r9		# upper arg is nan/inf
#	mov	r1+8(%rsp),%r9			# upper arg is nan/inf
	mov	$0x00008000000000000,%r11
	or	%r11,%r9
	mov	 %r9,r1+8(%rsp)			# r = x | 0x0008000000000000
	xor	%r10,%r10
	mov	 %r10,rr1+8(%rsp)		# rr = 0
	mov	 %r10d,region1+4(%rsp)		# region =0

.align 16
0:
	jmp	.L__vrd4_cos_reconstruct


#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.L__vrd4_cos_reconstruct:
#Results
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# p_sign0  = Sign, xmm0 = r, xmm2 = %xmm6,%r2 =rr
# p_sign1  = Sign, xmm1 = r, xmm3 = %xmm7,%r2 =rr
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#DEBUG
#	movapd	region(%rsp),%xmm4
#	movapd	region1(%rsp),%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

	movapd	r(%rsp),%xmm0
	movapd	r1(%rsp),%xmm1

	movapd	rr(%rsp),%xmm6
	movapd	rr1(%rsp),%xmm7

	mov	region(%rsp),%rax
	mov	region1(%rsp),%rcx

	mov	%rax,%r8
	mov	%rcx,%r9

	add .L__reald_one_one(%rip),%r8
	add .L__reald_one_one(%rip),%r9
	and .L__reald_two_two(%rip),%r8
	and .L__reald_two_two(%rip),%r9

	mov %r8,%r10
	mov %r9,%r11
	shl $62,%r8
	and .L__reald_two_zero(%rip),%r10
	shl $30,%r10
	shl $62,%r9
	and .L__reald_two_zero(%rip),%r11
	shl $30,%r11

	mov	 %r8,p_sign(%rsp)
	mov	 %r10,p_sign+8(%rsp)
	mov	 %r9,p_sign1(%rsp)
	mov	 %r11,p_sign1+8(%rsp)

	and	.L__reald_one_one(%rip),%rax		# Region
	and	.L__reald_one_one(%rip),%rcx		# Region

	mov	%rax,%r8
	mov	%rcx,%r9

	movapd	%xmm0,%xmm2
	movapd	%xmm1,%xmm3

	mulpd	%xmm0,%xmm2				# r2
	mulpd	%xmm1,%xmm3				# r2

	and	.L__reald_zero_one(%rip),%rax
	and	.L__reald_zero_one(%rip),%rcx
	shr	$31,%r8
	shr	$31,%r9
	or	%r8,%rax
	or	%r9,%rcx
	shl	$2,%rcx
	or	%rcx,%rax



#DEBUG
#	movd	%rax,%xmm4
#	movd	%rax,%xmm5
#	xorpd	%xmm0,%xmm0
#	xorpd	%xmm1,%xmm1
#	jmp 	.L__vrd4_cos_cleanup
#DEBUG

	leaq	 .Levencos_oddsin_tbl(%rip),%rsi
	jmp	 *(%rsi,%rax,8)	#Jmp table for cos/sin calculation based on even/odd region

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.L__vrd4_cos_cleanup:

	movapd	  p_sign(%rsp),%xmm0
	movapd	  p_sign1(%rsp),%xmm1

	xorpd	%xmm4,%xmm0			# (+) Sign
	xorpd	%xmm5,%xmm1			# (+) Sign

	add	$0x1C8,%rsp
	ret

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;JUMP TABLE;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# p_sign0  = Sign, xmm0 = r, xmm2 = %xmm6,%r2 =rr
# p_sign1  = Sign, xmm1 = r, xmm3 = %xmm7,%r2 =rr
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lcoscos_coscos_piby4:
	movapd	%xmm2,%xmm10					# r
	movapd	%xmm3,%xmm11					# r

	movdqa	.Lcosarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lcosarray+0x50(%rip),%xmm5			# c6

	movapd	.Lcosarray+0x20(%rip),%xmm8			# c3
	movapd	.Lcosarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10		# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11		# r = 0.5 *x2

	mulpd	 %xmm2,%xmm4					# c6*x2
	mulpd	 %xmm3,%xmm5					# c6*x2

	movapd	 %xmm10,p_temp2(%rsp)			# r
	movapd	 %xmm11,p_temp3(%rsp)			# r

	mulpd	 %xmm2,%xmm8					# c3*x2
	mulpd	 %xmm3,%xmm9					# c3*x2

	subpd	.L__real_3ff0000000000000(%rip),%xmm10		# -t=r-1.0	;trash r
	subpd	.L__real_3ff0000000000000(%rip),%xmm11		# -t=r-1.0	;trash r

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lcosarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lcosarray+0x40(%rip),%xmm5			# c5+x2c6

	addpd	.Lcosarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lcosarray+0x10(%rip),%xmm9			# c2+x2C3

	addpd   .L__real_3ff0000000000000(%rip),%xmm10		# 1 + (-t)	;trash t
	addpd   .L__real_3ff0000000000000(%rip),%xmm11		# 1 + (-t)	;trash t

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)

	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lcosarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lcosarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)

	addpd	.Lcosarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lcosarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zc
	addpd	%xmm9,%xmm5					# zc

	mulpd	%xmm2,%xmm2					# x4 recalculate
	mulpd	%xmm3,%xmm3					# x4 recalculate

	movapd   p_temp2(%rsp),%xmm12			# r
	movapd   p_temp3(%rsp),%xmm13			# r

	mulpd	%xmm0,%xmm6					# x * xx
	mulpd	%xmm1,%xmm7					# x * xx

	subpd   %xmm12,%xmm10					# (1 + (-t)) - r
	subpd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x4 * zc
	mulpd	%xmm3,%xmm5					# x4 * zc

	subpd   %xmm6,%xmm10					# ((1 + (-t)) - r) - x*xx
	subpd   %xmm7,%xmm11					# ((1 + (-t)) - r) - x*xx

	addpd   %xmm10,%xmm4					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addpd   %xmm11,%xmm5					# x4*zc + (((1 + (-t)) - r) - x*xx)

	subpd	.L__real_3ff0000000000000(%rip),%xmm12		# t relaculate, -t = r-1
	subpd	.L__real_3ff0000000000000(%rip),%xmm13		# t relaculate, -t = r-1

	subpd   %xmm12,%xmm4					# + t
	subpd   %xmm13,%xmm5					# + t

	jmp 	.L__vrd4_cos_cleanup

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lcossin_cossin_piby4:
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# p_sign0  = Sign, xmm0 = r, xmm2 = %xmm6,%r2 =rr
# p_sign1  = Sign, xmm1 = r, xmm3 = %xmm7,%r2 =rr
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movapd	 %xmm6,p_temp(%rsp)		# Store rr
	movapd	 %xmm7,p_temp1(%rsp)		# Store rr

	movdqa	.Lsincosarray+0x50(%rip),%xmm4		# s6
	movdqa	.Lsincosarray+0x50(%rip),%xmm5		# s6
	movapd	.Lsincosarray+0x20(%rip),%xmm8		# s3
	movapd	.Lsincosarray+0x20(%rip),%xmm9		# s3

	movapd	%xmm2,%xmm10				# move x2 for x4
	movapd	%xmm3,%xmm11				# move x2 for x4

	mulpd	%xmm2,%xmm4				# x2s6
	mulpd	%xmm3,%xmm5				# x2s6
	mulpd	%xmm2,%xmm8				# x2s3
	mulpd	%xmm3,%xmm9				# x2s3

	mulpd	%xmm2,%xmm10				# x4
	mulpd	%xmm3,%xmm11				# x4

	addpd	.Lsincosarray+0x40(%rip),%xmm4		# s5+x2s6
	addpd	.Lsincosarray+0x40(%rip),%xmm5		# s5+x2s6
	addpd	.Lsincosarray+0x10(%rip),%xmm8		# s2+x2s3
	addpd	.Lsincosarray+0x10(%rip),%xmm9		# s2+x2s3

	movapd	%xmm2,%xmm12				# move x2 for x6
	movapd	%xmm3,%xmm13				# move x2 for x6

	mulpd	%xmm2,%xmm4				# x2(s5+x2s6)
	mulpd	%xmm3,%xmm5				# x2(s5+x2s6)
	mulpd	%xmm2,%xmm8				# x2(s2+x2s3)
	mulpd	%xmm3,%xmm9				# x2(s2+x2s3)

	mulpd	%xmm10,%xmm12				# x6
	mulpd	%xmm11,%xmm13				# x6

	addpd	.Lsincosarray+0x30(%rip),%xmm4		# s4+x2(s5+x2s6)
	addpd	.Lsincosarray+0x30(%rip),%xmm5		# s4+x2(s5+x2s6)
	addpd	.Lsincosarray(%rip),%xmm8		# s1+x2(s2+x2s3)
	addpd	.Lsincosarray(%rip),%xmm9		# s1+x2(s2+x2s3)

	movhlps	%xmm10,%xmm10				# move high x4 for cos term
	movhlps	%xmm11,%xmm11				# move high x4 for cos term
	mulpd	%xmm12,%xmm4				# x6(s4+x2(s5+x2s6))
	mulpd	%xmm13,%xmm5				# x6(s4+x2(s5+x2s6))

	movsd	%xmm2,%xmm6				# move low x2 for x3 for sin term
	movsd	%xmm3,%xmm7				# move low x2 for x3 for sin term
	mulsd	%xmm0,%xmm6				# get low x3 for sin term
	mulsd	%xmm1,%xmm7				# get low x3 for sin term
	mulpd 	.L__real_3fe0000000000000(%rip),%xmm2	# 0.5*x2 for sin and cos terms
	mulpd 	.L__real_3fe0000000000000(%rip),%xmm3	# 0.5*x2 for sin and cos terms

	addpd	%xmm8,%xmm4				# z
	addpd	%xmm9,%xmm5				# z

	movhlps	%xmm2,%xmm12				# move high r for cos
	movhlps	%xmm3,%xmm13				# move high r for cos
	movhlps	%xmm4,%xmm8				# xmm4 = sin , xmm8 = cos
	movhlps	%xmm5,%xmm9				# xmm4 = sin , xmm8 = cos

	mulsd	%xmm6,%xmm4				# sin *x3
	mulsd	%xmm7,%xmm5				# sin *x3
	mulsd	%xmm10,%xmm8				# cos *x4
	mulsd	%xmm11,%xmm9				# cos *x4

	mulsd	p_temp(%rsp),%xmm2		# 0.5 * x2 * xx for sin term
	mulsd	p_temp1(%rsp),%xmm3		# 0.5 * x2 * xx for sin term
	movsd	%xmm12,%xmm6				# Keep high r for cos term
	movsd	%xmm13,%xmm7				# Keep high r for cos term

	subsd	.L__real_3ff0000000000000(%rip),%xmm12 	# -t=r-1.0
	subsd	.L__real_3ff0000000000000(%rip),%xmm13 	# -t=r-1.0

	subsd	%xmm2,%xmm4				# sin - 0.5 * x2 *xx
	subsd	%xmm3,%xmm5				# sin - 0.5 * x2 *xx

	movhlps	%xmm0,%xmm10				# move high x for x*xx for cos term
	movhlps	%xmm1,%xmm11				# move high x for x*xx for cos term

	mulsd	p_temp+8(%rsp),%xmm10		# x * xx
	mulsd	p_temp1+8(%rsp),%xmm11		# x * xx

	movsd	%xmm12,%xmm2				# move -t for cos term
	movsd	%xmm13,%xmm3				# move -t for cos term

	addsd	.L__real_3ff0000000000000(%rip),%xmm12 	# 1+(-t)
	addsd	.L__real_3ff0000000000000(%rip),%xmm13	# 1+(-t)
	addsd	p_temp(%rsp),%xmm4			# sin+xx
	addsd	p_temp1(%rsp),%xmm5			# sin+xx
	subsd	%xmm6,%xmm12				# (1-t) - r
	subsd	%xmm7,%xmm13				# (1-t) - r
	subsd	%xmm10,%xmm12				# ((1 + (-t)) - r) - x*xx
	subsd	%xmm11,%xmm13				# ((1 + (-t)) - r) - x*xx
	addsd	%xmm0,%xmm4				# sin + x
	addsd	%xmm1,%xmm5				# sin + x
	addsd   %xmm12,%xmm8				# cos+((1-t)-r - x*xx)
	addsd   %xmm13,%xmm9				# cos+((1-t)-r - x*xx)
	subsd   %xmm2,%xmm8				# cos+t
	subsd   %xmm3,%xmm9				# cos+t

	movlhps	%xmm8,%xmm4
	movlhps	%xmm9,%xmm5
	jmp 	.L__vrd4_cos_cleanup

.align 16
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# p_sign0  = Sign, xmm0 = r, xmm2 = %xmm6,%r2 =rr
# p_sign1  = Sign, xmm1 = r, xmm3 = %xmm7,%r2 =rr
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.Lsincos_cossin_piby4:					# changed from sincos_sincos
							# xmm1 is cossin and xmm0 is sincos

	movapd	 %xmm6,p_temp(%rsp)		# Store rr
	movapd	 %xmm7,p_temp1(%rsp)		# Store rr
	movapd	 %xmm1,p_temp3(%rsp)		# Store r for the sincos term

	movapd	.Lsincosarray+0x50(%rip),%xmm4		# s6
	movapd	.Lcossinarray+0x50(%rip),%xmm5		# s6
	movdqa	.Lsincosarray+0x20(%rip),%xmm8		# s3
	movdqa	.Lcossinarray+0x20(%rip),%xmm9		# s3

	movapd	%xmm2,%xmm10				# move x2 for x4
	movapd	%xmm3,%xmm11				# move x2 for x4

	mulpd	%xmm2,%xmm4				# x2s6
	mulpd	%xmm3,%xmm5				# x2s6
	mulpd	%xmm2,%xmm8				# x2s3
	mulpd	%xmm3,%xmm9				# x2s3

	mulpd	%xmm2,%xmm10				# x4
	mulpd	%xmm3,%xmm11				# x4

	addpd	.Lsincosarray+0x40(%rip),%xmm4		# s5+x2s6
	addpd	.Lcossinarray+0x40(%rip),%xmm5		# s5+x2s6
	addpd	.Lsincosarray+0x10(%rip),%xmm8		# s2+x2s3
	addpd	.Lcossinarray+0x10(%rip),%xmm9		# s2+x2s3

	movapd	%xmm2,%xmm12				# move x2 for x6
	movapd	%xmm3,%xmm13				# move x2 for x6

	mulpd	%xmm2,%xmm4				# x2(s5+x2s6)
	mulpd	%xmm3,%xmm5				# x2(s5+x2s6)
	mulpd	%xmm2,%xmm8				# x2(s2+x2s3)
	mulpd	%xmm3,%xmm9				# x2(s2+x2s3)

	mulpd	%xmm10,%xmm12				# x6
	mulpd	%xmm11,%xmm13				# x6

	addpd	.Lsincosarray+0x30(%rip),%xmm4		# s4+x2(s5+x2s6)
	addpd	.Lcossinarray+0x30(%rip),%xmm5		# s4+x2(s5+x2s6)
	addpd	.Lsincosarray(%rip),%xmm8		# s1+x2(s2+x2s3)
	addpd	.Lcossinarray(%rip),%xmm9		# s1+x2(s2+x2s3)

	movhlps	%xmm10,%xmm10				# move high x4 for cos term

	mulpd	%xmm12,%xmm4				# x6(s4+x2(s5+x2s6))
	mulpd	%xmm13,%xmm5				# x6(s4+x2(s5+x2s6))

	movsd	%xmm2,%xmm6				# move low x2 for x3 for sin term  (cossin)
	movhlps	%xmm3,%xmm7				# move high x2 for x3 for sin term (sincos)

	mulsd	%xmm0,%xmm6				# get low x3 for sin term
	mulsd	p_temp3+8(%rsp),%xmm7		# get high x3 for sin term

	mulpd 	.L__real_3fe0000000000000(%rip),%xmm2	# 0.5*x2 for sin and cos terms
	mulpd 	.L__real_3fe0000000000000(%rip),%xmm3	# 0.5*x2 for sin and cos terms


	addpd	%xmm8,%xmm4				# z
	addpd	%xmm9,%xmm5				# z

	movhlps	%xmm2,%xmm12				# move high r for cos (cossin)
	movhlps	%xmm3,%xmm13				# move high 0.5*x2 for sin term (sincos)

	movhlps	%xmm4,%xmm8				# xmm8 = cos , xmm4 = sin	(cossin)
	movhlps	%xmm5,%xmm9				# xmm9 = sin , xmm5 = cos	(sincos)

	mulsd	%xmm6,%xmm4				# sin *x3
	mulsd	%xmm11,%xmm5				# cos *x4
	mulsd	%xmm10,%xmm8				# cos *x4
	mulsd	%xmm7,%xmm9				# sin *x3

	mulsd	p_temp(%rsp),%xmm2		# low  0.5 * x2 * xx for sin term (cossin)
	mulsd	p_temp1+8(%rsp),%xmm13		# high 0.5 * x2 * xx for sin term (sincos)

	movsd	%xmm12,%xmm6				# Keep high r for cos term
	movsd	%xmm3,%xmm7				# Keep low r for cos term

	subsd	.L__real_3ff0000000000000(%rip),%xmm12 	# -t=r-1.0
	subsd	.L__real_3ff0000000000000(%rip),%xmm3 	# -t=r-1.0

	subsd	%xmm2,%xmm4				# sin - 0.5 * x2 *xx	(cossin)
	subsd	%xmm13,%xmm9				# sin - 0.5 * x2 *xx	(sincos)

	movhlps	%xmm0,%xmm10				# move high x for x*xx for cos term (cossin)
	movhlps	%xmm1,%xmm11				# move high x for x for sin term    (sincos)

	mulsd	p_temp+8(%rsp),%xmm10		# x * xx
	mulsd	p_temp1(%rsp),%xmm1		# x * xx

	movsd	%xmm12,%xmm2				# move -t for cos term
	movsd	%xmm3,%xmm13				# move -t for cos term

	addsd	.L__real_3ff0000000000000(%rip),%xmm12	# 1+(-t)
	addsd	.L__real_3ff0000000000000(%rip),%xmm3 # 1+(-t)

	addsd	p_temp(%rsp),%xmm4		# sin+xx	+
	addsd	p_temp1+8(%rsp),%xmm9		# sin+xx	+

	subsd	%xmm6,%xmm12				# (1-t) - r
	subsd	%xmm7,%xmm3				# (1-t) - r

	subsd	%xmm10,%xmm12				# ((1 + (-t)) - r) - x*xx
	subsd	%xmm1,%xmm3				# ((1 + (-t)) - r) - x*xx

	addsd	%xmm0,%xmm4				# sin + x	+
	addsd	%xmm11,%xmm9				# sin + x	+

	addsd   %xmm12,%xmm8				# cos+((1-t)-r - x*xx)
	addsd   %xmm3,%xmm5				# cos+((1-t)-r - x*xx)

	subsd   %xmm2,%xmm8				# cos+t
	subsd   %xmm13,%xmm5				# cos+t

	movlhps	%xmm8,%xmm4				# cossin
	movlhps	%xmm9,%xmm5				# sincos

	jmp	.L__vrd4_cos_cleanup

.align 16
.Lsincos_sincos_piby4:
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# p_sign0  = Sign, xmm0 = r, xmm2 = %xmm6,%r2 =rr
# p_sign1  = Sign, xmm1 = r, xmm3 = %xmm7,%r2 =rr
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movapd	 %xmm6,p_temp(%rsp)		# Store rr
	movapd	 %xmm7,p_temp1(%rsp)		# Store rr
	movapd	 %xmm0,p_temp2(%rsp)		# Store r
	movapd	 %xmm1,p_temp3(%rsp)		# Store r


	movapd	.Lcossinarray+0x50(%rip),%xmm4		# s6
	movapd	.Lcossinarray+0x50(%rip),%xmm5		# s6
	movdqa	.Lcossinarray+0x20(%rip),%xmm8		# s3
	movdqa	.Lcossinarray+0x20(%rip),%xmm9		# s3

	movapd	%xmm2,%xmm10				# move x2 for x4
	movapd	%xmm3,%xmm11				# move x2 for x4

	mulpd	%xmm2,%xmm4				# x2s6
	mulpd	%xmm3,%xmm5				# x2s6
	mulpd	%xmm2,%xmm8				# x2s3
	mulpd	%xmm3,%xmm9				# x2s3

	mulpd	%xmm2,%xmm10				# x4
	mulpd	%xmm3,%xmm11				# x4

	addpd	.Lcossinarray+0x40(%rip),%xmm4		# s5+x2s6
	addpd	.Lcossinarray+0x40(%rip),%xmm5		# s5+x2s6
	addpd	.Lcossinarray+0x10(%rip),%xmm8		# s2+x2s3
	addpd	.Lcossinarray+0x10(%rip),%xmm9		# s2+x2s3

	movapd	%xmm2,%xmm12				# move x2 for x6
	movapd	%xmm3,%xmm13				# move x2 for x6

	mulpd	%xmm2,%xmm4				# x2(s5+x2s6)
	mulpd	%xmm3,%xmm5				# x2(s5+x2s6)
	mulpd	%xmm2,%xmm8				# x2(s2+x2s3)
	mulpd	%xmm3,%xmm9				# x2(s2+x2s3)

	mulpd	%xmm10,%xmm12				# x6
	mulpd	%xmm11,%xmm13				# x6

	addpd	.Lcossinarray+0x30(%rip),%xmm4		# s4+x2(s5+x2s6)
	addpd	.Lcossinarray+0x30(%rip),%xmm5		# s4+x2(s5+x2s6)
	addpd	.Lcossinarray(%rip),%xmm8		# s1+x2(s2+x2s3)
	addpd	.Lcossinarray(%rip),%xmm9		# s1+x2(s2+x2s3)

	mulpd	%xmm12,%xmm4				# x6(s4+x2(s5+x2s6))
	mulpd	%xmm13,%xmm5				# x6(s4+x2(s5+x2s6))

	movhlps	%xmm2,%xmm6				# move low x2 for x3 for sin term
	movhlps	%xmm3,%xmm7				# move low x2 for x3 for sin term
	mulsd	p_temp2+8(%rsp),%xmm6		# get low x3 for sin term
	mulsd	p_temp3+8(%rsp),%xmm7		# get low x3 for sin term

	mulpd 	.L__real_3fe0000000000000(%rip),%xmm2	# 0.5*x2 for sin and cos terms
	mulpd 	.L__real_3fe0000000000000(%rip),%xmm3	# 0.5*x2 for sin and cos terms

	addpd	%xmm8,%xmm4				# z
	addpd	%xmm9,%xmm5				# z

	movhlps	%xmm2,%xmm12				# move high 0.5*x2 for sin term
	movhlps	%xmm3,%xmm13				# move high 0.5*x2 for sin term
							# Reverse 12 and 2

	movhlps	%xmm4,%xmm8				# xmm8 = sin , xmm4 = cos
	movhlps	%xmm5,%xmm9				# xmm9 = sin , xmm5 = cos

	mulsd	%xmm6,%xmm8				# sin *x3
	mulsd	%xmm7,%xmm9				# sin *x3
	mulsd	%xmm10,%xmm4				# cos *x4
	mulsd	%xmm11,%xmm5				# cos *x4

	mulsd	p_temp+8(%rsp),%xmm12		# 0.5 * x2 * xx for sin term
	mulsd	p_temp1+8(%rsp),%xmm13		# 0.5 * x2 * xx for sin term
	movsd	%xmm2,%xmm6				# Keep high r for cos term
	movsd	%xmm3,%xmm7				# Keep high r for cos term

	subsd	.L__real_3ff0000000000000(%rip),%xmm2 	# -t=r-1.0
	subsd	.L__real_3ff0000000000000(%rip),%xmm3 	# -t=r-1.0

	subsd	%xmm12,%xmm8				# sin - 0.5 * x2 *xx
	subsd	%xmm13,%xmm9				# sin - 0.5 * x2 *xx

	movhlps	%xmm0,%xmm10				# move high x for x for sin term
	movhlps	%xmm1,%xmm11				# move high x for x for sin term
							# Reverse 10 and 0

	mulsd	p_temp(%rsp),%xmm0		# x * xx
	mulsd	p_temp1(%rsp),%xmm1		# x * xx

	movsd	%xmm2,%xmm12				# move -t for cos term
	movsd	%xmm3,%xmm13				# move -t for cos term

	addsd	.L__real_3ff0000000000000(%rip),%xmm2 	# 1+(-t)
	addsd	.L__real_3ff0000000000000(%rip),%xmm3 	# 1+(-t)
	addsd	p_temp+8(%rsp),%xmm8			# sin+xx
	addsd	p_temp1+8(%rsp),%xmm9			# sin+xx

	subsd	%xmm6,%xmm2				# (1-t) - r
	subsd	%xmm7,%xmm3				# (1-t) - r

	subsd	%xmm0,%xmm2				# ((1 + (-t)) - r) - x*xx
	subsd	%xmm1,%xmm3				# ((1 + (-t)) - r) - x*xx

	addsd	%xmm10,%xmm8				# sin + x
	addsd	%xmm11,%xmm9				# sin + x

	addsd   %xmm2,%xmm4				# cos+((1-t)-r - x*xx)
	addsd   %xmm3,%xmm5				# cos+((1-t)-r - x*xx)

	subsd   %xmm12,%xmm4				# cos+t
	subsd   %xmm13,%xmm5				# cos+t

	movlhps	%xmm8,%xmm4
	movlhps	%xmm9,%xmm5
	jmp 	.L__vrd4_cos_cleanup

.align 16
.Lcossin_sincos_piby4:					# changed from sincos_sincos
							# xmm1 is cossin and xmm0 is sincos
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# p_sign0  = Sign, xmm0 = r, xmm2 = %xmm6,%r2 =rr
# p_sign1  = Sign, xmm1 = r, xmm3 = %xmm7,%r2 =rr
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movapd	 %xmm6,p_temp(%rsp)		# Store rr
	movapd	 %xmm7,p_temp1(%rsp)		# Store rr
	movapd	 %xmm0,p_temp2(%rsp)		# Store r


	movapd	.Lcossinarray+0x50(%rip),%xmm4		# s6
	movapd	.Lsincosarray+0x50(%rip),%xmm5		# s6
	movdqa	.Lcossinarray+0x20(%rip),%xmm8		# s3
	movdqa	.Lsincosarray+0x20(%rip),%xmm9		# s3

	movapd	%xmm2,%xmm10				# move x2 for x4
	movapd	%xmm3,%xmm11				# move x2 for x4

	mulpd	%xmm2,%xmm4				# x2s6
	mulpd	%xmm3,%xmm5				# x2s6
	mulpd	%xmm2,%xmm8				# x2s3
	mulpd	%xmm3,%xmm9				# x2s3

	mulpd	%xmm2,%xmm10				# x4
	mulpd	%xmm3,%xmm11				# x4

	addpd	.Lcossinarray+0x40(%rip),%xmm4		# s5+x2s6
	addpd	.Lsincosarray+0x40(%rip),%xmm5		# s5+x2s6
	addpd	.Lcossinarray+0x10(%rip),%xmm8		# s2+x2s3
	addpd	.Lsincosarray+0x10(%rip),%xmm9		# s2+x2s3

	movapd	%xmm2,%xmm12				# move x2 for x6
	movapd	%xmm3,%xmm13				# move x2 for x6

	mulpd	%xmm2,%xmm4				# x2(s5+x2s6)
	mulpd	%xmm3,%xmm5				# x2(s5+x2s6)
	mulpd	%xmm2,%xmm8				# x2(s2+x2s3)
	mulpd	%xmm3,%xmm9				# x2(s2+x2s3)

	mulpd	%xmm10,%xmm12				# x6
	mulpd	%xmm11,%xmm13				# x6

	addpd	.Lcossinarray+0x30(%rip),%xmm4		# s4+x2(s5+x2s6)
	addpd	.Lsincosarray+0x30(%rip),%xmm5		# s4+x2(s5+x2s6)
	addpd	.Lcossinarray(%rip),%xmm8		# s1+x2(s2+x2s3)
	addpd	.Lsincosarray(%rip),%xmm9		# s1+x2(s2+x2s3)

	movhlps	%xmm11,%xmm11				# move high x4 for cos term	+

	mulpd	%xmm12,%xmm4				# x6(s4+x2(s5+x2s6))
	mulpd	%xmm13,%xmm5				# x6(s4+x2(s5+x2s6))

	movhlps	%xmm2,%xmm6				# move low x2 for x3 for sin term
	movsd	%xmm3,%xmm7				# move low x2 for x3 for sin term   	+
	mulsd	p_temp2+8(%rsp),%xmm6		# get low x3 for sin term
	mulsd	%xmm1,%xmm7				# get low x3 for sin term		+

	mulpd 	.L__real_3fe0000000000000(%rip),%xmm2	# 0.5*x2 for sin and cos terms
	mulpd 	.L__real_3fe0000000000000(%rip),%xmm3	# 0.5*x2 for sin and cos terms

	addpd	%xmm8,%xmm4				# z
	addpd	%xmm9,%xmm5				# z

	movhlps	%xmm2,%xmm12				# move high 0.5*x2 for sin term
	movhlps	%xmm3,%xmm13				# move high r for cos

	movhlps	%xmm4,%xmm8				# xmm8 = sin , xmm4 = cos
	movhlps	%xmm5,%xmm9				# xmm9 = cos , xmm5 = sin

	mulsd	%xmm6,%xmm8				# sin *x3
	mulsd	%xmm11,%xmm9				# cos *x4
	mulsd	%xmm10,%xmm4				# cos *x4
	mulsd	%xmm7,%xmm5				# sin *x3

	mulsd	p_temp+8(%rsp),%xmm12		# 0.5 * x2 * xx for sin term
	mulsd	p_temp1(%rsp),%xmm3		# 0.5 * x2 * xx for sin term

	movsd	%xmm2,%xmm6				# Keep high r for cos term
	movsd	%xmm13,%xmm7				# Keep high r for cos term

	subsd	.L__real_3ff0000000000000(%rip),%xmm2 	# -t=r-1.0
	subsd	.L__real_3ff0000000000000(%rip),%xmm13 	# -t=r-1.0

	subsd	%xmm12,%xmm8				# sin - 0.5 * x2 *xx
	subsd	%xmm3,%xmm5				# sin - 0.5 * x2 *xx

	movhlps	%xmm0,%xmm10				# move high x for x for sin term
	movhlps	%xmm1,%xmm11				# move high x for x*xx for cos term

	mulsd	p_temp(%rsp),%xmm0		# x * xx
	mulsd	p_temp1+8(%rsp),%xmm11		# x * xx

	movsd	%xmm2,%xmm12				# move -t for cos term
	movsd	%xmm13,%xmm3				# move -t for cos term

	addsd	.L__real_3ff0000000000000(%rip),%xmm2 	# 1+(-t)
	addsd	.L__real_3ff0000000000000(%rip),%xmm13 	# 1+(-t)

	addsd	p_temp+8(%rsp),%xmm8		# sin+xx
	addsd	p_temp1(%rsp),%xmm5		# sin+xx

	subsd	%xmm6,%xmm2				# (1-t) - r
	subsd	%xmm7,%xmm13				# (1-t) - r

	subsd	%xmm0,%xmm2				# ((1 + (-t)) - r) - x*xx
	subsd	%xmm11,%xmm13				# ((1 + (-t)) - r) - x*xx


	addsd	%xmm10,%xmm8				# sin + x
	addsd	%xmm1,%xmm5				# sin + x

	addsd   %xmm2,%xmm4				# cos+((1-t)-r - x*xx)
	addsd   %xmm13,%xmm9				# cos+((1-t)-r - x*xx)

	subsd   %xmm12,%xmm4				# cos+t
	subsd   %xmm3,%xmm9				# cos+t

	movlhps	%xmm8,%xmm4
	movlhps	%xmm9,%xmm5
	jmp 	.L__vrd4_cos_cleanup

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lcoscos_sinsin_piby4:

	movapd	%xmm2,%xmm10					# x2
	movapd	%xmm3,%xmm11					# x2

	movdqa	.Lsinarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lcosarray+0x50(%rip),%xmm5			# c6
	movapd	.Lsinarray+0x20(%rip),%xmm8			# c3
	movapd	.Lcosarray+0x20(%rip),%xmm9			# c3

	movapd	 %xmm2,p_temp2(%rsp)			# store x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11	# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2
	movapd	 %xmm11,p_temp3(%rsp)			# store r
	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	mulpd	%xmm2,%xmm10					# x4
	subpd	.L__real_3ff0000000000000(%rip),%xmm11	# -t=r-1.0

	movapd	%xmm2,%xmm12					# copy of x2 for 0.5*x2
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lsinarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lcosarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lsinarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lcosarray+0x10(%rip),%xmm9			# c2+x2C3

	addpd   .L__real_3ff0000000000000(%rip),%xmm11	# 1 + (-t)

	mulpd	%xmm2,%xmm10					# x6
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	.L__real_3fe0000000000000(%rip),%xmm12	# 0.5 *x2
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lsinarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lcosarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lcosarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm10,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zs
	addpd	%xmm9,%xmm5					# zc

	mulpd	%xmm0,%xmm2					# x3 recalculate
	mulpd	%xmm3,%xmm3					# x4 recalculate

	movapd   p_temp3(%rsp),%xmm13			# r

	mulpd	%xmm6,%xmm12					# 0.5 * x2 *xx
	mulpd	%xmm1,%xmm7					# x * xx

	subpd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x3 * zs
	mulpd	%xmm3,%xmm5					# x4 * zc

	subpd	%xmm12,%xmm4					# -0.5 * x2 *xx
	subpd   %xmm7,%xmm11					# ((1 + (-t)) - r) - x*xx

	addpd	%xmm6,%xmm4					# x3 * zs +xx
	addpd   %xmm11,%xmm5					# x4*zc + (((1 + (-t)) - r) - x*xx)

	subpd	.L__real_3ff0000000000000(%rip),%xmm13	# t relaculate, -t = r-1
	addpd	%xmm0,%xmm4					# +x
	subpd   %xmm13,%xmm5					# + t

	jmp 	.L__vrd4_cos_cleanup

.align 16
.Lsinsin_coscos_piby4:

	movapd	%xmm2,%xmm10					# x2
	movapd	%xmm3,%xmm11					# x2

	movdqa	.Lcosarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lsinarray+0x50(%rip),%xmm5			# c6
	movapd	.Lcosarray+0x20(%rip),%xmm8			# c3
	movapd	.Lsinarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10	# r = 0.5 *x2
	movapd	 %xmm3,p_temp3(%rsp)			# store x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2
	movapd	 %xmm10,p_temp2(%rsp)			# store r
	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subpd	.L__real_3ff0000000000000(%rip),%xmm10	# -t=r-1.0
	mulpd	%xmm3,%xmm11					# x4

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for 0.5*x2

	addpd	.Lcosarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lsinarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lcosarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lsinarray+0x10(%rip),%xmm9			# c2+x2C3

	addpd   .L__real_3ff0000000000000(%rip),%xmm10	# 1 + (-t)

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm11					# x6

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	.L__real_3fe0000000000000(%rip),%xmm13	# 0.5 *x2

	addpd	.Lcosarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lcosarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lsinarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm11,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zc
	addpd	%xmm9,%xmm5					# zs

	mulpd	%xmm2,%xmm2					# x4 recalculate
	mulpd	%xmm1,%xmm3					# x3 recalculate

	movapd   p_temp2(%rsp),%xmm12			# r

	mulpd	%xmm0,%xmm6					# x * xx
	mulpd	%xmm7,%xmm13					# 0.5 * x2 *xx
	subpd   %xmm12,%xmm10					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x4 * zc
	mulpd	%xmm3,%xmm5					# x3 * zs

	subpd   %xmm6,%xmm10					# ((1 + (-t)) - r) - x*xx;;;;;;;;;;;;;;;;;;;;;
	subpd	%xmm13,%xmm5					# -0.5 * x2 *xx
	addpd   %xmm10,%xmm4					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addpd	%xmm7,%xmm5					# +xx
	subpd	.L__real_3ff0000000000000(%rip),%xmm12	# t relaculate, -t = r-1
	addpd	%xmm1,%xmm5					# +x
	subpd   %xmm12,%xmm4					# + t

	jmp 	.L__vrd4_cos_cleanup

#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.align 16
.Lcoscos_cossin_piby4:				#Derive from cossin_coscos
	movapd	%xmm2,%xmm10					# r
	movapd	%xmm3,%xmm11					# r

	movdqa	.Lsincosarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lcosarray+0x50(%rip),%xmm5			# c6
	movapd	.Lsincosarray+0x20(%rip),%xmm8			# c3
	movapd	.Lcosarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10		# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11		# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm10,p_temp2(%rsp)			# r
	movapd	 %xmm11,p_temp3(%rsp)			# r
	movapd	 %xmm6,p_temp(%rsp)			# rr
	movhlps	%xmm10,%xmm10					# get upper r for t for cos

	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subsd	.L__real_3ff0000000000000(%rip),%xmm10	# -t=r-1.0  for cos
	subpd	.L__real_3ff0000000000000(%rip),%xmm11	# -t=r-1.0

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lsincosarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lcosarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lsincosarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lcosarray+0x10(%rip),%xmm9			# c2+x2C3

	addsd   .L__real_3ff0000000000000(%rip),%xmm10	# 1 + (-t)
	addpd   .L__real_3ff0000000000000(%rip),%xmm11	# 1 + (-t)

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lsincosarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lcosarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lsincosarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lcosarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zczs
	addpd	%xmm9,%xmm5					# zc

	movsd	%xmm0,%xmm8					# lower x for sin
	mulsd	%xmm2,%xmm8					# lower x3 for sin

	mulpd	%xmm2,%xmm2					# x4
	mulpd	%xmm3,%xmm3					# upper x4 for cos
	movsd	%xmm8,%xmm2					# lower x3 for sin

	movsd	 %xmm6,%xmm9					# lower xx
								# note using odd reg

	movlpd   p_temp2+8(%rsp),%xmm12		# upper r for cos term
	movapd   p_temp3(%rsp),%xmm13			# r

	mulpd	%xmm0,%xmm6					# x * xx for upper cos term
	mulpd	%xmm1,%xmm7					# x * xx
	movhlps	%xmm6,%xmm6
	mulsd	p_temp2(%rsp),%xmm9 			# xx * 0.5*x2 for sin term

	subsd   %xmm12,%xmm10					# (1 + (-t)) - r
	subpd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x4 * zc
	mulpd	%xmm3,%xmm5					# x4 * zc
								# x3 * zs

	movhlps	%xmm4,%xmm8					# xmm8= cos, xmm4= sin

	subsd	%xmm9,%xmm4					# x3zs - 0.5*x2*xx

	subsd   %xmm6,%xmm10					# ((1 + (-t)) - r) - x*xx
	subpd   %xmm7,%xmm11					# ((1 + (-t)) - r) - x*xx

	addsd   %xmm10,%xmm8					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addpd   %xmm11,%xmm5					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp(%rsp),%xmm4			# +xx


	subsd	.L__real_3ff0000000000000(%rip),%xmm12	# -t = r-1
	subpd	.L__real_3ff0000000000000(%rip),%xmm13	# -t = r-1

	subsd   %xmm12,%xmm8					# + t
	addsd	%xmm0,%xmm4					# +x
	subpd   %xmm13,%xmm5					# + t

	movlhps	%xmm8,%xmm4

	jmp	.L__vrd4_cos_cleanup

.align 16
.Lcoscos_sincos_piby4:		#Derive from sincos_coscos
	movapd	%xmm2,%xmm10					# r
	movapd	%xmm3,%xmm11					# r

	movdqa	.Lcossinarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lcosarray+0x50(%rip),%xmm5			# c6
	movapd	.Lcossinarray+0x20(%rip),%xmm8			# c3
	movapd	.Lcosarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10	# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11	# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm10,p_temp2(%rsp)			# r
	movapd	 %xmm11,p_temp3(%rsp)			# r
	movapd	 %xmm6,p_temp(%rsp)			# rr

	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subsd	.L__real_3ff0000000000000(%rip),%xmm10	# -t=r-1.0 for cos
	subpd	.L__real_3ff0000000000000(%rip),%xmm11	# -t=r-1.0

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lcossinarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lcosarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lcossinarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lcosarray+0x10(%rip),%xmm9			# c2+x2C3

	addsd   .L__real_3ff0000000000000(%rip),%xmm10	# 1 + (-t) for cos
	addpd   .L__real_3ff0000000000000(%rip),%xmm11	# 1 + (-t)

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lcossinarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lcosarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lcossinarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lcosarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zszc
	addpd	%xmm9,%xmm5					# z

	mulpd	%xmm0,%xmm2					# upper x3 for sin
	mulsd	%xmm0,%xmm2					# lower x4 for cos
	mulpd	%xmm3,%xmm3					# x4

	movhlps	%xmm6,%xmm9					# upper xx for sin term
								# note using odd reg

	movlpd  p_temp2(%rsp),%xmm12			# lower r for cos term
	movapd  p_temp3(%rsp),%xmm13			# r


	mulpd	%xmm0,%xmm6					# x * xx for lower cos term
	mulpd	%xmm1,%xmm7					# x * xx

	mulsd	p_temp2+8(%rsp),%xmm9 			# xx * 0.5*x2 for upper sin term

	subsd   %xmm12,%xmm10					# (1 + (-t)) - r
	subpd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# lower=x4 * zc
								# upper=x3 * zs
	mulpd	%xmm3,%xmm5
								# x4 * zc

	movhlps	%xmm4,%xmm8					# xmm8= sin, xmm4= cos
	subsd	%xmm9,%xmm8					# x3zs - 0.5*x2*xx


	subsd   %xmm6,%xmm10					# ((1 + (-t)) - r) - x*xx
	subpd   %xmm7,%xmm11					# ((1 + (-t)) - r) - x*xx

	addsd   %xmm10,%xmm4					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addpd   %xmm11,%xmm5					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp+8(%rsp),%xmm8			# +xx

	movhlps	%xmm0,%xmm0					# upper x for sin
	subsd	.L__real_3ff0000000000000(%rip),%xmm12	# -t = r-1
	subpd	.L__real_3ff0000000000000(%rip),%xmm13	# -t = r-1

	subsd   %xmm12,%xmm4					# + t
	subpd   %xmm13,%xmm5					# + t
	addsd	%xmm0,%xmm8					# +x

	movlhps	%xmm8,%xmm4

	jmp 	.L__vrd4_cos_cleanup

.align 16
.Lcossin_coscos_piby4:
	movapd	%xmm2,%xmm10					# r
	movapd	%xmm3,%xmm11					# r

	movdqa	.Lcosarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lsincosarray+0x50(%rip),%xmm5			# c6
	movapd	.Lcosarray+0x20(%rip),%xmm8			# c3
	movapd	.Lsincosarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10		# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11		# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm10,p_temp2(%rsp)			# r
	movapd	 %xmm11,p_temp3(%rsp)			# r
	movapd	 %xmm7,p_temp1(%rsp)			# rr
	movhlps	%xmm11,%xmm11					# get upper r for t for cos

	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subpd	.L__real_3ff0000000000000(%rip),%xmm10	# -t=r-1.0
	subsd	.L__real_3ff0000000000000(%rip),%xmm11	# -t=r-1.0 for cos

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lcosarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lsincosarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lcosarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lsincosarray+0x10(%rip),%xmm9			# c2+x2C3

	addpd   .L__real_3ff0000000000000(%rip),%xmm10		# 1 + (-t)	;trash t
	addsd   .L__real_3ff0000000000000(%rip),%xmm11		# 1 + (-t)	;trash t

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lcosarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lsincosarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lcosarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lsincosarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zc
	addpd	%xmm9,%xmm5					# zcs

	movsd	%xmm1,%xmm9					# lower x for sin
	mulsd	%xmm3,%xmm9					# lower x3 for sin

	mulpd	%xmm2,%xmm2					# x4
	mulpd	%xmm3,%xmm3					# upper x4 for cos
	movsd	%xmm9,%xmm3					# lower x3 for sin

	movsd	 %xmm7,%xmm8					# lower xx
								# note using even reg

	movapd   p_temp2(%rsp),%xmm12			# r
	movlpd   p_temp3+8(%rsp),%xmm13		# upper r for cos term

	mulpd	%xmm0,%xmm6					# x * xx
	mulpd	%xmm1,%xmm7					# x * xx for upper cos term
	movhlps	%xmm7,%xmm7
	mulsd	p_temp3(%rsp),%xmm8 			# xx * 0.5*x2 for sin term

	subpd   %xmm12,%xmm10					# (1 + (-t)) - r
	subsd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x4 * zc
	mulpd	%xmm3,%xmm5					# x4 * zc
								# x3 * zs

	movhlps	%xmm5,%xmm9					# xmm9= cos, xmm5= sin

	subsd	%xmm8,%xmm5					# x3zs - 0.5*x2*xx

	subpd   %xmm6,%xmm10					# ((1 + (-t)) - r) - x*xx
	subsd   %xmm7,%xmm11					# ((1 + (-t)) - r) - x*xx

	addpd   %xmm10,%xmm4					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd   %xmm11,%xmm9					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp1(%rsp),%xmm5			# +xx


	subpd	.L__real_3ff0000000000000(%rip),%xmm12		# t relaculate, -t = r-1
	subsd	.L__real_3ff0000000000000(%rip),%xmm13		# t relaculate, -t = r-1

	subpd   %xmm12,%xmm4					# + t
	subsd   %xmm13,%xmm9					# + t
	addsd	%xmm1,%xmm5					# +x

	movlhps	%xmm9,%xmm5

	jmp 	.L__vrd4_cos_cleanup

.align 16
.Lcossin_sinsin_piby4:		# Derived from sincos_sinsin
	movapd	%xmm2,%xmm10					# x2
	movapd	%xmm3,%xmm11					# x2

	movdqa	.Lsinarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lsincosarray+0x50(%rip),%xmm5			# c6
	movapd	.Lsinarray+0x20(%rip),%xmm8			# c3
	movapd	.Lsincosarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10		# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11		# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm11,p_temp3(%rsp)			# r
	movapd	 %xmm7,p_temp1(%rsp)			# rr

	movhlps	%xmm11,%xmm11
	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subsd	.L__real_3ff0000000000000(%rip),%xmm11	# -t=r-1.0 for cos

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lsinarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lsincosarray+0x40(%rip),%xmm5		# c5+x2c6
	addpd	.Lsinarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lsincosarray+0x10(%rip),%xmm9			# c2+x2C3

	mulpd	%xmm6,%xmm10					# 0.5*x2*xx
	addsd   .L__real_3ff0000000000000(%rip),%xmm11	# 1 + (-t) for cos

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lsinarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lsincosarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lsincosarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zs
	addpd	%xmm9,%xmm5					# zczs

	movsd	%xmm3,%xmm12
	mulsd	%xmm1,%xmm12					# low x3 for sin

	mulpd	%xmm0,%xmm2					# x3
	mulpd	%xmm3,%xmm3					# high x4 for cos
	movsd	%xmm12,%xmm3					# low x3 for sin

	movhlps	%xmm1,%xmm8					# upper x for cos term
								# note using even reg
	movlpd  p_temp3+8(%rsp),%xmm13			# upper r for cos term

	mulsd	p_temp1+8(%rsp),%xmm8			# x * xx for upper cos term

	mulsd	p_temp3(%rsp),%xmm7 			# xx * 0.5*x2 for lower sin term

	subsd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x3 * zs
	mulpd	%xmm3,%xmm5					# lower=x4 * zc
								# upper=x3 * zs

	movhlps	%xmm5,%xmm9					# xmm9= cos, xmm5= sin

	subsd	%xmm7,%xmm5					# x3zs - 0.5*x2*xx

	subsd   %xmm8,%xmm11					# ((1 + (-t)) - r) - x*xx

	subpd	%xmm10,%xmm4					# x3*zs - 0.5*x2*xx
	addsd   %xmm11,%xmm9					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp1(%rsp),%xmm5			# +xx

	addpd	%xmm6,%xmm4					# +xx
	subsd	.L__real_3ff0000000000000(%rip),%xmm13	# -t = r-1


	addsd	%xmm1,%xmm5					# +x
	addpd	%xmm0,%xmm4					# +x
	subsd   %xmm13,%xmm9					# + t

	movlhps	%xmm9,%xmm5

	jmp 	.L__vrd4_cos_cleanup

.align 16
.Lsincos_coscos_piby4:
	movapd	%xmm2,%xmm10					# r
	movapd	%xmm3,%xmm11					# r

	movdqa	.Lcosarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lcossinarray+0x50(%rip),%xmm5			# c6
	movapd	.Lcosarray+0x20(%rip),%xmm8			# c3
	movapd	.Lcossinarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10		# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11		# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm10,p_temp2(%rsp)			# r
	movapd	 %xmm11,p_temp3(%rsp)			# r
	movapd	 %xmm7,p_temp1(%rsp)			# rr

	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subpd	.L__real_3ff0000000000000(%rip),%xmm10	# -t=r-1.0
	subsd	.L__real_3ff0000000000000(%rip),%xmm11	# -t=r-1.0 for cos

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lcosarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lcossinarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lcosarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lcossinarray+0x10(%rip),%xmm9			# c2+x2C3

	addpd   .L__real_3ff0000000000000(%rip),%xmm10	# 1 + (-t)
	addsd   .L__real_3ff0000000000000(%rip),%xmm11	# 1 + (-t) for cos

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lcosarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lcossinarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lcosarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lcossinarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zc
	addpd	%xmm9,%xmm5					# zszc

	mulpd	%xmm2,%xmm2					# x4
	mulpd	%xmm1,%xmm3					# upper x3 for sin
	mulsd	%xmm1,%xmm3					# lower x4 for cos

	movhlps	%xmm7,%xmm8					# upper xx for sin term
								# note using even reg

	movapd  p_temp2(%rsp),%xmm12			# r
	movlpd  p_temp3(%rsp),%xmm13			# lower r for cos term

	mulpd	%xmm0,%xmm6					# x * xx
	mulpd	%xmm1,%xmm7					# x * xx for lower cos term

	mulsd	p_temp3+8(%rsp),%xmm8 			# xx * 0.5*x2 for upper sin term

	subpd   %xmm12,%xmm10					# (1 + (-t)) - r
	subsd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x4 * zc
	mulpd	%xmm3,%xmm5					# lower=x4 * zc
								# upper=x3 * zs

	movhlps	%xmm5,%xmm9					# xmm9= sin, xmm5= cos

	subsd	%xmm8,%xmm9					# x3zs - 0.5*x2*xx

	subpd   %xmm6,%xmm10					# ((1 + (-t)) - r) - x*xx
	subsd   %xmm7,%xmm11					# ((1 + (-t)) - r) - x*xx

	addpd   %xmm10,%xmm4					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd   %xmm11,%xmm5					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp1+8(%rsp),%xmm9			# +xx

	movhlps	%xmm1,%xmm1					# upper x for sin
	subpd	.L__real_3ff0000000000000(%rip),%xmm12	# -t = r-1
	subsd	.L__real_3ff0000000000000(%rip),%xmm13	# -t = r-1

	subpd   %xmm12,%xmm4					# + t
	subsd   %xmm13,%xmm5					# + t
	addsd	%xmm1,%xmm9					# +x

	movlhps	%xmm9,%xmm5

	jmp 	.L__vrd4_cos_cleanup


.align 16
.Lsincos_sinsin_piby4:		# Derived from sincos_coscos
	movapd	%xmm2,%xmm10					# r
	movapd	%xmm3,%xmm11					# r

	movdqa	.Lsinarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lcossinarray+0x50(%rip),%xmm5			# c6
	movapd	.Lsinarray+0x20(%rip),%xmm8			# c3
	movapd	.Lcossinarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10		# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11		# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm11,p_temp3(%rsp)			# r
	movapd	 %xmm7,p_temp1(%rsp)			# rr

	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subsd	.L__real_3ff0000000000000(%rip),%xmm11	# -t=r-1.0 for cos

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lsinarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lcossinarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lsinarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lcossinarray+0x10(%rip),%xmm9			# c2+x2C3

	mulpd	%xmm6,%xmm10					# 0.5x2*xx
	addsd   .L__real_3ff0000000000000(%rip),%xmm11	# 1 + (-t) for cos

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lsinarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lcossinarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lcossinarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zs
	addpd	%xmm9,%xmm5					# zszc

	mulpd	%xmm0,%xmm2					# x3
	mulpd	%xmm1,%xmm3					# upper x3 for sin
	mulsd	%xmm1,%xmm3					# lower x4 for cos

	movhlps	%xmm7,%xmm8					# upper xx for sin term
								# note using even reg

	movlpd  p_temp3(%rsp),%xmm13			# lower r for cos term

	mulpd	%xmm1,%xmm7					# x * xx for lower cos term

	mulsd	p_temp3+8(%rsp),%xmm8 			# xx * 0.5*x2 for upper sin term

	subsd   %xmm13,%xmm11					# (1 + (-t)) - r

	mulpd	%xmm2,%xmm4					# x3 * zs
	mulpd	%xmm3,%xmm5					# lower=x4 * zc
								# upper=x3 * zs

	movhlps	%xmm5,%xmm9					# xmm9= sin, xmm5= cos

	subsd	%xmm8,%xmm9					# x3zs - 0.5*x2*xx

	subsd   %xmm7,%xmm11					# ((1 + (-t)) - r) - x*xx

	subpd	%xmm10,%xmm4					# x3*zs - 0.5*x2*xx
	addsd   %xmm11,%xmm5					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp1+8(%rsp),%xmm9			# +xx

	movhlps	%xmm1,%xmm1					# upper x for sin
	addpd	%xmm6,%xmm4					# +xx
	subsd	.L__real_3ff0000000000000(%rip),%xmm13	# -t = r-1

	addsd	%xmm1,%xmm9					# +x
	addpd	%xmm0,%xmm4					# +x
	subsd   %xmm13,%xmm5					# + t

	movlhps	%xmm9,%xmm5

	jmp 	.L__vrd4_cos_cleanup


.align 16
.Lsinsin_cossin_piby4:		# Derived from sincos_sinsin
	movapd	%xmm2,%xmm10					# x2
	movapd	%xmm3,%xmm11					# x2

	movdqa	.Lsincosarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lsinarray+0x50(%rip),%xmm5			# c6
	movapd	.Lsincosarray+0x20(%rip),%xmm8			# c3
	movapd	.Lsinarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10	# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11	# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm10,p_temp2(%rsp)			# x2
	movapd	 %xmm6,p_temp(%rsp)			# xx

	movhlps	%xmm10,%xmm10
	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subsd	.L__real_3ff0000000000000(%rip),%xmm10	# -t=r-1.0 for cos

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lsincosarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lsinarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lsincosarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lsinarray+0x10(%rip),%xmm9			# c2+x2C3

	mulpd	%xmm7,%xmm11					# 0.5*x2*xx
	addsd   .L__real_3ff0000000000000(%rip),%xmm10	# 1 + (-t) for cos

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lsincosarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lsincosarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lsinarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zczs
	addpd	%xmm9,%xmm5					# zs


	movsd	%xmm2,%xmm13
	mulsd	%xmm0,%xmm13					# low x3 for sin

	mulpd	%xmm1,%xmm3					# x3
	mulpd	%xmm2,%xmm2					# high x4 for cos
	movsd	%xmm13,%xmm2					# low x3 for sin


	movhlps	%xmm0,%xmm9					# upper x for cos term								; note using even reg
	movlpd  p_temp2+8(%rsp),%xmm12			# upper r for cos term
	mulsd	p_temp+8(%rsp),%xmm9			# x * xx for upper cos term
	mulsd	p_temp2(%rsp),%xmm6 			# xx * 0.5*x2 for lower sin term
	subsd   %xmm12,%xmm10					# (1 + (-t)) - r
	mulpd	%xmm3,%xmm5					# x3 * zs
	mulpd	%xmm2,%xmm4					# lower=x4 * zc
								# upper=x3 * zs

	movhlps	%xmm4,%xmm8					# xmm8= cos, xmm4= sin
	subsd	%xmm6,%xmm4					# x3zs - 0.5*x2*xx

	subsd   %xmm9,%xmm10					# ((1 + (-t)) - r) - x*xx

	subpd	%xmm11,%xmm5					# x3*zs - 0.5*x2*xx

	addsd   %xmm10,%xmm8					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp(%rsp),%xmm4			# +xx

	addpd	%xmm7,%xmm5					# +xx
	subsd	.L__real_3ff0000000000000(%rip),%xmm12	# -t = r-1

	addsd	%xmm0,%xmm4					# +x
	addpd	%xmm1,%xmm5					# +x
	subsd   %xmm12,%xmm8					# + t
	movlhps	%xmm8,%xmm4

	jmp 	.L__vrd4_cos_cleanup

.align 16
.Lsinsin_sincos_piby4:		# Derived from sincos_coscos

	movapd	%xmm2,%xmm10					# x2
	movapd	%xmm3,%xmm11					# x2

	movdqa	.Lcossinarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lsinarray+0x50(%rip),%xmm5			# c6
	movapd	.Lcossinarray+0x20(%rip),%xmm8			# c3
	movapd	.Lsinarray+0x20(%rip),%xmm9			# c3

	mulpd	.L__real_3fe0000000000000(%rip),%xmm10		# r = 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm11		# r = 0.5 *x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2

	movapd	 %xmm10,p_temp2(%rsp)			# r
	movapd	 %xmm6,p_temp(%rsp)			# rr

	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	subsd	.L__real_3ff0000000000000(%rip),%xmm10	# -t=r-1.0 for cos

	movapd	%xmm2,%xmm12					# copy of x2 for x4
	movapd	%xmm3,%xmm13					# copy of x2 for x4

	addpd	.Lcossinarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lsinarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lcossinarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lsinarray+0x10(%rip),%xmm9			# c2+x2C3

	mulpd	%xmm7,%xmm11					# 0.5x2*xx
	addsd   .L__real_3ff0000000000000(%rip),%xmm10	# 1 + (-t) for cos

	mulpd	%xmm2,%xmm12					# x4
	mulpd	%xmm3,%xmm13					# x4

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	%xmm2,%xmm12					# x6
	mulpd	%xmm3,%xmm13					# x6

	addpd	.Lcossinarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lcossinarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lsinarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm12,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm13,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zs
	addpd	%xmm9,%xmm5					# zszc

	mulpd	%xmm1,%xmm3					# x3
	mulpd	%xmm0,%xmm2					# upper x3 for sin
	mulsd	%xmm0,%xmm2					# lower x4 for cos

	movhlps	%xmm6,%xmm9					# upper xx for sin term
								# note using even reg

	movlpd  p_temp2(%rsp),%xmm12			# lower r for cos term

	mulpd	%xmm0,%xmm6					# x * xx for lower cos term

	mulsd	p_temp2+8(%rsp),%xmm9 			# xx * 0.5*x2 for upper sin term

	subsd   %xmm12,%xmm10					# (1 + (-t)) - r

	mulpd	%xmm3,%xmm5					# x3 * zs
	mulpd	%xmm2,%xmm4					# lower=x4 * zc
								# upper=x3 * zs

	movhlps	%xmm4,%xmm8					# xmm9= sin, xmm5= cos

	subsd	%xmm9,%xmm8					# x3zs - 0.5*x2*xx

	subsd   %xmm6,%xmm10					# ((1 + (-t)) - r) - x*xx

	subpd	%xmm11,%xmm5					# x3*zs - 0.5*x2*xx
	addsd   %xmm10,%xmm4					# x4*zc + (((1 + (-t)) - r) - x*xx)
	addsd	p_temp+8(%rsp),%xmm8			# +xx

	movhlps	%xmm0,%xmm0					# upper x for sin
	addpd	%xmm7,%xmm5					# +xx
	subsd	.L__real_3ff0000000000000(%rip),%xmm12	# -t = r-1


	addsd	%xmm0,%xmm8					# +x
	addpd	%xmm1,%xmm5					# +x
	subsd   %xmm12,%xmm4					# + t

	movlhps	%xmm8,%xmm4

	jmp 	.L__vrd4_cos_cleanup


.align 16
.Lsinsin_sinsin_piby4:
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
# p_sign0  = Sign, xmm0 = r, xmm2 = %xmm6,%r2 =rr
# p_sign1  = Sign, xmm1 = r, xmm3 = %xmm7,%r2 =rr
#;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	movapd	%xmm2,%xmm10					# x2
	movapd	%xmm3,%xmm11					# x2

	movdqa	.Lsinarray+0x50(%rip),%xmm4			# c6
	movdqa	.Lsinarray+0x50(%rip),%xmm5			# c6
	movapd	.Lsinarray+0x20(%rip),%xmm8			# c3
	movapd	.Lsinarray+0x20(%rip),%xmm9			# c3

	movapd	 %xmm2,p_temp2(%rsp)			# copy of x2
	movapd	 %xmm3,p_temp3(%rsp)			# copy of x2

	mulpd	%xmm2,%xmm4					# c6*x2
	mulpd	%xmm3,%xmm5					# c6*x2
	mulpd	%xmm2,%xmm8					# c3*x2
	mulpd	%xmm3,%xmm9					# c3*x2

	mulpd	%xmm2,%xmm10					# x4
	mulpd	%xmm3,%xmm11					# x4

	addpd	.Lsinarray+0x40(%rip),%xmm4			# c5+x2c6
	addpd	.Lsinarray+0x40(%rip),%xmm5			# c5+x2c6
	addpd	.Lsinarray+0x10(%rip),%xmm8			# c2+x2C3
	addpd	.Lsinarray+0x10(%rip),%xmm9			# c2+x2C3

	mulpd	%xmm2,%xmm10					# x6
	mulpd	%xmm3,%xmm11					# x6

	mulpd	%xmm2,%xmm4					# x2(c5+x2c6)
	mulpd	%xmm3,%xmm5					# x2(c5+x2c6)
	mulpd	%xmm2,%xmm8					# x2(c2+x2C3)
	mulpd	%xmm3,%xmm9					# x2(c2+x2C3)

	mulpd	.L__real_3fe0000000000000(%rip),%xmm2		# 0.5 *x2
	mulpd	.L__real_3fe0000000000000(%rip),%xmm3		# 0.5 *x2

	addpd	.Lsinarray+0x30(%rip),%xmm4			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray+0x30(%rip),%xmm5			# c4 + x2(c5+x2c6)
	addpd	.Lsinarray(%rip),%xmm8			# c1 + x2(c2+x2C3)
	addpd	.Lsinarray(%rip),%xmm9			# c1 + x2(c2+x2C3)

	mulpd	%xmm6,%xmm2					# 0.5 * x2 *xx
	mulpd	%xmm7,%xmm3					# 0.5 * x2 *xx

	mulpd	%xmm10,%xmm4					# x6(c4 + x2(c5+x2c6))
	mulpd	%xmm11,%xmm5					# x6(c4 + x2(c5+x2c6))

	addpd	%xmm8,%xmm4					# zs
	addpd	%xmm9,%xmm5					# zs

	movapd	p_temp2(%rsp),%xmm10			# x2
	movapd	p_temp3(%rsp),%xmm11			# x2

	mulpd	%xmm0,%xmm10					# x3
	mulpd	%xmm1,%xmm11					# x3

	mulpd	%xmm10,%xmm4					# x3 * zs
	mulpd	%xmm11,%xmm5					# x3 * zs

	subpd	%xmm2,%xmm4					# -0.5 * x2 *xx
	subpd	%xmm3,%xmm5					# -0.5 * x2 *xx

	addpd	%xmm6,%xmm4					# +xx
	addpd	%xmm7,%xmm5					# +xx

	addpd	%xmm0,%xmm4					# +x
	addpd	%xmm1,%xmm5					# +x

	jmp 	.L__vrd4_cos_cleanup
