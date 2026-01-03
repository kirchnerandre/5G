
$path_root  = Get-Location

Set-Location ./build/Tests

ctest --output-on-failure -C Release

Set-Location $path_root
