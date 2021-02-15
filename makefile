PROJECT_NAME=cornerstone

runcmd=build/driver/cornerstone ../cornerstone/lib/main-driver.bb

# === BOOTSTRAP ============================================

.PHONY: default
default: build

.PHONY: run
run: compile
	./prog

.PHONY: gdb
gdb: build
	gdb -q --args ${runcmd}

.PHONY: compile
compile: build
	${runcmd} > prog.ll
	clang -Wno-override-module prog.ll -o prog

# === RUN ==================================================

.PHONY: build
build:
	@[[ -d build ]] || mkdir build
	@cd build; cmake -DGTEST=False ..; make -j8

.PHONY: run\:%
run\:%: build
	build/driver/${PROJECT_NAME} $*

.PHONY: matcher
matcher: compile
	build/matcher/matcher ints

# === TEST =================================================

.PHONY: test-build
test-build:
	@[[ -d build ]] || mkdir build
	cd build; cmake -DGTEST=True ..; make -j8

.PHONY: test-gdb
test-gdb: test-build
	gdb -q --args build/test/${PROJECT_NAME}_test --gtest_color=yes

.PHONY: test
test: test-build
	build/test/${PROJECT_NAME}_test --gtest_color=yes

.PHONY: test\:%
test\:%: test-build
	build/test/${PROJECT_NAME}_test --gtest_filter='*$**'

.PHONY: list-tests
list-tests: test-build
	build/test/${PROJECT_NAME}_test --gtest_list_tests

# === MISC =================================================

.PHONY: clean
clean:
	rm -rf build

# === PROFILE =============================================

.PHONY: profile\:%
profile\:%:
	valgrind --tool=callgrind "$*"
	kcachegrind callgrind.out.*
	rm -f callgrind.out.*
