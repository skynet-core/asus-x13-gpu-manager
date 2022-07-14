#!/usr/bin/env sh

set -e

cmake -DCMAKE_BUILD_TYPE:STRING=Release -G Ninja -B ./build -S./
cmake --build ./build --config Release --target all

sudo /opt/asus-gpu-manager/bin/unistall

sudo cmake --install ./build --config Release
sudo systemctl daemon-reload

sudo systemctl enable asus-gpu-switch.service
sudo systemctl enable --now asus-gpu-manager.service

sudo /opt/asus-gpu-manager/bin/asus-gpu-cli -m