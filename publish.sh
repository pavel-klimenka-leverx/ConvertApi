#!/bin/bash

APPLICATION_NAME="ConvertApi"
APPLICATION_DIR="/usr/local/bin/$APPLICATION_NAME"
APPLICATION_BIN="$APPLICATION_DIR/$APPLICATION_NAME"
PROJECT_DIR="/home/azureuser/Projects/$APPLICATION_NAME"
AZURE_USER="azureuser"

function build() {
	CURRENT_DIR=$(pwd)
	cd $PROJECT_DIR
	yes | git pull
	sudo rm -rf $APPLICATION_DIR
	echo "2" | ./build.sh > /dev/null
}

function enable_service() {
	sudo mkdir -p $APPLICATION_DIR
	cd $APPLICATION_DIR
	echo -e "[Unit]
Description=$APPLICATION_NAME service

[Service]
ExecStart=$APPLICATION_BIN
User=$AZURE_USER
SysLogIdentifier=$APPLICATION_NAME
Restart=always
RestartSec=5

[Install]
WantedBy=multi-user.target" | sudo tee /etc/systemd/system/$APPLICATION_NAME.service >/dev/null
	sudo systemctl daemon-reload
	if systemctl is-active --quiet $APPLICATION_NAME; then
		echo "Restarting service..."
		sudo systemctl restart $APPLICATION_NAME
	else
		echo "Enabling service..."
		sudo systemctl enable $APPLICATION_NAME
		sudo systemctl start $APPLICATION_NAME
	fi
}


##### Script #####
build && \
enable_service && \
echo "$APPLICATION_NAME service started successfully"
##################
