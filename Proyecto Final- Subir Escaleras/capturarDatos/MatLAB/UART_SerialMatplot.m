%Función que toma datos por un puerto serial y los grafica por medio de la
%funcion plot
%
%Autor: Leoncio Rios     
 
function ejeXYZ = ADC_Serial(muestras) %la funcion recibe el # de muestras que debe tomar

close all;
clc;
ejeY=0; %Declara variable en la cual se van a guardar los valores
ejeZ=0; %Declara variable en la cual se van a guardar los valores
%Borra datos que se encuentren previos y vuelve a declarar el puerto y la
%velocidad de transmisión
delete(instrfind({'port'},{'COM4'})); 
puerto=serial('COM4');
puerto.BaudRate=9600;

fopen(puerto);%abre el puerto a utilizar
contador=1;

%configura la ventana donde se va a mostrar la grafica
figure('Name','Grafica de la aceleracion por eje')
title('GRAFICA ACCEL UART-SERIAL');
xlabel('Numero de Muestras');
ylabel('Accel');
grid off;
hold on;

%Ciclo para ir realizando la grafica paso a paso
while contador<=muestras
    ylim([0 5000]); %Limites del eje y
    xlim([0 contador]); %Limites del eje x
    valorUART=fscanf(puerto,'%d,%d')'; %Toma el valor recibido por el puerto y lo guarda en la variable
    ejeY(contador)=valorUART(1); %Datos de Y 
    ejeZ(contador)=valorUART(2); %Datos de Z
    plot(ejeY); %Grafica y
    plot(ejeZ); %Grafica Z
    drawnow
    contador=contador+1;
end
%cierra y borra el puerto utilizado, borra todas las variables utilizadas
fclose(puerto);
delete(puerto);
end