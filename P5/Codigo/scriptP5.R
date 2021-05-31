
library(tuneR)
library(seewave)
library(audio)

setwd("/home/antoniojrg/Escritorio/PDIH/Practica5")

perro <- readWave('sonidos/perro.wav')
perro
gato <- readMP3("sonidos/gato.mp3")
gato

#Dibujamos las ondas de ambos sonidos

plot(perro)
plot(gato)

#Informacion de las cabeceras

str(perro)
str(gato)

#unimos los sonidos

union <- pastew(perro, gato, output="Wave")
union

plot(union)

#Pasarle un filtro de frecuencia para eliminar las frecuencias entre 10000 HZ y 20000 Hz

unionfiltro <- bwfilter(union, f=44100, channel=1, n=1, from=10000, to=20000, bandpass=TRUE, listen=FALSE, output = "Wave")

#Almacenamos la señal obtenida en un fichero .wav

writeWave(unionfiltro, file.path("mezcla.wav"))

#Cargar un nuevo archivo de sonido, aplicarle eco y a continuacion darle la vuelta al sonido.
#Almacenar la señal obtenida como un fichero WAV denominado "alreves.wav"

hola <- readWave('sonidos/hola.wav')
str(hola)
holaECO <- echo(hola,f=22050, amp=c(0.8,0.4,0.2), delay=c(1,2,3), output="Wave")
holaECO@left <- 10000 * holaECO@left
alreves <- revw(holaECO, output="Wave")
writeWave(alreves, file.path("alreves.wav"))