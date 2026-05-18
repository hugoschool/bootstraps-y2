# Step 1

1. `ansible -i my-inventory.yml all -m command -a "uptime"`
2. `ansible -i my-inventory.yml all -m reboot`
3. `ansible -i my-inventory.yml all -m apt -a "name=htop"`, `ansible -i my-inventory.yml web -m apt -a "name=nginx"`
4. `ansible -i my-inventory.yml all -m apt -a "name=htop state=absent"`
5. `ansible -i my-inventory.yml web -m service -a "name=nginx enabled=yes"`
