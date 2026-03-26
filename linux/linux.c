#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INSTALLED 100
char installed_packages[MAX_INSTALLED][50] = {
    "bash", "apt", "coreutils", "ubuntu-minimal", "systemd",
    "dpkg", "libc6", "libstdc++6", "grep", "sed", "gawk",
    "tar", "gzip", "bzip2", "xz-utils", "wget", "curl",
    "python3", "python3-pip", "python3-venv"
};
int installed_count = 20;

#define MAX_FILES 30
typedef struct {
    char name[100];
    char content[4096];
} VirtualFile;
VirtualFile vfiles[MAX_FILES];
int vfile_count = 0;

VirtualFile *find_file(const char *name) {
    for (int i = 0; i < vfile_count; i++) {
        if (strcmp(vfiles[i].name, name) == 0) return &vfiles[i];
    }
    return NULL;
}

VirtualFile *create_or_get_file(const char *name) {
    VirtualFile *f = find_file(name);
    if (f) return f;
    if (vfile_count < MAX_FILES) {
        strncpy(vfiles[vfile_count].name, name, 99);
        vfiles[vfile_count].content[0] = '\0';
        return &vfiles[vfile_count++];
    }
    return NULL;
}

#define MAX_PIP 50
char pip_packages[MAX_PIP][50];
int pip_count = 0;

bool pip_is_installed(const char *pkg) {
    for (int i = 0; i < pip_count; i++) {
        if (strcmp(pip_packages[i], pkg) == 0) return true;
    }
    return false;
}

void pip_install(const char *pkg) {
    if (pip_count < MAX_PIP && !pip_is_installed(pkg)) {
        strncpy(pip_packages[pip_count++], pkg, 49);
    }
}

bool is_installed(const char *pkg) {
    for (int i = 0; i < installed_count; i++) {
        if (strcmp(installed_packages[i], pkg) == 0) return true;
    }
    return false;
}

void install_package(const char *pkg) {
    if (installed_count < MAX_INSTALLED && !is_installed(pkg)) {
        strncpy(installed_packages[installed_count++], pkg, 49);
    }
}

void print_help() {
    printf("\r\n\033[1;37mComandos disponibles en MauNux Shell (Ubuntu 24.04):\033[0m\r\n");
    printf("\033[0;90m────────────────────────────────────────────────────────\033[0m\r\n");
    printf(" \033[1;33mArchivos:\033[0m   ls, ls -la, cd, pwd, mkdir, rm, cp, mv, cat [file], touch\r\n");
    printf(" \033[1;33mSistema:\033[0m    uname -a, whoami, id, hostname, uptime, date, df -h, free -h\r\n");
    printf(" \033[1;33mProcesos:\033[0m   ps aux, top, htop\r\n");
    printf(" \033[1;33mRed:\033[0m        ip addr, ping [host], curl [url], wget [url], ss -tulnp\r\n");
    printf(" \033[1;33mPaquetes:\033[0m   apt update, apt install [pkg], apt remove [pkg], apt list --installed\r\n");
    printf(" \033[1;33mSnap:\033[0m       snap install [pkg], snap list, snap remove [pkg]\r\n");
    printf(" \033[1;33mUsuarios:\033[0m   sudo, passwd, useradd, whoami, groups\r\n");
    printf(" \033[1;33mServicios:\033[0m  systemctl status/start/stop/restart [servicio]\r\n");
    printf(" \033[1;33mPython:\033[0m     python3, python3 --version, python3 [archivo.py]\r\n");
    printf(" \033[1;33mPip:\033[0m        pip3 install [pkg], pip3 list, pip3 uninstall [pkg]\r\n");
    printf(" \033[1;33mEditor:\033[0m     nano [archivo], vim [archivo]  (auto-plantilla para bot.py)\r\n");
    printf(" \033[1;33mOtros:\033[0m      neofetch, lsb_release -a, clear, exit\r\n");
    printf("\r\n\033[1;32m Bot de Telegram:\033[0m\r\n");
    printf("   pip3 install pyTelegramBotAPI\r\n");
    printf("   nano bot.py          (genera plantilla automaticamente)\r\n");
    printf("   python3 bot.py       (ejecuta el bot)\r\n\r\n");
}

