
# install.packages('tuneR', dep=TRUE)
# install.packages('seewave', dep=TRUE)
# install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
#library(soundgen)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("/Users/pedro/Desktop/s-varios-sonidos/")

# la siguiente línea, sólo para macOS
setWavPlayer('/usr/bin/afplay')

# cargar archivos de sonido (wav/mp3):
perro <- readWave('perro.wav')
perro

gato  <- readMP3('gato.mp3')
gato

# mostrar los campos del archivo de sonido
str(perro)
str(gato)

# calcular la duración exacta del sonido (con tres decimales)
round(length(gato@left) / gato@samp.rate, 3)


f <- gato@samp.rate    #44100

# escuchar un sonido:
listen(gato,f=f)

# mostrar la onda del sonido:
plot( extractWave(gato, from = 1, to = 393984) )


# escuchar una porción del sonido original:
listen(gato, f=f, from=6.5, to=8.9)

