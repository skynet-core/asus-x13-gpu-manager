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