void run_neofetch(const char *username) {
    printf("\r\n");
    printf("\033[1;31m        .-/+oossssoo+/-.\033[0m    \033[1;37m%s\033[0m@\033[1;37mmaunux\033[0m\r\n", username);
    printf("\033[1;31m    `:+ssssssssssssssssss+:`\033[0m  \033[0;90m-----------------------\033[0m\r\n");
    printf("\033[1;31m  -+ssssssssssssssssssyyssss+-\033[0m \033[1;32mOS\033[0m: MauNux 2.0 LTS x86_64\r\n");
    printf("\033[1;31m .ossssssssssssssssss\033[1;37mdMMMNy\033[1;31msssso.\033[0m \033[1;32mBase\033[0m: Ubuntu 24.04 Noble Numbat\r\n");
    printf("\033[1;31m /ssssssssssss\033[1;37mhdmmNNmmyNMMMMh\033[1;31mssssss/\033[0m \033[1;32mKernel\033[0m: 6.8.0-49-maunux\r\n");
    printf("\033[1;31m +ssssssssss\033[1;37mhm\033[1;31myd\033[1;37mMMMMMMMNdddd\033[1;31mmyssssssss+\033[0m \033[1;32mUptime\033[0m: 1 day, 3 hours\r\n");
    printf("\033[1;31m /ssssssssss\033[1;37mhNMMMyh\033[1;31mhyyyyh\033[1;37mmNMMMNh\033[1;31mssssssss/\033[0m \033[1;32mShell\033[0m: bash 5.2.21\r\n");
    printf("\033[1;31m .ssssssssss\033[1;37mdMMMNh\033[1;31mssssssssss\033[1;37mhNMMMd\033[1;31mssssssss.\033[0m \033[1;32mDE\033[0m: GNOME 46\r\n");
    printf("\033[1;31m +sssshhhyNMMNyssssssssssssyNMMMysssssss+\033[0m \033[1;32mTerminal\033[0m: maunux-terminal\r\n");
    printf("\033[1;31m ossyNMMMNyMMhsssssssssssssshmmmhssssssso\033[0m \033[1;32mCPU\033[0m: 8 cores @ 3.6 GHz\r\n");
    printf("\033[1;31m ossyNMMMNyMMhsssssssssssssshmmmhssssssso\033[0m \033[1;32mMemory\033[0m: 3421MiB / 16384MiB\r\n");
    printf("\033[1;31m +sssshhhyNMMNyssssssssssssyNMMMysssssss+\033[0m \033[1;32mDisk\033[0m: 42G / 512G (8%%)\r\n");
    printf("\033[1;31m .sssssssssdMMMNhssssssssssshNMMMdssssssss.\033[0m\r\n");
    printf("\033[1;31m /ssssssssshNMMMyhhhyyhmNMMMNhssssssss/\033[0m  \033[1;31m███\033[1;33m███\033[1;32m███\033[1;34m███\033[1;35m███\033[1;36m███\033[0m\r\n");
    printf("\033[1;31m  -+ssssssssssssssssssyyssss+-\033[0m\r\n");
    printf("\033[1;31m    `:+ssssssssssssssssss+:`\033[0m\r\n");
    printf("\033[1;31m        .-/+oossssoo+/-.\033[0m\r\n\r\n");
}

