# Floatwheel's Light Control Module (LCM)

Board inside the ADV Floatwheel that controls lighting, power, charing and buzzer. That board is controlled by a tiny microcontroller, the HK32F030MF4P6.

# Requirements

* Floatwheels's LCM
* Programmer
  * J-Link: J-Link OB programmer
  * PyOCD: DAPLink, J-Link or ST-LINK
* SEGGER J-Link Software and Documentation pack [https://www.segger.com/downloads/jlink/](https://www.segger.com/downloads/jlink/)
* PyOCD [https://pyocd.io/](https://pyocd.io/)
* GNU Arm Embedded Toolchain

# Building

## 1. Install GNU Arm Embedded Toolchain

Download the toolchain yourself from [Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) according to your pc architecture, extract the files. Or use the provided link in the commands below

```bash
cd ~/Downloads
curl  https://developer.arm.com/-/media/Files/downloads/gnu/12.2.mpacbti-rel1/binrel/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz -L -o arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz
tar xvf arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz
sudo mkdir -p /opt/gcc-arm 
cd /opt/gcc-arm/
sudo mv ~/Downloads/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/ .
sudo chown -R root:root arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/
```

## 2. Option #1: Install SEGGER J-Link

Download and install JLink from [J-Link / J-Trace Downloads](https://www.segger.com/downloads/jlink/).

```bash
# installation command for .deb
sudo dpkg -i JLink_Linux_V770a_x86_64.deb
```

The default installation directory is */opt/SEGGER*

## 2. Option #2: Install PyOCD

Install from pip instead of apt repository because the version is 0.13.1+dfsg-1, which is too low to recognize J-Link probe

```bash
pip install pyocd
```

This will install PyOCD into:

```txt
/home/[user]/.local/bin/pyocd
/home/[user]/.local/bin/pyocd-gdbserver
/home/[user]/.local/lib/python3.10/site-packages/pyocd-0.34.2.dist-info/*
/home/[user]/.local/lib/python3.10/site-packages/pyocd/*
```

.profile will take care of the PATH, run `source ~/.profile` to make pyocd command available

## 3. Clone This Repository

Clone this repository to local workspace

## 4. Compiling And Flashing

```bash
# clean source code
make clean
# build
make
# or make with verbose output
V=1 make
# flash
make flash
```
