#Requires -RunAsAdministrator

# !!! This script is not meant to be run without administrator rights. !!!

$env_directory = "../env"
$python_requriements_dir = "../requirements.txt"

function Detect
{
    Param ( [string] $prefix, [string] $command)

    try
    {
        $cmdOutput = Invoke-Expression $command
        if ($cmdOutput -is [array])
        {
            Write-Host "($prefix) running on: " $cmdOutput[0]
        }
        else
        {
            Write-Host "($prefix) running on: " $cmdOutput
        }
        return $true
    }
    catch
    {
        Write-Host "($prefix not detected)"
        return $false
    }
}

function Install
{
    Param ( [string] $prefix, [string] $command)

    Write-Host "Installing $prefix..."
    Invoke-Expression $command
    Write-Host "$prefix installed. If the script fails, please re run the terminal and run the script once again."
}

$chocoDetected = Detect -prefix "Chocolatey" -command "choco info chocolatey"
$pythonDetected = Detect -prefix "Python" -command "python --version"
$cmakeDetected = Detect -prefix "CMake" -command "cmake --version"

# Don't run this with function Install, it might not work.
if ($chocoDetected -eq $false)
{
  Write-Host "(Chocolatey not detected)"
  Write-Host "Installing Chocolatey..."
  Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
  Write-Host "Chocolatey installed. Please re run the terminal and run the script once again."
}

if ($pythonDetected -eq $false)
{
    Install -prefix "Python" -command "choco install -y python3"
}

if ($cmakeDetected -eq $false)
{
    Install -prefix "CMake" -command "choco install -y cmake"
}

# Install the module for detection MSVC.
if (!(Get-InstalledModule "VSSetup"))
{
    Write-Host "VSSetup module not detected."
    Write-Host "Installing VSSetup module..."
    Install-Module VSSetup -Scope CurrentUser
    Write-Host "VSSetup module installed."
}
else
{
    Write-Host "VSSetup module detected."
}

$vsSetup = Get-VSSetupInstance | Select-VSSetupInstance -Latest

if ($vsSetup -eq $null)
{
    Write-Host "Visual Studio not detected. Please install the newest release of Visual Studio. Exiting..."
    exit
}

$vsMajorVersion = $vsSetup.InstallationVersion.Major
$vsLineVersion  = $vsSetup.CatalogInfo["ProductLineVersion"]

$compilerConfig = @{}

$compilerConfig["compilator"] = "Visual Studio"
$compilerConfig["version"] = $vsMajorVersion
$compilerConfig["release_date"] = $vsLineVersion

$compilerConfig | ConvertTo-Json | Out-File "config.json"

Write-Host "Visual Studio $vsMajorVersion $vsLineVersion detected, saved to config.json"

if (!(Test-Path $env_directory))
{
    Write-Host "Env directory not detected, creating..."
    Invoke-Expression "python -m venv $env_directory"
}

Write-Host "Env directory detected, activating..."

Invoke-Expression "$env_directory\Scripts\activate"

if (Test-Path env:VIRTUAL_ENV)
{
    Write-Host "(Pyhon) Virtual environment activated."
}
else
{
    Write-Host "(Python) Virtual environment not activated. Exiting..."
    exit
}

Write-Host "Installing Python requirements..."
Invoke-Expression "pip install -r $python_requriements_dir"

Write-Host "Python requirements installed."
Write-Host "Setup complete."