void run_ubuntu_subsystem(const char *username) {
    char input[256];
    char cwd[200];
    char home_user[50];
    strncpy(home_user, username, 49);
    char *at2 = strchr(home_user, '@');
    if (at2) *at2 = '\0';

    snprintf(cwd, sizeof(cwd), "/home/%s", home_user);

    printf("\033[H\033[2J\033[3J");
    printf("\033[1;32m[  OK  ] Started MauNux system initialization.\033[0m\r\n");
    usleep(80000);
    printf("\033[1;32m[  OK  ] Reached target Graphical Interface.\033[0m\r\n");
    usleep(80000);
    printf("\033[1;32m[  OK  ] Loaded Ubuntu 24.04 LTS package repositories.\033[0m\r\n");
    usleep(80000);
    printf("\033[1;32m[  OK  ] Started OpenSSH Server Daemon.\033[0m\r\n");
    usleep(80000);
    printf("\r\n");
    printf("Ubuntu 24.04.1 LTS (MauNux 2.0 LTS)\r\n");
    printf("Kernel 6.8.0-49-maunux on an x86_64\r\n\r\n");
    printf("System information as of %s\r\n\r\n", __DATE__);
    printf("  System load:  0.08               Processes:             185\r\n");
    printf("  Usage of /:   8.2%% of 512.00GB   Users logged in:       1\r\n");
    printf("  Memory usage: 21%%                IPv4 address for eth0: 192.168.1.100\r\n");
    printf("  Swap usage:   0%%\r\n\r\n");
    printf("Type 'help' for available commands.\r\n\r\n");

    char display_user[50];
    strncpy(display_user, username, 49);
    char *at = strchr(display_user, '@');
    if (at) *at = '\0';

    while (true) {
        printf("\033[1;32m%s\033[0m@\033[1;32mmaunux\033[0m:\033[1;34m%s\033[0m$ ", display_user, cwd);
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;
        input[strcspn(input, "\r")] = 0;

        if (strlen(input) == 0) continue;

        if (strcmp(input, "exit") == 0 || strcmp(input, "logout") == 0) {
            printf("logout\r\n");
            break;

        } else if (strcmp(input, "help") == 0) {
            print_help();

        } else if (strcmp(input, "clear") == 0) {
            printf("\033[H\033[2J\033[3J");

        } else if (strcmp(input, "pwd") == 0) {
            printf("%s\r\n", cwd);

        } else if (strcmp(input, "ls") == 0) {
            printf("\033[1;34mDesktop\033[0m  \033[1;34mDocuments\033[0m  \033[1;34mDownloads\033[0m  \033[1;34mMusic\033[0m  \033[1;34mPictures\033[0m  \033[1;34mPublic\033[0m  \033[1;34mSnap\033[0m  \033[1;34mTemplates\033[0m  \033[1;34mVideos\033[0m");
            for (int i = 0; i < vfile_count; i++) {
                printf("  \033[1;32m%s\033[0m", vfiles[i].name);
            }
            printf("\r\n");

        } else if (strcmp(input, "ls -la") == 0 || strcmp(input, "ls -l") == 0) {
            printf("total 56\r\n");
            printf("drwxr-x--- 12 %s %s 4096 Mar 26 10:00 .\r\n", username, username);
            printf("drwxr-xr-x  3 root  root  4096 Mar 26 09:00 ..\r\n");
            printf("-rw-r--r--  1 %s %s  220 Mar 26 09:00 .bash_logout\r\n", username, username);
            printf("-rw-r--r--  1 %s %s 3526 Mar 26 09:00 .bashrc\r\n", username, username);
            printf("drwxrwxr-x  2 %s %s 4096 Mar 26 09:01 \033[1;34mDesktop\033[0m\r\n", username, username);
            printf("drwxrwxr-x  2 %s %s 4096 Mar 26 09:01 \033[1;34mDocuments\033[0m\r\n", username, username);
            printf("drwxrwxr-x  2 %s %s 4096 Mar 26 09:01 \033[1;34mDownloads\033[0m\r\n", username, username);
            printf("drwxrwxr-x  2 %s %s 4096 Mar 26 09:01 \033[1;34mMusic\033[0m\r\n", username, username);
            printf("drwxrwxr-x  2 %s %s 4096 Mar 26 09:01 \033[1;34mPictures\033[0m\r\n", username, username);
            printf("drwxrwxr-x  2 %s %s 4096 Mar 26 09:01 \033[1;34mVideos\033[0m\r\n", username, username);

        } else if (strncmp(input, "cd ", 3) == 0) {
            char *dir = input + 3;
            if (strcmp(dir, "~") == 0 || strcmp(dir, "") == 0) {
                snprintf(cwd, sizeof(cwd), "/home/%s", username);
            } else if (strcmp(dir, "..") == 0) {
                char *last = strrchr(cwd, '/');
                if (last && last != cwd) *last = '\0';
            } else if (dir[0] == '/') {
                snprintf(cwd, sizeof(cwd), "%s", dir);
            } else {
                char newpath[200];
                snprintf(newpath, sizeof(newpath), "%s/%s", cwd, dir);
                snprintf(cwd, sizeof(cwd), "%s", newpath);
            }

        } else if (strcmp(input, "cd") == 0) {
            snprintf(cwd, sizeof(cwd), "/home/%s", username);

        } else if (strncmp(input, "mkdir ", 6) == 0) {
            printf("mkdir: created directory '%s'\r\n", input + 6);

        } else if (strncmp(input, "rm ", 3) == 0) {
            printf("removed '%s'\r\n", input + 3);

        } else if (strncmp(input, "cp ", 3) == 0) {
            printf("copied.\r\n");

        } else if (strncmp(input, "mv ", 3) == 0) {
            printf("renamed/moved.\r\n");

        } else if (strncmp(input, "touch ", 6) == 0) {
            printf("(created/updated '%s')\r\n", input + 6);

        } else if (strncmp(input, "cat ", 4) == 0) {
            printf("cat: %s: No such file or directory\r\n", input + 4);

        } else if (strncmp(input, "echo ", 5) == 0) {
            printf("%s\r\n", input + 5);

        } else if (strcmp(input, "whoami") == 0) {
            printf("%s\r\n", username);

        } else if (strcmp(input, "id") == 0) {
            printf("uid=1000(%s) gid=1000(%s) grupos=1000(%s),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),122(lpadmin),135(sambashare)\r\n", username, username, username);

        } else if (strcmp(input, "hostname") == 0) {
            printf("maunux\r\n");

        } else if (strcmp(input, "uptime") == 0) {
            printf(" 10:00:00 up 1 day,  3:21,  1 user,  load average: 0.08, 0.09, 0.06\r\n");

        } else if (strcmp(input, "date") == 0) {
            printf("Thu Mar 26 10:00:00 UTC 2026\r\n");

        } else if (strcmp(input, "df -h") == 0 || strcmp(input, "df") == 0) {
            printf("Filesystem      Size  Used Avail Use%% Mounted on\r\n");
            printf("tmpfs           1.6G  2.1M  1.6G   1%% /run\r\n");
            printf("/dev/sda1       512G   42G  449G   9%% /\r\n");
            printf("tmpfs           7.8G     0  7.8G   0%% /dev/shm\r\n");
            printf("/dev/sda2       512M  6.1M  506M   2%% /boot/efi\r\n");

        } else if (strcmp(input, "free -h") == 0 || strcmp(input, "free") == 0) {
            printf("               total        used        free      shared  buff/cache   available\r\n");
            printf("Mem:            16Gi       3.4Gi        10Gi       256Mi       2.4Gi        12Gi\r\n");
            printf("Swap:          2.0Gi          0B       2.0Gi\r\n");

        } else if (strcmp(input, "ps aux") == 0 || strcmp(input, "ps") == 0) {
            printf("USER         PID %%CPU %%MEM    VSZ   RSS TTY      STAT START   TIME COMMAND\r\n");
            printf("root           1  0.0  0.1 167972 11268 ?        Ss   09:00   0:02 /sbin/init\r\n");
            printf("root         234  0.0  0.0  14432  3456 ?        Ss   09:00   0:00 /usr/sbin/sshd -D\r\n");
            printf("root         312  0.0  0.3 232840 58432 ?        Ssl  09:00   0:05 /usr/lib/snapd/snapd\r\n");
            printf("%s        1002  0.0  0.0  11568  4352 pts/0    Ss   10:00   0:00 bash\r\n", username);

        } else if (strcmp(input, "top") == 0 || strcmp(input, "htop") == 0) {
            printf("top - 10:00:01 up 1 day,  3:21,  1 user,  load average: 0.08, 0.09, 0.06\r\n");
            printf("Tasks: 185 total,   1 running, 184 sleeping,   0 stopped,   0 zombie\r\n");
            printf("%%Cpu(s):  0.6 us,  0.2 sy,  0.0 ni, 98.9 id,  0.2 wa,  0.0 hi,  0.0 si\r\n");
            printf("MiB Mem :  16384.0 total,  10240.0 free,   3421.0 used,   2723.0 buff/cache\r\n");
            printf("MiB Swap:   2048.0 total,   2048.0 free,      0.0 used.  12510.0 avail Mem\r\n\r\n");
            printf("  PID USER      PR  NI    VIRT    RES    SHR S  %%CPU  %%MEM     TIME+ COMMAND\r\n");
            printf("    1 root      20   0  167972  11268   8192 S   0.0   0.1   0:02.34 systemd\r\n");
            printf("  312 root      20   0  232840  58432  32768 S   0.3   0.3   0:05.12 snapd\r\n");
            printf(" 1002 %s    20   0   11568   4352   3584 S   0.0   0.0   0:00.08 bash\r\n", username);
            printf("\r\nPresiona ENTER para salir de top.\r\n");
            char dummy[10]; fgets(dummy, sizeof(dummy), stdin);

        } else if (strcmp(input, "ip addr") == 0 || strcmp(input, "ip a") == 0) {
            printf("1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536\r\n");
            printf("    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00\r\n");
            printf("    inet 127.0.0.1/8 scope host lo\r\n");
            printf("2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500\r\n");
            printf("    link/ether 52:54:00:ab:cd:ef brd ff:ff:ff:ff:ff:ff\r\n");
            printf("    inet 192.168.1.100/24 brd 192.168.1.255 scope global eth0\r\n");

        } else if (strncmp(input, "ping ", 5) == 0) {
            char *host = input + 5;
            printf("PING %s: 56 data bytes\r\n", host);
            printf("64 bytes from %s: icmp_seq=0 ttl=64 time=1.23 ms\r\n", host);
            printf("64 bytes from %s: icmp_seq=1 ttl=64 time=1.19 ms\r\n", host);
            printf("64 bytes from %s: icmp_seq=2 ttl=64 time=1.21 ms\r\n", host);
            printf("\r\n--- %s ping statistics ---\r\n", host);
            printf("3 packets transmitted, 3 received, 0%% packet loss\r\n");

        } else if (strncmp(input, "curl ", 5) == 0 || strncmp(input, "wget ", 5) == 0) {
            printf("Connecting to %s...\r\nResponse: HTTP/2 200 OK\r\n(Contenido simulado)\r\n", input + 5);

        } else if (strcmp(input, "ss -tulnp") == 0) {
            printf("Netid  State   Recv-Q  Send-Q  Local Address:Port\r\n");
            printf("tcp    LISTEN  0       128     0.0.0.0:22    (sshd)\r\n");
            printf("tcp    LISTEN  0       5       127.0.0.1:631 (cupsd)\r\n");

        } else if (strcmp(input, "apt update") == 0 || strcmp(input, "sudo apt update") == 0) {
            printf("Obj:1 http://archive.ubuntu.com/ubuntu noble InRelease\r\n");
            printf("Obj:2 http://archive.ubuntu.com/ubuntu noble-updates InRelease\r\n");
            printf("Obj:3 http://archive.ubuntu.com/ubuntu noble-backports InRelease\r\n");
            printf("Obj:4 http://security.ubuntu.com/ubuntu noble-security InRelease\r\n");
            printf("Leyendo lista de paquetes... Hecho\r\n");
            printf("Creando arbol de dependencias... Hecho\r\n");
            printf("Leyendo informacion de estado... Hecho\r\n");
            printf("\033[1;32mTodos los paquetes estan actualizados.\033[0m\r\n");

        } else if (strcmp(input, "apt upgrade") == 0 || strcmp(input, "sudo apt upgrade") == 0) {
            printf("Leyendo lista de paquetes... Hecho\r\n");
            printf("Calculando arbol de dependencias... Hecho\r\n");
            printf("0 actualizados, 0 se instalaran, 0 para eliminar y 0 no actualizados.\r\n");

        } else if (strncmp(input, "apt install ", 12) == 0 || strncmp(input, "sudo apt install ", 17) == 0) {
            char *pkg = strstr(input, "install ") + 8;
            printf("Leyendo lista de paquetes... Hecho\r\n");
            printf("Calculando arbol de dependencias... Hecho\r\n");
            printf("Leyendo informacion de estado... Hecho\r\n");
            printf("Los paquetes NUEVOS siguientes se instalaran:\r\n  %s\r\n", pkg);
            printf("0 actualizados, 1 se instalaran, 0 para eliminar y 0 no actualizados.\r\n");
            printf("Get:1 http://archive.ubuntu.com/ubuntu noble/main amd64 %s amd64 [simulado]\r\n", pkg);
            printf("Obtenidos 0 B en 0 s.\r\n");
            printf("Seleccionando el paquete %s previamente no seleccionado.\r\n", pkg);
            printf("(Leyendo la base de datos ... 280450 ficheros y directorios instalados actualmente.)\r\n");
            printf("Preparando para desempaquetar .../archives/%s.deb ...\r\n", pkg);
            printf("Desempaquetando %s ...\r\n", pkg);
            printf("Configurando %s ...\r\n", pkg);
            printf("Procesando disparadores para man-db ...\r\n");
            printf("\033[1;32mInstalacion completada.\033[0m\r\n");
            install_package(pkg);

        } else if (strncmp(input, "apt remove ", 11) == 0 || strncmp(input, "sudo apt remove ", 16) == 0) {
            char *pkg = strstr(input, "remove ") + 7;
            printf("Leyendo lista de paquetes... Hecho\r\n");
            printf("Los paquetes siguientes se ELIMINARAN:\r\n  %s\r\n", pkg);
            printf("0 actualizados, 0 se instalaran, 1 para eliminar y 0 no actualizados.\r\n");
            printf("Desinstalando %s ... Hecho\r\n", pkg);

        } else if (strcmp(input, "apt list --installed") == 0) {
            printf("Listando... Hecho\r\n");
            for (int i = 0; i < installed_count; i++) {
                printf("%s/noble,now amd64 [instalado]\r\n", installed_packages[i]);
            }

        } else if (strcmp(input, "apt") == 0) {
            printf("apt 2.7.14 (amd64)\r\n");
            printf("Uso: apt [opciones] comando\r\n\r\n");
            printf("Comandos:\r\n");
            printf("  list              - lista paquetes\r\n");
            printf("  search            - busca paquetes\r\n");
            printf("  show              - muestra detalles de un paquete\r\n");
            printf("  install           - instala paquetes\r\n");
            printf("  reinstall         - reinstala paquetes\r\n");
            printf("  remove            - elimina paquetes\r\n");
            printf("  autoremove        - elimina dependencias innecesarias\r\n");
            printf("  update            - actualiza lista de paquetes\r\n");
            printf("  upgrade           - actualiza paquetes\r\n");

        } else if (strncmp(input, "dpkg -l", 7) == 0) {
            printf("Desired=Unknown/Install/Remove/Purge/Hold\r\n");
            printf("|Status=Not/Inst/Conf-files/Unpacked/halF-conf/Half-inst/trig-aWait/Trig-pend\r\n");
            printf("||/ Name                Version                Architecture Description\r\n");
            printf("+++-===================-=====================-============-========================\r\n");
            for (int i = 0; i < installed_count && i < 10; i++) {
                printf("ii  %-20s 1.0-ubuntu24.04   amd64        Ubuntu package\r\n", installed_packages[i]);
            }

        } else if (strncmp(input, "snap install ", 13) == 0) {
            char *pkg = input + 13;
            printf("%s 1.0 from Canonical installed\r\n", pkg);
            install_package(pkg);

        } else if (strcmp(input, "snap list") == 0) {
            printf("Name               Version          Rev  Tracking       Publisher   Notes\r\n");
            printf("core22             20241001         1663  latest/stable  canonical   base\r\n");
            printf("firefox            126.0-1          4821  latest/stable  mozilla     -\r\n");
            printf("gnome-42-2204      0+git.510a601    176   latest/stable  canonical   -\r\n");
            printf("snapd              2.63             21759 latest/stable  canonical   snapd\r\n");

        } else if (strncmp(input, "snap remove ", 12) == 0) {
            printf("%s removed\r\n", input + 12);

        } else if (strncmp(input, "sudo ", 5) == 0) {
            printf("[sudo] password for %s: \r\n", username);
            char pass[50];
            fgets(pass, sizeof(pass), stdin);
            char cmd[200];
            snprintf(cmd, sizeof(cmd), "%s", input + 5);
            printf("Ejecutando como root: %s\r\n", cmd);

        } else if (strcmp(input, "passwd") == 0) {
            printf("Changing password for %s.\r\n", username);
            printf("Current password: "); fflush(stdout);
            char p[50]; fgets(p, sizeof(p), stdin);
            printf("New password: "); fflush(stdout);
            fgets(p, sizeof(p), stdin);
            printf("Retype new password: "); fflush(stdout);
            fgets(p, sizeof(p), stdin);
            printf("passwd: password updated successfully\r\n");

        } else if (strncmp(input, "useradd ", 8) == 0) {
            printf("(creado usuario '%s')\r\n", input + 8);

        } else if (strcmp(input, "groups") == 0) {
            printf("%s adm cdrom sudo dip plugdev lpadmin sambashare\r\n", username);

        } else if (strcmp(input, "systemctl status") == 0) {
            printf("\033[1;32m●\033[0m maunux.service - MauNux 2.0 LTS\r\n");
            printf("     Loaded: loaded (/lib/systemd/system/maunux.service)\r\n");
            printf("     Active: \033[1;32mactive (running)\033[0m since Thu 2026-03-26 09:00:00 UTC; 1h ago\r\n");
            printf("   Main PID: 1 (systemd)\r\n");

        } else if (strncmp(input, "systemctl ", 10) == 0) {
            char *rest = input + 10;
            if (strncmp(rest, "start ", 6) == 0) {
                printf("\033[1;32m[  OK  ]\033[0m Started %s.\r\n", rest + 6);
            } else if (strncmp(rest, "stop ", 5) == 0) {
                printf("\033[1;33m[  OK  ]\033[0m Stopped %s.\r\n", rest + 5);
            } else if (strncmp(rest, "restart ", 8) == 0) {
                printf("\033[1;32m[  OK  ]\033[0m Restarted %s.\r\n", rest + 8);
            } else if (strncmp(rest, "enable ", 7) == 0) {
                printf("Created symlink /etc/systemd/system/multi-user.target.wants/%s\r\n", rest + 7);
            } else {
                printf("systemctl: operacion no reconocida.\r\n");
            }

        } else if (strcmp(input, "uname -a") == 0 || strcmp(input, "uname") == 0) {
            printf("Linux maunux 6.8.0-49-maunux #49~24.04.1-MauNux SMP PREEMPT_DYNAMIC Mon Oct  7 2025 x86_64 x86_64 x86_64 GNU/Linux\r\n");

        } else if (strcmp(input, "lsb_release -a") == 0 || strcmp(input, "lsb_release") == 0) {
            printf("No LSB modules are available.\r\n");
            printf("Distributor ID: MauNux\r\n");
            printf("Description:    MauNux 2.0 LTS (Based on Ubuntu 24.04.1 LTS)\r\n");
            printf("Release:        24.04\r\n");
            printf("Codename:       noble\r\n");

        } else if (strcmp(input, "neofetch") == 0) {
            run_neofetch(username);

        } else if (strcmp(input, "node -v") == 0 || strcmp(input, "node --version") == 0) {
            if (is_installed("nodejs") || is_installed("node")) {
                printf("v20.14.0\r\n");
            } else {
                printf("bash: node: command not found\r\nTip: sudo apt install nodejs\r\n");
            }

        } else if (strcmp(input, "python3 --version") == 0 || strcmp(input, "python3 -V") == 0) {
            if (is_installed("python3") || is_installed("python3-minimal")) {
                printf("Python 3.12.3\r\n");
            } else {
                printf("bash: python3: command not found\r\nTip: sudo apt install python3\r\n");
            }

        } else if (strcmp(input, "git --version") == 0) {
            if (is_installed("git")) {
                printf("git version 2.43.0\r\n");
            } else {
                printf("bash: git: command not found\r\nTip: sudo apt install git\r\n");
            }

        } else if (strcmp(input, "java --version") == 0 || strcmp(input, "java -version") == 0) {
            if (is_installed("openjdk-21-jdk") || is_installed("default-jdk")) {
                printf("openjdk 21.0.3 2024-04-16\r\n");
                printf("OpenJDK Runtime Environment (build 21.0.3+9-Ubuntu-1ubuntu1)\r\n");
                printf("OpenJDK 64-Bit Server VM (build 21.0.3+9-Ubuntu-1ubuntu1, mixed mode, sharing)\r\n");
            } else {
                printf("bash: java: command not found\r\nTip: sudo apt install default-jdk\r\n");
            }

        } else if (strcmp(input, "python3 --version") == 0 || strcmp(input, "python3 -V") == 0 || strcmp(input, "python3 --version") == 0) {
            printf("Python 3.12.3\r\n");

        } else if (strcmp(input, "pip3 --version") == 0 || strcmp(input, "pip3 -V") == 0 || strcmp(input, "pip --version") == 0) {
            printf("pip 24.0 from /usr/lib/python3/dist-packages/pip (python 3.12)\r\n");

        } else if (strncmp(input, "pip3 install ", 13) == 0 || strncmp(input, "pip install ", 12) == 0) {
            char *pkg = strstr(input, "install ") + 8;
            printf("Collecting %s\r\n", pkg);
            usleep(200000);
            printf("  Downloading %s-latest-py3-none-any.whl\r\n", pkg);
            usleep(300000);
            printf("Installing collected packages: %s\r\n", pkg);
            usleep(200000);
            printf("\033[1;32mSuccessfully installed %s\033[0m\r\n", pkg);
            pip_install(pkg);

        } else if (strcmp(input, "pip3 list") == 0 || strcmp(input, "pip list") == 0) {
            printf("Package                Version\r\n");
            printf("---------------------- -------\r\n");
            printf("pip                    24.0\r\n");
            printf("setuptools             68.0.0\r\n");
            printf("wheel                  0.43.0\r\n");
            for (int i = 0; i < pip_count; i++) {
                printf("%-22s latest\r\n", pip_packages[i]);
            }

        } else if (strncmp(input, "pip3 uninstall ", 15) == 0 || strncmp(input, "pip uninstall ", 14) == 0) {
            char *pkg = strstr(input, "uninstall ") + 10;
            printf("Found existing installation: %s\r\n", pkg);
            printf("Uninstalling %s:\r\n", pkg);
            printf("\033[1;32mSuccessfully uninstalled %s\033[0m\r\n", pkg);

        } else if (strncmp(input, "nano ", 5) == 0 || strncmp(input, "vim ", 4) == 0) {
            char *editor = strncmp(input, "nano", 4) == 0 ? "nano" : "vim";
            char *filename = input + (strncmp(input, "nano ", 5) == 0 ? 5 : 4);

            int is_bot = (strstr(filename, "bot") != NULL && strstr(filename, ".py") != NULL);
            int is_py = strstr(filename, ".py") != NULL;

            if (is_bot && !pip_is_installed("pyTelegramBotAPI") && !pip_is_installed("python-telegram-bot") && !pip_is_installed("telebot")) {
                printf("\033[1;33mAviso: No tienes instalada ninguna libreria de Telegram.\033[0m\r\n");
                printf("Sugerencia: pip3 install pyTelegramBotAPI\r\n\r\n");
            }

            printf("\033[1;37m  GNU %s 7.2   %s\033[0m\r\n\033[0;90m", editor, filename);
            printf("─────────────────────────────────────────────────\033[0m\r\n");

            VirtualFile *vf = create_or_get_file(filename);
            if (vf && strlen(vf->content) > 0) {
                printf("%s\r\n", vf->content);
            } else if (is_bot) {
                printf("\033[0;90m# Plantilla de bot de Telegram generada por MauNux\033[0m\r\n");
                printf("import telebot\r\n\r\n");
                printf("TOKEN = 'TU_TOKEN_AQUI'\r\n");
                printf("bot = telebot.TeleBot(TOKEN)\r\n\r\n");
                printf("@bot.message_handler(commands=['start'])\r\n");
                printf("def start(message):\r\n");
                printf("    bot.reply_to(message, '¡Hola! Soy un bot hecho en MauNux 🐧')\r\n\r\n");
                printf("@bot.message_handler(commands=['help'])\r\n");
                printf("def help_cmd(message):\r\n");
                printf("    bot.reply_to(message, 'Comandos: /start /help')\r\n\r\n");
                printf("@bot.message_handler(func=lambda m: True)\r\n");
                printf("def echo(message):\r\n");
                printf("    bot.reply_to(message, message.text)\r\n\r\n");
                printf("print('Bot iniciado...')\r\n");
                printf("bot.polling(none_stop=True)\r\n");
                if (vf) {
                    snprintf(vf->content, sizeof(vf->content),
                        "import telebot\n\nTOKEN = 'TU_TOKEN_AQUI'\nbot = telebot.TeleBot(TOKEN)\n\n"
                        "@bot.message_handler(commands=['start'])\ndef start(message):\n    bot.reply_to(message, '¡Hola! Soy un bot hecho en MauNux 🐧')\n\n"
                        "@bot.message_handler(func=lambda m: True)\ndef echo(message):\n    bot.reply_to(message, message.text)\n\n"
                        "print('Bot iniciado...')\nbot.polling(none_stop=True)\n");
                }
            } else if (is_py) {
                printf("\033[0;90m# Nuevo archivo Python\033[0m\r\n");
                printf("print('Hola desde MauNux!')\r\n");
                if (vf) snprintf(vf->content, sizeof(vf->content), "print('Hola desde MauNux!')\n");
            }

            printf("\r\n\033[0;90m[ Escribe el contenido y presiona ENTER para guardar y salir ]\033[0m\r\n");
            fflush(stdout);

            char new_content[4096];
            if (fgets(new_content, sizeof(new_content), stdin)) {
                new_content[strcspn(new_content, "\n")] = 0;
                if (strlen(new_content) > 0 && vf) {
                    snprintf(vf->content, sizeof(vf->content), "%s\n", new_content);
                }
            }
            printf("\033[1;32mGuardado: %s\033[0m\r\n", filename);

        } else if (strncmp(input, "cat ", 4) == 0) {
            char *filename = input + 4;
            VirtualFile *vf = find_file(filename);
            if (vf && strlen(vf->content) > 0) {
                printf("%s\r\n", vf->content);
            } else {
                printf("cat: %s: No such file or directory\r\n", filename);
            }

        } else if (strncmp(input, "python3 ", 8) == 0) {
            char *filename = input + 8;
            VirtualFile *vf = find_file(filename);

            int is_bot = (strstr(filename, "bot") != NULL);
            bool has_telebot = pip_is_installed("pyTelegramBotAPI") || pip_is_installed("telebot") || pip_is_installed("python-telegram-bot");

            if (is_bot && !has_telebot) {
                printf("\033[1;31mModuleNotFoundError: No module named 'telebot'\033[0m\r\n");
                printf("Instala primero: \033[1;33mpip3 install pyTelegramBotAPI\033[0m\r\n");
            } else if (vf || is_bot) {
                printf("\033[1;32mBot iniciado...\033[0m\r\n");
                usleep(300000);
                printf("2026-03-26 10:00:00,123 - TeleBot - INFO - Starting bot\r\n");
                usleep(200000);
                printf("2026-03-26 10:00:00,456 - TeleBot - INFO - Bot polling started\r\n");
                printf("\r\n\033[1;32m✓ Bot de Telegram corriendo en MauNux 2.0 LTS\033[0m\r\n");
                printf("\033[0;90m  Esperando mensajes... (presiona ENTER para detener)\033[0m\r\n");
                fflush(stdout);
                char dummy[10];
                fgets(dummy, sizeof(dummy), stdin);
                printf("\r\n\033[1;33mKeyboardInterrupt\033[0m\r\n");
                printf("Bot detenido.\r\n");
            } else {
                printf("python3: can't open file '%s': [Errno 2] No such file or directory\r\n", filename);
            }

        } else if (strcmp(input, "python3") == 0) {
            printf("Python 3.12.3 (main, Mar 26 2026, 10:00:00) [Clang 18.0.0] on linux\r\n");
            printf("Type \"help\", \"copyright\", \"credits\" or \"license\" for more information.\r\n");
            printf(">>> ");
            fflush(stdout);
            char pyinput[256];
            while (fgets(pyinput, sizeof(pyinput), stdin)) {
                pyinput[strcspn(pyinput, "\n")] = 0;
                if (strcmp(pyinput, "exit()") == 0 || strcmp(pyinput, "quit()") == 0) break;
                if (strncmp(pyinput, "print(", 6) == 0) {
                    char *start = strchr(pyinput, '(') + 1;
                    char *end = strrchr(pyinput, ')');
                    if (start && end && end > start) {
                        char out[256];
                        int len = end - start;
                        if (len > 255) len = 255;
                        strncpy(out, start, len);
                        out[len] = '\0';
                        if (out[0] == '\'' || out[0] == '"') {
                            memmove(out, out+1, strlen(out));
                            out[strlen(out)-1] = '\0';
                        }
                        printf("%s\r\n", out);
                    }
                } else if (strlen(pyinput) > 0) {
                    printf(">>> \r\n");
                }
                printf(">>> ");
                fflush(stdout);
            }

        } else if (strlen(input) > 0) {
            printf("\033[0;31mbash: %s: command not found\033[0m\r\n", input);
        }
    }
}
