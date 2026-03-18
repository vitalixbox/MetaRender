set shell := ["powershell.exe", "-c"]

configure:
    cmake --preset x64-release-msvc

configure2:
    cmake --preset x64-release

clean:
    Remove-Item -Path out/ -Recurse -Force

run:
    cmake --build --preset x64-release-msvc
    .\out\build\x64-release-msvc\Release\MetaRender.exe
