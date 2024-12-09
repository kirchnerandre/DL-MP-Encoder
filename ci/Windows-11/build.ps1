
pushd ./

mkdir Extras -erroraction 'silentlycontinue'
cd Extras

if (test-path -path "DirectX-Headers")
{
    cd DirectX-Headers
    git pull
    cd ..
}
else
{
    git clone https://github.com/microsoft/DirectX-Headers.git
}

popd

pushd ./
mkdir build -erroraction 'silentlycontinue'
cd build
cmake -DPLATFORM=Windows -DCMAKE_BUILD_TYPE=Release ..
&"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\amd64\msbuild" Encoder.sln
popd
