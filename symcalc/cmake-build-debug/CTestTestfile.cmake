# CMake generated Testfile for 
# Source directory: /Users/minimumtanaku/Downloads/symcalc-master
# Build directory: /Users/minimumtanaku/Downloads/symcalc-master/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(direct "/Users/minimumtanaku/Downloads/symcalc-master/cmake-build-debug/tests-direct")
add_test(runner-direct "/Users/minimumtanaku/Downloads/symcalc-master/cmake-build-debug/tests-runner-direct")
add_test(runner-subprocess "/Users/minimumtanaku/Downloads/symcalc-master/cmake-build-debug/tests-runner-subprocess")
set_tests_properties(runner-subprocess PROPERTIES  ENVIRONMENT "TEST_CMD=\"./symcalc\"")
