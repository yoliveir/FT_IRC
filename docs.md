#_42
Argumentos:
- puerto de conexión: El puerto de nuestro servidor, nuestro programa tendrá que estar a la escucha de este.
- Contraseña de conexión: La necesitará el cliente para poderse conectar al servidor.

# <mark style="background: #78a3ebAA; color:bbbbbb; padding: 2px 20px 2px 20px ">Funciones externas permitidas:</mark>

<u>socket</u>
`int socket(int domain, int type, int protocol)`
Crea un punto de comunicación entre dos nodos dentro de una red, devuelve un fd, archivo que será el punto de comunicación.
- **domain:** Familia de protocolo usada para la comunicación. IRC será AF_INET? al final va por internet, no?? no lo sé ;( creo que si!!!
- **type:** especifica las semáticas de comunicación. Si se transmiten bytes, si tiene longitud máxima... Dependiendo si queremos un socket TCP o UDP podrá ser SOCK_STREAM o SOCK_DGRAM, hay más pero esos son los relevantes diría.
- **protocolo:** El protocolo a usar con el socket. Normalmente hay un solo protocolo disponible para la combinación de domain + socket, por lo que se puede poner 0.

<u>close</u>
	Para cerrar el fd del socket mi pana poco más que decir

<u>setsockopt y getsockname</u>
Para configurar y obtener opciones de un socket.
`int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);`




<u>getprotobyname</u>

<u>gethostbyname</u>


<u>getaddrinfo</u>


<u>freeaddrinfo</u>


<u>bind</u>
`int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

Cuando se crea un socket con socket() este aún no tiene una dirección asignada. bind() asigna la dirección especificada con addr al sockfd

La estructura pasada en addr dependerá de la familia de la dirección (?).
Esta estructura está definida tal que:
```c
struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
}
```

creo que sa_family_t es la familia de protocolo, o sea AF_UNIX, AF_INET, AF_INET6....

Esta estructura es genérica, la dirección es un array sin más y es por tanto complicada de usar, por lo que he visto la gente lo que usa es struct sockaddr_in.

<u>connect</u>

<u>listen</u>

`int listen(int sockfd, int backlog);`

Marca el socket indicado en sockfd como un socket pasico, es decir, que va a ser usado para recibir peticiones de conexión con *accept*.
- El socket debe ser tipo SOCK_STREAM o SOCK_SEQPACKET. El socket que estamos usando nosotros para el ft_irc es tipo SOCK_STREAM.
	- <span style="color:rgb(199, 67, 67)">??? Cuál es la diferencia entre ambos?</span>
- backlog es el número máximo de la cola de peticiones de conexión pendientes. Si una petición llega cuando la cola ya está llena, el cliente recibirá un error de que la conexión se ha rechazado.



<u>accept</u>

<u>htons y htonl</u>
convierte el orden de los bytes de unsigned short integer y unsigned long integer del host al orden de la red.

En los hosts, el orden de los bytes es primero el byte menos significativo, en Internet es primero el byte más significativo.

<u>inet_addr</u>
`in_addr_t inet_addr(const char *cp);`
convierte la dirección cp de la notación típica IPv4 a notación binaria legible por la red.
Dice que el manual que esta función es problemática porque en caso de fallar devuelve -1 pero la dirección *255.255.255.255* también devuelve -1, pero las opciones que recomienda de funciones no me dejan usarlas así que :')

<u>inet_ntoa</u> (DEPRECADA)
<u>inet_ntop</u>
`const char *inet_ntop(int af, const void *restrict src, char dst[restrict .size], socklen_t size);`

Creo que esta función hace lo opuesto, recibe una estructura de dirección y devuelve la dirección en notación legible para nosotros.

<u>send</u> y <u>recv</u>

`ssize_t send(int sockfd, const void *buf, size_t len, int flags);`

Usar solo cuando el socket esté en un estado de conexión.
*send* es equivalente a *write* cuando este no lleva flags.
Ahora, qué flags se pueden usar que nos sean relevantes:
- ??? no sé no los entiendo T.T


`ssize_t recv(int sockfd, void *buf, size_t len, int flags);`

Recibe mensajes de un socket.
Al igual que *send*, *recv* es equivalente a *read* cuando no se usan flags.

Al igual que sus equivalentes read y write, devuelven la longitud del mensaje recibido  o enviado cuando todo sale bien.
Si el mensaje es demasiado largo para entrar en el buffer, el excedente se podría descartar (dependiendo del tipo de socket!!)

Si no hay mensajes disponibles en el socket, se espera  a que llegue, a menos que el socket sea nonblocking! en cuyo caso se devuelve -1.

Y aquí es donde entran en juego *select*, *poll* o *epoll*,  pues permiten determinar cuando llega información (a la vez me imagino?) en un socket.



<u>signal, sigaction... movidas de señales</u>

<u>lseek</u>

<u>fstat</u>

<u>fcntl</u>

<u>poll</u>

`int poll(struct pollfd *fds, nfds_t nfds, int timeout);`

Espera que uno o más fd estén disponibles para realizar I/O. *epoll* proporciona lo mismo pero mejorado, luego investigaré el qué y la diferencia con *select*.

- El conjunto de fd a monitorizar se especifica en ese *struct pollfd*, que es un array de estructuras, o sea cada instancia del array será uno de los fd a monitorizar imagino.

- *nfds*: Es el número de fds que hay para monitorizar. Para que no se salga del array imagino.

- *timeout* : especifica el tiempo en <u>milisegundos</u> que *poll* debe quedarse bloqueado esperando a que un fd esté listo. Por tanto, poll se quedará esperando en un mismo fd del array hasta que:
	1. El fd quede listo.
	2. La llamada sea interrumpida por una señal.
	3. Pase el timeout.
	
	Un valor negativo indica tiempo de espera infinito owo

Ahora vamos a ver esta estructura rara de pollfd

```cpp title:"struct pollfd"
struct pollfd {
    int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
```

- El *fd* al que debemos estar atentos. Es decir, el fd del cliente que se haya conectado al servidor. Tenemos que meter el fd de cada cliente que se conecte en el array de pollfd para que podamos mantener la conexión  todos ellos.
- *events*: Parámetro de input, una máscara de bits que especifica qué eventos le interesan al servidor de input del cliente.
- *revents*: Lo mismo pero para el output.

	- `POLLIN`: Nos va a interesar para leer datos del cliente.
	- `POLLOUT`: Se puede escribir, <span style="color:rgb(199, 67, 67)">pero el servidor al cliente o el cliente al servidor???</span> 

Por ahora sólo hemos usado pollin jeje



# <mark style="background: #78a3ebAA; color:bbbbbb; padding: 2px 20px 2px 20px ">Teoría</mark>

## ¿Qué es un socket?
https://www.geeksforgeeks.org/c/socket-programming-cc/

Es el punto final de una comunicación bidireccional, permite que procesos o nodos conectados a una misma red se puedan comunicar entre ellos.
- IP + puerto
Pueden ser
- TCP Socket - Stream Socket
- UDP Socket - Datagrama socket. Más rápido pero no fiable.

Siguen una arquitectura cliente-servidor.
![[socket-cliente-servidor.png | 300]]





# <mark style="background: #78a3ebAA; color:bbbbbb; padding: 2px 20px 2px 20px ">Consejos caídos del cielo</mark>

- No usar `at` al usar el contenedor map porque no es estándar c++98 aunque compile con el flag correspondiente.