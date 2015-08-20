iptables -A INPUT -p icmp --icmp-type echo-request -j ACCEPT
iptables -P OUTPUT DROP
iptables -P INPUT DROP
iptables -A OUTPUT -p icmp --icmp-type echo-request -j ACCEPT
iptables iptables
