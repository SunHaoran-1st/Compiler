.data
temp_space:.space 6500
nextline:.asciiz "\n"
str1:.asciiz "testnum[2]?=?"
str2:.asciiz "testnum[1]?=?"
str3:.asciiz "testnum[3]?=?"
str4:.asciiz "testnum[0]?=?"
str5:.asciiz "glist[a]?=?"
str6:.asciiz "**********1***********"
str7:.asciiz "glist[a]?=?"
str8:.asciiz "**********2?**********"
str9:.asciiz "glist[a]?=?"
str10:.asciiz "**********?3?***********"
str11:.asciiz "glist[a]?=?"
str12:.asciiz "**********?4?*********"
str13:.asciiz "glist[a]?=?"
str14:.asciiz "**********?5?***********"
str15:.asciiz "glist[a]?=?"
str16:.asciiz "*********************"
.text
add $fp,$sp,4
j main
main:
li $t8,0
la $t9,temp_space
sw $t8,128($t9)
li $t8,80
li $t9,8
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t0,temp_space($t8)
li $t8,80
mul $t0,$t0,4
add $t8,$t8,$t0
lw $t1,temp_space($t8)
li $v0,4
la $a0,str1
syscall
li $v0,1
move $a0,$t1
syscall
li $v0,4
la $a0,nextline
syscall
li $t8,80
li $t9,1
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t0,temp_space($t8)
li $v0,4
la $a0,str2
syscall
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,nextline
syscall
li $t8,80
li $t9,5
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t0,temp_space($t8)
li $t8,80
mul $t0,$t0,4
add $t8,$t8,$t0
lw $t1,temp_space($t8)
li $t8,80
li $t9,9
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t0,temp_space($t8)
move $t8,$t1
move $t9,$t0
add $t2,$t8,$t9
li $t8,80
mul $t2,$t2,4
add $t8,$t8,$t2
lw $t0,temp_space($t8)
li $v0,4
la $a0,str3
syscall
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,nextline
syscall
li $t8,80
li $t9,0
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t0,temp_space($t8)
li $v0,4
la $a0,str4
syscall
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,nextline
syscall
li $t8,1
la $t9,temp_space
sw $t8,120($t9)
label_0:
la $s5,temp_space
lw $s6,120($s5)
li $s7,10
BGE $s6,$s7,label_1
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
sub $t0,$t8,$t9
li $t8,0
mul $t0,$t0,4
add $t8,$t8,$t0
lw $t1,temp_space($t8)
move $t8,$t1
li $t9,1
add $t0,$t8,$t9
la $s6,temp_space
lw $s7,120($s6)
li $s6,0
mul $s7,$s7,4
add $s6,$s6,$s7
sw $t0,temp_space($s6)
li $t8,0
la $s7,temp_space
lw $t9,120($s7)
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t0,temp_space($t8)
li $v0,4
la $a0,str5
syscall
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,nextline
syscall
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
add $t0,$t8,$t9
la $t8,temp_space
sw $t0,120($t8)
j label_0
label_1:
li $v0,4
la $a0,str6
syscall
li $v0,4
la $a0,nextline
syscall
li $t8,1
la $t9,temp_space
sw $t8,120($t9)
label_2:
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t0,$t8,$t9
move $t8,$t0
li $t9,10
add $t1,$t8,$t9
BEQ $t1,$0,label_3
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
sub $t0,$t8,$t9
li $t8,0
mul $t0,$t0,4
add $t8,$t8,$t0
lw $t2,temp_space($t8)
move $t8,$t2
li $t9,1
add $t0,$t8,$t9
la $s6,temp_space
lw $s7,120($s6)
li $s6,0
mul $s7,$s7,4
add $s6,$s6,$s7
sw $t0,temp_space($s6)
li $t8,0
la $s7,temp_space
lw $t9,120($s7)
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t0,temp_space($t8)
li $v0,4
la $a0,str7
syscall
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,nextline
syscall
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
add $t0,$t8,$t9
la $t8,temp_space
sw $t0,120($t8)
j label_2
label_3:
li $v0,4
la $a0,str8
syscall
li $v0,4
la $a0,nextline
syscall
li $t8,5
la $t9,temp_space
sw $t8,120($t9)
label_4:
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t0,$t8,$t9
BEQ $t0,$0,label_5
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
sub $t2,$t8,$t9
li $t8,0
mul $t2,$t2,4
add $t8,$t8,$t2
lw $t3,temp_space($t8)
move $t8,$t3
li $t9,1
add $t2,$t8,$t9
la $s6,temp_space
lw $s7,120($s6)
li $s6,0
mul $s7,$s7,4
add $s6,$s6,$s7
sw $t2,temp_space($s6)
li $t8,0
la $s7,temp_space
lw $t9,120($s7)
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t2,temp_space($t8)
li $v0,4
la $a0,str9
syscall
li $v0,1
move $a0,$t2
syscall
li $v0,4
la $a0,nextline
syscall
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
sub $t2,$t8,$t9
la $t8,temp_space
sw $t2,120($t8)
j label_4
label_5:
li $v0,4
la $a0,str10
syscall
li $v0,4
la $a0,nextline
syscall
li $t8,5
li $t9,1
mul $t2,$t8,$t9
move $t8,$0
move $t9,$t2
sub $t3,$t8,$t9
li $t8,1
li $t9,1
div $t2,$t8,$t9
move $t8,$t3
move $t9,$t2
sub $t4,$t8,$t9
move $t8,$t4
li $t9,+1
add $t2,$t8,$t9
li $t8,1
li $t9,1
div $t3,$t8,$t9
move $t8,$t2
move $t9,$t3
sub $t4,$t8,$t9
la $t8,temp_space
sw $t4,120($t8)
label_6:
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t2,$t8,$t9
BEQ $t2,$0,label_7
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t3,$t8,$t9
la $s7,temp_space
lw $t8,120($s7)
li $s6,0
mul $t3,$t3,4
add $s6,$s6,$t3
sw $t8,temp_space($s6)
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t3,$t8,$t9
li $t8,0
mul $t3,$t3,4
add $t8,$t8,$t3
lw $t4,temp_space($t8)
li $v0,4
la $a0,str11
syscall
li $v0,1
move $a0,$t4
syscall
li $v0,4
la $a0,nextline
syscall
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
add $t3,$t8,$t9
la $t8,temp_space
sw $t3,120($t8)
j label_6
label_7:
li $v0,4
la $a0,str12
syscall
li $v0,4
la $a0,nextline
syscall
la $s7,temp_space
lw $t8,120($s7)
la $t9,temp_space
sw $t8,120($t9)
label_8:
la $s5,temp_space
lw $s6,120($s5)
li $s7,0
BLE $s6,$s7,label_9
la $s7,temp_space
lw $t8,120($s7)
li $t9,+1
sub $t3,$t8,$t9
li $t8,0
mul $t3,$t3,4
add $t8,$t8,$t3
lw $t4,temp_space($t8)
move $t8,$t4
li $t9,1
add $t3,$t8,$t9
la $s6,temp_space
lw $s7,120($s6)
li $s6,0
mul $s7,$s7,4
add $s6,$s6,$s7
sw $t3,temp_space($s6)
li $t8,0
la $s7,temp_space
lw $t9,120($s7)
mul $t9,$t9,4
add $t8,$t8,$t9
lw $t3,temp_space($t8)
li $v0,4
la $a0,str13
syscall
li $v0,1
move $a0,$t3
syscall
li $v0,4
la $a0,nextline
syscall
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
sub $t3,$t8,$t9
la $t8,temp_space
sw $t3,120($t8)
j label_8
label_9:
li $v0,4
la $a0,str14
syscall
li $v0,4
la $a0,nextline
syscall
move $t8,$0
li $t9,17
sub $t3,$t8,$t9
la $t8,temp_space
sw $t3,120($t8)
label_10:
la $s5,temp_space
lw $s6,120($s5)
li $s7,0
BGE $s6,$s7,label_11
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t3,$t8,$t9
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t4,$t8,$t9
move $t8,$t4
li $t9,+1
sub $t5,$t8,$t9
li $t8,0
mul $t5,$t5,4
add $t8,$t8,$t5
lw $t4,temp_space($t8)
move $t8,$t4
li $t9,1
add $t5,$t8,$t9
li $s6,0
mul $t3,$t3,4
add $s6,$s6,$t3
sw $t5,temp_space($s6)
move $t8,$0
la $s7,temp_space
lw $t9,120($s7)
sub $t3,$t8,$t9
li $t8,0
mul $t3,$t3,4
add $t8,$t8,$t3
lw $t4,temp_space($t8)
li $v0,4
la $a0,str15
syscall
li $v0,1
move $a0,$t4
syscall
li $v0,4
la $a0,nextline
syscall
la $s7,temp_space
lw $t8,120($s7)
li $t9,1
add $t3,$t8,$t9
la $t8,temp_space
sw $t3,120($t8)
j label_10
label_11:
li $v0,4
la $a0,str16
syscall
li $v0,4
la $a0,nextline
syscall
li $v0,10
syscall
