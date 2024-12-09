
pushd ./
echo A | rmdir ./Data/Output -erroraction silentlycontinue
cd build
ctest --output-on-failure --build-config Debug
popd
