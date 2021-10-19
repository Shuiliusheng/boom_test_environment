riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o median.riscv ./median/median_main.c ./median/median.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data median.riscv > median.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o qsort.riscv ./qsort/qsort_main.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data qsort.riscv > qsort.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o rsort.riscv ./rsort/rsort.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data rsort.riscv > rsort.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o towers.riscv ./towers/towers_main.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data towers.riscv > towers.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o vvadd.riscv ./vvadd/vvadd_main.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data vvadd.riscv > vvadd.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o multiply.riscv ./multiply/multiply_main.c ./multiply/multiply.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data multiply.riscv > multiply.riscv.dump
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data mm.riscv > mm.riscv.dump
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data dhrystone.riscv > dhrystone.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o spmv.riscv ./spmv/spmv_main.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data spmv.riscv > spmv.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o mt-vvadd.riscv ./mt-vvadd/mt-vvadd.c ./mt-vvadd/vvadd.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data mt-vvadd.riscv > mt-vvadd.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o mt-matmul.riscv ./mt-matmul/matmul.c ./mt-matmul/mt-matmul.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data mt-matmul.riscv > mt-matmul.riscv.dump
riscv64-unknown-linux-gnu-gcc -I./../env -I./common -I./median -I./qsort -I./rsort -I./towers -I./vvadd -I./multiply -I./mm -I./dhrystone -I./spmv -I./mt-vvadd -I./mt-matmul -I./pmp -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns -o pmp.riscv ./pmp/pmp.c ./common/syscalls.c ./common/crt.S -static -nostdlib -nostartfiles -lm -lgcc -T ./common/test.ld
riscv64-unknown-linux-gnu-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data pmp.riscv > pmp.riscv.dump

mv *.riscv output/
mv *.dump output/