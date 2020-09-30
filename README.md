# TGA

## Sockets - Share de arquivos

## Integrantes

* Gabriel Porto
* Leonardo Zucatti


## Depts
* gcc (g++)
* make
* Boost.Asio 

### Debian-based

```sudo apt-get install build-essential libboost-all-dev g++ gcc make automake```

### Fedora(RHEL)-based

```sudo dnf install boost-devel automake make kernel-devel gcc gcc-c++```

### Arch-based

```pacman -Ss base-devel boost-libs boost make automake gcc```

### Referências

* **Conceitos apresentados em aula**;
* **Livro**: Boost.Asio C++ Network Programming, 2013, Packt

### Instruções

* ```make clean``` - limpa os binários ```client``` e ```server``` do diretório

* ```make || make build``` - Compila o servidor e o cliente

* ```make client``` - Compila apenas o client

* ```make server``` - Compila apenas o server

#### Nota

Resolvi não deixar o projeto muito complexo usando um "CMakeLists.txt" para ficar mais prático
