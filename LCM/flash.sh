#!/bin/sh

# Get the firmware file from the command line
firmware_file=$1

# Check that the firmware file was provided
if [ -z "$firmware_file" ]; then
    echo "Usage: ./flash.sh <firmware hex file>"
    exit 1
fi

# Check that the firmware file exists
if [ ! -f "$firmware_file" ]; then
    echo "File not found: $firmware_file"
    exit 1
fi

# Get the extension of the firmware file
extension=$(basename -- "$firmware_file")
extension="${extension##*.}"

# Verify that the firmware file is a .hex
if [ "$extension" != "hex" ]; then
    echo "File is not a .hex file"
    exit 1
fi

# Check that the pyocd command is installed
if [ ! -x "$(command -v pyocd)" ]; then
    echo "pyocd is not installed or was not found in your PATH"
    echo "Install it with: python -m pip install --upgrade pyocd==0.34.3"
    echo "If you have installed pyocd and it cannot be found, please add it to your PATH"
    exit 1
fi

# Check that the pyocd command is installed
if [ ! -x "$(command -v st-flash)" ]; then
    echo "ST-Link tools are not installed"
    echo "See https://github.com/stlink-org/stlink"
    exit 1
fi

# Check that HKMicroChip.HK32F030xMxx_DFP.1.0.17.pack exists
if [ ! -f "./HKMicroChip.HK32F030xMxx_DFP.1.0.17.pack" ]; then
    echo "HKMicroChip.HK32F030xMxx_DFP.1.0.17.pack not found"
    echo "Download it from https://github.com/surfdado/floatwheel"
    exit 1
fi

# Delimiter to separate the output
delimiter="========"

# Check that pyocd.yaml exists
if [ ! -f "./pyocd.yaml" ]; then
    echo "$delimiter"
    echo "pyocd.yaml not found, generating it..."
    printf "pack:\n  - HKMicroChip.HK32F030xMxx_DFP.1.0.17.pack\n" >pyocd.yaml
    echo "pyocd.yaml generated"
    echo "$delimiter"
fi

# Erase and flash the firmware
echo "Erasing the old firmware..."
echo "$delimiter"
pyocd erase -c -t hk32f030mf4p6 --config ./pyocd.yaml

echo "$delimiter"
echo "Flashing the new firmware..."
echo "$delimiter"
pyocd load "$firmware_file" -t hk32f030mf4p6 --config ./pyocd.yaml

echo "$delimiter"
echo "Please check the flashing messages to make sure the flash was successful."
echo "Float on!"
echo "$delimiter"
