#bubbleSort(Array A)
#   for (n=A.size; n>1; --n){
#       for (i=0; i<n-1; ++i){
##         if (A[i] > A[i+1]){
#              A.swap(i, i+1)
#          }
#       }
#   }

.data
dataStart:
.string "Dies ist ein String zum Sortieren."
dataEnd:

.text
    la a1, dataStart
    li a0, 4
    ecall

    la s0, dataStart
    la t0, dataEnd

    sub s1, t0, s0
    addi s1, s1, -1 # n in s1

# for (n=A.size; n>1; --n){
loop0:
    addi t0, x0, 1 # 1 in t0
    ble s1, t0, loop0end

# for (i=0; i<n-1; ++i){
    addi s2, x0, 0 # i in s2
loop1:
    addi t0, s1, -1 # n-1 in t0
    bge s2, t0, loop1end

## if (A[i] > A[i+1]){
    add s3, s0, s2
    lb t0, 0(s3)
    lb t1, 1(s3)
    ble t0, t1, notif
# A.swap(i, i+1)
    sb t0, 1(s3)
    sb t1, 0(s3)

notif:
    addi s2, s2, 1

    j loop1
loop1end:

    la a1, dataStart
    li a0, 4
    ecall

    addi s1, s1, -1
    j loop0
loop0end:


    li a0, 10 # venus exit
    ecall