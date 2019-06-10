sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get install -y vim
sudo apt-get install -y sudo
sudo apt-get install -y net-tools
sudo apt-get install -y iptables-persistent
sudo apt-get install -y fail2ban
sudo apt-get install -y sendmail
sudo apt-get install -y apache2
sudo apt-get install -y php libapache2-mod-php
sudo apt-get install -y php7.0-mbstring
sudo cat files/sshd_config > /etc/ssh/sshd_config
sudo cat files/interfaces > /etc/network/interfaces
sudo systemctl restart networking
# sudo ssh-keygen -b 4096
sudo systemctl restart sshd
sudo cat files/iptables > /etc/network/if-pre-up.d/iptables
sudo chmod +x /etc/network/if-pre-up.d/iptables
sudo touch /var/log/apache2/server.log
sudo cat files/jail.local > /etc/fail2ban/jail.local
sudo cat files/http-get-dos.conf > /etc/fail2ban/filter.d/http-get-dos.conf
sudo systemctl restart fail2ban.service
sudo cat files/update_script.sh > $HOME/update_script.sh
sudo chmod +x $HOME/update_script.sh

sudo cat files/crontab > /etc/crontab
sudo cp /etc/crontab $HOME/tmp

sudo echo "Salut a tous les amis pour ceux qui me connaissent pas et bah c'est moi" > $HOME/email.txt
sudo cat files/watch_script.sh > $HOME/watch_script.sh
sudo chmod +x $HOME/watch_script.sh

sudo cat files/crontab2 > /etc/crontab

sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/roger-skyline.com.key -out /etc/ssl/certs/roger-skyline.com.crt
sudo cat files/default-ssl > /etc/apache2/sites-available/default-ssl.conf
sudo systemctl restart apache2.service
sudo mkdir /var/www/monserveur
sudo cat files/index.php > /var/www/monserveur/index.php
sudo cat files/001-default.conf > /etc/apache2/sites-available/001-default.conf
sudo a2dissite 000-default.conf
sudo a2ensite 001-default.conf
sudo a2dismod mpm_event
sudo a2enmod mpm_prefork
sudo a2enmod php7.0
sudo systemctl reload apache2
sudo chown -R /var/www/monserveur
sudo reboot