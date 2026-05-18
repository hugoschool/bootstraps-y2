#!/usr/bin/bash env
ansible-vault encrypt_string --vault-password-file password "octopus-secrets" --name "password"
