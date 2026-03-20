set windows-shell := ["powershell.exe", "-c"]
preset := "x64-release"

default:
  @just run

configure:
  cmake --preset {{preset}}

run:
  cmake --build --preset {{preset}} --target run
