#!/bin/bash
sudo cat /etc/crontab > $HOME/new
DIFF=$(diff new tmp)
if [ "$DIFF" != "" ]; then
	sudo sendmail tim.dautreme@gmail.com < $HOME/email.txt
	sudo rm -rf $HOME/tmp
	sudo cp $HOME/new $HOME/tmp
fi