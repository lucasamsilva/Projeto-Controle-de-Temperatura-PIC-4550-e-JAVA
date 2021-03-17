#Projeto de Controle de Temperatura utilizando PIC 4550 e Java para Comunicação Serial.

PARA CORRETO FUNCIONAMENTO DA COMUNICAÇÃO SERIAL É NECESSÁRIO SEGUIR OS SEGUINTES PASSOS:

1- ACESSE O SITE http://jlog.org/rxtx.html E FAÇA DOWNLOAD DOS ARQUIVOS rxtxSerial.dll, librxtxSerial.so e RXTXcomm.jar.
Obs.: Lembrando de que devemos fazer download dos arquivos de acordo a arquitetura do sistema operacional
32-bits (x86) ou 64-bits (x64).

2- Windows
      Copie o arquivo rxtxSerial.dll para:

C:\Program Files\Java\jdkx.x.x\bin, onde x.x.x é a versão do JDK, por exemplo C:\Program Files\Java\jdk1.6.40\bin;
C:\Program Files\Java\jrex\bin,  onde x é a versão do JRE, por exemplo C:\Program Files\Java\jre7\bin;
C:\Windows\System32;
C:\Windows\SysWOW64 (caso sistema operacional 64-bits (x64)).
     Copie o arquivo RXTXcomm.jar para:

C:\Program Files\Java\jre\jrex\lib\ext, onde x é a versão do JRE, por exemplo C:\Program Files\Java\jre7\lib\ext.
 
Linux
      Copie o arquivo librxtxSerial.so para:   

/usr/lib/, exemplo: cp /home/Usuario/librxtxSerial.so /usr/lib/.
      Copie o arquivo RXTXcomm.jar para:

/usr/share/java/, exemplo.: cp /home/Usuario/RXTXcomm.jar /usr/share/java/.
