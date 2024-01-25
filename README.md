
# current cinema program

### this program allows you to display the current films released in cinemas

## library used

- gtk :
is an open-source software library used for the development of graphical user interfaces (GUIs).
- curl :
is a software library and command-line tool used for transferring data via various network protocols.
- cJSON :
is a lightweight C library used for manipulating data in JSON (JavaScript Object Notation) format.


## language used

- C
- MakeFile

## install all libs

### GTK (GIMP Toolkit)

#### Debian/Ubuntu
```bash
sudo apt-get update
sudo apt-get install libgtk-3-dev
```
#### Red Hat/Fedora
```bash
sudo dnf install gtk3-devel
```
#### other os based on RPM 
```bash
sudo package-manager install gtk3-devel
```
#### other os based on AUR
```bash
yay -S gtk3
```

### Curl

#### Debian/Ubuntu
```bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev
```
#### Red Hat/Fedora
```bash
sudo dnf install libcurl-devel
```
#### other os based on RPM 
```bash
sudo package-manager install libcurl-devel
```
#### other os based on AUR
```bash
yay -S curl
```

### cJSON

#### Debian/Ubuntu
```bash
sudo apt-get update
sudo apt-get install libcjson-dev
```
#### Red Hat/Fedora
```bash
sudo dnf install cJSON-devel
```
#### other os based on RPM 
```bash
sudo package-manager install cJSON-devel
```
#### other os based on AUR
```bash
yay -S cJSON
```

## how to run the project ?

#### compile :
```bash

├──🮤  ~/c_proj🮥
└─   make  

```
#### launch :
```bash

├──🮤  ~/c_proj🮥
└─   ./film_programs

```