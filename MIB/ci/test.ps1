
$path_root  = Get-Location

Set-Location ./build/Tests

ctest -C Release

Set-Location $path_root
