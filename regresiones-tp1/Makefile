TP1 = ./tp1
# TP1 = bc
# TP1 = valgrind --tool=memcheck --error-exitcode=1 tp1

test tests: 0-warmup.out 1-spaces.out 2-precision.out 3-recursion.out 4-mixed.out
	@echo OK

clean:
	rm -f *.out || :

0-warmup.out: 0-warmup.in
	@$(TP1) < 0-warmup.in > 0-warmup.out
	@diff -s -b 0-warmup.out 0-warmup.ref

1-spaces.out: 1-spaces.in
	@$(TP1) < 1-spaces.in > 1-spaces.out
	@diff -s -b 1-spaces.out 1-spaces.ref

2-precision.out: 2-precision.in
	@$(TP1) < 2-precision.in > 2-precision.out
	@diff -s -b 2-precision.out 2-precision.ref

3-recursion.out: 3-recursion.in
	@$(TP1) < 3-recursion.in > 3-recursion.out
	@diff -s -b 3-recursion.out 3-recursion.ref

4-mixed.out: 4-mixed.in
	@$(TP1) < 4-mixed.in > 4-mixed.out
	@diff -s -b 4-mixed.out 4-mixed.ref
