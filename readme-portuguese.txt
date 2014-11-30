Documentação do TP 2 de Computação Gráfica
Boids
2014/02
Aluno: Renato Utsch Gonçalves

== Compilando
=============
Para compilar o TP, deve-se utilizar o CMake.
Os passos estão a seguir:
1. Extrair o zip do tp para uma nova pasta.
2. Criar uma pasta chamada "build".
3. Navegar até a pasta "build" com o terminal.
4. Executar o comando: "cmake .."
5. Executar o comando: "make"

Um executável de nome boids será gerado e poderá ser
executado por "./boids".

As dependências do programa são no CMake, em um compilador
de C++, nas dependências do glfw estarem instaladas (no
ubuntu, têm o nome de xorg-dev and libglu1-mesa-dev) e
no OpenGL.

A compilação do jogo foi testada em ambiente
Linux (ArchLinux e Ubuntu), OS X (OS X Yosemite) e
Windows (Windows 7 e 8.1).

Para compilar no linux, é necessário instalar as
bibliotecas que o GLFW depende para compilar.

== Decisões de Implementação
============================
O trabalho implementou todas as exigências básicas (80% da nota):
1) Mundo razoavelmente grande definido, com chão. Uma torre central
    em forma de cone.
2) Há 4 modos de visualização, os 3 especificados pelo trabalho mais
    um modo de movimentação livre que é útil para debugging. A
    visualização pode ser escolhida pelas teclas 1, 2, 3 e 4.
3) O mundo é iluminado, inclusive com um belo sol no céu azul.
4) Os boids foram desenhados como poliedros tridimensionais.
5) O número de boids pode variar com as teclas + e -.
6) Os boids tem movimentos animados correspondentes ao batido das
    asas. A direção e a posição atual das asas são randômicos e
    diferentes para cada boid. A velocidade da batida das asas é
    a mesma, pois para os boids voarem juntos, eles precisam de
    estar na mesma velocidade e, portanto, precisam bater as asas
    na mesma velocidade.

As seguintes funcionalidades extras foram implementadas:
2) Sombras (5%): As sombras dos boids são projetadas no chão.
3) Fog (5%): O botão F ativa e desativa o fog.
4) Modo de pausa (5%): é possível pausar e despausar o jogo apertando a
    tecla P. Entrar e sair do modo de depuração também é possível
    apertando o botão direito do mouse. Uma vez no modo de depuração,
    é possível mover utilizando a Free Camera (tecla 1) ou visualizar
    a cena com as outras câmeras. Também é possível adicionar ou
    remover boids e avançar o jogo passo-a-passo com impressão para
    depuração com o botão esquerdo do mouse.
5) Reshape (5%): é possível redimensionar a janela de visualização.

O jogo foi feito em C++.
A implementação utilizou a biblioteca GLFW para cuidar das
janelas e do input do usuário.

O código foi dividido internamente em sistemas. Cada sistema
se responsabiliza por atualizar apenas uma parte a engine.
Por exemplo, o sistema de animação (system/AnimationSystem.hpp)
se responsabiliza por atualizar a posição das asas dos boids.
O sistema de movimento (system/MovementSystem.hpp) se responsabiliza 
por movimentar os boids (incluindo a orientação do boid objetivo).
O sistema de câmera (system/CameraSystem.hpp) se responsabiliza por
posicionar as câmeras segundo a entrada do usuário. Por fim, o
sistema de render (system/RenderSystem.hpp) se responsabiliza apenas
por desenhar na tela os objetos e pelos efeitos gráficos (iluminação,
sombra, fog, chão, etc).
Com esse design foi possível separar cada tipo de simulação de jogo:
todo o código relacionado à câmera ficou em system/CameraSystem.cpp,
todo o código de animação ficou em system/AnimationSystem.cpp, e por
aí vai.

Essa implementação utilizou somente display lists para desenhar. Não
são feitas chamadas de desenho do OpenGL a cada frame, apenas chamadas
a listas previamente geradas. Isso permitiu um grande ganho de
performance, pois o OpenGL salva na memória da GPU todos os desenhos,
não sendo necessário calcular como desenhar novamente.

Um sistema de GameStateManager (GSM) foi utilizado para cuidar dos
estados diferentes do jogo: RunState (jogo rodando normalmente),
PauseState (jogo pausado) e DebugState (jogo em debug).
Esse método permite que organizemos as chamadas de atualização dos
sistamas em classes derivadas da classe State. É possível, portanto,
facilmente implementar estados diferentes de jogo e com pouca
complicação de código. Os estados existentes nesse jogo estão
implementados na pasta state, junto com o StateManager que cuida de
mudar de um estado para o outro.

Colisão não foi implementada (exceto evitar colidir com o chão ou ir
alto demais) por falta de tempo. Porém, como colisão é parte extra do
trabalho, não foi considerado que acarretaria em muitas perdas, visto
que tudo o que é obrigatório (e features extras) foram implementadas.

