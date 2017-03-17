#Baja Sensor Network

**Rede de sensores para prótotipo do tipo baja desenvolvido na equipe Bombaja - UFSM.** 

#A proposta

Baja SAE é um projeto desenvolvido pela Sociedade de Engenharia Automotiva (SAE) e tem como objetivo principal que os alunos de engenharia possam aplicar na vida real os conhecimentos adquiridos nas universidades e faculdades. Os alunos de engenharia devem projetar e construir um protótipo mini baja que atenda aos requisitos do concurso e ao estatuto de regras e diretrizes de projeto, dados pela própria SAE.

A competição tem diferentes fases. A primeira delas é teórica, quando os alunos têm que escrever um relatório de projeto e apresentar seus projetos do veículo para juízes (engenheiros graduados e atuantes no mercado automotivo). A segunda etapa é prática, onde o carro é avaliado em diferentes exames, cada um tendo como objetivo estressar uma ou mais peças e partes do carro, a fim de verificar se o projteo fora executado de forma condizente com o que fora apresentado teoricamente.

O último teste de competição é uma prova de durabilidade, basicamente uma corrida de resistência, onde o carro que executa mais voltas em um circuito estipulado, durante 3 horas seguidas, vence a corrida.
O circuito de competição tem diversos obstáculos, como troncos de árvores e pedras enormes, e seu objetivo é justamente impedir a passagem do veículo, e consequentemente, quebrar o carro.
Baja SAE é um projeto de resistência e os veículos dos estudantes precisam estar preparados para vencer qualquer obstáculo.

Bombaja UFSM é a equipe que leva o nome da Universidade Federal de Santa Maria.
O objetivo deste projeto é desenvolver uma rede de sensores, utilizando eletrônica embarcada, para monitorar o protótipo em tempo real.

A implementação de sistemas embarcaods neste tipo de veículo é uma das tarefas mais difíceis e desafiadoras de engenharia, pois o ambiente é completamente inóspito, e o sistema precisa suportar não só impactos mecânicos, mas também poeira, água, lama e ruídos do meio externo.

#Desenvolvimento

O microcontrolador usado no projeto é um XMEGA2560.

O Mega 2560 é um microcontrolador baseado no ATmega2560. Ele possui 54 pinos de entrada/saída digital (dos quais 15 podem ser usados como saídas PWM), 16 entradas analógicas, 4 UARTs (portas seriais de hardware), um oscilador de cristal de 16 MHz, uma conexão USB, um plug de energia, um header ICSP e um botão de reset.

Foi usado Arduino IDE para o desenvolvimento do software.
Foi escolhida a  plataforma Arduino para desenvolvimento porque a mesma detém uma grande comunidade, é um kit eletrônico embarcado de baixo custo e detém código aberto.

O projeto detém os seguintes sensores:

- Sensor de nível de combustível
- Sensor de temperatura
- Sensor de velocidade
- Sensor de Rotações por Minuto (RPM)

Além disso, possui um Relógio de Tempo Real (RTC), um cartão Standard Disk (SD) para gravar dados monitorados e um Display Gráfico de Cristal Líquido (GLCD), fixo no volante para tornar a informação em tempo real visível para o piloto do carro.

O RTC fornece o TimeStamp e suas informações na tela GLCD.
O cartão SD recebe e armazena informações de tempo real do veículo a cada 2 segundos.
O sensor de combustível é um sensor capacitivo e monitora o nível de combustível no protótipo do tanque do automóvel.
Os sensores de velocidade e RPM são sensores indutivos que detectam pulsos de passagem e os enviam para o microcontrolador, que efetua os devidos cálculos e conversões de unidade.

O piloto tem acesso a duas telas diferentes no display GLCD, trocadas usando um botão de "Troca de Tela", fixado ao volante.
Na primeira tela é mostrada a temperatura da caixa de redução, velocidade e RPM do motor.
Na segunda tela, é exibido o Timestamp e o nível de combustível do veículo.

