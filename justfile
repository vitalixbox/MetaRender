set windows-shell := ["powershell.exe", "-c"]

preset := "x64-release"
generator := if os() == "windows" { "Visual Studio 18 2026" } else { "Ninja" }

default:
    @just run

configure:
    cmake --preset {{ preset }} -G "{{ generator }}"

run:
    cmake --build --preset {{ preset }} --target run
