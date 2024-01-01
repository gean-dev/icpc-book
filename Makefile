all:
	echo "Hello World!"
compile-all:
	./scripts/compile-test.sh .
test-all:
	./scripts/run-test.sh .