Uma nova ideia é usar dois módulos de Rádio Frequência (RF) para enviar os dados monitorados para outro microcontrolador situado no local de parada dos boxes da equipe.
O módulo RF precisa enviar informações em intervalos de tempos iguais, utilizando mesmo tempo quando são armazenadas informações no cartão SD.
Seu principal objetivo é conceder a toda a equipe, em tempo real, medidas físicas do veículo, facilitando o processo de detecção de falhas e detecção/correção de problemas.

##RPM + Velocidade

Para melhorar a confiabilidade dos dados adquiridos pelos sensores indutivos (RPM + velocidade) são utilizadas interrupções do sistema para aquisição de dados do sensor.
Além disso, é calculada uma média a cada 10 aquisições, aumentar a precisão das medidas.

##Combustível

O sensor capacitivo é posicionado na metade inferior do tanque de combustível, assegurando a detecção de nível de combustível baixo. Para melhorar a medida do sensor, depois de detectar a falta de combustível, é habilitado um temporizador que é resetado caso seja detectado outro sinal de presença de combustível. Dessa forma, somente se o sensor detectar falta de combustível durante 20 segundos consecutivos o GLCD exibirá o aviso "Tanque Vazio". Este sistema de detecção utilizando temporização evita a detecção de falsos alertas.

##Temperatura

A temperatura é medida usando um Termopar Tipo K, que é fixado na caixa de câmbio. Para ler o seu sinal com perfeição é utilizado um circuito integrado AD595, responsável pela Compensação de Junção Fria e melhoria de precisão. Após este condicionamento de sinal, a temperatura é enviada através de portas analógicas para o microcontrolador.

#Modificações Futuras

Para melhorar o sistema embarcado do carro está sendo desenvolvido o mesmo software utilizando uma arquitetura diferente e com hardware superior, permitindo a utilização de uma melhor IDE. Para isso, será utilizado o microcontrolador MSP430, da Texas Instruments, em conjunto com o Code Composer Studio ou então a placa FRDM K-22F, com Kinetis Design Studio e um Cortex ARM, da Freescale.

Além disso, os termopares, sensores indutivos e capacitivos serão substituídos por sensores automotivos.
Para melhorar a visibilidade do piloto durante a condução será desenvolvido um painel automotivo analógico para mostrar medições de RPM + Velocidade.

O protótipo do sistema eletrônico conta também com um par de faróis LED e uma buzina.
Todo o sistema é protegido por um fusível de 1A e alimentado por uma bateria de 1000mAh Zippy, usada principalmente em projetos de aeromodelismo.

#Imagens do Protótipo

Este protótipo é chamado BJ-14 e foi desenvolvido durante o ano de 2016 pela Bombaja UFSM, Baja Team da Universidade Federal de Santa Maria. As fotos a seguir foram tiradas durante a competição Sul brasileira de baja (Baja-Sul), realizada de 18 a 20 de novembro de 2016, em Passo Fundo - RS.

#Direitos

Baja SAE é uma competição de engenharia e por 2 anos este foi o projeto do sistema embarcado da Bombaja UFSM.
Além disso, este projeto obteve a 3º colocação durante a "Competição Nacional Baja SAE 2015" e a "Competição Baja Sul 2016" na categoria "Eletrônica Embarcada: Projeto".

No entanto, agora é de código aberto e está disponível para outras equipes, entusiastas de carros, hobbistas e demais colegas engenheiros que se interessarem em ver o projeto e obterem algumas ideias para desenvolver seus próprios projetos DIY.
Hoje, o protótipo está sendo desenvolvido utilizando sensores automotivos e arquitetura de hardware superior.

O projeto pode ser reproduzido, sem problemas.
No entanto, eu só peço que caso isso aconteça, sejam mantidos créditos originais/referências ao autor.

Enjoy!

**Hollweg**
