set shell := ["powershell.exe", "-c"]

configure:
    cmake -G "Visual Studio 18 2026" -A x64 -B out/build/x64-msvc-release -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmakeн

run:
    cmake --build out/build/x64-msvc-release --config Release
    .\out\build\x64-msvc-release\Release\MetaRender.exe
