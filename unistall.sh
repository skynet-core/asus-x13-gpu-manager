#!/usr/bin/env sh

sudo systemctl disable --now asus-gpu-manager.service || true
sudo systemctl disable --now asus-gpu-switch.service || true

sudo rm -f /etc/system.d/system/asus-gpu-manager.service
sudo rm -f /etc/system.d/system/asus-gpu-switch.service
sudo rm -f /etc/dbus-1/system.d/org.skynet.asus.conf

sudo systemctl daemon-reload

sudo rm -rf /opt/asus-gpu-manager