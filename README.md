## ASUS FLOW X13 GPU MANAGER

# WARNING! WORK IN PROGRESS!

## configure

    cmake -DCMAKE_BUILD_TYPE:STRING=Release -G Ninja -B ./build

## build

    cmake --build ./build --config Release --target all

## install

    sudo cmake --install ./build --config Release

## enable service:

    sudo systemctl enable --now asus-gpu-man.service


## install script

    ./install.sh

## how to switch gpu

    sudo /opt/asus-gpu-manager/bin/asus-gpu-cli -s integrated && sudo reboot -> disable nvidia after reboot

    sudo /opt/asus-gpu-manager/bin/asus-gpu-cli -s hybrid && sudo reboot -> enable discrete NVIDIA GPU

    sudo /opt/asus-gpu-manager/bin/asus-gpu-cli -s egpu  && sudo reboot -> enable XMobile external GPU


## Well known issues:

1. Sometimes NVIDIA pci device does not turn on after switching from `integrated` mode. No solution at this time. The only way to force kernel to turn it on it to hard-reboot (press power button for a while)