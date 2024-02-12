@echo off

REM Get firmware file from argument, or use the default
if "%~1"=="" (
    set "firmware_file=lcm.hex"
) else (
    set "firmware_file=%~1"
)

REM Check firmware file exists
if not exist "%firmware_file%" (
    echo Firmware file not found: %firmware_file%.
    echo.
    echo Make sure you have copied your preferred lcm hex file into this folder and have named it "lcm.hex"
    pause
    exit 1
)

REM Check Python is installed
python --version >nul 2>nul
if errorlevel 1 (
    echo Python is not installed or was not found in your PATH
    echo.
    echo Install Python 3.7 using this link: https://www.python.org/ftp/python/3.7.9/python-3.7.9-amd64.exe
    echo.
	echo === IMPORTANT ===
    echo Choose "Custom",
    echo Accept all defaults on page 1, click Next
	echo On page 2, check the checkbox "add to environment"
	echo no other changes required
    pause
    exit 1
)

REM Check pyocd is installed
pyocd --version >nul 2>nul
if errorlevel 1 (
    echo pyocd is not installed or was not found in your PATH
    echo.
    echo Open CMD.exe, then run this command:
    echo python -m pip install --upgrade pyocd==0.34.3
    echo If you have installed pyocd but still see this error, please add it to your PATH
    pause
    exit 1
)

REM Check st-flash is installed
st-flash >nul 2>nul
if errorlevel 1 (
    echo ST-Link tools are not installed
    echo.
	echo Download and run the ST-Link Installer:
    echo https://www.st.com/en/development-tools/stsw-link004.html
    pause
    exit 1
)

REM Check HKMicroChip.HK32F030xMxx_DFP.1.0.17.pack exists
if not exist "HKMicroChip.HK32F030xMxx_DFP.1.0.17.pack" (
    echo HKMicroChip.HK32F030xMxx_DFP.1.0.17.pack not found
    echo.
    echo Make sure you have extracted all the files into a folder
    pause
    exit 1
)

REM Check pyocd.yaml exists
if not exist "pyocd.yaml" (
    echo pyocd.yaml not found
    echo.
    echo Make sure you have extracted all the files into a folder
    pause
    exit 1
)

REM Erase and flash the firmware
echo Erasing the old firmware...
pyocd erase -c -t hk32f030mf4p6 --config pyocd.yaml

echo Flashing the new firmware...
pyocd load "%firmware_file%" -t hk32f030mf4p6 --config pyocd.yaml

echo Please check the flashing messages to make sure the flashing was successful.
echo Float on!
pause