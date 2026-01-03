
$path_root  = Get-Location
$path_sln   = Join-Path $path_root "build/MIB.sln"

New-Item -Path "./build" -ItemType Directory -Force | Out-Null

Set-Location ./build

cmake ..

Set-Location "C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/amd64"

./MSBuild.exe $path_sln /t:Build /p:Configuration=Release

Set-Location $path_root
