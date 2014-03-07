# build google test framework
cd ../../Libraries/googletest
/opt/local/bin/scons

# build google mock framework
cd ../googlemock
/opt/local/bin/scons -j 2

# build tests
cd ../../Build
/opt/local/bin/scons --file=SConstruct-unittests -j 2

# run tests
./PacmanUnitTests --gtest_shuffle --gtest_output="xml:PacmanUnitTests.junit.xml"
#chmod a+x ../Tools/CodeCoverage/gcovr
#../Tools/CodeCoverage/gcovr -x -r .. > ut-coverage.xml
