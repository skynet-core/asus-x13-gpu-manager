#!/usr/bin/env sh

sudo systemctl disable --now asus-gpu-man.service || true

sudo rm -f /etc/system.d/system/asus-gpu-man.service
sudo rm -f /etc/dbus-1/system.d/org.skynet.asus.conf

sudo systemctl daemon-reload

sudo rm -rf /opt/asus-gpu-man