#Requires -RunAsAdministrator

Write-Host "Please always remember to run this script after running auto-config at least once."

Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process -Force

$workdir = Get-Location
$scriptdir = Set-Location -Path .. -PassThru

$env_directory = "$scriptdir\env"

# Check if env folder exists.
if (Test-Path $env_directory)
{
    Write-Host "Python env exists..."
} 
else
{
    Write-Host "Python env does not exist."
    Write-Host "Please run auto-config.ps1 first."
    exit
}

# Check if python env is running
if (Test-Path env:VIRTUAL_ENV)
{
    Write-Host "Python env is running..."
} 
else
{
    Write-Host "Python env is not running."
    Write-Host "Activating python env..."
    Invoke-Expression "$env_directory\Scripts\Activate.ps1"
}

Write-Host $workdir

Invoke-Expression "python $workdir\build.py install"
Invoke-Expression "python $workdir\build.py build"
Invoke-Expression "python $workdir\build.py release"

Set-Location -Path $workdir